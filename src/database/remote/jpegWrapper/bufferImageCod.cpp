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
#include <xip/inventor/remote/jpegWrapper/bufferImage.h>
#include <xip/inventor/remote/jpegWrapper/bufferImageJpeg.h>

/**
 * Encode the memory buffer to the Jpeg format format.
 * \param BuffObj: memory buffer 
 * \return true if is ok
 */
bool bufferImage::encodeBuffer(BuffObj *handledObj)
{
	bufferImageJPG newima;
	newima.copyPtr(this);
	if (newima.encodeBuffer(handledObj))
	{
		return true;
	} 
	else 
	{
		return false;
	}
	
		strcpy(info.Error,"encodeBuffer: Unknown format");
	return false;
}

/**
 * Decode the image from the memory buffer
 * \param buffer: memory buffer
 * \param size: size of buffer
 * \return true if is ok
 */
bool bufferImage::decodeBuffer(unsigned char * buffer, unsigned long size)
{
	MemoryObj file(buffer,size);
	return decodeBuffer(&file);
}

/**
 * Decode the image from BuffObj 
 * \param BuffObj: buffer object
 * \return true if is ok
 */
bool bufferImage::decodeBuffer(BuffObj *handledObj)
{
	bufferImageJPG newima;
	
	if (newima.decodeBuffer(handledObj)) 
	{ 
		 Transfer(newima); return true; 
	}
	
	if (newima.decodeBuffer(handledObj))
	{
		Transfer(newima);
		return true;
	} 
	else 
	{
		return false;
	}
	
	strcpy(info.Error,"decodeBuffer: Error");
	return false;
}
