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

/* author Sylvain Jaume, Julien Gein */

#ifndef SO_ITK_SIMPLEFUZZYCONNECTEDNESSSCALARIMAGEFILTER_H_
# define SO_ITK_SIMPLEFUZZYCONNECTEDNESSSCALARIMAGEFILTER_H_

# include <Inventor/fields/SoSFFloat.h>
# include "SoItkSimpleFuzzyConnectednessImageFilterBase.h"

class XIPIVITK_API SoItkSimpleFuzzyConnectednessScalarImageFilter : public SoItkSimpleFuzzyConnectednessImageFilterBase
{
	SO_ENGINE_HEADER( SimpleFuzzyConnectednessScalarImageFilter );

public:
	SoItkSimpleFuzzyConnectednessScalarImageFilter();

	SoSFFloat Mean;
	SoSFFloat Diff_Variance;
	SoSFFloat Diff_Mean;
	SoSFFloat Variance;
	
	static void initClass();

protected:
	~SoItkSimpleFuzzyConnectednessScalarImageFilter();

	virtual bool checkInput();
	virtual void evaluate();

};

#endif // SO_ITK_SIMPLEFUZZYCONNECTEDNESSSCALARIMAGEFILTER_H_
