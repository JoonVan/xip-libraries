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
/*
 * \brief
 * \author Sylvain Jaume <sylvain.jaume@siemens.com>, Francois Huguet
 */
 
#include "SoVtkBMPWriter.h"
#include "SoVtkUtils.h"

#include "vtkAlgorithmOutput.h"
#include "vtkImageData.h"

SO_ENGINE_SOURCE( SoVtkBMPWriter )

SoVtkBMPWriter::SoVtkBMPWriter()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkBMPWriter);

	mObject = vtkBMPWriter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkBMPWriter *aBMPWriter = vtkBMPWriter::New();

	SO_ENGINE_ADD_INPUT(FileName, (""));

	SO_ENGINE_ADD_INPUT(FileDimensionality, (0));
	FileDimensionality.setValue(aBMPWriter->GetFileDimensionality());

	SO_ENGINE_ADD_INPUT(FilePattern, (""));

	SO_ENGINE_ADD_INPUT(FilePrefix, (""));

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aBMPWriter->Delete();

	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;

	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;

	addCalled = 0;
}

SoVtkBMPWriter::~SoVtkBMPWriter()
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

void SoVtkBMPWriter::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkBMPWriter, SoEngine, "Engine" );
}

void SoVtkBMPWriter::evaluate()
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
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue(
												 mOutputPort ) );
}


void SoVtkBMPWriter::inputChanged(SoField * f)
{
	// Get the FileName value
	if ( f == &FileName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, FileName);

	// Get the FileDimensionality value
	if ( f == &FileDimensionality )
		SO_VTK_SET_FIELD_VALUE( mObject, FileDimensionality);

	// Get the FilePattern value
	if ( f == &FilePattern )
		SO_VTK_SET_FIELD_MFSTRING( mObject, FilePattern);

	// Get the FilePrefix value
	if ( f == &FilePrefix )
		SO_VTK_SET_FIELD_MFSTRING( mObject, FilePrefix);

	mObject->Update();
}

void SoVtkBMPWriter::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkBMPWriter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the FileName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, FileName);

	// Get the FileDimensionality value
	
		SO_VTK_SET_FIELD_VALUE( mObject, FileDimensionality);

	// Get the FilePattern value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, FilePattern);

	// Get the FilePrefix value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, FilePrefix);

	mObject->Update();
}

