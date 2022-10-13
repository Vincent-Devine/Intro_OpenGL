#include "camera.hpp"

#include <cmath>

#include "light.hpp"

void Camera::GameInput(GLFWwindow& _window)
{
    RotateCameraMouse(_window);

    // Movement
    if(glfwGetKey(&_window, GLFW_KEY_W) == GLFW_PRESS)
    {
        position.x += .1f * cosf((cameraRotation.x + 90) * M_PI / 180);
        position.z += .1f * sinf((cameraRotation.x + 90) * M_PI / 180);
    }
    if(glfwGetKey(&_window, GLFW_KEY_S) == GLFW_PRESS)
    {
        position.x -= .1f * cosf((cameraRotation.x + 90) * M_PI / 180);
        position.z -= .1f * sinf((cameraRotation.x + 90) * M_PI / 180);
    }
    if(glfwGetKey(&_window, GLFW_KEY_A) == GLFW_PRESS)
    {
        position.x += .1f * cosf(cameraRotation.x * M_PI / 180);
        position.z += .1f * sinf(cameraRotation.x * M_PI / 180);
    }
    if(glfwGetKey(&_window, GLFW_KEY_D) == GLFW_PRESS)
    {
        position.x -= .1f * cosf(cameraRotation.x * M_PI / 180);
        position.z -= .1f * sinf(cameraRotation.x * M_PI / 180);
    }
    if(glfwGetKey(&_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        position.y += .1f;
    if(glfwGetKey(&_window, GLFW_KEY_SPACE) == GLFW_PRESS)
        position.y -= .1f;
}

void Camera::RotateCameraMouse(GLFWwindow& _window)
{
    glfwGetCursorPos(&_window, &currentCursorPos.x, &currentCursorPos.y);

    cameraRotation.x += (currentCursorPos.x - lastCursorPos.x)/6;
    cameraRotation.y += (currentCursorPos.y - lastCursorPos.y)/6;

    lastCursorPos.x = currentCursorPos.x;
    lastCursorPos.y = currentCursorPos.y;
}

Camera::Camera(GLFWwindow& _window, const int& _screenWidth, const int& _screenHeight)
{
    glfwSetInputMode(&_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPos(&_window, _screenWidth/2, _screenHeight/2);
}

void Camera::Update(GLFWwindow& _window)
{
    // In GL_PROJECTION
    GameInput(_window);
    glRotatef(cameraRotation.y, 1.f, 0.f, 0.f);
    glRotatef(cameraRotation.x, 0.f, 1.f, 0.f);

    // In GL_MODELVIEW
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(position.x, position.y, position.z);
}