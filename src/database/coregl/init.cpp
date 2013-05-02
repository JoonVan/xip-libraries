/*
*  COPYRIGHT NOTICE.  Copyright (C) 2005 Siemens Corporate Research, 
*  Inc. ("caBIG(tm) Participant"). eXtensible Imaging Platform (XIP)
*  was created with NCI funding and is part of the caBIG(tm) 
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
#include <xip/system/standard.h>
#include <xip/system/GL/gl.h>

#include <xip/inventor/core/xipivcore.h>
#include <xip/inventor/core/SoXipData.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/core/SoXipMFDataImage.h>
#include <xip/inventor/core/SoXipActiveViewportElement.h>
#include <xip/inventor/core/SoXipCursor.h>
#include <xip/inventor/core/SoXipKit.h>
#include <xip/inventor/coregl/SoXipShaderProgramElement.h>
#include <xip/inventor/coregl/SoXipGLSLShaderProgramElement.h>
#include <xip/inventor/coregl/SoXipBlendFuncElement.h>
#include <xip/inventor/coregl/SoXipDrawQuad.h>
#include <xip/inventor/coregl/SoXipFrameRate.h>
#include <xip/inventor/coregl/SoXipFramebufferElement.h>
#include <xip/inventor/coregl/SoXipSetTransform.h>
#include <xip/inventor/coregl/SoXipBufferMaskElement.h>
#include <xip/inventor/coregl/SoXipCaptureImage.h>
#include <xip/inventor/coregl/SoXipDepthTestElement.h>
#include <xip/inventor/coregl/SoXipDrawImage.h>
#include <xip/inventor/coregl/SoXipFramebufferFlip.h>
#include <xip/inventor/coregl/SoXipGetTransform.h>
#include <xip/inventor/coregl/SoXipMultiplyMatrices.h>
#include <xip/inventor/coregl/SoXipOffscreenRenderer.h>

#include <xip/inventor/coregl/SoXipGlowElement.h>
#include <xip/inventor/coregl/SoXipFboElement.h>
#include <xip/inventor/coregl/SoXipDrawBuffersElement.h>

#include "SoXipClipPlaneKit.h"
#include "SoXipBlendFunc.h"
#include "SoXipBufferMask.h"
#include "SoXipUniformVariable.h"
#include "SoXipLoadShaders.h"
#include "SoXipLogGLState.h"
#include "SoXipDepthTest.h"
#include "SoXipDrawClipPlane.h"
#include "SoXipClearBuffer.h"
#include "SoXipFramebufferGroup.h"
#include "SoXipTextureUnit.h"
#include "SoXipClearFbo.h"
#include "SoXipFbo.h"
#include "SoXipFboAttachColor.h"
#include "SoXipFboAttachColor3D.h"
#include "SoXipFboAttachDepth.h"
#include "SoXipFboAttachDepth3D.h"
#include "SoXipPingPongFlip.h"
#include "SoXipPingPong.h"

#include "SoXipCube.h"
#include "SoXipDecomposeMFInt32.h"
#include "SoXipBindTextures.h"
#include "SoXipGetCameraProperties.h"
#include "SoXipGLSLPrograms.h"
#include "SoXipGLSLUniformGroup.h"
#include "SoXipGLSLUseProgram.h"
#include "SoXipLutTexture.h"
#include "SoXipOpenGLError.h"
#include "SoXipGLStringMarker.h"

#include  "SoXipTransparentGeometryRenderer.h"

int XIPIVCOREGL_API xipivcoregl_init()
{
	static bool isInit = false;
	if(isInit)
		return 1;
	isInit = true;

	xipivcore_init();

	//initialize elements first
    SoXipGLOWElement::initClass();
	SoXipShaderProgramElement::initClass();
	SoXipGLSLShaderProgramElement::initClass();
    SoXipFramebufferElement::initClass();
    SoXipBlendFuncElement::initClass();
    SoXipBufferMaskElement::initClass();
    SoXipDepthTestElement::initClass();
   	SoXipDrawBuffersElement::initClass();
   	SoXipFboElement::initClass();

	//then initialize rest
	SoXipTextureUnit::initClass();
	
	SoXipUniformVariable::initClass();
	SoXipUniformMatrix3::initClass();
	SoXipUniformMatrix4 ::initClass();
	SoXipUniformInt::initClass();
	SoXipUniformVec4f::initClass();
	SoXipUniformVec3f::initClass();
	SoXipUniformVec2f ::initClass();
	SoXipUniformFloat::initClass();

	SoXipClipPlaneKit::initClass();
	SoXipDrawClipPlane::initClass();
	SoXipDrawQuad::initClass();
	SoXipFrameRate::initClass();
	
	SoXipFramebufferGroup::initClass();
	SoXipSetTransform::initClass();
	
    SoXipBlendFunc::initClass();
	SoXipBufferMask::initClass();
	SoXipCaptureImage::initClass();
	SoXipClearBuffer::initClass();
	
	SoXipDepthTest::initClass();
	SoXipDrawImage::initClass();
	SoXipFramebufferFlip::initClass();
	SoXipGetTransform::initClass();
    SoXipGetCameraProperties::initClass();
	SoXipMultiplyMatrices::initClass();
	SoXipOffscreenRenderer::initClass();
	SoXipTransparentGeometryRenderer::initClass();

    SoXipLoadShaders::initClass();
    SoXipLogGLState::initClass();

    SoXipFbo::initClass();
    SoXipClearFbo::initClass();
    SoXipFboAttachColor::initClass();
    SoXipFboAttachColor3D::initClass();
    SoXipFboAttachDepth::initClass();
    SoXipFboAttachDepth3D::initClass();
    SoXipPingPong::initClass();
    SoXipPingPongFlip::initClass();

    SoXipCube::initClass();
    SoXipDecomposeMFInt32::initClass();
    SoXipBindTextures::initClass();
    SoXipGLSLPrograms::initClass();
    SoXipGLSLUseProgram::initClass();
    SoXipGLSLUniformGroup::initClass();

	SoXipLutTexture::initClass();
	SoXipOpenGLError::initClass();
	SoXipGLStringMarker::initClass();

	return 1;
}

#ifdef WIN32

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
		xipivcoregl_init();

	return TRUE;
}

#else /* not WIN32 */

static int initted = FALSE;    // a little protection--probably unnecessary
void __attribute__ ((constructor)) _init(void)// don't write this if DllMain is to be used
{
	int err;

	xipivcoregl_init();

	initted = TRUE;
	//return 0;
}

void __attribute__ ((destructor)) _fini(void)
{
	//printf ("fini print.\n");
}

#endif /* WIN32 */


