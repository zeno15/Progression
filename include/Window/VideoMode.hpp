#ifndef INCLUDED_WINDOW_VIDEO_MODE_HPP_
#define INCLUDED_WINDOW_VIDEO_MODE_HPP_

namespace Window {

	////////////////////////////////////////////////////////////
	///
	///	\brief	Struct describing basic video mode
	///
	////////////////////////////////////////////////////////////
	struct VideoMode {
		unsigned int bitsPerPixel = 32;	///<	Number of bits per pixel	
		unsigned int width = 1280;		///<	Width
		unsigned int height = 720;		///<	Height
		unsigned int major = 3;			///<	Major version of OpenGL
		unsigned int minor = 3;			///<	Minor version of OpenGL
	};

} 

#endif // INCLUDED_WINDOW_VIDEO_MODE_HPP_