#ifndef INCLUDED_INFRASTRUCTURE_INSTANCE_COLLECTION_HPP_
#define INCLUDED_INFRASTRUCTURE_INSTANCE_COLLECTION_HPP_


#include <Infrastructure/Manager.hpp>

#include <map>
#include <string>

////////////////////////////////////////////////////////////
///
/// \namespace  Infrastructure
///
////////////////////////////////////////////////////////////
namespace Infrastructure {
    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Class to allow single point of access to managers
    ///
    ////////////////////////////////////////////////////////////
    class InstanceCollection {
    public:
        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Register a manager by type
        ///
        /// \tparam The type of the manager, new instance will be made
        ///
        ////////////////////////////////////////////////////////////
        template <typename T>
        static void registerInstance(void) {
            if (m_Managers.find(T::Name) == m_Managers.end()) {
                m_Managers.insert(std::pair<std::string, Manager *>(T::Name, new T()));
            }
        }

        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Register a manager by type and value
        ///
        /// \tparam The type of the manager
        ///
        ////////////////////////////////////////////////////////////
        template <typename T>
        static void registerInstance(T *instance) {
            if (m_Managers.find(T::Name) == m_Managers.end()) {
                m_Managers.insert(std::pair<std::string, Manager *>(T::Name, instance));
            }
        }

        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Removes the manager by type
        ///
        /// \tparam The type of the manager
        ///
        ////////////////////////////////////////////////////////////
        template <typename T>
        static void removeInstance() {
            if (m_Managers.find(T::Name) == m_Managers.end()) {
                throw std::runtime_error(T::Name);
            }

            m_Managers.erase(T::Name);
        }

        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Removes the manager by value
        ///
        /// \tparam The type of the manager
        ///
        ////////////////////////////////////////////////////////////
        template <typename T>
        static void removeInstance(T *instance) {
            if (m_Managers.find(T::Name) == m_Managers.end()) {
                throw std::runtime_error(T::Name);
            }

            m_Managers.erase(T::Name);
        }

        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Gets a reference to the manager by type
        ///
        /// \tparam The type of the manager
        ///
        ////////////////////////////////////////////////////////////
        template <typename T>
        static T& getInstance() {
            if (m_Managers.find(T::Name) == m_Managers.end()) {
                throw std::runtime_error(T::Name);
            }

            return *static_cast<T *>(m_Managers[T::Name]);
        }

        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Clears all the managers
        ///
        ////////////////////////////////////////////////////////////
        static void clear(void);

    private:
        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Constructor
        ///
        ////////////////////////////////////////////////////////////
        InstanceCollection() {};

        static std::map<std::string, Manager *> m_Managers;     ///< Static collection of managers.
    };

}

#endif // INCLUDED_INFRASTRUCTURE_INSTANCE_COLLECTION_HPP_