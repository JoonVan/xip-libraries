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
 * \author Sylvain Jaume, Francois Huguet
 */

# include "SoVtkRungeKutta4.h"
# include "SoVtkUtils.h"

# include "vtkFunctionSet.h"


SO_ENGINE_SOURCE( SoVtkRungeKutta4 )

SoVtkRungeKutta4::SoVtkRungeKutta4()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkRungeKutta4);

	mObject = vtkRungeKutta4::New();

	mObject->Register(0);mObject->SetGlobalWarningDisplay(0);

	vtkRungeKutta4 *aRungeKutta4 = vtkRungeKutta4::New();

	SO_ENGINE_ADD_INPUT(FunctionSet, (0));

	aRungeKutta4->Delete();


	SO_ENGINE_ADD_OUTPUT(Output, SoSFVtkObject );
	mOutput = 0;

}

SoVtkRungeKutta4::~SoVtkRungeKutta4()
{
	// Deletion of the objects if they exist
	if ( mOutput )
	{
	
		mOutput->unref();
		mOutput = 0;
	}
	
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkRungeKutta4::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkRungeKutta4, SoEngine, "Engine" );
}

void SoVtkRungeKutta4::evaluate()
{
	try
	{
		// Deletion of the objects if they exist
		if ( mOutput )
		{
		
			mOutput->unref();
			mOutput = 0;
		}
		
		// Get the input type(s)
		mOutput = new SoVtkObject();
		mOutput->ref();
		mOutput->setPointer( mObject );

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
}


void SoVtkRungeKutta4::inputChanged(SoField * f)
{
	// Get the FunctionSet value
	if ( f == &FunctionSet )
		SO_VTK_SET_FIELD_DATA( mObject, FunctionSet, vtkFunctionSet);

	
}

