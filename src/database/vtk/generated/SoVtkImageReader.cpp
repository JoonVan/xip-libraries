/*
 *  COPYRIGHT NOTICE.  Copyright (C) 2007 Siemens Corporate Research, 
 *  Inc. ("caBIG(tm) Participant"). The eXtensible Imaging Platform
 *  (XIP) was created with NCI funding and is part of the caBIG(tm) 
 *  initiative. The software subject to this notice and license 
 *  includes both human readable source code form and machine 
 *  readable, binary, object code form (the "caBIG(tm) Software").
 *  
 *  This caBIG(tm) Software License (the "License") is between 
 *  caBIG(tm) Participant and You.  "You (or "Your") shall mean a 
 *  person or an entity, and all other entities that control, are 
 *  controlled by, or are under common control with the entity.  
 *  "Control" for purposes of this definition means (i) the direct or 
 *  indirect power to cause the direction or management of such 
 *  entity, whether by contract or otherwise, or (ii) ownership of 
 *  fifty percent (50%) or more of the outstanding shares, or (iii) 
 *  beneficial ownership of such entity.
 *  
 *  LICENSE.  Provided that You agree to the conditions described 
 *  below, caBIG(tm) Participant grants You a non-exclusive, 
 *  worldwide, perpetual, fully-paid-up, no-charge, irrevocable, 
 *  transferable and royalty-free right and license in its rights in 
 *  the caBIG(tm) Software, including any copyright or patent rights 
 *  therein that may be infringed by the making, using, selling, 
 *  offering for sale, or importing of caBIG(tm) Software, to (i) 
 *  use, install, access, operate, execute, reproduce, copy, modify, 
 *  translate, market, publicly display, publicly perform, and 
 *  prepare derivative works of the caBIG(tm) Software; (ii) make, 
 *  have made, use, practice, sell, and offer for sale, and/or 
 *  otherwise dispose of caBIG(tm) Software (or portions thereof); 
 *  (iii) distribute and have distributed to and by third parties the 
 *  caBIG(tm) Software and any modifications and derivative works 
 *  thereof; and (iv) sublicense the foregoing rights set out in (i), 
 *  (ii) and (iii) to third parties, including the right to license 
 *  such rights to further third parties.  For sake of clarity, and 
 *  not by way of limitation, caBIG(tm) Participant shall have no 
 *  right of accounting or right of payment from You or Your 
 *  sublicensees for the rights granted under this License.  This 
 *  License is granted at no charge to You.  Your downloading, 
 *  copying, modifying, displaying, distributing or use of caBIG(tm) 
 *  Software constitutes acceptance of all of the terms and 
 *  conditions of this Agreement.  If you do not agree to such terms 
 *  and conditions, you have no right to download, copy, modify, 
 *  display, distribute or use the caBIG(tm) Software.
 *  
 *  1.	Your redistributions of the source code for the caBIG(tm) 
 *      Software must retain the above copyright notice, this list 
 *      of conditions and the disclaimer and limitation of 
 *      liability of Article 6 below.  Your redistributions in 
 *      object code form must reproduce the above copyright notice, 
 *      this list of conditions and the disclaimer of Article 6 in 
 *      the documentation and/or other materials provided with the 
 *      distribution, if any.
 *  2.	Your end-user documentation included with the 
 *      redistribution, if any, must include the following 
 *      acknowledgment: "This product includes software developed 
 *      by Siemens Corporate Research Inc."  If You do not include 
 *      such end-user documentation, You shall include this 
 *      acknowledgment in the caBIG(tm) Software itself, wherever 
 *      such third-party acknowledgments normally appear.
 *  3.	You may not use the names "Siemens Corporate Research, 
 *      Inc.", "The National Cancer Institute", "NCI", "Cancer 
 *      Bioinformatics Grid" or "caBIG(tm)" to endorse or promote 
 *      products derived from this caBIG(tm) Software.  This 
 *      License does not authorize You to use any trademarks, 
 *  	service marks, trade names, logos or product names of 
 *      either caBIG(tm) Participant, NCI or caBIG(tm), except as 
 *      required to comply with the terms of this License.
 *  4.	For sake of clarity, and not by way of limitation, You may 
 *      incorporate this caBIG(tm) Software into Your proprietary 
 *      programs and into any third party proprietary programs.  
 *      However, if You incorporate the caBIG(tm) Software into 
 *      third party proprietary programs, You agree that You are 
 *      solely responsible for obtaining any permission from such 
 *      third parties required to incorporate the caBIG(tm) 
 *      Software into such third party proprietary programs and for 
 *      informing Your sublicensees, including without limitation 
 *      Your end-users, of their obligation to secure any required 
 *      permissions from such third parties before incorporating 
 *      the caBIG(tm) Software into such third party proprietary 
 *      software programs.  In the event that You fail to obtain 
 *      such permissions, You agree to indemnify caBIG(tm) 
 *      Participant for any claims against caBIG(tm) Participant by 
 *      such third parties, except to the extent prohibited by law, 
 *      resulting from Your failure to obtain such permissions.
 *  5.	For sake of clarity, and not by way of limitation, You may 
 *      add Your own copyright statement to Your modifications and 
 *      to the derivative works, and You may provide additional or 
 *      different license terms and conditions in Your sublicenses 
 *      of modifications of the caBIG(tm) Software, or any 
 *      derivative works of the caBIG(tm) Software as a whole, 
 *      provided Your use, reproduction, and distribution of the 
 *      Work otherwise complies with the conditions stated in this 
 *      License.
 *  6.	THIS caBIG(tm) SOFTWARE IS PROVIDED "AS IS" AND ANY 
 *      EXPRESSED OR IMPLIED WARRANTIES (INCLUDING, BUT NOT LIMITED 
 *      TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-
 *      INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE 
 *      DISCLAIMED.  IN NO EVENT SHALL SIEMENS CORPORATE RESEARCH 
 *      INC. OR ITS AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, 
 *      INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 *      (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
 *      GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
 *      BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 *      LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
 *      OF THE USE OF THIS caBIG(tm) SOFTWARE, EVEN IF ADVISED OF 
 *      THE POSSIBILITY OF SUCH DAMAGE.
 *  
 */
 
 
 
# include "SoVtkImageReader.h"
# include "SoVtkUtils.h"

# include "vtkTransform.h"
# include "vtkAlgorithmOutput.h"
# include "vtkImageData.h"


SO_ENGINE_SOURCE( SoVtkImageReader )

SoVtkImageReader::SoVtkImageReader()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImageReader);

	mObject = vtkImageReader::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImageReader *aImageReader = vtkImageReader::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(DataSpacing, (0,0,0));

	x = aImageReader->GetDataSpacing();
	DataSpacing.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(Transform, (0));

	SO_ENGINE_ADD_INPUT(DataVOI, (0));

	SO_ENGINE_ADD_INPUT(FilePattern, (""));

	SO_ENGINE_ADD_INPUT(FilePrefix, (""));

	SO_ENGINE_ADD_INPUT(FileDimensionality, (0));
	FileDimensionality.setValue(aImageReader->GetFileDimensionality());

	SO_ENGINE_ADD_INPUT(DataOrigin, (0,0,0));

	x = aImageReader->GetDataOrigin();
	DataOrigin.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(DataMask, (0));
	SO_ENGINE_ADD_INPUT(DataScalarType, (0));
	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	SO_ENGINE_ADD_INPUT(DataExtent, (0));

	SO_ENGINE_ADD_INPUT(HeaderSize, (0));
	HeaderSize.setValue(aImageReader->GetHeaderSize());

	SO_ENGINE_ADD_INPUT(FileNameSliceOffset, (0));
	FileNameSliceOffset.setValue(aImageReader->GetFileNameSliceOffset());

	SO_ENGINE_ADD_INPUT(NumberOfScalarComponents, (0));
	NumberOfScalarComponents.setValue(aImageReader->GetNumberOfScalarComponents());

	SO_ENGINE_ADD_INPUT(FileLowerLeft, (0));
	FileLowerLeft.setValue(aImageReader->GetFileLowerLeft());

	SO_ENGINE_ADD_INPUT(ScalarArrayName, (""));

	SO_ENGINE_ADD_INPUT(DataByteOrder, (0));
	DataByteOrder.setValue(aImageReader->GetDataByteOrder());

	SO_ENGINE_ADD_INPUT(FileName, (""));

	SO_ENGINE_ADD_INPUT(SwapBytes, (0));
	SwapBytes.setValue(aImageReader->GetSwapBytes());

	SO_ENGINE_ADD_INPUT(FileNameSliceSpacing, (0));
	FileNameSliceSpacing.setValue(aImageReader->GetFileNameSliceSpacing());

	aImageReader->Delete();


	SO_ENGINE_ADD_OUTPUT( oTransform, SoSFVtkObject );
	mTransform = 0;
	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkImageReader::~SoVtkImageReader()
{
	// Deletion of the objects if they exist
	if ( mTransform )
	{
	
		mTransform->unref();
		mTransform = 0;
	}
	
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

void SoVtkImageReader::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImageReader, SoEngine, "Engine" );
}

void SoVtkImageReader::evaluate()
{
	try
	{
		// Get the input type(s)
		SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
		
		if (inputPortPtr)
			mObject->SetInputConnection(inputPortPtr->getPointer());

		// Deletion of the objects if they exist
		if ( mTransform )
		{
		
			mTransform->unref();
			mTransform = 0;
		}
		
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

		mObject->GetTransform();
		mTransform = new SoVtkObject();
		mTransform->ref();
		mTransform->setPointer( mObject->GetTransform() );

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
	SO_ENGINE_OUTPUT( oTransform, SoSFVtkObject, setValue( mTransform ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
}


void SoVtkImageReader::inputChanged(SoField * f)
{
	// Get the DataSpacing value
	if ( f == &DataSpacing )
		SO_VTK_SET_FIELD_VEC3F( mObject, DataSpacing);

	// Get the Transform value
	if ( f == &Transform )
		SO_VTK_SET_FIELD_DATA( mObject, Transform, vtkTransform);

	// Get the DataVOI value
	if ( f == &DataVOI )
	{
		if ( DataVOI.getNum() >= 6)
		{
			SO_VTK_SET_6_FIELD_MFINT32( mObject, DataVOI);
		}
		else
		{
			SoDebugError::post( __FILE__, "This field must have 6 values." );
		}
	}

	// Get the FilePattern value
	if ( f == &FilePattern )
		SO_VTK_SET_FIELD_MFSTRING( mObject, FilePattern);

	// Get the FilePrefix value
	if ( f == &FilePrefix )
		SO_VTK_SET_FIELD_MFSTRING( mObject, FilePrefix);

	// Get the FileDimensionality value
	if ( f == &FileDimensionality )
		SO_VTK_SET_FIELD_VALUE( mObject, FileDimensionality);

	// Get the DataOrigin value
	if ( f == &DataOrigin )
		SO_VTK_SET_FIELD_VEC3F( mObject, DataOrigin);

	// Get the DataMask value
	if ( f == &DataMask )
		SO_VTK_SET_FIELD_VALUE( mObject, DataMask);

	// Get the DataScalarType value
	if ( f == &DataScalarType )
		SO_VTK_SET_FIELD_VALUE( mObject, DataScalarType);

	// Get the DataExtent value
	if ( f == &DataExtent )
	{
		if ( DataExtent.getNum() >= 6)
		{
			SO_VTK_SET_6_FIELD_MFINT32( mObject, DataExtent);
		}
		else
		{
			SoDebugError::post( __FILE__, "This field must have 6 values." );
		}
	}

	// Get the HeaderSize value
	if ( f == &HeaderSize )
		SO_VTK_SET_FIELD_VALUE( mObject, HeaderSize);

	// Get the FileNameSliceOffset value
	if ( f == &FileNameSliceOffset )
		SO_VTK_SET_FIELD_VALUE( mObject, FileNameSliceOffset);

	// Get the NumberOfScalarComponents value
	if ( f == &NumberOfScalarComponents )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfScalarComponents);

	// Get the FileLowerLeft value
	if ( f == &FileLowerLeft )
		SO_VTK_SET_FIELD_VALUE( mObject, FileLowerLeft);

	// Get the ScalarArrayName value
	if ( f == &ScalarArrayName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, ScalarArrayName);

	// Get the DataByteOrder value
	if ( f == &DataByteOrder )
		SO_VTK_SET_FIELD_VALUE( mObject, DataByteOrder);

	// Get the FileName value
	if ( f == &FileName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, FileName);

	// Get the SwapBytes value
	if ( f == &SwapBytes )
		SO_VTK_SET_FIELD_VALUE( mObject, SwapBytes);

	// Get the FileNameSliceSpacing value
	if ( f == &FileNameSliceSpacing )
		SO_VTK_SET_FIELD_VALUE( mObject, FileNameSliceSpacing);

	mObject->Update();
}

void SoVtkImageReader::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImageReader::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the DataSpacing value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, DataSpacing);

	// Get the Transform value
	
		SO_VTK_SET_FIELD_DATA( mObject, Transform, vtkTransform);

	// Get the DataVOI value
	
	{
		if ( DataVOI.getNum() >= 6)
		{
			SO_VTK_SET_6_FIELD_MFINT32( mObject, DataVOI);
		}
		else
		{
			SoDebugError::post( __FILE__, "This field must have 6 values." );
		}
	}

	// Get the FilePattern value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, FilePattern);

	// Get the FilePrefix value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, FilePrefix);

	// Get the FileDimensionality value
	
		SO_VTK_SET_FIELD_VALUE( mObject, FileDimensionality);

	// Get the DataOrigin value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, DataOrigin);

	// Get the DataMask value
	
		SO_VTK_SET_FIELD_VALUE( mObject, DataMask);

	// Get the DataScalarType value
	
		SO_VTK_SET_FIELD_VALUE( mObject, DataScalarType);

	// Get the DataExtent value
	
	{
		if ( DataExtent.getNum() >= 6)
		{
			SO_VTK_SET_6_FIELD_MFINT32( mObject, DataExtent);
		}
		else
		{
			SoDebugError::post( __FILE__, "This field must have 6 values." );
		}
	}

	// Get the HeaderSize value
	
		SO_VTK_SET_FIELD_VALUE( mObject, HeaderSize);

	// Get the FileNameSliceOffset value
	
		SO_VTK_SET_FIELD_VALUE( mObject, FileNameSliceOffset);

	// Get the NumberOfScalarComponents value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfScalarComponents);

	// Get the FileLowerLeft value
	
		SO_VTK_SET_FIELD_VALUE( mObject, FileLowerLeft);

	// Get the ScalarArrayName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, ScalarArrayName);

	// Get the DataByteOrder value
	
		SO_VTK_SET_FIELD_VALUE( mObject, DataByteOrder);

	// Get the FileName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, FileName);

	// Get the SwapBytes value
	
		SO_VTK_SET_FIELD_VALUE( mObject, SwapBytes);

	// Get the FileNameSliceSpacing value
	
		SO_VTK_SET_FIELD_VALUE( mObject, FileNameSliceSpacing);

	mObject->Update();
}