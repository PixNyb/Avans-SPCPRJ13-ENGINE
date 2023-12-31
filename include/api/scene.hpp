/**
 * @file scene.hpp
 * @author Robin Pijnappels
 * @version 0.1
 * @date 2023-11-12
 *
 * @brief Defines the Scene class for managing and rendering game scenes in the game engine.
 * The Scene class is responsible for holding and managing game objects within a particular scene.
 * It includes functionalities for updating, rendering, adding, and removing game objects, as well
 * as querying and manipulating them based on various criteria. The Scene class is essential for
 * creating and organizing the different parts of a game's world.
 *
 * @copyright Copyright (c) 2023
 */

#ifndef AVANS_SPCPRJ13_SCENE_H
#define AVANS_SPCPRJ13_SCENE_H

#include "camera.hpp"
#include "game_object.hpp"
#include <memory>
#include <utility>
#include <vector>

/**
 * @class Scene
 * @brief Represents a scene in the game engine.
 *
 * A Scene is a container for game objects, providing methods for updating and rendering them.
 * It is responsible for managing the lifecycle and interactions of the contained game objects.
 */
class Scene
{
  private:
    std::shared_ptr<Camera> _camera; ///< The shared pointer to the active Camera object.
  public:
    /**
     * @brief This function is called by a Camera to render the scene on the engine.
     * TODO: Check if this is really the case?
     */
    virtual void RenderScene();

    Scene() = default;
    virtual ~Scene() = default;

    /**
     * @brief Updates all game objects in the scene.
     * @param deltaTime The time passed since the last frame.
     */
    virtual void Update(double deltaTime)
    {
        // TODO: Call an update on game object?
    }

    /**
     * @brief This property contains all the Game Object that are contained in this scene.
     *
     * TODO: Make this private and add a getter?
     */
    std::vector<std::shared_ptr<GameObject>> contents;

    /**
     * @brief Adds a game object, might be required for stuff like prefabs
     */
    void AddGameObject(const std::shared_ptr<GameObject> &gameObject);

    /**
     * @brief Creates a game object and adds it to the scene, should be the preferred method of
     * creating game objects for clear ownership
     * @return The created game object as a weak pointer because the created game object is owned by
     * the scene
     */
    std::weak_ptr<GameObject> CreateGameObject();

    /**
     * @brief Creates a game object and adds it to the scene, should be the preferred method of
     * creating game objects for clear ownership
     * @tparam GameObjectType The type of game object to create.
     * @tparam Args The types of arguments to forward to the GameObject constructor.
     * @param args The arguments to forward to the GameObject constructor.
     * @return The created game object as a weak pointer because the created game object is owned by
     * the scene.
     */
    template <typename GameObjectType, typename... Args>
    std::weak_ptr<GameObjectType> CreateGameObject(Args &&...args);

    /**
     * @brief Gets all game objects by type
     * @tparam T Type of the game object
     * @return A vector containing all game objects of the specified type
     */
    template <typename T> std::vector<std::weak_ptr<T>> inline GetAllByType()
    {
        std::vector<std::weak_ptr<T>> result;
        for (auto &go : contents)
        {
            auto casted = std::dynamic_pointer_cast<T>(go);
            if (casted != nullptr)
                result.push_back(casted);
        }
        return result;
    }

    /**
     * @brief Finds a game object by name
     * @param name Name of the game object
     * @return The game object if found, otherwise an empty pointer
     */
    std::weak_ptr<GameObject> FindGameObjectByName(const std::string &name);

    /**
     * @brief Finds game objects by tag
     * @param tag Tag of the game objects
     * @return The game objects if found, otherwise an empty vector
     */
    std::vector<std::weak_ptr<GameObject>> FindGameObjectByTag(const std::string &tag);

    /**
     * @brief Removes a game object by name
     * @param name Name of the game object
     * @return True if the game object was found and removed, otherwise false
     */
    bool RemoveGameObjectByName(const std::string &name);

    /**
     * @brief Removes a game object by tag
     * @param tag Tag of the game object
     * @return True if the game object was found and removed, otherwise false
     */
    bool RemoveGameObjectByTag(const std::string &tag);

    /**
     * @brief Removes all game objects from the scene
     */
    void Clear();

    /**
     * @brief Returns the amount of game objects in the scene
     * @return Amount of game objects in the scene
     */
    [[nodiscard]] size_t GetGameObjectCount() const { return contents.size(); }

    /**
     * @brief Sets the active status of a specific game object by name.
     * @param name Name of the game object.
     * @param isActive The new active status.
     * @return True if the game object was found and the status was updated, otherwise false.
     */
    bool SetActiveStatus(const std::string &name, bool isActive);

    /**
     * @brief Sets the camera of the scene
     * @param camera
     */
    void SetCamera(std::shared_ptr<Camera> camera) { _camera = std::move(camera); }

    /**
     * @brief Gets the camera of the scene
     * @return camera
     */
    std::shared_ptr<Camera> GetCamera() { return _camera; }
};

#endif // AVANS_SPCPRJ13_SCENE_H
