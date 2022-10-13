#pragma once

#include "type.hpp"

namespace gl
{
    // Configuration draw
    void ConfigDraw(GLFWwindow& window, bool& _showWireframe);
    
    // Draw Shape
    void DrawTriangle();
    void DrawQuad(const GLuint& _idTexture);
    void DrawCube(const GLuint& _idTexture, const bool _materialTest = false);
    void DrawSphere(const int& lon, const int& lat);
    void DrawPointSphere(const int& lon, const int& lat);
    void DrawCone(const int& res);
    void DrawGizmo();
    
    // ex 1 and ex 2
    void DrawAllShape(const GLuint& _idTexture);
    // ex 3 and ex 4
    void DrawCubeTest(const GLuint& _idTexture);
    // ex bonus
    void DrawLabyrinth(const GLuint& _idTexture);
    void DrawWall(const GLuint& _idTexture, const float3& _positionStart, const float& _length, const bool _perpendicular = false ,const bool _ground = false);
}