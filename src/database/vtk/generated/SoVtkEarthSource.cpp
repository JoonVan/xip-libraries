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
 
 
# include "SoVtkEarthSource.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkEarthSource )

SoVtkEarthSource::SoVtkEarthSource()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkEarthSource);

	mObject = vtkEarthSource::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkEarthSource *aEarthSource = vtkEarthSource::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(Radius, (0));
	Radius.setValue(aEarthSource->GetRadius());

	SO_ENGINE_ADD_INPUT(OnRatio, (0));
	OnRatio.setValue(aEarthSource->GetOnRatio());

	SO_ENGINE_ADD_INPUT(Outline, (0));
	Outline.setValue(aEarthSource->GetOutline());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aEarthSource->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkEarthSource::~SoVtkEarthSource()
{
	// Deletion of the objects if they exist
	if ( mOutput )
	{
	
		mOutput->unref();
		mOutput = 0;
	}
	
	if ( mOutputPort )
	{
	
		mOutputPort->unref();
		mOutputPort = 0;
	}
	
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkEarthSource::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkEarthSource, SoEngine, "Engine" );
}

void SoVtkEarthSource::evaluate()
{
	try
	{
		// Get the input type(s)
		SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
		
		if (inputPortPtr)
			mObject->SetInputConnection(inputPortPtr->getPointer());

		// Deletion of the objects if they exist
		if ( mOutput )
		{
		
			mOutput->unref();
			mOutput = 0;
		}
		
		if ( mOutputPort )
		{
		
			mOutputPort->unref();
			mOutputPort = 0;
		}
		
		if ( addCalled )
		{
			reset();
			addCalled = 0;
		}

		mObject->GetOutput()->Register(0);
		mOutput = new SoVtkObject();
		mOutput->ref();
		mOutput->setPointer( mObject->GetOutput() );

		if ( mObject->GetNumberOfOutputPorts() > 0 )
		{
			mObject->GetOutputPort()->Register(0);
			mOutputPort = new SoVtkAlgorithmOutput();
			mOutputPort->ref();
			mOutputPort->setPointer( mObject->GetOutputPort() );
		}

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
}


void SoVtkEarthSource::inputChanged(SoField * f)
{
	// Get the Radius value
	if ( f == &Radius )
		SO_VTK_SET_FIELD_VALUE( mObject, Radius);

	// Get the OnRatio value
	if ( f == &OnRatio )
		SO_VTK_SET_FIELD_VALUE( mObject, OnRatio);

	// Get the Outline value
	if ( f == &Outline )
		SO_VTK_SET_FIELD_VALUE( mObject, Outline);

	mObject->Update();
}

void SoVtkEarthSource::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkEarthSource::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the Radius value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Radius);

	// Get the OnRatio value
	
		SO_VTK_SET_FIELD_VALUE( mObject, OnRatio);

	// Get the Outline value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Outline);

	mObject->Update();
}
