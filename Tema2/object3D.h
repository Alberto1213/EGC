#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object3D
{
    // Create square with given bottom left corner, length and color
    Mesh* CreatePyramid(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = true);
    Mesh* CreateCube(const std::string& name, glm::vec3 leftBottomCorner, float length,float width,float height, glm::vec3 color, bool fill = true);
    Mesh* CreateCubeBroked(const std::string& name, glm::vec3 leftBottomCorner, float length, float height, float width, glm::vec3 color, bool fill,float rand);

}
