#include "object3D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

    Mesh* object3D::CreateCube(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    float height,
    float width,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(0, 0, width), color),
        VertexFormat(corner + glm::vec3(length, 0, width), color),
        VertexFormat(corner + glm::vec3(0, height, width), color),
        VertexFormat(corner + glm::vec3(length, height, width), color),
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(0, height, 0), color),
        VertexFormat(corner + glm::vec3(length, height, 0), color)
    };

    Mesh* wall = new Mesh(name);
    std::vector<unsigned int> indices = {
        0, 1, 2, 
        1, 3, 2,
        2, 3, 7,
        2, 7, 6,
        1, 7, 3,
        1, 5, 7,
        6, 7, 4,
        7, 5, 4,
        0, 4, 1,
        1, 4, 5,
        2, 6, 4,
        0, 2, 4};

    if (!fill) {
        wall->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    wall->InitFromData(vertices, indices);
    return wall;
}
    Mesh* object3D::CreateCubeBroked(
        const std::string& name,
        glm::vec3 leftBottomCorner,
        float length,
        float height,
        float width,
        glm::vec3 color,
        bool fill,
        float rand)
    {
        glm::vec3 corner = leftBottomCorner;

        std::vector<VertexFormat> vertices =
        {
            VertexFormat(corner + glm::vec3(rand/3, -rand/4, width+2*rand/5), color),
            VertexFormat(corner + glm::vec3(length-rand/3, rand, width+2*rand/3), color),
            VertexFormat(corner + glm::vec3(rand/4, height-rand, width+rand/2), color),
            VertexFormat(corner + glm::vec3(length+rand/2, height-rand/3, width+rand/5), color),
            VertexFormat(corner, color),
            VertexFormat(corner + glm::vec3(length+rand/2, 2*rand/3, -rand/4), color),
            VertexFormat(corner + glm::vec3(rand/5, height+rand/3, -rand), color),
            VertexFormat(corner + glm::vec3(length+(rand/3), height-rand/2, rand), color)
        };

        Mesh* wall = new Mesh(name);
        std::vector<unsigned int> indices = {
            0, 1, 2,
            1, 3, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4 };

        if (!fill) {
            wall->SetDrawMode(GL_LINE_LOOP);
        }
        else {
            // Draw 2 triangles. Add the remaining 2 indices
            indices.push_back(0);
            indices.push_back(2);
        }

        wall->InitFromData(vertices, indices);
        return wall;
    }
Mesh* object3D::CreatePyramid(
    const std::string& name2,
    glm::vec3 leftBottomCorner2,
    float length2,
    glm::vec3 color2,
    bool fill2)
{
    glm::vec3 corner = leftBottomCorner2;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color2),
        VertexFormat(corner + glm::vec3(length2, 0, 0), color2),
        VertexFormat(corner + glm::vec3(0, length2, 0), color2)
    };

    Mesh* triangle = new Mesh(name2);
    std::vector<unsigned int> indices = { 0, 1, 2 };

    if (!fill2) {
        triangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    triangle->InitFromData(vertices, indices);
    return triangle;
}

