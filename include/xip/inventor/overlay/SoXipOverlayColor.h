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
/**
*	@file    SoXipOverlayColor.h
*	@brief   Declaration of the SoXipOverlayColor class
*	@author  Julien Gein
**/

#ifndef SOXIPOVERLAYCOLOR_H
#define SOXIPOVERLAYCOLOR_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFFloat.h>
#include <xip/inventor/overlay/xipivoverlay.h>

/**
*	@class SoXipOverlayColor
*
* Set the color of one or more overlay object that have the specified labels
*
**/
class XIPIVOVERLAY_API SoXipOverlayColor : public SoNode
{
	SO_NODE_HEADER( SoXipOverlayColor );

public:
	/// Constructor
	SoXipOverlayColor();

	/// color is applied to overlay with following label
	SoMFString		label;
	/// color
	SoSFColor		color;
	/// transparency
	SoSFFloat		transparency;

	/// Open Inventor class initialization
	static void initClass();

protected:
	/// Destructor
	~SoXipOverlayColor();	

	/// Rendering method
	virtual void GLRender( SoGLRenderAction* action );

};

#endif // SOXIPOVERLAYCOLOR_H
