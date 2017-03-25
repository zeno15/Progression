#ifndef INCLUDED_GRAPHICS_RENDER_DATA_HPP_
#define INCLUDED_GRAPHICS_RENDER_DATA_HPP_

#include <System/Mat4x4.hpp>
#include <Graphics/Texture.hpp>

#include <string>

////////////////////////////////////////////////////////////
///
///	\namespace	Graphics
///
////////////////////////////////////////////////////////////
namespace Graphics {
	////////////////////////////////////////////////////////////
	///
	///	\brief	Class to hold data useful for rendering
	///
	////////////////////////////////////////////////////////////
	class RenderData {
	public:
		////////////////////////////////////////////////////////////
		///
		///	\brief	Constructor
		///
		////////////////////////////////////////////////////////////
		RenderData(void);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Constructor
		///
		///	\param	The view matrix to use
		///
		///	\param	The prpjection matrix to use
		///
		////////////////////////////////////////////////////////////
		RenderData(const System::Mat4x4& _view, const System::Mat4x4& _projection);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Constructor
		///
		///	\param	The view matrix to use
		///
		///	\param	The prpjection matrix to use
		///
		///	\param	The name of the shader to use
		///
		////////////////////////////////////////////////////////////
		RenderData(const System::Mat4x4& _view, const System::Mat4x4& _projection, const std::string& _shaderName);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Constructor
		///
		///	\param	The view matrix to use
		///
		///	\param	The prpjection matrix to use
		///
		///	\param	The name of the shader to use
		///
		///	\param	The texture to use
		///
		////////////////////////////////////////////////////////////
		RenderData(const System::Mat4x4& _view, const System::Mat4x4& _projection, const std::string& _shaderName, Graphics::Texture *_texture);


		std::string shaderName;			///<	The Shader name to use
		System::Mat4x4 view;			///<	The vertex view matrix to use
		System::Mat4x4 projection;			///<	The vertex projection matrix to use
		Graphics::Texture *texture;		///<	The texture to apply
	};
}

#endif // INCLUDED_GRAPHICS_RENDER_DATA_HPP_