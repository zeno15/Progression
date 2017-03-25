#ifndef INCLUDED_GRAPHICS_IMAGE_LOADER_HPP_
#define INCLUDED_GRAPHICS_IMAGE_LOADER_HPP_

#include <string>
#include <vector>
#include <cstdint>

#include <System/Vector2.hpp>

namespace Graphics {

	////////////////////////////////////////////////////////////
	//
	//	Class to handle saving & loading images
	//
	////////////////////////////////////////////////////////////
	class ImageLoader {
	public:
		////////////////////////////////////////////////////////////
		//
		//	Method to return static instance of the loader
		//
		////////////////////////////////////////////////////////////
		static ImageLoader& getInstance(void);

		////////////////////////////////////////////////////////////
		//
		//	Method to load image from file, type depends on extensions
		//
		////////////////////////////////////////////////////////////
		bool loadImageFromFile(const std::string& _filename, std::vector<uint8_t>& _pixels, System::Vector2<unsigned int>& _size);

		////////////////////////////////////////////////////////////
		//
		//	Method to save image to file, file type depends on extension
		//
		////////////////////////////////////////////////////////////
		bool saveImageToFile(const std::string& _filename, const std::vector<uint8_t>& _pixels, const System::Vector2<unsigned int>& _size);

	private:
		////////////////////////////////////////////////////////////
		//
		//	Private constructor
		//
		////////////////////////////////////////////////////////////
		ImageLoader(void);
		////////////////////////////////////////////////////////////
		//
		//	Private deconstructor
		//
		////////////////////////////////////////////////////////////
		~ImageLoader(void);
	};

}

#endif // INCLUDED_GRAPHICS_IMAGE_LOADER_HPP_