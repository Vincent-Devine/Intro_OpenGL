#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdio>

#include "gl.hpp"
#include "draw.hpp"
#include "camera.hpp"
#include "light.hpp"
#include "texture.hpp"

void ConfigProjection(GLFWwindow& _window, bool& _isPerspective, const int& _screenWidth, const int& _screenHeight)
{
    // Perspective
    if(glfwGetKey(&_window, GLFW_KEY_F3) == GLFW_PRESS)
        _isPerspective = false;
    if(glfwGetKey(&_window, GLFW_KEY_F4) == GLFW_PRESS)
        _isPerspective = true;

    // Clear buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.2f, 0.3f, 1.f);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(_isPerspective)
        gluPerspective(90.f, (float)_screenWidth / _screenHeight, 0.5f, 100.f);
    else
        glOrtho(-8, 8, -6, 6, -10, 10);
}

bool PlayerLabyrinthEnd(const float3& _playerPosition)
{
    if(_playerPosition.z > -4.f && _playerPosition.z < -3.f
    && _playerPosition.x > -2.f && _playerPosition.x < 0.f
    && _playerPosition.y > -2.f && _playerPosition.y < 1.f)
        return true;
    return false;
}

int main(int argc, char* argv[])
{
    const int screenWidth  = 800;
    const int screenHeight = 600;

    bool isPerspective = true;
    bool showWireframe = false;

    const exercice actualEx = EXERCICE_LABYRINTH;

    if (!glfwInit())
        return -1;
    
    // Target OpenGL 3.3 API in Compatibility mode
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    // Add debug flag in    se we want to debug it
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Load funcs", nullptr, nullptr);
    if (window == nullptr)
    {
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    loadGLFunctions();

    printf("GLFW_VERSION: %s\n", glfwGetVersionString());
    printf("GL_VERSION: %s\n",  glGetString(GL_VERSION));
    printf("GL_VENDOR: %s\n",   glGetString(GL_VENDOR));
    printf("GL_RENDERER: %s\n", glGetString(GL_RENDERER));

    Camera camera = Camera(*window, screenWidth, screenHeight);
    texture::idWall = texture::LoadTexture("assets/wall.bmp");
    light::Init(actualEx);

    while (glfwWindowShouldClose(window) == false)
    {
        glfwPollEvents();
        
        ConfigProjection(*window, isPerspective, screenWidth, screenHeight);
        camera.Update(*window);
        light::Update(actualEx ,camera.GetCameraRotation(), camera.GetPosition());
        gl::ConfigDraw(*window, showWireframe);
        
        switch (actualEx)
        {
        case EXERCICE_1_AND_2:
            gl::DrawAllShape(texture::idWall);
            break;

        case EXERCICE_3_AND_4:
            gl::DrawCubeTest(texture::idWall);
            break;
        
        case EXERCICE_LABYRINTH:
            gl::DrawLabyrinth(texture::idWall);
            break;

        default:
            break;
        }

        glfwSwapBuffers(window);

        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || PlayerLabyrinthEnd(camera.GetPosition()))
            break;
    }

    glfwTerminate();

    texture::Delete();

    return 0;
}