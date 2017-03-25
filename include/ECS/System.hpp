#pragma once

#include <ECS/Entity.hpp>
#include <ECS/EntityManager.hpp>
#include <Infrastructure/InstanceCollection.hpp>

#include <System/Event.hpp>
#include <Graphics/Renderable.hpp>

#include <cassert>
#include <algorithm> 
#include <functional>

////////////////////////////////////////////////////////////
///
/// \namespace  ECS
///
////////////////////////////////////////////////////////////
namespace ECS {

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Base class for ECS System
    ///
    ////////////////////////////////////////////////////////////
    class SystemBase {
    public:
        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Virtual destructor
        ///
        ////////////////////////////////////////////////////////////
        virtual ~SystemBase() {};

        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Updates all entities within the system
        ///
        /// \param  The elapsed update time in seconds.
        ///
        ////////////////////////////////////////////////////////////
        virtual void update(float _delta) {};
        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Passes events to all enties within the system.
        ///
        /// \param  The system event to process
        ///
        ////////////////////////////////////////////////////////////
        virtual void handleEvent(const System::Event& _event) {};
        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Draws all entities within the system.
        ///
        /// \param  The render _target
        ///
        /// \param  The render _states
        ///
        ////////////////////////////////////////////////////////////
        virtual void Renderable(Window::Window& _window, Graphics::RenderData _states) const {};

        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Adds an entity to the system.
        ///
        /// \param  The entity to be added.
        ///
        ////////////////////////////////////////////////////////////
        virtual void addEntity(Entity& _entity) = 0;
        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Checks whether an entity is within the system
        ///
        /// \param  The entity id
        ///
        /// \return Whether the entity id is within the system
        ///
        ////////////////////////////////////////////////////////////
        virtual bool containsEntity(unsigned int _id) = 0;
        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Removes an entity from the system
        ///
        /// \param  The entity id to remove.
        ///
        ////////////////////////////////////////////////////////////
        virtual void removeEnitity(unsigned int _id) = 0;
    protected:
        std::vector<Entity *> m_SystemEntities;					///<    Entities that belong to this system
		unsigned int m_EntityKilledCallbackRegistrationId;		///<	The registration id of the callback when entities are killed
    };

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Base for all ECS systems
    ///
    /// \tparam The component types the system requires.
    ///
    ////////////////////////////////////////////////////////////
    template <typename... Args>
    class System : public SystemBase {
    public:
		System() {
			m_EntityKilledCallbackRegistrationId = 
				Infrastructure::InstanceCollection::getInstance<EntityManager>()
					.entityKilled.registerCallback(std::bind(&System::onEntityKilled, this, std::placeholders::_1));
		}

        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Virtual destructor
        ///
        ////////////////////////////////////////////////////////////
        virtual ~System() {};


        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Adds an entity to the system.
        ///
        /// \param  The entity to be added.
        ///
        ////////////////////////////////////////////////////////////
        virtual void addEntity(Entity& _entity) override {
            assert(_entity.hasComponents<Args...>());
            assert(!containsEntity(_entity.getId()));

            m_SystemEntities.push_back(&_entity);
        }

        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Checks whether an entity is within the system
        ///
        /// \param  The entity id
        ///
        /// \return Whether the entity id is within the system
        ///
        ////////////////////////////////////////////////////////////
        virtual bool containsEntity(unsigned int _id) override {
            return m_SystemEntities.end() != std::find_if(m_SystemEntities.begin(), m_SystemEntities.end(), [&](const Entity *_entity) {
                return _entity->getId() == _id;
            });
        }

        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Removes an entity from the system
        ///
        /// \param  The entity id to remove.
        ///
        ////////////////////////////////////////////////////////////
        virtual void removeEnitity(unsigned int _id) override {
            m_SystemEntities.erase(
                std::remove_if(m_SystemEntities.begin(), m_SystemEntities.end(), [&](const Entity *_entity) {
                    return _entity->getId() == _id;
                }), m_SystemEntities.end());
        }

	private:
		void onEntityKilled(unsigned int _entityId) {
			removeEnitity(_entityId);
		}

    };

}