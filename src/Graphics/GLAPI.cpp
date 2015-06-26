#include <GL/glext.h>
#include <OS.hpp>
#include <SDL2/SDL_video.h>

PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLDELETEBUFFERSPROC glDeleteBuffers;
PFNGLBUFFERDATAPROC glBufferData;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLCREATESHADERPROC glCreateShader;
PFNGLUSEPROGRAMPROC glUseProgram;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
PFNGLGETSHADERIVPROC glGetShaderiv;
PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLATTACHSHADERPROC glAttachShader;
PFNGLBINDFRAGDATALOCATIONPROC glBindFragDataLocation;
PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLDELETEPROGRAMPROC glDeleteProgram;
PFNGLDELETESHADERPROC glDeleteShader;
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
PFNGLUNIFORM1FVPROC glUniform1fv;
PFNGLUNIFORM2FVPROC glUniform2fv;
PFNGLUNIFORM3FVPROC glUniform3fv;
PFNGLUNIFORM4FVPROC glUniform4fv;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
PFNGLUNIFORM1IVPROC glUniform1iv;
PFNGLUNIFORM1FPROC glUniform1f;
PFNGLGETPROGRAMIVPROC glGetProgramiv;
PFNGLGENERATEMIPMAPPROC glGenerateMipmap;

void GLAPI_load() {

	glGenBuffers = (PFNGLGENBUFFERSPROC)SDL_GL_GetProcAddress("glGenBuffers");

	if(!glGenBuffers)
		 OS::get()->Log("[GLAPI_load()] Error getting address of glGenBuffers\n");

	glBindBuffer = (PFNGLBINDBUFFERPROC)SDL_GL_GetProcAddress("glBindBuffer");

	if(!glBindBuffer)
		 OS::get()->Log("[GLAPI_load()] Error getting address of glBindBuffer\n");

	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)SDL_GL_GetProcAddress("glDeleteBuffers");

	if(!glDeleteBuffers)
		 OS::get()->Log("[GLAPI_load()] Error getting address of glDeleteBuffers\n");

	glBufferData = (PFNGLBUFFERDATAPROC)SDL_GL_GetProcAddress("glBufferData");

	if(!glBufferData)
		 OS::get()->Log("[GLAPI_load()] Error getting address of glBufferData\n");

	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)SDL_GL_GetProcAddress("glGenVertexArrays");

	if(!glGenVertexArrays)
		 OS::get()->Log("[GLAPI_load()] Error getting address of glGenVertexArrays\n");

	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)SDL_GL_GetProcAddress("glBindVertexArray");

	if(!glBindVertexArray)
		 OS::get()->Log("[GLAPI_load()] Error getting address of glBindVertexArray\n");

	glShaderSource = (PFNGLSHADERSOURCEPROC)SDL_GL_GetProcAddress("glShaderSource");

	if(!glShaderSource)
		 OS::get()->Log("[GLAPI_load()] Error getting address of glShaderSource\n");

	glCompileShader = (PFNGLCOMPILESHADERPROC)SDL_GL_GetProcAddress("glCompileShader");

	if(!glCompileShader)
		 OS::get()->Log("[GLAPI_load()] Error getting address of glCompileShader\n");

	glCreateShader = (PFNGLCREATESHADERPROC)SDL_GL_GetProcAddress("glCreateShader");

	if(!glCreateShader)
		 OS::get()->Log("[GLAPI_load()] Error getting address of glCreateShader\n");

	glUseProgram = (PFNGLUSEPROGRAMPROC)SDL_GL_GetProcAddress("glUseProgram");

	if(!glUseProgram)
		 OS::get()->Log("[GLAPI_load()] Error getting address of glUseProgram\n");

	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)SDL_GL_GetProcAddress("glVertexAttribPointer");

	if(!glVertexAttribPointer)
		 OS::get()->Log("[GLAPI_load()] Error getting address of glVertexAttribPointer\n");

	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)SDL_GL_GetProcAddress("glEnableVertexAttribArray");

	if(!glEnableVertexAttribArray)
		 OS::get()->Log("[GLAPI_load()] Error getting address of glEnableVertexAttribArray\n");

	glGetShaderiv = (PFNGLGETSHADERIVPROC)SDL_GL_GetProcAddress("glGetShaderiv");

	if(!glGetShaderiv)
		 OS::get()->Log("[GLAPI_load()] Error getting address of glGetShaderiv\n");

	glCreateProgram = (PFNGLCREATEPROGRAMPROC)SDL_GL_GetProcAddress("glCreateProgram");

	if(!glCreateProgram)
		 OS::get()->Log("[GLAPI_load()] Error getting address of glCreateProgram\n");

	glAttachShader = (PFNGLATTACHSHADERPROC)SDL_GL_GetProcAddress("glAttachShader");

	if(!glAttachShader)
		 OS::get()->Log("[GLAPI_load()] Error getting address of glAttachShader\n");

	glBindFragDataLocation = (PFNGLBINDFRAGDATALOCATIONPROC)SDL_GL_GetProcAddress("glBindFragDataLocation");

	if(!glBindFragDataLocation)
		 OS::get()->Log("[GLAPI_load()] Error getting address of glBindFragDataLocation\n");

	glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)SDL_GL_GetProcAddress("glBindAttribLocation");

	if(!glBindAttribLocation)
		 OS::get()->Log("[GLAPI_load()] Error getting address of glBindAttribLocation\n");

	glLinkProgram = (PFNGLLINKPROGRAMPROC)SDL_GL_GetProcAddress("glLinkProgram");

	if(!glLinkProgram)
		 OS::get()->Log("[GLAPI_load()] Error getting address of glLinkProgram\n");

	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)SDL_GL_GetProcAddress("glDeleteProgram");

	if(!glDeleteProgram)
		 OS::get()->Log("[GLAPI_load()] Error getting address of glDeleteProgram\n");

	glDeleteShader = (PFNGLDELETESHADERPROC)SDL_GL_GetProcAddress("glDeleteShader");

	if(!glDeleteShader)
		 OS::get()->Log("[GLAPI_load()] Error getting address of glDeleteShader\n");

	glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)SDL_GL_GetProcAddress("glGetAttribLocation");

	if(!glGetAttribLocation)
		 OS::get()->Log("[GLAPI_load()] Error getting address of glGetAttribLocation\n");

	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)SDL_GL_GetProcAddress("glGetShaderInfoLog");

	if(!glGetShaderInfoLog)
		 OS::get()->Log("[GLAPI_load()] Error getting address of glGetShaderInfoLog\n");

	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)SDL_GL_GetProcAddress("glGetProgramInfoLog");

	if(!glGetProgramInfoLog)
		 OS::get()->Log("[GLAPI_load()] Error getting address of glGetProgramInfoLog\n");

	glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)SDL_GL_GetProcAddress("glDisableVertexAttribArray");

	if(!glDisableVertexAttribArray)
		 OS::get()->Log("[GLAPI_load()] Error getting address of glDisableVertexAttribArray\n");

	glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)SDL_GL_GetProcAddress("glDeleteVertexArrays");

	if(!glDeleteVertexArrays)
		 OS::get()->Log("[GLAPI_load()] Error getting address of glDeleteVertexArrays\n");

	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)SDL_GL_GetProcAddress("glGetUniformLocation");

	if(!glGetUniformLocation)
		 OS::get()->Log("[GLAPI_load()] Error getting address of glGetUniformLocation\n");

	glUniform1fv = (PFNGLUNIFORM1FVPROC)SDL_GL_GetProcAddress("glUniform1fv");

	if(!glUniform1fv)
		 OS::get()->Log("[GLAPI_load()] Error getting address of glUniform1fv\n");

	glUniform2fv = (PFNGLUNIFORM2FVPROC)SDL_GL_GetProcAddress("glUniform2fv");

	if(!glUniform2fv)
		 OS::get()->Log("[GLAPI_load()] Error getting address of glUniform2fv\n");

	glUniform3fv = (PFNGLUNIFORM3FVPROC)SDL_GL_GetProcAddress("glUniform3fv");

	if(!glUniform3fv)
		 OS::get()->Log("[GLAPI_load()] Error getting address of glUniform3fv\n");

	glUniform4fv = (PFNGLUNIFORM4FVPROC)SDL_GL_GetProcAddress("glUniform4fv");

	if(!glUniform4fv)
		 OS::get()->Log("[GLAPI_load()] Error getting address of glUniform4fv\n");

	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)SDL_GL_GetProcAddress("glUniformMatrix4fv");

	if(!glUniformMatrix4fv)
		 OS::get()->Log("[GLAPI_load()] Error getting address of glUniformMatrix4fv\n");

	glUniform1iv = (PFNGLUNIFORM1IVPROC)SDL_GL_GetProcAddress("glUniform1iv");

	if(!glUniform1iv)
		 OS::get()->Log("[GLAPI_load()] Error getting address of glUniform1iv\n");

	glUniform1f = (PFNGLUNIFORM1FPROC)SDL_GL_GetProcAddress("glUniform1f");

	if(!glUniform1f)
		 OS::get()->Log("[GLAPI_load()] Error getting address of glUniform1f\n");

	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)SDL_GL_GetProcAddress("glGetProgramiv");

	if(!glGetProgramiv)
		 OS::get()->Log("[GLAPI_load()] Error getting address of glGetProgramiv\n");

	glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)SDL_GL_GetProcAddress("glGenerateMipmap");

	if(!glGenerateMipmap)
		 OS::get()->Log("[GLAPI_load()] Error getting address of glGenerateMipmap\n");

}
