/*
Copyright (c) 2011, Siemens Corporate Research a Division of Siemens Corporation 
All rights reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#include <xip/inventor/remote/XipRenderActionParams.h>

#if defined(WINDOWS) || defined(_WIN32)
	#include <winsock2.h>
#else
	#include <string.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <sys/uio.h>
	#include <unistd.h>
	#include <errno.h>
	#include <netdb.h>
#endif

#include "SoXipClientBase.h"

#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/sensors/SoFieldSensor.h>


SO_ENGINE_ABSTRACT_SOURCE(SoXipClientBase)


// --------------------------------------------------------------------------
//! Initializes this class. Called on dll initialization.
// --------------------------------------------------------------------------
void SoXipClientBase::initClass()
{
  SO_ENGINE_INIT_ABSTRACT_CLASS(SoXipClientBase, SoEngine, "Engine");
}

// --------------------------------------------------------------------------
//! Constructor, creates fields
// --------------------------------------------------------------------------
SoXipClientBase::SoXipClientBase()
{
	// Execute inventor internal stuff for node construction.
	SO_ENGINE_CONSTRUCTOR(SoXipClientBase);

	mServerPort = 0;
	mNeedVolumeUpdate = FALSE;
	mRampCenter = 0.0;
	mRampWidth = 0.0;

	//different socket states
	SO_ENGINE_DEFINE_ENUM_VALUE(State, DISCONNECTED);
	SO_ENGINE_DEFINE_ENUM_VALUE(State, CONNECTED);
	SO_ENGINE_DEFINE_ENUM_VALUE(State, CONNECTION_ERROR);
	SO_ENGINE_DEFINE_ENUM_VALUE(State, AUTHENTIFICATION_ERROR);

	////! different data plugin
	//SO_ENGINE_DEFINE_ENUM_VALUE(DataPlugin, RADDATACARC);
	//SO_ENGINE_DEFINE_ENUM_VALUE(DataPlugin, RADDATANET);

	// different data loading states
	SO_ENGINE_DEFINE_ENUM_VALUE(DState, DATA_EMPTY);
	SO_ENGINE_DEFINE_ENUM_VALUE(DState, DATA_OK);
	SO_ENGINE_DEFINE_ENUM_VALUE(DState, DATA_ERROR);

	//possible limitation of volume size    
	SO_ENGINE_DEFINE_ENUM_VALUE(VSizelimit, LIMIT);
	SO_ENGINE_DEFINE_ENUM_VALUE(VSizelimit, TARGET);
	SO_ENGINE_DEFINE_ENUM_VALUE(VSizelimit, ORIGINAL);

	// Copy static information for "State" enumerated type field
	// into this instance. 
	SO_ENGINE_SET_SF_ENUM_TYPE(connectionState, State);
	//SO_ENGINE_SET_SF_ENUM_TYPE(serverDataPlugin, DataPlugin);
	SO_ENGINE_SET_SF_ENUM_TYPE(dataState, DState);
	SO_ENGINE_SET_SF_ENUM_TYPE(volumeTargetSize, VSizelimit);


	// define the engine inputs
	SO_ENGINE_ADD_INPUT(serverAddress, (""));
	SO_ENGINE_ADD_INPUT(serverPort, (12121));
    SO_ENGINE_ADD_INPUT(dataLocation, (""));
	SO_ENGINE_ADD_INPUT(connectionState, (DISCONNECTED));


	SO_ENGINE_ADD_INPUT(volumeTargetSize, (LIMIT));    
	SO_ENGINE_ADD_INPUT(volumeWidth, (256));
	SO_ENGINE_ADD_INPUT(volumeHeight, (256));
	SO_ENGINE_ADD_INPUT(volumeDepth, (256));

	SO_ENGINE_ADD_INPUT(volumeUpdate, ());
	SO_ENGINE_ADD_INPUT(dataState, (DATA_EMPTY));

    SoFieldSensor *fieldSensor=NULL;
    SoField *fields[] = {&serverAddress, &serverPort, &dataLocation};
    for (int i=0; i<(sizeof(fields)/sizeof(SoField*)); i++)
    {
        fieldSensor = new SoFieldSensor(&fieldSensorCBFunc, this);
        fieldSensor->attach(fields[i]);
        //if (i <= 1) fieldSensor->setPriority(0);
        mInputSensors.push_back(fieldSensor);
    }

	this->initialize();
}

// --------------------------------------------------------------------------
//! Protected destructor to cleans up internally created nodes and node sensor.
// --------------------------------------------------------------------------
SoXipClientBase::~SoXipClientBase()
{
	this->finalize();

	std::vector<SoFieldSensor *>::iterator i;
	for (i = mInputSensors.begin(); i != mInputSensors.end(); i++)
	{
		delete (*i);
	}

}


//-----------------------------------------------------------------------------
// Called to clean the present c++ pointer
//-----------------------------------------------------------------------------
void SoXipClientBase::deletePointer()
{
	if(mSocketStream)
	{
		delete mSocketStream;
		mSocketStream = 0;
	}

	if(mStreamLength)
	{
		delete mStreamLength;
		mStreamLength = 0;
	}
}


//-----------------------------------------------------------------------------
// Called to initialize WinSock
// Return 0 if OK and -1 if WSAStartup problems
//-----------------------------------------------------------------------------
int SoXipClientBase::initialize()
{
	#if defined(WINDOWS) || defined(_WIN32)
		WSADATA wsaData;
		if (::WSAStartup(0x0202, &wsaData) != 0)
		{
			fprintf(stderr,"WSAStartup error %d\n",GetLastError());
			return -1;
		}
	#endif

	mClientSocket = 0;
	mSocketStream = 0;
	mStreamLength = 0;
	mStreamLength2 = 0;

	mServerAddress = SbString();
	mServerPort = 0;
	//mDataID = SbString();
    mDataLocation = SbString();

	return 0;
}


//-----------------------------------------------------------------------------
// Called to liberate socket ans WSA before closing
//-----------------------------------------------------------------------------
void SoXipClientBase::finalize()
{
	disconnectSocket();
	#if defined(WINDOWS) || defined(_WIN32)
		WSACleanup();
	#endif
}


//-----------------------------------------------------------------------------
// method to initialize and connect the socket
// return 0 if socket is connected or -1 if problems appear during connexion
//-----------------------------------------------------------------------------
int SoXipClientBase::initializeSocket()
{
	mClientSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (mClientSocket == INVALID_SOCKET)
	{
		#if defined(WINDOWS) || defined(_WIN32)
			fprintf(stderr,"socket error %d\n", GetLastError());
		#else
			perror("socket error: ");
		#endif
		return -1;
	}

	struct hostent *hostPtr;
	hostPtr = ::gethostbyname(serverAddress.getValue().getString());

	if (hostPtr == NULL)
	{
		#if defined(WINDOWS) || defined(_WIN32)
			fprintf(stderr,"address error %d\n", GetLastError());
		#else
			perror("address error: ");
		#endif
		return -1;
	}

	struct sockaddr_in serverInfo;
	memset((void*) &serverInfo, 0, sizeof(serverInfo));

	serverInfo.sin_family = AF_INET;
	serverInfo.sin_port = htons((unsigned short) serverPort.getValue());
	memcpy(&serverInfo.sin_addr, hostPtr->h_addr, hostPtr->h_length);


	/************************************/
	/*BOOL bOptVal = TRUE;
	if (setsockopt(mClientSocket, IPPROTO_TCP, TCP_NODELAY, (char*) &bOptVal, sizeof(BOOL)) == SOCKET_ERROR)
	{
		SoError::post("Warning from ivtRemoteUtil: setsockopt() failed!\n");
	}*/
	/***********************************/


	if (::connect(mClientSocket, (const struct sockaddr *) &serverInfo, sizeof(serverInfo)) != 0)
	{
		#if defined(WINDOWS) || defined(_WIN32)
			fprintf(stderr,"socket connexion error %d\n", GetLastError());
		#else
			perror("socket connexion error: ");
		#endif
		return -1;		
	}


	//create a radStream using the socket.
	deletePointer();	//to be sure the pointers are cleaned 
	mSocketStream = new XipStreamSockets(mClientSocket);		// socket connection
	mStreamLength = new XipStreamLengthPackage(mSocketStream);	// add length info
	mStreamLength2 = new XipStreamLengthPackage(mSocketStream);	// add length info

	mReqSender.initSender(mStreamLength, -1);
	mReqReceiver.initReceiver(mStreamLength);

	return 0;
}


//-----------------------------------------------------------------------------
// method to close the socket
//-----------------------------------------------------------------------------
void SoXipClientBase::disconnectSocket()
{
	if(mClientSocket)
	{
		terminate();
		#if defined(WINDOWS) || defined(_WIN32)
			closesocket(mClientSocket);
		#else
			close(mClientSocket);
		#endif
		mClientSocket = 0;
		deletePointer();
	}
}


//-----------------------------------------------------------------------------
// Called to identify the client on the server
// return 0 if logon is accepted and -1 else
//-----------------------------------------------------------------------------
int SoXipClientBase::authenticate()
{
	if(!mStreamLength)
		return -1;

    // authentication is not necessary for this version
    return 0;

	//try
	//{
	//	//mReqSender.initSender(mStreamLength, LOAD_PLUGIN_ACTION);
	//	//int pluginLoaded;
	//	//bool res;


	//	////************ load the good data plugin on the server
	//	//if(serverDataPlugin.getValue() == RADDATANET)
	//	//{
	//	//	char pluginName[] = "RadDataNet"; 
	//	//	int bufLen = sizeof(pluginName);
	//	//	mReqSender.rHtonl(&bufLen);
	//	//	mReqSender.addChildElement(LOAD_PLUGIN_ACTION, LOADPLUGINREQUEST_BUFFERSIZE, sizeof(int), &bufLen);
	//	//	int pluginType = DATA_PLUGIN;
	//	//	mReqSender.rHtonl(&pluginType);
	//	//	mReqSender.addChildElement(LOAD_PLUGIN_ACTION, LOADPLUGINREQUEST_PLUGINTYPE, sizeof(int), &pluginType);
	//	//	mReqSender.addChildElement(LOAD_PLUGIN_ACTION, LOADPLUGINREQUEST_PLUGINNAME, sizeof(pluginName), pluginName);
	//	//	mReqSender.send();
	//	//}
	//	//else
	//	//{
	//	//	char pluginName[] = "raddatacarc";
	//	//	int bufLen = sizeof(pluginName);
	//	//	mReqSender.rHtonl(&bufLen);
	//	//	mReqSender.addChildElement(LOAD_PLUGIN_ACTION, LOADPLUGINREQUEST_BUFFERSIZE, sizeof(int), &bufLen);
	//	//	int pluginType = DATA_PLUGIN;
	//	//	mReqSender.rHtonl(&pluginType);
	//	//	mReqSender.addChildElement(LOAD_PLUGIN_ACTION, LOADPLUGINREQUEST_PLUGINTYPE, sizeof(int), &pluginType);
	//	//	mReqSender.addChildElement(LOAD_PLUGIN_ACTION, LOADPLUGINREQUEST_PLUGINNAME, sizeof(pluginName), pluginName);
	//	//	mReqSender.send();	
	//	//}

	//	//
	//	//// expect the logon response from the server
	//	//mReqReceiver.receive();
	//	//if(mReqReceiver.getFirstElementId() != LOAD_PLUGIN_ACTION)
	//	//	return -1;

	//	//res = mReqReceiver.getUniqueIntElement(LOADPLUGINRESPONSE_LOADED, pluginLoaded);
	//	//mReqReceiver.rNtohl(&pluginLoaded);
	//	//if((!res) || (pluginLoaded != 1))
	//	//	return -1;


	//	////************ load the sort plugin on the server
	//	//char sortPlugin[] = "radsortgeneric";
	//	//int bufLen = sizeof(sortPlugin);
	//	//mReqSender.initSender(mStreamLength, LOAD_PLUGIN_ACTION);
	//	//mReqSender.rHtonl(&bufLen);
	//	//mReqSender.addChildElement(LOAD_PLUGIN_ACTION, LOADPLUGINREQUEST_BUFFERSIZE, sizeof(int), &bufLen);
	//	//int pluginType = SORT_PLUGIN;
	//	//mReqSender.rHtonl(&pluginType);
	//	//mReqSender.addChildElement(LOAD_PLUGIN_ACTION, LOADPLUGINREQUEST_PLUGINTYPE, sizeof(int), &pluginType);
	//	//mReqSender.addChildElement(LOAD_PLUGIN_ACTION, LOADPLUGINREQUEST_PLUGINNAME, sizeof(sortPlugin), sortPlugin);
	//	//mReqSender.send();	


	//	//// expect the logon response from the server
	//	//mReqReceiver.receive();
	//	//if(mReqReceiver.getFirstElementId() != LOAD_PLUGIN_ACTION)
	//	//	return -1;

	//	//res = mReqReceiver.getUniqueIntElement(LOADPLUGINRESPONSE_LOADED, pluginLoaded);
	//	//mReqReceiver.rNtohl(&pluginLoaded);
	//	//if((!res) || (pluginLoaded != 1))
	//	//	return -1;



	//	// in case of use of raddatanet plugin, send more authentification information to the server
	//	if(serverDataPlugin.getValue() == RADDATANET)
	//	{
	//		char accessToken[256] = {'\0'};
	//		sprintf(accessToken, "GSM:%s:%s:%i", datanetTitle.getValue().getString(), 
	//											 datanetAddress.getValue().getString(), 
	//											 datanetPort.getValue());

	//		mReqSender.initSender(mStreamLength, LOGON_ACTION);
	//		int buffL = 256;
	//		mReqSender.rHtonl(&buffL);
	//		mReqSender.addChildElement(LOGON_ACTION, LOGONREQUEST_STRBUFFERSIZE, sizeof(int), &buffL);
	//		mReqSender.addChildElement(LOGON_ACTION, LOGONREQUEST_CLIENTSTR, 256, accessToken);
	//		mReqSender.send();	


	//		// expect the logon response from the server
	//		mReqReceiver.receive();
	//		if(mReqReceiver.getFirstElementId() != LOGON_ACTION)
	//			return -1;

	//		int logonAccepted;
	//		res = mReqReceiver.getUniqueIntElement(LOGONRESPONSE_ACCEPTED, logonAccepted);
	//		mReqReceiver.rNtohl(&logonAccepted);
	//		if((!res) || (logonAccepted != 1))
	//			return -1;
	//	}

	//	// logon is accepted.
	//	return 0;

	//}
	////catch (RadException &e)
	////{
	////	SoError::post("Caught RadException while client authentification.\n");
	////	SoError::post("RadException(source: %s, line: %d, type: %d, info: %S)\n",
	////		e.file, e.line, e.type, e.message ? e.message : L"not available");
	////}
	//catch (...)
	//{
	//	SoError::post("Caught Unknown Exception while client authentification!\n");
	//}

	//// logon is refused.
	//return -1;
}


//-----------------------------------------------------------------------------
// Called to flush the stream
//-----------------------------------------------------------------------------
void SoXipClientBase::flush()
{
	if(!mClientSocket)
		return;

	int len = 0;

	// receive any un-received data meant for this socket and clear the network buffer.
	::recv(mClientSocket, (char*) &len, sizeof(int), 0);
	if(len)
	{
		char* tmpBuffer = new char[len+1];
		::recv(mClientSocket, (char*) tmpBuffer, len, 0);
		delete [] tmpBuffer;
		tmpBuffer = 0;
	}
}


//-----------------------------------------------------------------------------
// Called to clean the socket before closing it
//-----------------------------------------------------------------------------
void SoXipClientBase::terminate()
{
	if(!mClientSocket)
		return;

	mReqSender.initSender(mStreamLength, CLOSE_ACTION);
	mReqSender.send();

	#if defined(WINDOWS) || defined(_WIN32)
		//shut down the socket.say that no more data will be sent.
		if(shutdown(mClientSocket, SD_SEND) == SOCKET_ERROR)
		{
			DWORD error = WSAGetLastError();
		}
	#endif
}



//-----------------------------------------------------------------------------
// Called to load wanted data from the server
// return 0 when data are loaded correctly and -1 else
// virtual function to be implemented in heriting classes
//-----------------------------------------------------------------------------
int SoXipClientBase::loadData()
{
	// implemented in child classes
	return -1;
}



//-----------------------------------------------------------------------------
//! Called when field ConnectTrigger changed
//-----------------------------------------------------------------------------
void SoXipClientBase::connectTriggerCall()
{	
	mServerAddress = SbString();
	mServerPort = 0;	
	
	//return if socket is already connected
	if(connectionState.getValue() == CONNECTED)
		disconnectSocket();

	//change state if there is connexion problems
	if(initializeSocket() != 0)
	{
		connectionState.setValue(CONNECTION_ERROR);
		return;
	}

	//change state if there is authentification problems
	if(authenticate() != 0)
	{
		connectionState.setValue(AUTHENTIFICATION_ERROR);
	    disconnectSocket();
		return;
	}

	//change state if everything is OK
	connectionState.setValue(CONNECTED);

	mServerPort = serverPort.getValue();
	mServerAddress = serverAddress.getValue();
}



//-----------------------------------------------------------------------------
//! Called when field DeconnectTrigger changed
//-----------------------------------------------------------------------------
void SoXipClientBase::disconnectTriggerCall()
{
	disconnectSocket();

  	//change state to disconnected
	connectionState.setValue(DISCONNECTED);

	mServerPort = 0;
	mServerAddress = SbString();
}



//-----------------------------------------------------------------------------
//! Called when field LoadDataTrigger changed
//-----------------------------------------------------------------------------
void SoXipClientBase::loadDataTriggerCall()
{
	
	try
	{
		//change state of loading data after loaded it
		int res = loadData();

		//mDataID = SbString();
        mDataLocation = SbString();

		if(res == -1)
		{
			dataState.setValue(DATA_ERROR);
			flush();
		}
		else
		{
			//mDataID = dataID.getValue();
            mDataLocation = dataLocation.getValue();
            dataState.setValue(DATA_OK);	
		}

		return;
	}
	catch (...)
	{
		SoError::post("Caught Unknown Exception while loading volume!\n");
	}

	dataState.setValue(DATA_ERROR);
	flush();
}


//-----------------------------------------------------------------------------
//! Called on any input change on the node, field might by also NULL
//-----------------------------------------------------------------------------
void SoXipClientBase::inputChanged(SoField *whichField)
{
	// button pressed to manually reload data
	if(whichField == &volumeUpdate)
    {
		mNeedVolumeUpdate = TRUE;
    }
    else if ( whichField == &serverAddress )
    {
        if ( (serverAddress.getValue().getLength()>0) && (serverPort.getValue()!=0) )
        {
            if ((serverPort.getValue() != mServerPort) ||
                (serverAddress.getValue() != mServerAddress) )
            {
                connectTriggerCall();
            }
        }
        else if ( serverAddress.getValue().getLength()==0)
        {
	        disconnectTriggerCall();        
        }
    }
    else if ( whichField == &serverPort )
    {
        if ( (serverPort.getValue()>0) && (serverAddress.getValue().getLength()>0) )
        {
            if ((serverPort.getValue() != mServerPort) ||
                (serverAddress.getValue() != mServerAddress) )
            {
                connectTriggerCall();
            }
        }
        else if ( serverPort.getValue()==0 )
        {
            disconnectTriggerCall();
        }
    }
    else if ( whichField == &dataLocation )
    {
		
    }

	SoEngine::inputChanged(whichField);
}


//-----------------------------------------------------------------------------
//! Evaluation method
//-----------------------------------------------------------------------------
void SoXipClientBase::evaluate()
{
	// server port and address fields change 
	if ((serverAddress.getValue().getLength() > 0) && (serverPort.getValue() != 0))
	{
		if ((serverPort.getValue() != mServerPort) ||
			(serverAddress.getValue() != mServerAddress) )
		{
			// connect to the server
			connectTriggerCall();
		}
	}
	else
	{
		disconnectTriggerCall();
	}

	// data id field change
	if (connectionState.getValue() & CONNECTED)
	{
        if ((dataLocation.getValue() != mDataLocation) || mNeedVolumeUpdate)
        {
            // load new data
            loadDataTriggerCall();
            mNeedVolumeUpdate = FALSE;
        }
	}
}

void SoXipClientBase::fieldSensorCBFunc(void *usr, SoSensor *sensor)
{
    ((SoXipClientBase*)usr)->inputChanged(((SoFieldSensor*) sensor)->getAttachedField());
}
