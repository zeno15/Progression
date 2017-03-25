#ifndef INCLUDED_INFRASTRUCTURE_TEXTURE_MANAGER_HPP_
#define INCLUDED_INFRASTRUCTURE_TEXTURE_MANAGER_HPP_

#include <Infrastructure/Manager.hpp>

#include <Graphics/Texture.hpp>

#include <map>

////////////////////////////////////////////////////////////
///
///	\namespace	Infrastructure
///
////////////////////////////////////////////////////////////
namespace Infrastructure {

	////////////////////////////////////////////////////////////
	///
	///	\brief	Class to manage textures
	///
	////////////////////////////////////////////////////////////
	class TextureManager : public Manager {
	public:
		friend class InstanceCollection;

		const static std::string Name;		///<	The name of the manager

		////////////////////////////////////////////////////////////
		///
		///	\brief	Adds a texture to the manager
		///
		///	\param	The filename of the texture to add
		///
		///	\param	The name of the texture
		///
		////////////////////////////////////////////////////////////
		void addTexture(const std::string& _filename, const std::string& _textureName);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets a texture
		///	
		///	\param	The name of the texture
		///
		///	\return	The texture
		///
		////////////////////////////////////////////////////////////
		Graphics::Texture& getTexture(const std::string& _textureName);

	private:
		////////////////////////////////////////////////////////////
		///
		///	\brief	Constructor
		///
		////////////////////////////////////////////////////////////
		TextureManager();
		////////////////////////////////////////////////////////////
		///
		///	\brief	Destructor
		///
		////////////////////////////////////////////////////////////
		~TextureManager();

		std::map<std::string, Graphics::Texture *> m_Textures;		///<	Texture name map
	};
}

#endif // INCLUDED_INFRASTRUCTURE_TEXTURE_MANAGER_HPP_