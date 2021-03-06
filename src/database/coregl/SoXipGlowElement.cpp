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
#include <Inventor/errors/SoDebugError.h>
#include <xip/inventor/coregl/SoXipGlowElement.h>

//#ifdef WIN32
    //#define INIT_EXT(PF, F) F = (PF) xipGlGetProcAddress(#F)
//#elif defined(linux)
    //#define INIT_EXT(PF, F) F = (PF) xipGlGetProcAddress((const GLubyte*)#F)
//#endif //WIN32


bool GLOW_init = false;
bool GLOW_GREMEDY_string_marker = false;
bool GLOW_EXT_framebuffer_object = false;
bool GLOW_ARB_pixel_buffer_object = false;
bool GLOW_ARB_shader_objects = false;
bool GLOW_ARB_fragment_shader = false;
bool GLOW_EXT_geometry_shader4 = false;
bool GLOW_ARB_shading_language_100 = false;
bool GLOW_EXT_depth_bounds_test = false;
bool GLOW_ARB_texture_non_power_of_two = false;
bool GLOW_ARB_draw_buffers = false;
bool GLOW_EXT_timer_query = false;
bool GLOW_ARB_occlusion_query = false;

#ifndef WIN32
#ifndef DARWIN
#ifndef linux
PFNGLGETQUERYOBJECTI64VEXTPROC	glGetQueryObjecti64vEXT = 0;
PFNGLGETQUERYOBJECTUI64VEXTPROC	glGetQueryObjectui64vEXT = 0;
//#endif //linux
PFNGLGENQUERIESARBPROC			glGenQueriesARB = 0;
PFNGLDELETEQUERIESARBPROC		glDeleteQueriesARB = 0;
PFNGLBEGINQUERYARBPROC			glBeginQueryARB = 0;
PFNGLENDQUERYARBPROC			glEndQueryARB = 0;
PFNGLGETQUERYIVARBPROC			glGetQueryivARB = 0;
PFNGLGETQUERYOBJECTIVARBPROC	glGetQueryObjectivARB = 0;
PFNGLGETQUERYOBJECTUIVARBPROC	glGetQueryObjectuivARB = 0;

PFNGLTEXIMAGE3DEXTPROC				glTexImage3D = 0;
PFNGLTEXSUBIMAGE3DEXTPROC			glTexSubImage3D = 0;
PFNGLCOPYTEXSUBIMAGE3DPROC          glCopyTexSubImage3D = 0;
PFNGLACTIVETEXTUREPROC				glActiveTexture = 0;

PFNGLDRAWRANGEELEMENTSPROC			glDrawRangeElements = 0;
PFNGLDRAWBUFFERSPROC				glDrawBuffers = 0;
PFNGLBINDBUFFERPROC					glBindBuffer = 0;
PFNGLDELETEBUFFERSPROC				glDeleteBuffers = 0;
PFNGLGENBUFFERSPROC					glGenBuffers = 0;
PFNGLISBUFFERPROC					glIsBuffer = 0;
PFNGLBUFFERDATAPROC					glBufferData = 0;
PFNGLBUFFERSUBDATAPROC				glBufferSubData = 0;
PFNGLGETBUFFERSUBDATAPROC			glGetBufferSubData = 0;
PFNGLMAPBUFFERPROC					glMapBuffer = 0;
PFNGLUNMAPBUFFERPROC				glUnmapBuffer = 0;
PFNGLGETBUFFERPARAMETERIVPROC		glGetBufferParamateriv = 0;
PFNGLGETBUFFERPOINTERVPROC			glGetBufferPointerv = 0;

PFNGLATTACHSHADERPROC				glAttachShader = 0;
PFNGLBINDATTRIBLOCATIONPROC			glBindAttribLocation= 0;
PFNGLCOMPILESHADERPROC				glCompileShader= 0;
PFNGLCREATEPROGRAMPROC				glCreateProgram= 0;
PFNGLCREATESHADERPROC				glCreateShader= 0;
PFNGLDELETEPROGRAMPROC				glDeleteProgram= 0;
PFNGLDELETESHADERPROC				glDeleteShader= 0;
PFNGLDETACHSHADERPROC				glDetachShader= 0;
PFNGLDISABLEVERTEXATTRIBARRAYPROC	glDisableVertexAttribArray= 0;
PFNGLENABLEVERTEXATTRIBARRAYPROC	glEnableVertexAttribArray= 0;
PFNGLGETACTIVEATTRIBPROC			glGetActiveAttrib= 0;
PFNGLGETACTIVEUNIFORMPROC			glGetActiveUniform= 0;
PFNGLGETATTACHEDSHADERSPROC			glGetAttachedShaders= 0;
PFNGLGETATTRIBLOCATIONPROC			glGetAttribLocation= 0;
PFNGLGETPROGRAMIVPROC				glGetProgramiv= 0;
PFNGLGETPROGRAMINFOLOGPROC			glGetProgramInfoLog= 0;
PFNGLGETSHADERIVPROC				glGetShaderiv= 0;
PFNGLGETSHADERINFOLOGPROC			glGetShaderInfoLog= 0;
PFNGLGETSHADERSOURCEPROC			glGetShaderSource= 0;
PFNGLGETUNIFORMLOCATIONPROC			glGetUniformLocation= 0;
PFNGLGETUNIFORMFVPROC				glGetUniformfv= 0;
PFNGLGETUNIFORMIVPROC				glGetUniformiv= 0;
PFNGLGETVERTEXATTRIBDVPROC			glGetVertexAttribdv= 0;
PFNGLGETVERTEXATTRIBFVPROC			glGetVertexAttribfv= 0;
PFNGLGETVERTEXATTRIBIVPROC			glGetVertexAttribiv= 0;
PFNGLGETVERTEXATTRIBPOINTERVPROC	glGetVertexAttribPointerv= 0;
PFNGLISPROGRAMPROC					glIsProgram= 0;
PFNGLISSHADERPROC					glIsShader= 0;
PFNGLLINKPROGRAMPROC				glLinkProgram= 0;
PFNGLSHADERSOURCEPROC				glShaderSource= 0;
PFNGLUSEPROGRAMPROC					glUseProgram= 0;
PFNGLUNIFORM1FPROC					glUniform1f= 0;
PFNGLUNIFORM2FPROC					glUniform2f= 0;
PFNGLUNIFORM3FPROC					glUniform3f= 0;
PFNGLUNIFORM4FPROC					glUniform4f= 0;
PFNGLUNIFORM1IPROC					glUniform1i= 0;
PFNGLUNIFORM2IPROC					glUniform2i= 0;
PFNGLUNIFORM3IPROC					glUniform3i= 0;
PFNGLUNIFORM4IPROC					glUniform4i= 0;
PFNGLUNIFORM1FVPROC					glUniform1fv= 0;
PFNGLUNIFORM2FVPROC					glUniform2fv= 0;
PFNGLUNIFORM3FVPROC					glUniform3fv= 0;
PFNGLUNIFORM4FVPROC					glUniform4fv= 0;
PFNGLUNIFORM1IVPROC					glUniform1iv= 0;
PFNGLUNIFORM2IVPROC					glUniform2iv= 0;
PFNGLUNIFORM3IVPROC					glUniform3iv= 0;
PFNGLUNIFORM4IVPROC					glUniform4iv= 0;
PFNGLUNIFORMMATRIX2FVPROC			glUniformMatrix2fv= 0;	
PFNGLUNIFORMMATRIX3FVPROC			glUniformMatrix3fv= 0;	
PFNGLUNIFORMMATRIX4FVPROC			glUniformMatrix4fv= 0;
PFNGLVALIDATEPROGRAMPROC			glValidateProgram= 0;
PFNGLVERTEXATTRIB1DPROC				glVertexAttrib1d = 0;
PFNGLVERTEXATTRIB1DVPROC			glVertexAttrib1dv= 0;
PFNGLVERTEXATTRIB1FPROC				glVertexAttrib1f = 0;
PFNGLVERTEXATTRIB1FVPROC			glVertexAttrib1fv= 0;
PFNGLVERTEXATTRIB1SPROC				glVertexAttrib1s = 0;
PFNGLVERTEXATTRIB1SVPROC			glVertexAttrib1sv= 0;
PFNGLVERTEXATTRIB2DPROC				glVertexAttrib2d = 0;
PFNGLVERTEXATTRIB2DVPROC			glVertexAttrib2dv= 0;
PFNGLVERTEXATTRIB2FPROC				glVertexAttrib2f = 0;
PFNGLVERTEXATTRIB2FVPROC			glVertexAttrib2fv= 0;
PFNGLVERTEXATTRIB2SPROC				glVertexAttrib2s = 0;
PFNGLVERTEXATTRIB2SVPROC			glVertexAttrib2sv= 0;
PFNGLVERTEXATTRIB3DPROC				glVertexAttrib3d = 0;
PFNGLVERTEXATTRIB3DVPROC			glVertexAttrib3dv= 0;
PFNGLVERTEXATTRIB3FPROC				glVertexAttrib3f = 0;
PFNGLVERTEXATTRIB3FVPROC			glVertexAttrib3fv= 0;
PFNGLVERTEXATTRIB3SPROC				glVertexAttrib3s = 0;
PFNGLVERTEXATTRIB3SVPROC			glVertexAttrib3sv= 0;
PFNGLVERTEXATTRIB4NBVPROC			glVertexAttrib4Nbv= 0;
PFNGLVERTEXATTRIB4NIVPROC			glVertexAttrib4Niv= 0;
PFNGLVERTEXATTRIB4NSVPROC			glVertexAttrib4Nsv= 0;
PFNGLVERTEXATTRIB4NUBPROC			glVertexAttrib4Nub= 0;
PFNGLVERTEXATTRIB4NUBVPROC			glVertexAttrib4Nubv= 0;
PFNGLVERTEXATTRIB4NUIVPROC			glVertexAttrib4Nuiv= 0;
PFNGLVERTEXATTRIB4NUSVPROC			glVertexAttrib4Nusv= 0;
PFNGLVERTEXATTRIB4BVPROC			glVertexAttrib4bv= 0;
PFNGLVERTEXATTRIB4DPROC				glVertexAttrib4d= 0;
PFNGLVERTEXATTRIB4DVPROC			glVertexAttrib4dv= 0;
PFNGLVERTEXATTRIB4FPROC				glVertexAttrib4f= 0;
PFNGLVERTEXATTRIB4FVPROC			glVertexAttrib4fv= 0;
PFNGLVERTEXATTRIB4IVPROC			glVertexAttrib4iv= 0;
PFNGLVERTEXATTRIB4SPROC				glVertexAttrib4s= 0; 
PFNGLVERTEXATTRIB4SVPROC			glVertexAttrib4sv= 0; 
PFNGLVERTEXATTRIB4UBVPROC			glVertexAttrib4ubv= 0; 
PFNGLVERTEXATTRIB4UIVPROC			glVertexAttrib4uiv= 0;
PFNGLVERTEXATTRIB4USVPROC			glVertexAttrib4usv= 0;
PFNGLVERTEXATTRIBPOINTERPROC		glVertexAttribPointer= 0;

PFNGLISRENDERBUFFEREXTPROC						glIsRenderbufferEXT = 0;
PFNGLBINDRENDERBUFFEREXTPROC					glBindRenderbufferEXT = 0;
PFNGLDELETERENDERBUFFERSEXTPROC					glDeleteRenderbuffersEXT = 0;
PFNGLGENRENDERBUFFERSEXTPROC					glGenRenderbuffersEXT = 0;
PFNGLRENDERBUFFERSTORAGEEXTPROC					glRenderbufferStorageEXT = 0;
PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC			glGetRenderbufferParameterivEXT = 0;
PFNGLISFRAMEBUFFEREXTPROC						glIsFramebufferEXT = 0;
PFNGLBINDFRAMEBUFFEREXTPROC						glBindFramebufferEXT = 0;
PFNGLDELETEFRAMEBUFFERSEXTPROC					glDeleteFramebuffersEXT = 0;
PFNGLGENFRAMEBUFFERSEXTPROC						glGenFramebuffersEXT = 0;
PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC				glCheckFramebufferStatusEXT = 0;
PFNGLFRAMEBUFFERTEXTURE1DEXTPROC				glFramebufferTexture1DEXT = 0;
PFNGLFRAMEBUFFERTEXTURE2DEXTPROC				glFramebufferTexture2DEXT = 0;
PFNGLFRAMEBUFFERTEXTURE3DEXTPROC				glFramebufferTexture3DEXT = 0;
PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC				glFramebufferRenderbufferEXT = 0;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC	glGetFramebufferAttachmentParameterivEXT = 0;
PFNGLGENERATEMIPMAPEXTPROC						glGenerateMipmapEXT = 0;
PFNGLPROGRAMPARAMETERIEXTPROC					glProgramParameteriEXT = 0;
PFNGLFRAMEBUFFERTEXTUREEXTPROC					glFramebufferTextureEXT = 0;
PFNGLFRAMEBUFFERTEXTURELAYEREXTPROC				glFramebufferTextureLayerEXT = 0; 
PFNGLFRAMEBUFFERTEXTUREFACEEXTPROC				glFramebufferTextureFaceEXT = 0; 

PFNGLSTRINGMARKERGREMEDYPROC					glStringMarkerGREMEDY = 0;

PFNGLGETHANDLEARBPROC				glGetHandleARB = 0;

PFNGLBLENDEQUATIONEXTPROC			glBlendEquationEXT = 0;

PFNGLDEPTHBOUNDSEXTPROC				glDepthBoundsEXT = 0;
#endif //linux
#endif // DARWIN
#endif // WIN32


// FIXME: clean this up a bit and put bool flags in blocs with INIT_EXTs
void SoXipGLOW::init()
{
	if(GLOW_init)
		return;

	const unsigned char *str = glGetString(GL_EXTENSIONS);
	if (!str)
		return;

	GLOW_init = true;
	
	GLOW_GREMEDY_string_marker = strstr((const char *)str,			"GL_GREMEDY_string_marker") ? true : false;
	GLOW_EXT_framebuffer_object = strstr((const char *)str,			"GL_EXT_framebuffer_object") ? true : false;
	GLOW_ARB_pixel_buffer_object = strstr((const char *)str,		"GL_ARB_pixel_buffer_object") ? true : false;
	GLOW_ARB_shader_objects = strstr((const char *)str,				"GL_ARB_shader_objects") ? true : false;
	GLOW_ARB_fragment_shader = strstr((const char *)str,			"GL_ARB_fragment_shader") ? true : false;
	GLOW_EXT_geometry_shader4 = strstr((const char *)str,			"GL_EXT_geometry_shader4") ? true : false;
	GLOW_ARB_shading_language_100 = strstr((const char *)str,		"GL_ARB_shading_language_100") ? true : false;
	GLOW_EXT_depth_bounds_test = strstr((const char *)str,			"GL_EXT_depth_bounds_test") ? true : false;
	GLOW_ARB_texture_non_power_of_two = strstr((const char *)str,	"GL_ARB_texture_non_power_of_two") ? true : false;
	GLOW_ARB_draw_buffers = strstr((const char *)str,				"GL_ARB_draw_buffers") ? true : false;
	GLOW_EXT_timer_query = strstr((const char *)str,				"GL_EXT_timer_query") ? true : false;
	GLOW_ARB_occlusion_query = strstr((const char *)str,			"GL_ARB_occlusion_query") ? true : false;

//#if defined (__APPLE__) || defined(linux) || defined (WIN32)
    //init GLEW here ???
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
      // Problem: glewInit failed, something is seriously wrong.
      // TODO fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
//#endif

#ifndef WIN32
#ifndef DARWIN
#ifndef linux
	// Timer query
	INIT_EXT(PFNGLGETQUERYOBJECTI64VEXTPROC,	glGetQueryObjecti64vEXT);
	INIT_EXT(PFNGLGETQUERYOBJECTUI64VEXTPROC,	glGetQueryObjectui64vEXT);
	// Occlusion query
	INIT_EXT(PFNGLGENQUERIESARBPROC,		glGenQueriesARB);
//#endif //linux
	INIT_EXT(PFNGLDELETEQUERIESARBPROC,		glDeleteQueriesARB);
	INIT_EXT(PFNGLBEGINQUERYARBPROC,		glBeginQueryARB);
	INIT_EXT(PFNGLENDQUERYARBPROC,			glEndQueryARB);
	INIT_EXT(PFNGLGETQUERYIVARBPROC,		glGetQueryivARB);
	INIT_EXT(PFNGLGETQUERYOBJECTIVARBPROC,	glGetQueryObjectivARB);
	INIT_EXT(PFNGLGETQUERYOBJECTUIVARBPROC,	glGetQueryObjectuivARB);
				
	//3D texture
	INIT_EXT(PFNGLTEXIMAGE3DEXTPROC, glTexImage3D);
    INIT_EXT(PFNGLTEXSUBIMAGE3DEXTPROC, glTexSubImage3D);
	INIT_EXT(PFNGLCOPYTEXSUBIMAGE3DPROC, glCopyTexSubImage3D);

	// Depth bounds test
	INIT_EXT(PFNGLDEPTHBOUNDSEXTPROC, glDepthBoundsEXT);

	// Geometry Shader
	INIT_EXT(PFNGLPROGRAMPARAMETERIEXTPROC, glProgramParameteriEXT);
	INIT_EXT(PFNGLFRAMEBUFFERTEXTUREEXTPROC, glFramebufferTextureEXT);
	INIT_EXT(PFNGLFRAMEBUFFERTEXTURELAYEREXTPROC, glFramebufferTextureLayerEXT); 
	INIT_EXT(PFNGLFRAMEBUFFERTEXTUREFACEEXTPROC, glFramebufferTextureFaceEXT); 


	// Shader GL2.0 exts
	INIT_EXT(PFNGLATTACHSHADERPROC,				glAttachShader);
	INIT_EXT(PFNGLBINDATTRIBLOCATIONPROC,			glBindAttribLocation);
	INIT_EXT(PFNGLCOMPILESHADERPROC,				glCompileShader);
	INIT_EXT(PFNGLCREATEPROGRAMPROC,				glCreateProgram);
	INIT_EXT(PFNGLCREATESHADERPROC,				glCreateShader);
	INIT_EXT(PFNGLDELETEPROGRAMPROC,				glDeleteProgram);
	INIT_EXT(PFNGLDELETESHADERPROC,				glDeleteShader);
	INIT_EXT(PFNGLDETACHSHADERPROC,				glDetachShader);
	INIT_EXT(PFNGLDISABLEVERTEXATTRIBARRAYPROC,	glDisableVertexAttribArray);
	INIT_EXT(PFNGLENABLEVERTEXATTRIBARRAYPROC,	glEnableVertexAttribArray);
	INIT_EXT(PFNGLGETACTIVEATTRIBPROC,			glGetActiveAttrib);
	INIT_EXT(PFNGLGETACTIVEUNIFORMPROC,			glGetActiveUniform);
	INIT_EXT(PFNGLGETATTACHEDSHADERSPROC,			glGetAttachedShaders);
	INIT_EXT(PFNGLGETATTRIBLOCATIONPROC,			glGetAttribLocation);
	INIT_EXT(PFNGLGETPROGRAMIVPROC,				glGetProgramiv);
	INIT_EXT(PFNGLGETPROGRAMINFOLOGPROC,			glGetProgramInfoLog);
	INIT_EXT(PFNGLGETSHADERIVPROC,				glGetShaderiv);
	INIT_EXT(PFNGLGETSHADERINFOLOGPROC,			glGetShaderInfoLog);
	INIT_EXT(PFNGLGETSHADERSOURCEPROC,			glGetShaderSource);
	INIT_EXT(PFNGLGETUNIFORMLOCATIONPROC,			glGetUniformLocation);
	INIT_EXT(PFNGLGETUNIFORMFVPROC,				glGetUniformfv);
	INIT_EXT(PFNGLGETUNIFORMIVPROC,				glGetUniformiv);
	INIT_EXT(PFNGLGETVERTEXATTRIBDVPROC,			glGetVertexAttribdv);
	INIT_EXT(PFNGLGETVERTEXATTRIBFVPROC,			glGetVertexAttribfv);
	INIT_EXT(PFNGLGETVERTEXATTRIBIVPROC,			glGetVertexAttribiv);
	INIT_EXT(PFNGLGETVERTEXATTRIBPOINTERVPROC,	glGetVertexAttribPointerv);
	INIT_EXT(PFNGLISPROGRAMPROC,					glIsProgram);
	INIT_EXT(PFNGLISSHADERPROC,					glIsShader);
	INIT_EXT(PFNGLLINKPROGRAMPROC,				glLinkProgram);
	INIT_EXT(PFNGLSHADERSOURCEPROC,				glShaderSource);
	INIT_EXT(PFNGLUSEPROGRAMPROC,					glUseProgram);
	INIT_EXT(PFNGLUNIFORM1FPROC,					glUniform1f);
	INIT_EXT(PFNGLUNIFORM2FPROC,					glUniform2f);
	INIT_EXT(PFNGLUNIFORM3FPROC,					glUniform3f);
	INIT_EXT(PFNGLUNIFORM4FPROC,					glUniform4f);
	INIT_EXT(PFNGLUNIFORM1IPROC,					glUniform1i);
	INIT_EXT(PFNGLUNIFORM2IPROC,					glUniform2i);
	INIT_EXT(PFNGLUNIFORM3IPROC,					glUniform3i);
	INIT_EXT(PFNGLUNIFORM4IPROC,					glUniform4i);
	INIT_EXT(PFNGLUNIFORM1FVPROC,					glUniform1fv);
	INIT_EXT(PFNGLUNIFORM2FVPROC,					glUniform2fv);
	INIT_EXT(PFNGLUNIFORM3FVPROC,					glUniform3fv);
	INIT_EXT(PFNGLUNIFORM4FVPROC,					glUniform4fv);
	INIT_EXT(PFNGLUNIFORM1IVPROC,					glUniform1iv);
	INIT_EXT(PFNGLUNIFORM2IVPROC,					glUniform2iv);
	INIT_EXT(PFNGLUNIFORM3IVPROC,					glUniform3iv);
	INIT_EXT(PFNGLUNIFORM4IVPROC,					glUniform4iv);
	INIT_EXT(PFNGLUNIFORMMATRIX2FVPROC,			glUniformMatrix2fv);	
	INIT_EXT(PFNGLUNIFORMMATRIX3FVPROC,			glUniformMatrix3fv);	
	INIT_EXT(PFNGLUNIFORMMATRIX4FVPROC,			glUniformMatrix4fv);
	INIT_EXT(PFNGLVALIDATEPROGRAMPROC,			glValidateProgram);
	INIT_EXT(PFNGLVERTEXATTRIB1DPROC,				glVertexAttrib1d);
	INIT_EXT(PFNGLVERTEXATTRIB1DVPROC,			glVertexAttrib1dv);
	INIT_EXT(PFNGLVERTEXATTRIB1FPROC,				glVertexAttrib1f);
	INIT_EXT(PFNGLVERTEXATTRIB1FVPROC,			glVertexAttrib1fv);
	INIT_EXT(PFNGLVERTEXATTRIB1SPROC,				glVertexAttrib1s);
	INIT_EXT(PFNGLVERTEXATTRIB1SVPROC,			glVertexAttrib1sv);
	INIT_EXT(PFNGLVERTEXATTRIB2DPROC,				glVertexAttrib2d);
	INIT_EXT(PFNGLVERTEXATTRIB2DVPROC,			glVertexAttrib2dv);
	INIT_EXT(PFNGLVERTEXATTRIB2FPROC,				glVertexAttrib2f);
	INIT_EXT(PFNGLVERTEXATTRIB2FVPROC,			glVertexAttrib2fv);
	INIT_EXT(PFNGLVERTEXATTRIB2SPROC,				glVertexAttrib2s);
	INIT_EXT(PFNGLVERTEXATTRIB2SVPROC,			glVertexAttrib2sv);
	INIT_EXT(PFNGLVERTEXATTRIB3DPROC,				glVertexAttrib3d);
	INIT_EXT(PFNGLVERTEXATTRIB3DVPROC,			glVertexAttrib3dv);
	INIT_EXT(PFNGLVERTEXATTRIB3FPROC,				glVertexAttrib3f);
	INIT_EXT(PFNGLVERTEXATTRIB3FVPROC,			glVertexAttrib3fv);
	INIT_EXT(PFNGLVERTEXATTRIB3SPROC,				glVertexAttrib3s);
	INIT_EXT(PFNGLVERTEXATTRIB3SVPROC,			glVertexAttrib3sv);
	INIT_EXT(PFNGLVERTEXATTRIB4NBVPROC,			glVertexAttrib4Nbv);
	INIT_EXT(PFNGLVERTEXATTRIB4NIVPROC,			glVertexAttrib4Niv);
	INIT_EXT(PFNGLVERTEXATTRIB4NSVPROC,			glVertexAttrib4Nsv);
	INIT_EXT(PFNGLVERTEXATTRIB4NUBPROC,			glVertexAttrib4Nub);
	INIT_EXT(PFNGLVERTEXATTRIB4NUBVPROC,			glVertexAttrib4Nubv);
	INIT_EXT(PFNGLVERTEXATTRIB4NUIVPROC,			glVertexAttrib4Nuiv);
	INIT_EXT(PFNGLVERTEXATTRIB4NUSVPROC,			glVertexAttrib4Nusv);
	INIT_EXT(PFNGLVERTEXATTRIB4BVPROC,			glVertexAttrib4bv);
	INIT_EXT(PFNGLVERTEXATTRIB4DPROC,				glVertexAttrib4d);
	INIT_EXT(PFNGLVERTEXATTRIB4DVPROC,			glVertexAttrib4dv);
	INIT_EXT(PFNGLVERTEXATTRIB4FPROC,				glVertexAttrib4f);
	INIT_EXT(PFNGLVERTEXATTRIB4FVPROC,			glVertexAttrib4fv);
	INIT_EXT(PFNGLVERTEXATTRIB4IVPROC,			glVertexAttrib4iv);
	INIT_EXT(PFNGLVERTEXATTRIB4SPROC,				glVertexAttrib4s); 
	INIT_EXT(PFNGLVERTEXATTRIB4SVPROC,			glVertexAttrib4sv); 
	INIT_EXT(PFNGLVERTEXATTRIB4UBVPROC,			glVertexAttrib4ubv); 
	INIT_EXT(PFNGLVERTEXATTRIB4UIVPROC,			glVertexAttrib4uiv);
	INIT_EXT(PFNGLVERTEXATTRIB4USVPROC,			glVertexAttrib4usv);
	INIT_EXT(PFNGLVERTEXATTRIBPOINTERPROC,		glVertexAttribPointer);

	INIT_EXT(PFNGLGETHANDLEARBPROC,				glGetHandleARB);
	INIT_EXT(PFNGLBLENDEQUATIONEXTPROC,			glBlendEquationEXT);
	INIT_EXT(PFNGLACTIVETEXTUREPROC,			glActiveTexture);

	// FBO exts
	INIT_EXT(PFNGLISRENDERBUFFEREXTPROC, glIsRenderbufferEXT);
	INIT_EXT(PFNGLBINDRENDERBUFFEREXTPROC, glBindRenderbufferEXT);
	INIT_EXT(PFNGLDELETERENDERBUFFERSEXTPROC, glDeleteRenderbuffersEXT);
	INIT_EXT(PFNGLGENRENDERBUFFERSEXTPROC, glGenRenderbuffersEXT);
	INIT_EXT(PFNGLRENDERBUFFERSTORAGEEXTPROC, glRenderbufferStorageEXT);
	INIT_EXT(PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC, glGetRenderbufferParameterivEXT);
	INIT_EXT(PFNGLISFRAMEBUFFEREXTPROC, glIsFramebufferEXT);
	INIT_EXT(PFNGLBINDFRAMEBUFFEREXTPROC, glBindFramebufferEXT);
	INIT_EXT(PFNGLDELETEFRAMEBUFFERSEXTPROC, glDeleteFramebuffersEXT);
	INIT_EXT(PFNGLGENFRAMEBUFFERSEXTPROC, glGenFramebuffersEXT);
	INIT_EXT(PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC, glCheckFramebufferStatusEXT);
	INIT_EXT(PFNGLFRAMEBUFFERTEXTURE1DEXTPROC, glFramebufferTexture1DEXT);
	INIT_EXT(PFNGLFRAMEBUFFERTEXTURE2DEXTPROC, glFramebufferTexture2DEXT);
	INIT_EXT(PFNGLFRAMEBUFFERTEXTURE3DEXTPROC, glFramebufferTexture3DEXT);
	INIT_EXT(PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC, glFramebufferRenderbufferEXT);
	INIT_EXT(PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC, glGetFramebufferAttachmentParameterivEXT);
	INIT_EXT(PFNGLGENERATEMIPMAPEXTPROC, glGenerateMipmapEXT);

	// gdebugger ext
	INIT_EXT(PFNGLSTRINGMARKERGREMEDYPROC, glStringMarkerGREMEDY);

	// PBOs
    INIT_EXT(PFNGLDRAWRANGEELEMENTSPROC,			glDrawRangeElements);
	INIT_EXT(PFNGLDRAWBUFFERSPROC,					glDrawBuffers);
	INIT_EXT(PFNGLBINDBUFFERPROC,					glBindBuffer);
	INIT_EXT(PFNGLDELETEBUFFERSPROC,				glDeleteBuffers);
	INIT_EXT(PFNGLGENBUFFERSPROC,					glGenBuffers);
	INIT_EXT(PFNGLISBUFFERPROC,					glIsBuffer);
	INIT_EXT(PFNGLBUFFERDATAPROC,					glBufferData);
	INIT_EXT(PFNGLBUFFERSUBDATAPROC,				glBufferSubData);
	INIT_EXT(PFNGLGETBUFFERSUBDATAPROC,			glGetBufferSubData);
	INIT_EXT(PFNGLMAPBUFFERPROC,					glMapBuffer);
	INIT_EXT(PFNGLUNMAPBUFFERPROC,				glUnmapBuffer);
	INIT_EXT(PFNGLGETBUFFERPARAMETERIVPROC,		glGetBufferParamateriv);
	INIT_EXT(PFNGLGETBUFFERPOINTERVPROC,			glGetBufferPointerv);
#endif // linux
#endif // DARWIN
#endif // WIN32
	
}


int	getPackAlignment(int width)
{
	if (!(width % 8))
		return 8;
	else if (!(width % 4))
		return 4;
	else if (!(width % 2))
		return 2;
	else
		return 1;
}

SO_ELEMENT_SOURCE(SoXipGLOWElement);


void SoXipGLOWElement::initClass()
{
	SO_ELEMENT_INIT_CLASS(SoXipGLOWElement, SoElement);
}

void SoXipGLOWElement::init(SoState *state)
{
	SoXipGLOW::init();
}


