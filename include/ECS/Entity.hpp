#ifndef INCLUDED_ECS_ENTITY_HPP_
#define INCLUDED_ECS_ENTITY_HPP_

#include <ECS/Component.hpp>

#include <map>
#include <vector>
#include <cassert>
#include <typeindex>

////////////////////////////////////////////////////////////
///
///	\namespace	ECS
///
////////////////////////////////////////////////////////////
namespace ECS {

	////////////////////////////////////////////////////////////
	///
	///	\brief  Class represent an entity in an entity component system.
	///
	////////////////////////////////////////////////////////////
	class Entity {
	public:
		////////////////////////////////////////////////////////////
		///
		///	\brief Constructor with id.
		///
		/// \param	Id for the entity
		///
		////////////////////////////////////////////////////////////
		explicit Entity(unsigned int _id) :
			m_Id(_id),
			m_Alive(true),
			m_ToBeRemoved(false) {

		}

		////////////////////////////////////////////////////////////
		///
		///	\brief Copy constructor.
		///
		/// \param	The Entity to be copied.
		///
		////////////////////////////////////////////////////////////
		Entity(Entity&& e) {
			m_Id = e.m_Id;
			m_Alive = false;
			m_ToBeRemoved = false;
			m_Components.insert(e.m_Components.begin(), e.m_Components.end());
			e.m_Components.clear();
		}

		////////////////////////////////////////////////////////////
		///
		///	\brief Destructor
		///
		////////////////////////////////////////////////////////////		
		~Entity(void) {
			for (auto& c : m_Components) {
				delete c.second;
			}
		}



		////////////////////////////////////////////////////////////
		///
		///	\brief Gets the Id of the entity.
		///
		///	\return	The entities Id.
		///
		////////////////////////////////////////////////////////////
		inline unsigned int Entity::getId(void) const {
			return m_Id;
		}

	private:
		unsigned int m_Id;										///<	Entity Id
		bool m_Alive;											///<	Indicates if the entity is alive or not
		bool m_ToBeRemoved;										///<	Indicates whether the entity needs to be removed or not

		std::map<std::type_index, Component*> m_Components;		///<	Collection of components on the entity
	};
}


#endif // INCLUDED_ECS_ENTITY_HPP_