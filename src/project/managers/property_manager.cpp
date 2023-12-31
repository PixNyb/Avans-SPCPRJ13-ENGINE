/**
 * @file property_manager.hpp
 * @author Maxuuuu
 * @brief This file contains the implementation of the PropertyManager class.
 * @version 0.1
 * @date 15/12/2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "property_manager.hpp"

PropertyManager::PropertyManager(std::shared_ptr<JSONHandler> &jHandler)
    : jsonHandler(jHandler), fileExtension(".json")
{
}
