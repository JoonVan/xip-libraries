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
#ifndef XIPIVEXTRA_H
#define XIPIVEXTRA_H

// use XIPIVEXTRAGL_API only for classes that are needed in other
// libraries

#ifdef WIN32
	#ifdef  XIPIVEXTRA_EXPORTS
		#define XIPIVEXTRA_API __declspec(dllexport)
	#else
		#define XIPIVEXTRA_API __declspec(dllimport)
	#endif
#else
	// no export needed for non-Windows platforms
	#define XIPIVEXTRA_API 
#endif

int XIPIVEXTRA_API xipivextra_init();

#endif // XIPIVEXTRA_H