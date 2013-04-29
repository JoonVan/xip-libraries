/*
 *
 *  Copyright (C) 2000 Silicon Graphics, Inc.  All Rights Reserved. 
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  Further, this software is distributed without any warranty that it is
 *  free of the rightful claim of any third person regarding infringement
 *  or the like.  Any license provided herein, whether implied or
 *  otherwise, applies only to this software file.  Patent licenses, if
 *  any, provided herein do not apply to combinations of this program with
 *  other software, or any other product whatsoever.
 * 
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,
 *  Mountain View, CA  94043, or:
 * 
 *  http://www.sgi.com 
 * 
 *  For further information regarding this notice, see: 
 * 
 *  http://oss.sgi.com/projects/GenInfo/NoticeExplan/
 *
 */

/*
 * Copyright (C) 1990,91,92   Silicon Graphics, Inc.
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 1.1.1.1 $
 |
 |   Classes:
 |	SoV1Text2
 |
 |   Author(s)		: Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#include "SoV1Text2.h"
#include <Inventor/nodes/SoText2.h>

#include <iconv.h>
#include <errno.h>


SO_NODE_SOURCE(SoV1Text2);


////////////////////////////////////////////////////////////////////////
//
// Description:
//    Default constructor
//
// Use: public

SoV1Text2::SoV1Text2()
//
////////////////////////////////////////////////////////////////////////
{
    SO_NODE_CONSTRUCTOR(SoV1Text2);

    SO_NODE_ADD_FIELD(string,	(""));
    SO_NODE_ADD_FIELD(spacing,	(1.0));
    SO_NODE_ADD_FIELD(justification,	(LEFT));

    // Set up static info for enumerated type field
    SO_NODE_DEFINE_ENUM_VALUE(Justification,	LEFT);
    SO_NODE_DEFINE_ENUM_VALUE(Justification,	RIGHT);
    SO_NODE_DEFINE_ENUM_VALUE(Justification,	CENTER);

    // Set up info in enumerated type field
    SO_NODE_SET_SF_ENUM_TYPE(justification, Justification);
    
    isBuiltIn = TRUE;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Destructor.
//
// Use: private

SoV1Text2::~SoV1Text2()
//
////////////////////////////////////////////////////////////////////////
{
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Create a version 2.0 SoText2.
//
// Use: private

SoNode *
SoV1Text2::createNewNode()
//
////////////////////////////////////////////////////////////////////////
{
    SoText2 *result = SO_UPGRADER_CREATE_NEW(SoText2);


    // if european characters present they are converted to UTF-8
    for (int i = 0; i < string.getNum(); i++) {
	result->string.set1Value(i, *convertToUTF8(string[i]));
    }
    result->spacing.setValue(spacing.getValue());
    result->justification.setValue(justification.getValue());

    return result;
}

static iconv_t codeConvert1 = NULL;
static iconv_t codeConvert2 = NULL;

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Convert a string to UTF-8.  If it's ascii, leave it alone.
//    otherwise assume it's ISO-8859-1 (Western European)
//
// Use: static, public 

const SbString*
SoV1Text2::convertToUTF8(const SbString &strng)
//
////////////////////////////////////////////////////////////////////////
{
    const char* str = strng.getString();
    SbBool ascii = TRUE;
    for (int i= 0; i< strng.getLength(); i++){
	if ( str[i]& 0x80) {
	    ascii = FALSE;
	    break;
	}
    }
    if (ascii) return &strng;
    
    //Do a conversion first to UCS-2, then UTF-8.  That's because
    //not all Irix systems have  iconv conversion table to go
    //directly to UTF-8
    
    if( codeConvert1 == NULL){    
	codeConvert1 = iconv_open("UCS-2", "ISO8859-1");
	codeConvert2 = iconv_open("UTF-8", "UCS-2");
#ifdef DEBUG	
	if ( codeConvert1 == (iconv_t)-1 ){
	    SoDebugError::post("SoV1Text2::convertToUTF8", 
		"Invalid ISO8859-1 to UCS-2 conversion");
	}
	if ( codeConvert2 == (iconv_t)-1 ){
	    SoDebugError::post("SoV1Text2::convertToUTF8", 
		"Invalid UCS-2 to UTF-8 conversion");
	}
#endif /*DEBUG*/
    }
    // allocate a sufficiently large buffer:
    char * UCSBuf = new char[2*strng.getLength()+1];
    char * UTFBuf = new char[2*strng.getLength()+1];
    
    char* input = (char *)strng.getString();
    size_t inbytes = strng.getLength();
    size_t outbytes = 2*inbytes;
    char* output = (char*)UCSBuf;    
#if defined(WIN32) || defined(DARWIN)
    if ((iconv(codeConvert1, const_cast<const char**>(&input), &inbytes, &output, &outbytes) != NULL)){
#else
    if ((iconv(codeConvert1, &input, &inbytes, &output, &outbytes) != NULL)){
#endif
#ifdef DEBUG
	SoDebugError::post("SoV1Text2::convertToUTF8", 
	    "Error converting text to UCS-2");
#endif /*DEBUG*/ 
    }	
    input = (char *)UCSBuf;
    outbytes = 2*strng.getLength()+1;
    inbytes = 2*strng.getLength();
    output = (char*)UTFBuf;    
#if defined(WIN32) || defined(DARWIN)
    if ((iconv(codeConvert2, const_cast<const char**>(&input), &inbytes, &output, &outbytes) != 0)){
#else
    if ((iconv(codeConvert2, &input, &inbytes, &output, &outbytes) != 0)){
#endif
#ifdef DEBUG
	switch(errno){
	    case EILSEQ:  printf("EILSEQ\n");
			    break;
	    case EINVAL:  printf("EINVAL\n");
			    break;
	    case E2BIG:	printf("E2BIG\n");
			    break;
	    default:	printf("errno %d\n", errno);
	}
	SoDebugError::post("SoV1Text2::convertToUTF8", 
	    "Error converting text to UTF-8");
       
#endif /*DEBUG*/ 
    }
    
    delete [] UCSBuf;
    SbString* str1 = new SbString(UTFBuf, 0, 2*strng.getLength()-outbytes);    
    return (str1);         
}