/**
 * @file level_factory.hpp
 * @author Maxuuuu
 * @brief Creates levels
 * @version 0.1
 * @date 11/11/2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef DEFUNBOBENGINE_LEVEL_FACTORY_HPP
#define DEFUNBOBENGINE_LEVEL_FACTORY_HPP

#include "iscene_factory.hpp"
#include "prefab_manager.hpp"
#include <memory>

/**
 * @class LevelFactory
 * @brief Creates levels based on a provided JSON object.
 *
 * This class is responsible for creating Levels based on a JSON object.
 * It has a PrefabManager which is used to create new GameObjects based on the provided JSON.
 * It will only create GameObjects for registered prefabs.
 * If the JSON is not formatted properly and error will be thrown.
 */
class LevelFactory : public ISceneFactory
{
  protected:
    /**
     * @brief The PrefabManager which is used to retrieve the registered prefabs.
     */
    std::shared_ptr<PrefabManager> prefabManager;

    /**
     * @brief A recursive function which adds the objects in a JSON to the provided Scene.
     * @param scene The Scene to which the GameObjects are to be added.
     * @param objectsJson The JSON from which the GameObjects are to be retrieved.
     * @return A vector of GameObjects that were just added to the Scene.
     */
    std::vector<std::shared_ptr<GameObject>> AddObjects(Scene &scene,
                                                        const nlohmann::json &objectsJson);

    /**
     * @brief Converts JSON to a Transform struct.
     * @param transformJson The JSON from which the Transform struct is to be retrieved.
     * @return The new Transform struct created based on the provided JSON.
     */
    [[nodiscard]] Transform ConvertTransform(const nlohmann::json &transformJson) const;

    /**
     * @brief Converts JSON to a Camera.
     * @param cameraJson The JSON from which the Camera specifications are to be retrieved.
     * @return The new Camera created based on the provided JSON.
     */
    std::shared_ptr<Camera> ConvertCamera(const nlohmann::json &transformJson) const;

  public:
    /**
     * @brief Constructor for the level factory.
     * @param PrefabManager Provides the PrefabManager from where the prefabs are to be retrieved.
     */
    explicit LevelFactory(std::shared_ptr<PrefabManager> &PrefabManager);

    /**
     * @brief Creates a scene based on a JSON format.
     * @param sceneJson The level JSON.
     * @return The scene created based on the level JSON.
     */
    [[nodiscard]] std::shared_ptr<Scene> CreateScene(nlohmann::json sceneJson) override;
};

#endif // DEFUNBOBENGINE_LEVEL_FACTORY_HPP
