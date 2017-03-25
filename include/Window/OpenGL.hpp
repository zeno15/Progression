#ifndef INCLUDED_WINDOW_OPEN_GL_HPP_
#define INCLUDED_WINDOW_OPEN_GL_HPP_

#include <Window/OpenGLDefinitions.hpp>


typedef HGLRC(WINAPI * PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC, HGLRC, const int *);

typedef GLuint(GLAPIENTRY * PFNGLCREATEPROGRAMPROC) (void);
typedef GLuint(GLAPIENTRY * PFNGLCREATESHADERPROC) (GLenum);
typedef void (GLAPIENTRY * PFNGLSHADERSOURCEPROC) (GLuint, GLsizei, const GLchar *const*, const GLint *);
typedef void (GLAPIENTRY * PFNGLCOMPILESHADERPROC) (GLuint);
typedef void (GLAPIENTRY * PFNGLGETSHADERINFOLOGPROC) (GLuint, GLsizei, GLsizei *, GLchar *);
typedef void (GLAPIENTRY * PFNGLGETSHADERIVPROC) (GLuint, GLenum, GLint *);
typedef void (GLAPIENTRY * PFNGLATTACHSHADERPROC) (GLuint, GLuint);
typedef void (GLAPIENTRY * PFNGLLINKPROGRAMPROC) (GLuint);
typedef void (GLAPIENTRY * PFNGLGETPROGRAMIVPROC) (GLuint, GLenum, GLint *);
typedef void (GLAPIENTRY * PFNGLGETPROGRAMINFOLOGPROC) (GLuint, GLsizei, GLsizei *, GLchar *);
typedef void (GLAPIENTRY * PFNGLDELETESHADERPROC) (GLuint);
typedef GLint(GLAPIENTRY * PFNGLGETUNIFORMLOCATIONPROC) (GLuint, const GLchar *);

typedef void (GLAPIENTRY * PFNGLUNIFORM1FPROC) (GLint, GLfloat);
typedef void (GLAPIENTRY * PFNGLUNIFORM2FPROC) (GLint, GLfloat, GLfloat);
typedef void (GLAPIENTRY * PFNGLUNIFORM3FPROC) (GLint, GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY * PFNGLUNIFORM4FPROC) (GLint, GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY * PFNGLUNIFORM1IPROC) (GLint, GLint);
typedef void (GLAPIENTRY * PFNGLUNIFORM2IPROC) (GLint, GLint, GLint);
typedef void (GLAPIENTRY * PFNGLUNIFORM3IPROC) (GLint, GLint, GLint, GLint);
typedef void (GLAPIENTRY * PFNGLUNIFORM4IPROC) (GLint, GLint, GLint, GLint, GLint);
typedef void (GLAPIENTRY * PFNGLUNIFORMMATRIX2FVPROC) (GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (GLAPIENTRY * PFNGLUNIFORMMATRIX3FVPROC) (GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (GLAPIENTRY * PFNGLUNIFORMMATRIX4FVPROC) (GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (GLAPIENTRY * PFNGLGENVERTEXARRAYSPROC) (GLsizei, GLuint *);
typedef void (GLAPIENTRY * PFNGLBINDVERTEXARRAYPROC) (GLuint);
typedef void (GLAPIENTRY * PFNGLGENBUFFERSPROC) (GLsizei, GLuint *);
typedef void (GLAPIENTRY * PFNGLBINDBUFFERPROC) (GLenum, GLuint);
typedef void (GLAPIENTRY * PFNGLBUFFERDATAPROC) (GLenum, GLsizeiptr, const void *, GLenum);
typedef void (GLAPIENTRY * PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint);
typedef void (GLAPIENTRY * PFNGLVERTEXATTRIBPOINTERPROC) (GLuint, GLint, GLenum , GLboolean, GLsizei, const void *); 
typedef void (GLAPIENTRY * PFNGLDISABLEVERTEXATTRIBARRAYPROC) (GLuint);
typedef void (GLAPIENTRY * PFNGLUSEPROGRAMPROC) (GLuint);
typedef void (GLAPIENTRY * PFNGLACTIVETEXTUREPROC) (GLenum);
typedef void (GLAPIENTRY * PFNGLDELETEBUFFERSARBPROC) (GLsizei n, const GLuint *buffers);
typedef void (GLAPIENTRY * PFNGLDELETEVERTEXARRAYSARBPROC) (GLsizei n, const GLuint *arrays);


extern PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;

extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLSHADERSOURCEPROC glShaderSource;
extern PFNGLCOMPILESHADERPROC glCompileShader;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
extern PFNGLGETSHADERIVPROC glGetShaderiv;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
extern PFNGLDELETESHADERPROC glDeleteShader;
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
extern PFNGLUNIFORM1FPROC glUniform1f;
extern PFNGLUNIFORM2FPROC glUniform2f;
extern PFNGLUNIFORM3FPROC glUniform3f;
extern PFNGLUNIFORM4FPROC glUniform4f;
extern PFNGLUNIFORM1IPROC glUniform1i;
extern PFNGLUNIFORM2IPROC glUniform2i;
extern PFNGLUNIFORM3IPROC glUniform3i;
extern PFNGLUNIFORM4IPROC glUniform4i;
extern PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv;
extern PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv;
extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
extern PFNGLGENBUFFERSPROC glGenBuffers;
extern PFNGLBINDBUFFERPROC glBindBuffer;
extern PFNGLBUFFERDATAPROC glBufferData;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
extern PFNGLUSEPROGRAMPROC glUseProgram;
extern PFNGLACTIVETEXTUREPROC glActiveTexture;
extern PFNGLDELETEBUFFERSARBPROC glDeleteBuffers;
extern PFNGLDELETEVERTEXARRAYSARBPROC glDeleteVertexArrays;

namespace Window {
	void initialiseExtensions(void);
}



#endif // INCLUDED_WINDOW_OPEN_GL_HPP_