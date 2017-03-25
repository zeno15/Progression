#ifndef INCLUDED_WINDOW_VIDEO_MODE_HPP_
#define INCLUDED_WINDOW_VIDEO_MODE_HPP_

namespace Window {

	////////////////////////////////////////////////////////////
	///
	///	\brief	Struct describing basic video mode
	///
	////////////////////////////////////////////////////////////
	struct VideoMode {
		unsigned int bitsPerPixel;		///<	Number of bits per pixel	
		unsigned int width;				///<	Width
		unsigned int height;			///<	Height
		unsigned int major;				///<	Major version of OpenGL
		unsigned int minor;				///<	Minor version of OpenGL
	};

} 

#endif // INCLUDED_WINDOW_VIDEO_MODE_HPP_