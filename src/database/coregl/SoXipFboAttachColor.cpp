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

#include <xip/system/standard.h>
#include <xip/system/GL/gl.h>
#include "SoXipFboAttachColor.h"
#include <xip/inventor/coregl/SoXipDrawBuffersElement.h>
#include <xip/inventor/coregl/SoXipFboElement.h>

SO_NODE_SOURCE(SoXipFboAttachColor);

SoXipFboAttachColor::SoXipFboAttachColor()
{
	SO_NODE_CONSTRUCTOR(SoXipFboAttachColor);

	SO_NODE_ADD_FIELD(multiplicity, (1));
    SO_NODE_ADD_FIELD(bufferStorage, (TEXTURE));
	SO_NODE_ADD_FIELD(format, (RGBA));
	SO_NODE_ADD_FIELD(internalFormat, (RGBA8));
	SO_NODE_ADD_FIELD(wrap, (CLAMP_TO_BORDER));
	SO_NODE_ADD_FIELD(filter, (NEAREST));

	SO_NODE_ADD_FIELD(handleOutput, (0));

	SO_NODE_DEFINE_ENUM_VALUE(BufferStorage, TEXTURE);
	SO_NODE_DEFINE_ENUM_VALUE(BufferStorage, RENDERBUFFER);
	SO_NODE_SET_SF_ENUM_TYPE(bufferStorage, BufferStorage);

	SO_NODE_DEFINE_ENUM_VALUE(Format, ALPHA);
	SO_NODE_DEFINE_ENUM_VALUE(Format, LUMINANCE);
	SO_NODE_DEFINE_ENUM_VALUE(Format, LUMINANCE_ALPHA);
	SO_NODE_DEFINE_ENUM_VALUE(Format, INTENSITY);
	SO_NODE_DEFINE_ENUM_VALUE(Format, RGB);
	SO_NODE_DEFINE_ENUM_VALUE(Format, RGBA);
	SO_NODE_SET_SF_ENUM_TYPE(format, Format);

	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, ALPHA4);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, ALPHA8);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, ALPHA12);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, ALPHA16);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, ALPHA16F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, ALPHA32F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE4);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE8);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE12);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE16);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE16F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE32F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE4_ALPHA4);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE6_ALPHA2);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE8_ALPHA8);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE12_ALPHA4);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE12_ALPHA12);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE16_ALPHA16);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE_ALPHA16F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE_ALPHA32F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, INTENSITY4);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, INTENSITY8);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, INTENSITY12);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, INTENSITY16);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, INTENSITY16F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, INTENSITY32F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, R3_G3_B2);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGB4);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGB5);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGB8);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGB10);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGB12);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGB16);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGB16F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGB32F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGBA2);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGBA4);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGB5_A1);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGBA8);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGB10_A2);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGBA12);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGBA16);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGBA16F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGBA32F_ARB);
	SO_NODE_SET_SF_ENUM_TYPE(internalFormat, InternalFormat);

	SO_NODE_DEFINE_ENUM_VALUE(Wrap,	 REPEAT);
	SO_NODE_DEFINE_ENUM_VALUE(Wrap,  CLAMP);
	SO_NODE_DEFINE_ENUM_VALUE(Wrap,	 CLAMP_TO_BORDER);
	SO_NODE_DEFINE_ENUM_VALUE(Wrap,  CLAMP_TO_EDGE);
	SO_NODE_DEFINE_ENUM_VALUE(Wrap,	 MIRRORED_REPEAT);
	SO_NODE_SET_SF_ENUM_TYPE(wrap, Wrap);

	SO_NODE_DEFINE_ENUM_VALUE(Filter, NEAREST);
	SO_NODE_DEFINE_ENUM_VALUE(Filter, LINEAR);
	SO_NODE_SET_SF_ENUM_TYPE(filter, Filter);

    // Attach output sensor to output fields
	mSensorOut = new SoFieldSensor(sensorOutCB, this);
    mSensorOut->attach(&handleOutput);

    mNumAttachments = 0;
    mMaxAttachments = 0;

    for (int i = 0; i < 16; i++)
        mHandles[i] = 0;

    mFboIn.clear();
    mFboOut.clear();
    mNodeId = 0;
}

/**
 *  Destructor.
 */
SoXipFboAttachColor::~SoXipFboAttachColor()
{
    if (mIsAllocated)
        deallocate();
    delete mSensorOut;
}

/**
 *  Class initiator.
 */
void SoXipFboAttachColor::initClass() {
	SO_NODE_INIT_CLASS(SoXipFboAttachColor, SoNode, "SoNode");

	SO_ENABLE(SoGLRenderAction, SoXipGLOWElement);
	SO_ENABLE(SoGLRenderAction, SoXipDrawBuffersElement);
    SO_ENABLE(SoGLRenderAction, SoXipFboElement);
}



/**
 *  Run a check and output any errors.
 */
bool SoXipFboAttachColor::checkFramebufferStatus()
{
    bool isOk = false;
    int db[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int tp[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    GLenum status = (GLenum)glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
    switch(status) {
        case GL_FRAMEBUFFER_COMPLETE_EXT:
            isOk = true;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
            SoDebugError::post("SoXipFboAttachColor", "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT");
            break;
        case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
            SoDebugError::post("SoXipFboAttachColor", "GL_FRAMEBUFFER_UNSUPPORTED_EXT");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
            SoDebugError::post("SoXipFboAttachColor", "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
            SoDebugError::post("SoXipFboAttachColor", "GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
            SoDebugError::post("SoXipFboAttachColor", "GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
            // Extract buffer setup
            for (int i = 0; i < mMaxAttachments; i++)
                glGetIntegerv(GL_DRAW_BUFFER0 + i, db + i);
            // Extract type setup
            for (int i = 0; i < mMaxAttachments; i++)
                glGetFramebufferAttachmentParameterivEXT(GL_FRAMEBUFFER_EXT,
                                                 GL_COLOR_ATTACHMENT0_EXT + i,
                                                 GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_EXT,
                                                 tp + i);
            // Print
            SoDebugError::post("SoXipFboAttachColor", "Incomplete Draw Buffer: draw (%d %d %d %d) type (%d %d %d %d)",
                db[0], db[1], db[2], db[3], tp[0], tp[1], tp[2], tp[3]);
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
            SoDebugError::post("SoXipFboAttachColor", "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT");
            break;
        default:
            SoDebugError::post("SoXipFboAttachColor", "UNKNWON frambuffer fault");
    }
    return isOk;
} 



/**
 *  Clamp attachment number field between 0 and context maximum.
 */
void SoXipFboAttachColor::checkMaxNumAttachments()
{
    glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS_EXT, &mMaxAttachments);

    int val = multiplicity.getValue();
    int max = mMaxAttachments;
    if (val < 1 || val > max) {
        val = (val < 1) ? 1 : (val > max) ? max : val;
        multiplicity.setValue(val);
        SoDebugError::postInfo("SoXipDBOAttachColor", "Valid range of attachments are [1,%d]", max);
    }
}



/**
 *  Replacing existing color attachments with new user defined ones.
 */
void SoXipFboAttachColor::allocate()
{
    if (bufferStorage.getValue() == TEXTURE)
    {
        // Generate textures
        glGenTextures(mNumAttachments, mHandles);
        for (int i = 0; i < mNumAttachments; i++)
        {
            glBindTexture(GL_TEXTURE_2D, mHandles[i]);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mFboOut.colorWrap);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mFboOut.colorWrap);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mFboOut.colorFilter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mFboOut.colorFilter);
            glTexImage2D(GL_TEXTURE_2D, 0, mFboOut.internalColorFormat, mFboOut.width, mFboOut.height,
                0, mFboOut.colorFormat, GL_UNSIGNED_BYTE, NULL);
        }
	    glBindTexture(GL_TEXTURE_2D, 0);
    }
    else if (bufferStorage.getValue() == RENDERBUFFER)
    {
        // Generate renderbuffers
        glGenRenderbuffersEXT(mNumAttachments, mHandles);
        for (int i = 0; i < mNumAttachments; i++)
        {
            glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, mHandles[i]);
            glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, mFboOut.internalColorFormat, mFboOut.width, mFboOut.height);
        }
        glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);
    }

    mIsAllocated = true;
}


/**
 *  Deallocation of textures and renderbuffers.
 */
void SoXipFboAttachColor::deallocate()
{
    if (mFboOut.colorStorage == TEXTURE)
        glDeleteTextures(mNumAttachments, mHandles);
    else if (mFboOut.colorStorage == RENDERBUFFER)
        glDeleteRenderbuffersEXT(mNumAttachments, mHandles);

    mNumAttachments = 0;
    for (int i = 0; i < 16; i++)
        mHandles[i] = 0;

    mIsAllocated = false;
}


/**
 *  Frame buffer object allocator.
 *  Allocates and re-allocates FBO's according to user/engine/state variables.
 */
void SoXipFboAttachColor::syncOutput()
{
    bool outputDirty = false;
    
    if (!mHandles || mNumAttachments > 16)
        SoDebugError::post("SoXipFbo", "invalid pointer or more than 16 handles");
    else {
        // Expand list by padding with zeros if to short
        if (handleOutput.getNum() < static_cast<int>(mNumAttachments)) {
            for (int i = handleOutput.getNum(); i < mNumAttachments; i++) {
                //SoDebugError::post("", "num mismatch %d (%d %d)", i, handleOutput.getNum(), mNumAttachments);
                handleOutput.set1Value(i, 0);
                outputDirty = true;
            }
        }

        // Update entries if changed
        for (int i = 0; i < mNumAttachments; i++) {
            if (handleOutput[i] != static_cast<int>(mHandles[i])) {
                //SoDebugError::post("", "handle mismatch %d (%d %d)", i, handleOutput[i], mHandles[i]);
                handleOutput.set1Value(i, static_cast<int>(mHandles[i]));
                outputDirty = true;
            }
        }

        // Remove absolete entries
        if (handleOutput.getNum() > static_cast<int>(mNumAttachments)) {
            //SoDebugError::post("", "length mismatch");
            handleOutput.deleteValues(mNumAttachments);
            outputDirty = true;
        }
    }

    mNodeId = getNodeId();
}


/**
 *  Sets up the buffers, saves the state and pushes the effected attributes.
 *  Allocates buffer if need be and performs most functionallity.
 */
void SoXipFboAttachColor::GLRender(SoGLRenderAction* action)
{
    FboSetup * fbo = SoXipFboElement::getActive(action->getState(), this);

    if (!fbo->isOpen)
        return;

    if (*fbo != mFboIn || fbo->isDirty)
    {
        if (fbo->numColorAttachments != 0)
            SoDebugError::postInfo("SoXipFboAttachColor",
                "Replacing existing color attachments, please set 0 attachments in Fbo node");
        mFboIn = *fbo;
        mFboIn.isDirty = false;
        mNeedsUpdate = true;
        //SoDebugError::postInfo("SoXipFboAttachColor", "mFboIn != fbo");
    }

    if (mNodeId != getNodeId()) {
        mNodeId = getNodeId();
        mFboIn = *fbo;
        mNeedsUpdate = true;
        //SoDebugError::postInfo("SoXipFboAttachColor", "mNodeId != nodeId");
    }

    if (mNeedsUpdate)
    {
        if (mIsAllocated)
            deallocate();

        checkMaxNumAttachments();

        // Update setup according to fields
        mNumAttachments = multiplicity.getValue();
        mFboOut = mFboIn;
        mFboOut.colorStorage = bufferStorage.getValue();
        mFboOut.numColorAttachments = mNumAttachments;
        mFboOut.colorFormat = format.getValue();
        mFboOut.internalColorFormat = internalFormat.getValue();
        mFboOut.colorWrap = wrap.getValue();
        mFboOut.colorFilter = filter.getValue();

        if (mFboOut.colorStorage == TEXTURE) {
            // Reserve a unit for setting up the fbo textures
            GLuint unit = SoXipMultiTextureElement::getFreeUnit(action->getState());
            SoXipMultiTextureElement::setUnit(action->getState(), unit);
            SoXipMultiTextureElement::bindTexture(action->getState(), GL_TEXTURE_2D, 0);
        }

        allocate();
        syncOutput();

        mFboOut.isDirty = true;
        mNeedsUpdate = false;
    }
    else
        mFboOut.isDirty = false;

    // Update settings
    mFboOut.numColorAttachments = mNumAttachments;
    for (int i = 0; i < mNumAttachments; i++)
        mFboOut.colorHandles[i] = mHandles[i];
    mFboOut.hasModColors = true;

    // Upload to element
    SoXipFboElement::set(action->getState(), this, mFboOut);
}

void SoXipFboAttachColor::sensorOutCB(void *usr, SoSensor *sensor) {
    SoXipFboAttachColor * thisObj = reinterpret_cast<SoXipFboAttachColor *>(usr);
    thisObj->syncOutput();
}


