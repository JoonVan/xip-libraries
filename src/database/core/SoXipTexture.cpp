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

#include <algorithm>

//#define glTexImage3D glTexImage3Dext
//#define glTexSubImage3D glTexSubImage3Dext
//#define glActiveTextureARB glActiveTextureARBext


#include <xip/inventor/core/SbXipImageAdaptor.h>
#include <xip/inventor/core/SoXipMultiTextureElement.h>


#include <Inventor/elements/SoGLTextureEnabledElement.h>
#include <Inventor/elements/SoTextureQualityElement.h>
#ifndef TGS_VERSION
#include <Inventor/elements/SoGLCacheContextElement.h>
#endif
#include <Inventor/SbBox.h>

#include "SoXipTexture.h"

#ifdef WIN32
#define INIT_EXT(PF, F) F = (PF) xipGlGetProcAddress(#F)
#else
#define INIT_EXT(PF, F)
#endif

#ifndef WIN32
#ifndef DARWIN
#ifndef linux
static PFNGLTEXIMAGE3DEXTPROC		glTexImage3D = 0;
static PFNGLTEXSUBIMAGE3DEXTPROC	glTexSubImage3D = 0;
//#endif //linux
static PFNGLGENBUFFERSPROC		glGenBuffers = 0;
static PFNGLDELETEBUFFERSPROC		glDeleteBuffers = 0;
static PFNGLBINDBUFFERPROC		glBindBuffer = 0;
static PFNGLBUFFERDATAPROC		glBufferData = 0;
static PFNGLBUFFERSUBDATAPROC		glBufferSubData = 0;
static PFNGLMAPBUFFERPROC		glMapBuffer = 0;
static PFNGLUNMAPBUFFERPROC		glUnmapBuffer = 0;
#endif //linux
#endif /* DARWIN */
#endif //WIN32

GLint  SoXipTexture::maxTextureSize = -1;


SoXipTexture::DataTypeInfo SoXipTexture::dataTypeInfo[] =
	{
		{GL_UNSIGNED_BYTE, 8, SoXipTexture::BITSUSED, {LUMINANCE8, LUMINANCE8_ALPHA8, RGB8, RGBA8}},
		{GL_BYTE, 8, SoXipTexture::BITSUSED_SIGNED, {LUMINANCE8, LUMINANCE8_ALPHA8, RGB8, RGBA8}},
		{GL_UNSIGNED_SHORT, 16, SoXipTexture::BITSUSED, {LUMINANCE16, LUMINANCE16_ALPHA16, RGB16, RGBA16}},
		{GL_SHORT, 16, SoXipTexture::BITSUSED_SIGNED, {LUMINANCE16, LUMINANCE16_ALPHA16, RGB16, RGBA16}},
		{GL_UNSIGNED_INT, 32, SoXipTexture::BITSUSED, {LUMINANCE16, LUMINANCE16_ALPHA16, RGB16, RGBA16}},
		{GL_INT, 32, SoXipTexture::BITSUSED_SIGNED, {LUMINANCE16, LUMINANCE16_ALPHA16, RGB16, RGBA16}},
		{GL_FLOAT, 0, SoXipTexture::NONE, {LUMINANCE16F_ARB, LUMINANCE_ALPHA16F_ARB, RGB16F_ARB, RGBA16F_ARB}},
		{0, 0, SoXipTexture::NONE, {0}}
};

GLenum SoXipTexture::baseFormats[] = {GL_LUMINANCE, GL_LUMINANCE_ALPHA, GL_RGB, GL_RGBA};

SO_NODE_SOURCE(SoXipTexture);

void SoXipTexture::initClass()
{
	//SO_NODE_INIT_CLASS(SoXipTexture, SoShape, "Shape");
    SO_NODE_INIT_CLASS(SoXipTexture, SoNode, "Node");
	SO_ENABLE(SoGLRenderAction,	SoGLTextureEnabledElement);
	SO_ENABLE(SoGLRenderAction,	SoXipMultiTextureElement);
}

/**
 *	Constructor
 */
SoXipTexture::SoXipTexture()
{
	SO_NODE_CONSTRUCTOR(SoXipTexture);


	// Set up enumerations for texture model
	SO_NODE_DEFINE_ENUM_VALUE(TextureDimension, AUTO);
	SO_NODE_DEFINE_ENUM_VALUE(TextureDimension, TEXTURE_1D);
	SO_NODE_DEFINE_ENUM_VALUE(TextureDimension, TEXTURE_2D);
	SO_NODE_DEFINE_ENUM_VALUE(TextureDimension, TEXTURE_3D);
	// Set up enumerations for texture model
	SO_NODE_DEFINE_ENUM_VALUE(Model, REPLACE);
	SO_NODE_DEFINE_ENUM_VALUE(Model, MODULATE);
	SO_NODE_DEFINE_ENUM_VALUE(Model, DECAL);
	SO_NODE_DEFINE_ENUM_VALUE(Model, BLEND);
	SO_NODE_DEFINE_ENUM_VALUE(Model, ADD);
	// Set up enumerations for texture wrap
	SO_NODE_DEFINE_ENUM_VALUE(Wrap, REPEAT);
	SO_NODE_DEFINE_ENUM_VALUE(Wrap, CLAMP);
	SO_NODE_DEFINE_ENUM_VALUE(Wrap, CLAMP_TO_BORDER);
	SO_NODE_DEFINE_ENUM_VALUE(Wrap, CLAMP_TO_EDGE);
	SO_NODE_DEFINE_ENUM_VALUE(Wrap, MIRRORED_REPEAT);
	// Set up enumerations for texture filter
	SO_NODE_DEFINE_ENUM_VALUE(Filter, NEAREST);
	SO_NODE_DEFINE_ENUM_VALUE(Filter, LINEAR);
	// Set up enumerations for texture internal format
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

	// Set up info in enumerated type field
	SO_NODE_SET_SF_ENUM_TYPE(model, Model);
	SO_NODE_SET_SF_ENUM_TYPE(wrapS, Wrap);
	SO_NODE_SET_SF_ENUM_TYPE(wrapT, Wrap);
	SO_NODE_SET_SF_ENUM_TYPE(wrapR, Wrap);
	SO_NODE_SET_SF_ENUM_TYPE(filter, Filter);
	SO_NODE_SET_SF_ENUM_TYPE(internalFormat, InternalFormat);
	SO_NODE_SET_SF_ENUM_TYPE(textureDimension, TextureDimension);

	// init the fields
	SO_NODE_ADD_FIELD(image, (0));
	SO_NODE_ADD_FIELD(on, (TRUE));
	SO_NODE_ADD_FIELD(textureMatrix, (FALSE));
	SO_NODE_ADD_FIELD(wrapS, (CLAMP_TO_EDGE));
	SO_NODE_ADD_FIELD(wrapT, (CLAMP_TO_EDGE));
	SO_NODE_ADD_FIELD(wrapR, (CLAMP_TO_EDGE));
	SO_NODE_ADD_FIELD(borderColor, (SbVec4f(0, 0, 0, 0)));
	SO_NODE_ADD_FIELD(filter, (LINEAR));
	SO_NODE_ADD_FIELD(model, (REPLACE));
	SO_NODE_ADD_FIELD(textureDimension, (AUTO));
	SO_NODE_ADD_FIELD(blendColor, (SbVec4f(0, 0, 0, 0)));
	SO_NODE_ADD_FIELD(overrideDefault, (FALSE));
	SO_NODE_ADD_FIELD(internalFormat, (RGBA8));
	SO_NODE_ADD_FIELD(padDimensions, (FALSE));
	SO_NODE_ADD_FIELD(textureSize, (SbVec3f(-1, -1, -1)));
    SO_NODE_ADD_FIELD(modelMatrix, (SbMatrix::identity()));
	SO_NODE_ADD_FIELD(usePBO, (FALSE));
	SO_NODE_ADD_FIELD(forceNPOT, (FALSE));
    SO_NODE_ADD_FIELD(autoScaleRange, (TRUE));


	// Set up sensors
	SoField* fields[] = {&wrapS, &wrapT, &wrapR, &filter, &borderColor};

	mNumFields = sizeof(fields) / sizeof(fields[0]);

	mSensors = new SoFieldSensor*[mNumFields];

	for (int i = 0; i < mNumFields; ++i) {
		mSensors[i] = new SoFieldSensor(paramHasChangedCB, this);
		mSensors[i]->attach(fields[i]);
	}

	SoField* criticalFields[] = {
	    &internalFormat, &overrideDefault, &padDimensions, &autoScaleRange
    };
	
	mNumCriticalFields = sizeof(criticalFields) / sizeof(criticalFields[0]);
	mCriticalSensors = new SoFieldSensor*[mNumCriticalFields];

	for (int j = 0; j < mNumCriticalFields; ++j) {
		mCriticalSensors[j] = new SoFieldSensor(textureInvalidCB, this);
		mCriticalSensors[j]->attach(criticalFields[j]);
	}

	// init members
	mImageId = 0;
	mImageHasChanged = true;
	mParamHasChanged = false;
	mTextureSize = SbXipImageDimensions(-1, -1, -1);
    mTextureModelMatrix = SbMatrix::identity();
	mTextureDimension = 0;
	mImageData = NULL;
	mTextureDataType = 0;
	mQueryExtensions = true;
	mGLTexture = 0;
	mPBOId = 0;
	mPBOBufSize = 0;
}

/**
 *	Destructor
 */
SoXipTexture::~SoXipTexture()
{
	// delete the texture
#ifdef TGS_VERSION
	deleteTexture();
#else
	if (mGLTexture)
		deleteTexture(NULL);	
#endif

	if (mImageData)
		mImageData->unref();

	// delete the sensors
	for (int i = 0; i < mNumFields; ++i) {
		delete mSensors[i];
	}

	delete [] mSensors;

	for (int j = 0; j < mNumCriticalFields; ++j) {
		delete mCriticalSensors[j];
	}

	delete [] mCriticalSensors;
}

#if 0 //SoXipTexture IS NO LONGER A SHAPE (Stefan Lindholm - 2009.8.19)
/**
 *	Compute the bounding box, taking the model matrix into account
 */
void SoXipTexture::computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center)
{
	box.makeEmpty();
	center = SbVec3f(0, 0, 0);

	// only if the textureMatrix flag is set we also update the bounding box
	if (action && textureMatrix.getValue())
	{
		// check state
		SoState *state = action->getState();
		if (!state) return;

		if (!image.getValue() || !image.getValue()->get())
			return;

		SbVec3f out;
		SbMatrix model = image.getValue()->get()->getModelMatrix();
		for (int s=0; s<8; s++)
		{
			model.multVecMatrix(SbVec3f((s&1) ? 1 : 0, (s&2) ? 1 : 0, (s&4) ? 1 : 0), out);
			box.extendBy(out);
		}
		center = (box.getMax() - box.getMin()) / 2;
	}
}
#endif

/**
 *	Computes the next power-of-two
 */
unsigned int SoXipTexture::powerOfTwo(unsigned int x) {
	unsigned int result = x > 0;

	if (x > 1) {
		x--;
		result <<= 1;

		while (x >>= 1)
			result <<= 1;
	}

	return result;
}

/**
 *	Computes new size of the texture 
 */
SbXipImageDimensions SoXipTexture::calcTextureSize(const SbXipImageDimensions &dim) 
{
	SbXipImageDimensions result;

	if (padDimensions.getValue()) 
	{
		result[0] = powerOfTwo(dim[0]);
		result[1] = powerOfTwo(dim[1]);
		result[2] = powerOfTwo(dim[2]);
	}
	else 
	{
		result = dim;
	}

	// clip to max texture size
	if (maxTextureSize < 0)
	{
	    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);
	}

	result[0] = std::min(result[0], maxTextureSize);
	result[1] = std::min(result[1], maxTextureSize);
	result[2] = std::min(result[2], maxTextureSize);

	return result;
}

/**
 *	Get the dimension (1D/2D/3D) of the texture
 */
GLenum SoXipTexture::getTextureDimension(const SbXipImageDimensions &dim)
{
	if( textureDimension.getValue() == AUTO )
	{
		if (dim[2] > 1)
			return GL_TEXTURE_3D;
		else if (dim[1] > 1)
			return GL_TEXTURE_2D;
		else if (dim[0] > 1)
			return GL_TEXTURE_1D;
	}

	return textureDimension.getValue();
}

/**
 *	Checks the input image
 */
bool SoXipTexture::validateImage()
{
	mNewImageData = image.getValue();

	if (!mNewImageData || !mNewImageData->get())
		return false;

	mNewTextureSize = calcTextureSize(mNewImageData->get()->getDimAllocated());

    mNewTextureModelMatrix = mNewImageData->get()->getModelMatrix();

	mNewTextureDimension = getTextureDimension(mNewTextureSize);
	// is the dimension correct ?
	if (mNewTextureDimension == 0)
	{
		SoDebugError::postInfo("SoXipTexture::validateImage", "Invalid image dimensions");
		return false;
	}

	// is it a non power of two size
	if (mNewTextureSize != SbXipImageDimensions(powerOfTwo(mNewTextureSize[0]), powerOfTwo(mNewTextureSize[1]), powerOfTwo(mNewTextureSize[2])))
	{
		SbBool supportsNonPowerOfTwo = hasNonPowerOfTwoExtensions();
		if (!supportsNonPowerOfTwo && (mNewTextureDimension == TEXTURE_3D))
		{
			SoDebugError::postInfo("SoXipTexture::validateImage", "Cannot create texture of size (%d x %d x %d). The OpenGL driver does not support non power of two textures!", 
				mNewTextureSize[0], mNewTextureSize[1], mNewTextureSize[2]);

			return false;
		}

		if (!supportsNonPowerOfTwo)
		{
			// if non power of two is not supported, scale textures
			mNewTextureSize = SbXipImageDimensions(powerOfTwo(mNewTextureSize[0]), powerOfTwo(mNewTextureSize[1]), powerOfTwo(mNewTextureSize[2]));
			SoDebugError::postWarning("SoXipTexture::validateImage", "The OpenGL driver does not support non power of two textures (performance warning).");
		}
	}

	mNewTextureDataType = mNewImageData->get()->getType();
	// is the data type correct ?
	if (mNewTextureDataType < 0 || mNewTextureDataType > 6)
	{
		SoDebugError::postInfo("SoXipTexture::validateImage", "Unknown image data type");
		return false;
	}

	// is the input buffer valid ?
	if (!(mNewImageData->get()->getComponents() == 1 || mNewImageData->get()->getComponentType() == SbXipImage::INTERLEAVED))
	{
		SoDebugError::postInfo("SoXipTexture::validateImage", "Only single channel or interleaved multi-channel images are supported");
		return false;
	}

	// we want to use our defined internal format
	if (overrideDefault.getValue())
	{
		mNewTextureInternalFormat = internalFormat.getValue();
	}
	else 
	{
		// or let the module decide for us
		const int formatIndex = mNewImageData->get()->getComponents() - 1;
		mNewTextureInternalFormat = dataTypeInfo[mNewTextureDataType].defaultFormat[formatIndex];
		if ((GLenum)internalFormat.getValue() != mNewTextureInternalFormat)
		    internalFormat.setValue(mNewTextureInternalFormat);
		mCriticalSensors[0]->unschedule();
	}

	SbVec3f texSize = SbVec3f(mNewTextureSize[0], mNewTextureSize[1], mNewTextureSize[2]);
	if(texSize != textureSize.getValue())
	{
	    textureSize.setValue(texSize);
	}

    if (mNewTextureModelMatrix != modelMatrix.getValue())
    {
        modelMatrix.setValue(mNewTextureModelMatrix);
    }

        // getBitsStored() returns bits used, so it can be 12!!!
	mPBOBufSize = texSize[0] * texSize[1] * texSize[2] *
            mNewImageData->get()->getComponents() *
            ((mNewImageData->get()->getBitsStored() + 7) / 8);

	return true;
}

/**
 *	Delete the texture
 */
#ifdef TGS_VERSION
void SoXipTexture::deleteTexture()
{
	if (!mGLTexture)
		SoDebugError::postInfo("SoXipTexture::deleteTexture", "mGLTexture is already null!");
	else
	{
		glDeleteTextures(1, &mGLTexture);
		mGLTexture = 0;
	}

	if (mHasPBOs && mPBOId)
	{
		glDeleteBuffers(1, &mPBOId);
		mPBOId = 0;
	}
}
#else
void SoXipTexture::deleteTexture(SoGLRenderAction *action)
{
	if (mGLTexture)
	{
		SoState *state = 0;
		if (action)
			state = action->getState();

		mGLTexture->unref(state);
		mGLTexture = 0;
	}
	else
	{
		SoDebugError::postWarning("SoXipTexture::deleteTexture", "Deleting null texture");
	}
}
#endif

/**
 *	compare images, return false if images are different
 */
bool SoXipTexture::compareImage()
{
	return mGLTexture == 0 ||
		mNewTextureInternalFormat != mTextureInternalFormat ||
		mNewTextureSize != mTextureSize ||
		mNewTextureModelMatrix != mTextureModelMatrix ||
		mNewImageData->get()->getComponents() != mImageData->get()->getComponents() ||
		mNewImageData->get()->getType() != mImageData->get()->getType();
}

/**
 *	Update the texture image
 */
void SoXipTexture::updateImage()
{
	// unref the previous one
	if (mImageData)
		mImageData->unref();

	mImageData = mNewImageData;

	// create the new image and initialize it
	if (mImageData)
	{
		mImageData->ref();

		mTextureSize = mNewTextureSize;

		mTextureModelMatrix = mNewTextureModelMatrix;

		mTextureDimension = mNewTextureDimension;

		mTextureDataType = mNewTextureDataType;

		mTextureInternalFormat = mNewTextureInternalFormat;
	}
}

/**
 *	Generate the texture
 */
#ifdef TGS_VERSION
void SoXipTexture::allocTexture()
{
	if (mGLTexture)
	{
		SoDebugError::postInfo("SoXipTexture::allocTexture", "Allocating texture without deleting");
		glDeleteTextures(1, &mGLTexture);
	}

	glGenTextures(1, &mGLTexture);

	if (mHasPBOs)
		glGenBuffers(1, &mPBOId);
}
#else
void SoXipTexture::allocTexture(SoGLRenderAction *action)
{
	if (mGLTexture)
	{
		SoDebugError::postWarning("SoXipTexture::allocTexture", "Allocating texture without deleting");
		deleteTexture(action);
	}

	mGLTexture = new SoGLDisplayList(action->getState(), SoGLDisplayList::TEXTURE_OBJECT);
	mGLTexture->ref();

	if (mHasPBOs)
		glGenBuffers(1, &mPBOId);
}
#endif

/**
 *	Bind the texture
 */
void SoXipTexture::bindTexture(SoState *state)
{
	if (mGLTexture)
	{
		if (textureMatrix.getValue())
		{
			glMatrixMode(GL_TEXTURE);
			// let's set the texture matrix as the inverse of the model matrix
			//	so that transformations of the original volume are taken into account
			//	when we generate the texture coordinates in the vertex program
			SbMatrix mat = mImageData->get()->getModelMatrix().inverse();
			glLoadMatrixf(mat);

			glMatrixMode(GL_MODELVIEW);
		}

		// actually bind the texture
	#ifdef TGS_VERSION
		SoXipMultiTextureElement::bindTexture(state, mTextureDimension, mGLTexture);
	#else
		SoXipMultiTextureElement::bindTexture(state, mTextureDimension, mGLTexture->getFirstIndex());
	#endif
	}
}

/**
 *	Create the texture
 *	No upload here, it is faster to use glTexSubImage (see updateTexture)
 */
void SoXipTexture::createTexture()
{
	const SbXipImage* image = mImageData->get();
	const int formatIndex = image->getComponents() - 1;

	switch (mTextureDimension)
	{
	case GL_TEXTURE_1D:
		glTexImage1D(
			GL_TEXTURE_1D,							// target
			0,										// level
			mTextureInternalFormat,					// internalFormat
			mTextureSize[0],						// width
			0,										// border
			baseFormats[formatIndex],				// format
			dataTypeInfo[mTextureDataType].type,	// type
			NULL);
		break;
	case GL_TEXTURE_2D:
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			mTextureInternalFormat,
			mTextureSize[0],
			mTextureSize[1],
			0,
			baseFormats[formatIndex],
			dataTypeInfo[mTextureDataType].type,
			NULL);
		break;
	case GL_TEXTURE_3D:
		{
/*#ifdef WIN32 
			if (!glTexImage3D)
				glTexImage3D = (PFNGLTEXIMAGE3DEXTPROC)xipGlGetProcAddress("glTexImage3DEXT");
#endif // DARWIN
*/
			if (glTexImage3D)
			{
				glTexImage3D(
					GL_TEXTURE_3D,
					0,
					mTextureInternalFormat,
					mTextureSize[0],
					mTextureSize[1],
					mTextureSize[2],
					0,
					baseFormats[formatIndex],
					dataTypeInfo[mTextureDataType].type,
					NULL);
			}
			else
			{
				SoError::post("glTexImage3DEXT is not supported on this graphic card!");
			}
		}
		break;
	}
	if (mHasPBOs && usePBO.getValue())
	{
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mPBOId);
		glBufferData(GL_PIXEL_UNPACK_BUFFER, mPBOBufSize, NULL, GL_STREAM_DRAW);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
	}
}

/**
 *	Update the texture
 */
void SoXipTexture::updateTexture()
{
	SbXipImage* image = mImageData->get();
	const SbXipImageDimensions& dim = image->getDimAllocated();
	const int formatIndex = image->getComponents() - 1;
	const void * imageBuffer = image->refBufferPtr();

	// Save alignment
	int align;
	glGetIntegerv(GL_UNPACK_ALIGNMENT, &align);

	// FIXME: get optimal alignment
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	bool didScale = false;
	bool didBias = false;
	if (dataTypeInfo[mTextureDataType].scaleOption != SoXipTexture::NONE
        &&  autoScaleRange.getValue())
	{
		// we need to scale the components of the texture
	        int bitsUsed = std::min(dataTypeInfo[mTextureDataType].bits, image->getBitsStored());
		double scale = (pow(2.0, dataTypeInfo[mTextureDataType].bits) - 1.0) / (pow(2.0, bitsUsed) - 1.0);

		if (dataTypeInfo[mTextureDataType].scaleOption == SoXipTexture::BITSUSED_SIGNED)
			scale *= 0.5;

		if (scale != 1.0) {
			//SoDebugError::postInfo("SoXipTexture::updateTexture", "Scaling with factor %f", scale);
			glPixelTransferf(GL_RED_SCALE, static_cast<float>(scale));
			glPixelTransferf(GL_GREEN_SCALE, static_cast<float>(scale));
			glPixelTransferf(GL_BLUE_SCALE, static_cast<float>(scale));
			glPixelTransferf(GL_ALPHA_SCALE, static_cast<float>(scale));
			didScale = true;
		}
		// we need to bias the components of the texture
		if (dataTypeInfo[mTextureDataType].scaleOption == SoXipTexture::BITSUSED_SIGNED)
		{
			//SoDebugError::postInfo("SoXipTexture::updateTexture", "Biasing with amount 0.5");
			glPixelTransferf(GL_RED_BIAS, 0.5f);
			glPixelTransferf(GL_GREEN_BIAS, 0.5f);
			glPixelTransferf(GL_BLUE_BIAS, 0.5f);
			glPixelTransferf(GL_ALPHA_BIAS, 0.5f);
			didBias = true;
		}
	}

	// actually uploads the texture in video memory
	switch (mTextureDimension)
	{
	case GL_TEXTURE_1D:
		if (dim != mTextureSize)
		{
			// texture size does not match image size: non power of two textures are not supported
			void *tmpBuffer = malloc(mTextureSize[0] * (formatIndex + 1));
			if (tmpBuffer)
			{
				gluScaleImage(baseFormats[formatIndex], dim[0], 1, GL_UNSIGNED_BYTE, imageBuffer,
					mTextureSize[0], 1, GL_UNSIGNED_BYTE, tmpBuffer);

				glTexSubImage1D(
					GL_TEXTURE_1D,
					0,
					0,
					mTextureSize[0],
					baseFormats[formatIndex],
					dataTypeInfo[mTextureDataType].type,
					tmpBuffer);

				free(tmpBuffer);
			}
		}
		else
		{
			if (mHasPBOs && usePBO.getValue())
			{
				glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mPBOId);
				glBufferData(GL_PIXEL_UNPACK_BUFFER, mPBOBufSize, NULL, GL_STREAM_DRAW);
				unsigned char *buf = (unsigned char*) glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);
				memcpy(buf, imageBuffer, mPBOBufSize);
				glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
				//glBufferSubData(GL_PIXEL_UNPACK_BUFFER, 0, mPBOBufSize, imageBuffer);
				glTexSubImage1D(GL_TEXTURE_1D, 0, 0, dim[0], baseFormats[formatIndex], dataTypeInfo[mTextureDataType].type, 0);
				glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
			}
			else
				glTexSubImage1D(
					GL_TEXTURE_1D,
					0,
					0,
					dim[0],
					baseFormats[formatIndex],
					dataTypeInfo[mTextureDataType].type,
					imageBuffer);
		}
		break;
	case GL_TEXTURE_2D:
		if (dim != mTextureSize)
		{
			// texture size does not match image size: non power of two textures are not supported
			void *tmpBuffer = malloc(mTextureSize[0] * mTextureSize[1] * (formatIndex + 1));
			if (tmpBuffer)
			{
				gluScaleImage(baseFormats[formatIndex], dim[0], dim[1], GL_UNSIGNED_BYTE, imageBuffer,
					mTextureSize[0], mTextureSize[1], GL_UNSIGNED_BYTE, tmpBuffer);

				glTexSubImage2D(
					GL_TEXTURE_2D,
					0,
					0,
					0,
					mTextureSize[0],
					mTextureSize[1],
					baseFormats[formatIndex],
					dataTypeInfo[mTextureDataType].type,
					tmpBuffer);

				free(tmpBuffer);
			}
		}
		else
		{
			if (mHasPBOs && usePBO.getValue())
			{
				glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mPBOId);				
				glBufferData(GL_PIXEL_UNPACK_BUFFER, mPBOBufSize, NULL, GL_STREAM_DRAW);
				unsigned char *buf = (unsigned char*) glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);
				memcpy(buf, imageBuffer, mPBOBufSize);
				glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
				//glBufferSubData(GL_PIXEL_UNPACK_BUFFER, 0, dim[0] * dim[1], imageBuffer);
				glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, dim[0], dim[1], baseFormats[formatIndex], dataTypeInfo[mTextureDataType].type, 0);
				glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
			}
			else
				glTexSubImage2D(
					GL_TEXTURE_2D,
					0,
					0,
					0,
					dim[0],
					dim[1],
					baseFormats[formatIndex],
					dataTypeInfo[mTextureDataType].type,
					imageBuffer);
		}
		break;
	case GL_TEXTURE_3D:
		{
//#ifdef WIN32 
//			if (!glTexSubImage3D)
//				glTexSubImage3D = (PFNGLTEXSUBIMAGE3DEXTPROC)xipGlGetProcAddress("glTexSubImage3DEXT");
//#endif // DARWIN
			if (glTexSubImage3D)
			{
				if (mHasPBOs && usePBO.getValue())
				{
					glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mPBOId);				
					glBufferData(GL_PIXEL_UNPACK_BUFFER, mPBOBufSize, NULL, GL_STREAM_DRAW);
					unsigned char *buf = (unsigned char*) glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);
					memcpy(buf, imageBuffer, mPBOBufSize);
					glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
					//glBufferSubData(GL_PIXEL_UNPACK_BUFFER, 0, mPBOBufSize, imageBuffer);
 					glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, 0, dim[0], dim[1], dim[2], baseFormats[formatIndex], dataTypeInfo[mTextureDataType].type, 0);
					glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
				}
				else
					glTexSubImage3D(
						GL_TEXTURE_3D,
						0,
						0,
						0,
						0,
						dim[0],
						dim[1],
						dim[2],
						baseFormats[formatIndex],
						dataTypeInfo[mTextureDataType].type,
						imageBuffer);
			}
			else
			{
				SoError::post("glTexImage3DEXT is not supported on this graphic card!");
			}
		}
		break;
	}

	image->unrefBufferPtr();

	// reset the scale and bias values
	if (didScale)
	{
		glPixelTransferf(GL_RED_SCALE, 1.0f);
		glPixelTransferf(GL_GREEN_SCALE, 1.0f);
		glPixelTransferf(GL_BLUE_SCALE, 1.0f);
		glPixelTransferf(GL_ALPHA_SCALE, 1.0f);
	}
	if (didBias)
	{
		glPixelTransferf(GL_RED_BIAS, 0.0f);
		glPixelTransferf(GL_GREEN_BIAS, 0.0f);
		glPixelTransferf(GL_BLUE_BIAS, 0.0f);
		glPixelTransferf(GL_ALPHA_BIAS, 0.0f);
	}
	// Restore alignement
	glPixelStorei(GL_UNPACK_ALIGNMENT, align);
}

/**
 *	Set the texture parameters
 */
void SoXipTexture::setTexParams()
{
	glTexParameteri(mTextureDimension, GL_TEXTURE_WRAP_S, wrapS.getValue());
	glTexParameteri(mTextureDimension, GL_TEXTURE_WRAP_T, wrapT.getValue());
	glTexParameteri(mTextureDimension, GL_TEXTURE_WRAP_R, wrapR.getValue());

	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor.getValue().getValue());

	glTexParameteri(mTextureDimension, GL_TEXTURE_MIN_FILTER, filter.getValue());
	glTexParameteri(mTextureDimension, GL_TEXTURE_MAG_FILTER, filter.getValue());
}

/**
 *	Set the environment
 */
void SoXipTexture::setTexEnv()
{
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, model.getValue());

	if (model.getValue() == GL_BLEND)
	{
		glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, blendColor.getValue().getValue());
	}
}

/**
 *	Enable texturing
 */
void SoXipTexture::enableTexture(SoState *state)
{
	if (mTextureDimension == GL_TEXTURE_2D) {
		SoGLTextureEnabledElement::set(state, TRUE);
	}
	//else {
	//	glEnable(mTextureDimension);
	//}
}

/**
 *	Open Inventor stuff
 */
void SoXipTexture::doAction(SoAction *action)
{
	SoState	*state = action->getState();

	if (!state)
		return;

	if (image.isIgnored() || SoTextureOverrideElement::getImageOverride(state))
		return;
	if (isOverride())
		SoTextureOverrideElement::setImageOverride(state, TRUE);
}

/**
 *	GLRender
 */
void SoXipTexture::GLRender(SoGLRenderAction *action)
{
	try
	{
		// TODO what does this do?
		//       doAction(action);

		if (mQueryExtensions)
		{
			const GLubyte* extensionsString = glGetString(GL_EXTENSIONS);
			mHasPBOs = (strstr((const char*) extensionsString, "GL_ARB_pixel_buffer_object") != 0);
			mPBOId = 0;
			if (mHasPBOs)
			{
/*#ifndef DARWIN
				INIT_EXT(PFNGLBINDBUFFERPROC,				glBindBuffer);
				INIT_EXT(PFNGLDELETEBUFFERSPROC,			glDeleteBuffers);
				INIT_EXT(PFNGLGENBUFFERSPROC,				glGenBuffers);
				INIT_EXT(PFNGLBUFFERDATAPROC,				glBufferData);
				INIT_EXT(PFNGLBUFFERSUBDATAPROC,			glBufferSubData);
				INIT_EXT(PFNGLMAPBUFFERPROC,				glMapBuffer);
				INIT_EXT(PFNGLUNMAPBUFFERPROC,				glUnmapBuffer);
#endif // DARWIN */
			}
			mQueryExtensions = false;
		}

		if (on.getValue())
		{
			bool imageNeedsRealloc = false;
			// track changed in connected image
			if (image.getValue())
			{
				if (mImageId != image.getValue()->getDataId())
				{
					mImageId = image.getValue()->getDataId();
					mImageHasChanged = true;
				}
			}
			else
			{
				if (mImageId) mImageHasChanged = true;
				mImageId = 0;
			}
#ifndef TGS_VERSION
			// if cache context changes, a new texture needs to be allocated
			if (mGLTexture)
			{
				if (static_cast<unsigned int>(mGLTexture->getContext()) != action->getCacheContext())
				{
					mImageHasChanged = true;
					imageNeedsRealloc = true;
				}
			}
#endif

			if (mImageHasChanged)
			{
				bool imageIsValid = validateImage();

				// check to see if we should update or create new or delete

				// if no new input image
				if (!imageIsValid)
				{
					// if there was an image
					if (mGLTexture != 0)
					{
						// delete
#ifdef TGS_VERSION
						deleteTexture();
#else
						deleteTexture(action);
#endif
						updateImage();
					}
				}
				// else new input image
				else
				{
					imageNeedsRealloc |= compareImage();

					// update image
					updateImage();

					// if texture cannot be reused
					if (imageNeedsRealloc)
					{
						// delete old texture if it exists
#ifdef TGS_VERSION
						if (mGLTexture)
							deleteTexture();
						// allocate new texture
						allocTexture();
#else
						if (mGLTexture)
							deleteTexture(action);
						// allocate new texture
						allocTexture(action);
#endif
						bindTexture(action->getState());
						createTexture();
						setTexParams();
						mParamHasChanged = false;
					}
					else {
						bindTexture(action->getState());
					}

					// update texture data
					updateTexture();
				}

				mImageHasChanged = false;
			}
			else
			{
				if (mGLTexture)
					bindTexture(action->getState());
			}
			if (mParamHasChanged)
			{
				if (mGLTexture)
					setTexParams();

				mParamHasChanged = false;
			}

			// set texture environment
			setTexEnv();

			if (mGLTexture)
			{
				// enable
				enableTexture(action->getState());
			}
		}
	}
	catch(...)
	{
		SoDebugError::postInfo( __FILE__, "Unknown Exception" );

		return;
	}

}

void SoXipTexture::paramHasChangedCB(void *data, SoSensor *s)
{
	((SoXipTexture*)data)->mParamHasChanged = true;
}

void SoXipTexture::textureInvalidCB(void *data, SoSensor *s)
{
	((SoXipTexture*)data)->mImageHasChanged = true;
}

SbBool SoXipTexture::hasNonPowerOfTwoExtensions() const
{
	// Certain video cards (ATI) support the extension but do not export the string
	if (forceNPOT.getValue())
		return true;

	const GLubyte* extensionsString = glGetString(GL_EXTENSIONS);
	return (strstr((const char*) extensionsString, "GL_ARB_texture_non_power_of_two") != 0);
}



