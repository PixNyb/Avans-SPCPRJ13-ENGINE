/**
 * @file CoreConstants.hpp
 * @author melvin van bree
 * @brief Meant to provide a way to store constants that are used in the core of the engine.
 * @version 0.1
 * @date 08/11/2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef DEFUNBOBENGINE_CORECONSTANTS_HPP
#define DEFUNBOBENGINE_CORECONSTANTS_HPP

#include "color.hpp"
#include "text.hpp"
#include <string>

namespace CoreConstants {
    namespace Text {
        const int DEFAULT_SIZE = 12;
        const std::string DEFAULT_FONT = "Sans.ttf";
        const Color DEFAULT_COLOR = Color::white();
        const Alignment DEFAULT_ALIGNMENT = Alignment::left;
    }
    namespace Engine {
        const int DEFAULT_FPS = 60;
    }
    namespace Debug {
        const bool EnableDebug = true;
        // Make sure it's false when you're not debugging
        const bool DrawColliders = true && EnableDebug;
    }
}

#endif // DEFUNBOBENGINE_CORECONSTANTS_HPP
