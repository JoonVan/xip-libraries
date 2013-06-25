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
 
 
# include "SoVtkImageRectilinearWipe.h"
# include "SoVtkUtils.h"

# include "vtkDataObject.h"
# include "vtkAlgorithmOutput.h"
# include "vtkImageData.h"


SO_ENGINE_SOURCE( SoVtkImageRectilinearWipe )

SoVtkImageRectilinearWipe::SoVtkImageRectilinearWipe()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImageRectilinearWipe);

	mObject = vtkImageRectilinearWipe::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImageRectilinearWipe *aImageRectilinearWipe = vtkImageRectilinearWipe::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(Input2, (0));

	SO_ENGINE_ADD_INPUT(Position, (0,0));

	y = (int *) aImageRectilinearWipe->GetPosition();
	Position.setValue((float) y[0],(float) y[1]);

	SO_ENGINE_ADD_INPUT(Wipe, (0));
	Wipe.setValue(aImageRectilinearWipe->GetWipe());

	SO_ENGINE_ADD_INPUT(NumberOfThreads, (0));
	NumberOfThreads.setValue(aImageRectilinearWipe->GetNumberOfThreads());

	SO_ENGINE_ADD_INPUT(Input1, (0));

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aImageRectilinearWipe->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkImageRectilinearWipe::~SoVtkImageRectilinearWipe()
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

void SoVtkImageRectilinearWipe::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImageRectilinearWipe, SoEngine, "Engine" );
}

void SoVtkImageRectilinearWipe::evaluate()
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


void SoVtkImageRectilinearWipe::inputChanged(SoField * f)
{
	// Get the Input2 value
	if ( f == &Input2 )
		SO_VTK_SET_FIELD_DATA( mObject, Input2, vtkDataObject);

	// Get the Position value
	if ( f == &Position )
		SO_VTK_SET_FIELD_VEC2F( mObject, Position);

	// Get the Wipe value
	if ( f == &Wipe )
		SO_VTK_SET_FIELD_VALUE( mObject, Wipe);

	// Get the NumberOfThreads value
	if ( f == &NumberOfThreads )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfThreads);

	// Get the Input1 value
	if ( f == &Input1 )
		SO_VTK_SET_FIELD_DATA( mObject, Input1, vtkDataObject);

	mObject->Update();
}

void SoVtkImageRectilinearWipe::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImageRectilinearWipe::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the Input2 value
	
		SO_VTK_SET_FIELD_DATA( mObject, Input2, vtkDataObject);

	// Get the Position value
	
		SO_VTK_SET_FIELD_VEC2F( mObject, Position);

	// Get the Wipe value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Wipe);

	// Get the NumberOfThreads value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfThreads);

	// Get the Input1 value
	
		SO_VTK_SET_FIELD_DATA( mObject, Input1, vtkDataObject);

	mObject->Update();
}
