#ifndef INCLUDED_ECS_ENTITY_MANAGER_HPP_
#define INCLUDED_ECS_ENTITY_MANAGER_HPP_

#include <ECS/Entity.hpp>

#include <Infrastructure/Manager.hpp>

#include <vector>

////////////////////////////////////////////////////////////
///
/// \namespace  ECS
///
////////////////////////////////////////////////////////////
namespace ECS {

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Class to manage entities in an entity component system.
    ///
    ////////////////////////////////////////////////////////////
    class EntityManager : public Infrastructure::Manager {
    public:
        friend class InstanceCollection;

        const static std::string Name;      ///<    Static name of the manager

        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Constructor
        ///
        ////////////////////////////////////////////////////////////
        EntityManager();
        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Destructor
        ///
        ////////////////////////////////////////////////////////////
        ~EntityManager();

        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Creates an entity
        ///
        /// \return Reference to the new entity
        ///
        ////////////////////////////////////////////////////////////
        static Entity& createEntity(void);
        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Gets an entity given by an id
        ///
        /// \param  The entity id
        ///
        /// \return Reference to the entity
        ///
        ////////////////////////////////////////////////////////////
        Entity& getEntity(unsigned int _id);
        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Kills the given entity
        ///
        /// \param  The entity to kill
        ///
        ////////////////////////////////////////////////////////////
        void killEntity(Entity& _entity);
        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Kills the entity by the given id
        ///
        /// \param  The id of the entity to kill
        ///
        ////////////////////////////////////////////////////////////
        void killEntity(unsigned int _id);

        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Retires all entities that have been marked as removeable
        ///
        ////////////////////////////////////////////////////////////
        void cleanupEntities(void);

        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Gets the next unassigned id
        ///
        ////////////////////////////////////////////////////////////
        unsigned int getNextUnassignedId(void) const;


        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Gets the ids of all currently alive entities
        ///
        /// \return Vector containing ids of entities
        ///
        ////////////////////////////////////////////////////////////
        std::vector<unsigned int> getAliveEntityIds(void) const;

    protected:
        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Creates a single entity
        ///
        /// \return Reference to the new entity
        ///
        ////////////////////////////////////////////////////////////
        Entity& createSingleEntity(void);

    private:
        unsigned int m_NextUnassignedId;               ///<    The next available entity id

        std::vector<unsigned int> m_ReUsableKeys;       ///<    Entity ids that are available for re use
        std::vector<Entity> m_Entities;                 ///<    The entities
    };
}

#endif // INCLUDED_ECS_ENTITY_MANAGER_HPP_