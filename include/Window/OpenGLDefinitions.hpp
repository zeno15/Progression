#ifndef INCLUDED_GRAPHICS_OPEN_GL_DEFINITIONS_HPP_
#define INCLUDED_GRAPHICS_OPEN_GL_DEFINITIONS_HPP_

#define GL_MAJOR_VERSION							0x821B
#define GL_MINOR_VERSION							0x821C
#define GL_FRAGMENT_SHADER							0x8B30
#define GL_VERTEX_SHADER							0x8B31
#define GL_GEOMETRY_SHADER							0x8DD9
#define GL_DELETE_STATUS							0x8B80
#define GL_COMPILE_STATUS							0x8B81
#define GL_LINK_STATUS								0x8B82
#define GL_VALIDATE_STATUS							0x8B83
#define GL_INFO_LOG_LENGTH							0x8B84

#define GL_ARRAY_BUFFER								0x8892
#define GL_STATIC_DRAW								0x88E4

#define GL_CLAMP_TO_EDGE							0x812F
#define GL_MIRRORED_REPEAT							0x8370

#define GL_TEXTURE0									0x84C0
#define GL_TEXTURE1									0x84C1
#define GL_TEXTURE2									0x84C2
#define GL_TEXTURE3									0x84C3
#define GL_TEXTURE4									0x84C4
#define GL_TEXTURE5									0x84C5
#define GL_TEXTURE6									0x84C6
#define GL_TEXTURE7									0x84C7
#define GL_TEXTURE8									0x84C8
#define GL_TEXTURE9									0x84C9
#define GL_TEXTURE10								0x84CA
#define GL_TEXTURE11								0x84CB
#define GL_TEXTURE12								0x84CC
#define GL_TEXTURE13								0x84CD
#define GL_TEXTURE14								0x84CE
#define GL_TEXTURE15								0x84CF
#define GL_TEXTURE16								0x84D0
#define GL_TEXTURE17								0x84D1
#define GL_TEXTURE18								0x84D2
#define GL_TEXTURE19								0x84D3
#define GL_TEXTURE20								0x84D4
#define GL_TEXTURE21								0x84D5
#define GL_TEXTURE22								0x84D6
#define GL_TEXTURE23								0x84D7
#define GL_TEXTURE24								0x84D8
#define GL_TEXTURE25								0x84D9
#define GL_TEXTURE26								0x84DA
#define GL_TEXTURE27								0x84DB
#define GL_TEXTURE28								0x84DC
#define GL_TEXTURE29								0x84DD
#define GL_TEXTURE30								0x84DE
#define GL_TEXTURE31								0x84DF
#define GL_ACTIVE_TEXTURE							0x84E0

#define GL_SHADING_LANGUAGE_VERSION					0x8B8C

typedef char GLchar;
typedef int GLsizeiptr;
typedef int GLintptr;

#ifdef WIN32
#include <Window/OpenGLDefinitionsWindows.hpp>
#endif 

#endif // INCLUDED_GRAPHICS_OPEN_GL_DEFINITIONS_HPP_