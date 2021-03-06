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

# ifndef SO_VTK_TRIANGLEFILTER_H_
# define SO_VTK_TRIANGLEFILTER_H_


# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkTriangleFilter.h"

# include "Inventor/fields/SoSFInt32.h"
# include <xip/inventor/core/SoSFVariant.h>

class SoVtkTriangleFilter : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkTriangleFilter );

public:

	/// Constructor
	SoVtkTriangleFilter();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// PassLines
	SoSFInt32 PassLines;
	/// PassVerts
	SoSFInt32 PassVerts;
	/// Input data of type vtkDataObject
	SoSFVtkObject Input;
	/// InputArrayToProcess
	SoSFVariant InputArrayToProcess;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;

	
	// Outputs
	/// SoSFVtkObject of type vtkPolyData
	SoEngineOutput Output;
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;

protected:

	/// Destructor
	~SoVtkTriangleFilter();

	/// Evaluate Function
	virtual void evaluate();

	virtual void inputChanged(SoField *);
	
	/// vtkPolyData
	SoVtkObject *mOutput;
	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;

private:

	vtkTriangleFilter* mObject;
};

#endif // SO_VTK_TRIANGLEFILTER_H_

