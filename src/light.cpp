#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <cmath>

#include "gl.hpp"

#include "light.hpp"

void light::Init(const exercice& _actualEx)
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0); // Ambiente
    glEnable(GL_LIGHT1); // Direction

    if(_actualEx == EXERCICE_1_AND_2 || _actualEx == EXERCICE_3_AND_4)
    {
        // GL_LIGHT0 Ambiente
        GLfloat ambientL0[4] = {.3f, .3f, .3f, 1.f};
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambientL0);

        // GL_LIGHT1 Direction
        GLfloat diffuseL1[4] = {1.f, 1.f, 1.f, 0.f};  
        glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseL1);
    }
    else // labyrinth
    {
        glEnable(GL_LIGHT2); // Spot Light (Start)
        glEnable(GL_LIGHT3); // Spot Light (End)
        glEnable(GL_LIGHT4); // Spot Light (flash light player)

        // GL_LIGHT0 Ambiente
        GLfloat ambientL0[4] = {.41f, .46f, .39f, 1.f};
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambientL0);

        // GL_LIGHT1 Direction
        GLfloat diffuseL1[4] = {.15f, .31f, .9f, 0.f};
        glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseL1);

        // GL_LIGHT2 Spot Light Start
        GLfloat diffuseL2[4] = {1.0f, 1.0f, 1.0f, 0.f};
        glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseL2);
        GLfloat spotDirectionL2[3] = {0.0f, -1.0f, 0.0f};
        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotDirectionL2);
        GLfloat spotExponentL2 = 0.f;
        glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, spotExponentL2);

        // GL_LIGHT3 Spot Light End
        GLfloat diffuseL3[4] = {0.0f, 1.0f, 0.0f, 0.f};
        glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuseL3);
        GLfloat spotDirectionL3[3] = {0.0f, -1.0f, 0.0f};
        glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spotDirectionL3);
        GLfloat spotExponentL3 = 0.f;
        glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, spotExponentL3);

        // GL_LIGHT4 Spot Light flash light
        GLfloat diffuseL4[4] = {1.0f, 1.0f, 1.0f, 0.f};
        glLightfv(GL_LIGHT4, GL_DIFFUSE, diffuseL4);
        GLfloat spotExponentL4 = 15.f;
        glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, spotExponentL4);
    }
}

void light::Update(const exercice& _actualEx, const double2& _cameraRotation, const float3& _cameraPosition)
{
    // GL_LIGHT0 Ambiente
    GLfloat positionL0[4] = {0.f, 0.f, 0.f, 0.f};
    glLightfv(GL_LIGHT0, GL_POSITION, positionL0);
    
    // GL_LIGHT1 Direction
    GLfloat positionL1[4] = {0.f, 1.f, -1.f, 0.f};
    glLightfv(GL_LIGHT1 ,GL_POSITION, positionL1);

    if(_actualEx == EXERCICE_LABYRINTH)
    {
        // GL_LIGHT2 Spot Light Start
        GLfloat positionL2[4] = {1.f, 2.f, 0.f, 1.f};
        glLightfv(GL_LIGHT2, GL_POSITION, positionL2);
        GLfloat spotCutOffL2 = 30.f;
        glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, spotCutOffL2);

        // GL_LIGHT3 Spot Light End
        GLfloat positionL3[4] = {1.f, 2.f, 3.5f, 1.f};
        glLightfv(GL_LIGHT3, GL_POSITION, positionL3);
        GLfloat spotCutOffL3 = 30.f;
        glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, spotCutOffL3);

        // GL_LIGHT4 Spot Light flash light
        GLfloat positionL4[4] = {-_cameraPosition.x, -_cameraPosition.y, -_cameraPosition.z, 1.f};
        glLightfv(GL_LIGHT4, GL_POSITION, positionL4);
        GLfloat spotCutOffL4 = 30.f;
        glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, spotCutOffL4);
        GLfloat spotDirectionL4[3] = {cosf(((_cameraRotation.x - 90) * M_PI / 180)), 0.0f, sinf(((_cameraRotation.x - 90) * M_PI / 180))};
        glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, spotDirectionL4);
    }
}