#ifndef INCLUDED_ECS_ENTITY_HPP_
#define INCLUDED_ECS_ENTITY_HPP_

#include <ECS/Component.hpp>

#include <map>
#include <vector>
#include <cassert>
#include <typeindex>

////////////////////////////////////////////////////////////
///
/// \namespace  ECS
///
////////////////////////////////////////////////////////////
namespace ECS {

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Class represent an entity in an entity component system.
    ///
    ////////////////////////////////////////////////////////////
    class Entity {
    public:
        ////////////////////////////////////////////////////////////
        ///
        /// \brief Constructor with id.
        ///
        /// \param  Id for the entity
        ///
        ////////////////////////////////////////////////////////////
        explicit Entity(unsigned int _id) :
            m_Id(_id),
            m_Alive(true),
            m_ToBeRemoved(false) {

        }

        ////////////////////////////////////////////////////////////
        ///
        /// \brief Copy constructor.
        ///
        /// \param  The Entity to be copied.
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
        /// \brief Destructor
        ///
        ////////////////////////////////////////////////////////////        
        ~Entity(void) {
            for (auto& c : m_Components) {
                delete c.second;
            }
        }



        ////////////////////////////////////////////////////////////
        ///
        /// \brief Gets the Id of the entity.
        ///
        /// \return The entities Id.
        ///
        ////////////////////////////////////////////////////////////
        inline unsigned int getId(void) const {
            return m_Id;
        }



        ////////////////////////////////////////////////////////////
        ///
        /// \brief Adds a component to the entity
        ///
        /// \param  The component
        ///
        /// \tparam The component type
        ///
        ////////////////////////////////////////////////////////////
        template <typename T>
        void addComponent(T *_component) {
            m_Components[std::type_index(typeid(T))] = _component;
        }

        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Gets a component by type
        ///
        /// \tparam The component type
        ///
        /// \return The component
        ///
        ////////////////////////////////////////////////////////////
        template <typename T>
        T *getComponent(void) {
            auto it = m_Components.find(std::type_index(typeid(T)));
            if (it != m_Components.end()) {
                return dynamic_cast<T*>(it->second);
            }
            return nullptr;
        }

        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Verifies if the entity has a component of a given type
        ///
        /// \tparam The component type
        ///
        /// \return Whether the entity has the component
        ///
        ////////////////////////////////////////////////////////////
        template<typename T>
        bool hasComponent() {
            auto type = std::type_index(typeid(T));
            auto find = m_Components.find(std::type_index(typeid(T)));
            auto result = find != m_Components.end();
            return result;
        }

        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Gets the components of the given types
        ///
        /// \tparam The component types
        ///
        /// \return Tuple of components
        ///
        ////////////////////////////////////////////////////////////
        template<typename... Args>
        std::tuple<Args*...> getComponents() {
            assert(hasComponents<Args*...>());
            return std::make_tuple(getComponent<Args>()...);
        }

        ////////////////////////////////////////////////////////////
        ///
        /// \brief Verifies if the entity has components of the given types
        ///
        /// \tparam The component types
        ///
        /// \return Whether the entity has the components
        ///
        ////////////////////////////////////////////////////////////
        template<typename... Args>
        bool hasComponents() {
            std::vector<bool> components = { hasComponent<Args>()... };
            for (auto&& ok : components) {
                if (!ok) return false;
            }
            return true;
        }



    private:
        unsigned int m_Id;                                      ///<    Entity Id
        bool m_Alive;                                           ///<    Indicates if the entity is alive or not
        bool m_ToBeRemoved;                                     ///<    Indicates whether the entity needs to be removed or not

        std::map<std::type_index, Component*> m_Components;     ///<    Collection of components on the entity
    };
}


#endif // INCLUDED_ECS_ENTITY_HPP_