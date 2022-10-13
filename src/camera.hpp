#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "gl.hpp"
#include "type.hpp"

class Camera
{
private:
    float3 position;

    double2 currentCursorPos;
    double2 cameraRotation;
    double2 lastCursorPos;

    void GameInput(GLFWwindow& _window);
    void RotateCameraMouse(GLFWwindow& _window);

public:
    Camera(GLFWwindow& _window, const int& _screenWidth, const int& _screenHeight);

    void Update(GLFWwindow& _window);

    const double2 GetCameraRotation() {return cameraRotation;};
    const float3 GetPosition() {return position;};
};