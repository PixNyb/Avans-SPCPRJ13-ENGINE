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

#include "abstract_scene_factory.hpp"
#include "prefab_manager.hpp"
#include <memory>

class LevelFactory : public AbstractSceneFactory {
  private:
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
    std::vector<std::shared_ptr<GameObject>> addObjects(Scene &scene, const nlohmann::json& objectsJson);

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
    [[nodiscard]] Scene CreateScene(nlohmann::json sceneJson) override;
};

#endif // DEFUNBOBENGINE_LEVEL_FACTORY_HPP
