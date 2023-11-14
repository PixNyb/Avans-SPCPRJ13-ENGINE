/**
 * @file game_object.hpp
 * @author Roël Couwenberg (contact@roelc.me)
 * @brief This file contains the GameObject class definition.
 * @version 0.1
 * @date 2023-11-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef AVANS_SPCPRJ13_GAMEOBJECT_H
#define AVANS_SPCPRJ13_GAMEOBJECT_H

#include "component.hpp"
#include "transform.hpp"
#include <memory>
#include <string>
#include <vector>

/**
 * @class GameObject
 * @brief The GameObject class represents an object in the game world.
 *
 * It contains a name, a list of components, an active flag, a tag, and a layer.
 * GameObjects can be added to the game world and can have their components
 * updated and rendered.
 */
class GameObject
{
  protected:
    std::string name; ///< The name of the GameObject.
    std::vector<std::shared_ptr<Component>>
        components;                     ///< The list of components attached to the GameObject.
    Transform transform;                ///< The transform of the GameObject.
    std::shared_ptr<GameObject> parent; ///< The parent of the GameObject.
    bool active;                        ///< The active flag of the GameObject.
    std::string tag;                    ///< The tag/type of the GameObject.
    int layer;                          ///< The layer of the GameObject.

  public:
    /**
     * @brief Default constructor for GameObject.
     */
    GameObject();

    /**
     * @brief Constructor for GameObject that sets the name.
     * @param name The name of the GameObject.
     */
    explicit GameObject(const std::string &name);

    /**
     * @brief Constructor for GameObject that sets the name and transform.
     *
     * @param name The name of the GameObject.
     * @param transform The transform of the GameObject.
     */
    GameObject(const std::string &name, const Transform &transform);

    /**
     * @brief Destructor for GameObject.
     */
    virtual ~GameObject() = default;

    /**
     * @brief Get the name of the GameObject.
     * @return The name of the GameObject.
     */
    [[nodiscard]] std::string GetName() const;

    /**
     * @brief Set the name of the GameObject.
     * @param name The new name of the GameObject.
     */
    void SetName(const std::string &name);

    /**
     * @brief Get the tag of the GameObject.
     * @return The tag of the GameObject.
     */
    std::string GetTag() const;

    /**
     * @brief Set the tag of the GameObject.
     * @param tag The new tag of the GameObject.
     */
    void SetTag(std::string tag);

    /**
     * @brief Get the layer of the GameObject.
     * @return The layer of the GameObject.
     */
    int GetLayer() const;

    /**
     * @brief Set the layer of the GameObject.
     * @param layer The new layer of the GameObject.
     */
    void SetLayer(int layer);

    /**
     * @brief Get the transform of the GameObject.
     * @return The transform of the GameObject.
     */
    const Transform &GetTransform() const;

    /**
     * @brief Set the transform of the GameObject.
     * @param transform The new transform of the GameObject.
     */
    void SetTransform(const Transform &transform);

    /**
     * @brief Get the parent of the GameObject.
     * @return The parent of the GameObject.
     */
    std::shared_ptr<GameObject> GetParent() const { return parent; }

    /**
     * @brief Set the parent of the GameObject.
     * @param parent The new parent of the GameObject.
     */
    void SetParent(std::shared_ptr<GameObject> parent) { this->parent = parent; }

    /**
     * @brief Check if the GameObject is active.
     * @return True if the GameObject is active, false otherwise.
     */
    bool IsActive() const;

    /**
     * @brief Set the active status of the GameObject.
     * @param active The new active status of the GameObject.
     */
    void SetActive(bool active);

    /**
     * @brief Check if the GameObject is active in the world.
     * @return True if the GameObject is active in the world, false otherwise.
     */
    bool IsActiveInWorld() const;

    /**
     * @brief Check if the GameObject is active itself.
     * @return True if the GameObject is active itself, false otherwise.
     */
    bool IsActiveSelf() const;

    /**
     * @brief Add a component to the GameObject.
     * @param component The component to add to the GameObject.
     */
    void AddComponent(std::shared_ptr<Component> component);

    /**
     * @brief Get the component of the specified type.
     * @tparam T The type of the component.
     * @return The component of the specified type.
     */
    template <typename T>
    std::shared_ptr<T> GetComponent() const
    {
        for (auto &component : components)
        {
            auto castedComponent = std::dynamic_pointer_cast<T>(component);
            if (castedComponent != nullptr)
            {
                return castedComponent;
            }
        }

        return nullptr;
    }
};

#endif // AVANS_SPCPRJ13_GAMEOBJECT_H