/**
 * @file level_factory.cpp
 * @author Maxuuuu
 * @brief Implementation of the level factory.
 * @version 0.1
 * @date 11/11/2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "level_factory.hpp"
#include "level_scene.hpp"

LevelFactory::LevelFactory(std::shared_ptr<PrefabManager> &PrefabManager)
    : prefabManager(PrefabManager)
{
}

std::shared_ptr<Scene> LevelFactory::CreateScene(nlohmann::json sceneJson)
{
    std::shared_ptr<Scene> scene = std::make_shared<LevelScene>();

    nlohmann::json objectsJson = sceneJson.at("objects");
    AddObjects(*scene, objectsJson);
    
    nlohmann::json cameraJson = sceneJson.at("camera");
    auto camera = ConvertCamera(cameraJson);
    scene->SetCamera(camera);

    return scene;
}

std::vector<std::shared_ptr<GameObject>> LevelFactory::AddObjects(Scene &scene,
                                                                  const nlohmann::json &objectsJson)
{
    std::vector<std::shared_ptr<GameObject>> objects;
    for (const nlohmann::json &jsonObject : objectsJson)
    {
        auto gameObject =
            prefabManager->GetPrefab(jsonObject.at("prefab").template get<std::string>());

        gameObject->SetName(jsonObject.at("name").template get<std::string>());

        gameObject->SetActive(jsonObject.at("active").template get<bool>());

        gameObject->SetLayer(jsonObject.at("layer").template get<int>());

        gameObject->SetTransform(ConvertTransform(jsonObject.at("transform")));

        // Recursive function call.
        auto children = LevelFactory::AddObjects(scene, jsonObject.at("children"));
        for (const auto &child : children)
            child->SetParent(gameObject);

        scene.AddGameObject(gameObject);
        objects.push_back(gameObject);
    }

    return objects;
}

Transform LevelFactory::ConvertTransform(const nlohmann::json &transformJson) const
{
    // Get Position from JSON.
    auto positionJson = transformJson.at("position");
    auto position = Point(positionJson.at("x").template get<double>(),
                          positionJson.at("y").template get<double>());

    // Get rotation and scale from JSON.
    auto rotation = transformJson.at("rotation").template get<double>();
    auto scale = transformJson.at("scale").template get<double>();

    return {position, rotation, scale};
}

std::shared_ptr<Camera> LevelFactory::ConvertCamera(const nlohmann::json &cameraJson) const
{
    auto width = cameraJson.at("width").template get<int>();
    auto height = cameraJson.at("height").template get<int>();

    auto camera = std::make_shared<Camera>();
    camera->SetAspectWidth(width);
    camera->SetAspectHeight(height);

    return camera;
}
