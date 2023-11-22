/**
 * @file behaviour_script_manager.cpp
 * @author "Melvin van Bree"
 * @brief Manager that updates all behaviour scripts.
 * @version 0.1
 * @date 15/11/2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "behaviour_script_manager.hpp"
#include "behaviour_script.hpp"
#include "core/engine.hpp"
#include "game_object.hpp"
#include "game_object_list.hpp"
#include "managers/scene_manager.hpp"

BehaviourScriptManager::BehaviourScriptManager() = default;
BehaviourScriptManager::~BehaviourScriptManager() = default;

void BehaviourScriptManager::Update()
{
    auto engine = Engine::GetInstance();
    auto sceneManager = engine->Get<SceneManager>();
    if(!sceneManager->HasScene()) return;
    auto scene = sceneManager->GetScene().lock();
    if(!scene) return;

    auto sceneGameObjects = scene->GetAllByType<GameObject>();
    for(auto& sceneGameObject : sceneGameObjects){
        auto objectList = sceneGameObject.lock()->GetObjectList();
        for (const auto&gameObjectNode : *objectList){

            auto currentObject = gameObjectNode->cur;
            // Skip inactive game objects
            if(!currentObject || !currentObject->IsActive()) break;

            auto scripts = currentObject->GetComponents<BehaviourScript>();
            for(auto& script : scripts){
                if(!script || !script->IsActive()) continue;

                if(!script->HasStarted())
                    script->OnStart();

                script->OnUpdate();
            }
        }
    }
}