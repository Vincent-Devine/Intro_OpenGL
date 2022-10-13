#include <cmath>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "gl.hpp"
#include "draw.hpp"

static float3 getSphericalCoords(float r, float theta, float phi)
{
    return {r * sinf(theta) * cosf(phi),
            r * cosf(theta),
            r * sinf(theta) * sinf(phi)};
}

void gl::ConfigDraw(GLFWwindow& _window, bool &_showWireframe)
{
    // F1-F2 to toggle wireframe
    if (glfwGetKey(&_window, GLFW_KEY_F1) == GLFW_PRESS)
        _showWireframe = false;
    else if (glfwGetKey(&_window, GLFW_KEY_F2) == GLFW_PRESS)
        _showWireframe = true;

    glEnable(GL_DEPTH_TEST);

    // Draw primitive
    glPolygonMode(GL_FRONT_AND_BACK, _showWireframe ? GL_LINE : GL_FILL);
}

void gl::DrawTriangle()
{
    glBegin(GL_TRIANGLES);
    glNormal3f(0.f, 0.f, -1.f);
    glVertex3f(-0.5f, -0.5f, 0.f);
    glNormal3f(0.f, 0.f, -1.f);
    glVertex3f(0.5f, -0.5f, 0.f);
    glNormal3f(0.f, 0.f, -1.f);
    glVertex3f(0.0f, 0.5f, 0.f);
    glEnd();
}

void gl::DrawQuad(const GLuint& _idTexture)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _idTexture);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glBegin(GL_TRIANGLES);

    glNormal3f(0.f, 0.f, 1.f);
    glTexCoord2f(0.f, 0.f);
    glVertex3f(-0.5f, -0.5f, +0.f);
    glTexCoord2f(1.f, 0.f);
    glVertex3f(+0.5f, -0.5f, +0.f);
    glTexCoord2f(0.f, 1.f);
    glVertex3f(-0.5f, +0.5f, +0.f);

    glTexCoord2f(0.f, 1.f);
    glVertex3f(-0.5f, +0.5f, +0.f);
    glTexCoord2f(1.f, 0.f);
    glVertex3f(+0.5f, -0.5f, +0.f);
    glTexCoord2f(1.f, 1.f);
    glVertex3f(+0.5f, +0.5f, +0.f);

    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glBindTexture(GL_TEXTURE_2D,0);
    glDisable(GL_TEXTURE_2D);
}

void gl::DrawCube(const GLuint& _idTexture, const bool _materialTest)
{
    if(!_materialTest)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _idTexture);
    }
    else
        glEnable(GL_COLOR_MATERIAL);

    glBegin(GL_TRIANGLES);

    if(_materialTest)
    {
        // Material : gold
        glColorMaterial(GL_FRONT, GL_AMBIENT);
        glColor3f(0.24725f, 0.1995f, 0.0745f);
        glColorMaterial(GL_FRONT, GL_DIFFUSE);
        glColor3f(0.75164f,	0.60648f, 0.22648f);
    }

    // Front
    glNormal3f(0.f, 0.f, 1.f);
    glTexCoord2f(0, 0);
    glVertex3f(-0.5f, -0.5f, .5f);
    glTexCoord2f(1, 0);
    glVertex3f(+0.5f, -0.5f, .5f);
    glTexCoord2f(0, 1);
    glVertex3f(-0.5f, +0.5f, .5f);

    glTexCoord2f(0, 1);
    glVertex3f(-0.5f, +0.5f, .5f);
    glTexCoord2f(1, 0);
    glVertex3f(+0.5f, -0.5f, .5f);
    glTexCoord2f(1, 1);
    glVertex3f(+0.5f, +0.5f, .5f);

    // Back
    glNormal3f(0.f, 0.f, -1.f);
    glTexCoord2f(0, 0);
    glVertex3f(-0.5f, -0.5f, -.5f);
    glTexCoord2f(1, 0);
    glVertex3f(+0.5f, -0.5f, -.5f);
    glTexCoord2f(0, 1);
    glVertex3f(-0.5f, +0.5f, -.5f);

    glTexCoord2f(0, 1);
    glVertex3f(-0.5f, +0.5f, -.5f);
    glTexCoord2f(1, 0);
    glVertex3f(+0.5f, -0.5f, -.5f);
    glTexCoord2f(1, 1);
    glVertex3f(+0.5f, +0.5f, -.5f);

    // Left
    glNormal3f(-1.f, 0.f, 0.f);
    glTexCoord2f(0, 0);
    glVertex3f(-0.5f, -0.5f, -.5f);
    glTexCoord2f(1, 0);
    glVertex3f(-0.5f, -0.5f, .5f);
    glTexCoord2f(0, 1);
    glVertex3f(-0.5f, +0.5f, -.5f);

    glTexCoord2f(0, 1);
    glVertex3f(-0.5f, +0.5f, -.5f);
    glTexCoord2f(1, 0);
    glVertex3f(-0.5f, -0.5f, .5f);
    glTexCoord2f(1, 1);
    glVertex3f(-0.5f, +0.5f, .5f);

    // Right 
    glNormal3f(1.f, 0.f, 0.f);
    glTexCoord2f(0, 0);
    glVertex3f(+0.5f, -0.5f, -.5f);
    glTexCoord2f(1, 0);
    glVertex3f(+0.5f, -0.5f, .5f);
    glTexCoord2f(0, 1);
    glVertex3f(+0.5f, +0.5f, -.5f);

    glTexCoord2f(0, 1);
    glVertex3f(+0.5f, +0.5f, -.5f);
    glTexCoord2f(1, 0);
    glVertex3f(+0.5f, -0.5f, .5f);
    glTexCoord2f(1, 1);
    glVertex3f(+0.5f, +0.5f, .5f);

    // Top
    glNormal3f(0.f, 1.f, 0.f);
    glTexCoord2f(1.f, 0.f);
    glVertex3f( 0.5f,  0.5f,  0.5f);
    glTexCoord2f(0.f, 0.f);
    glVertex3f(-0.5f,  0.5f,  0.5f);
    glTexCoord2f(0.f, 1.f);
    glVertex3f(-0.5f,  0.5f, -0.5f);

    glTexCoord2f(1.f, 0.f);
    glVertex3f( 0.5f,  0.5f,  0.5f);
    glTexCoord2f(0.f, 1.f);
    glVertex3f(-0.5f,  0.5f, -0.5f);
    glTexCoord2f(1.f, 1.f);
    glVertex3f( 0.5f,  0.5f, -0.5f);

    // Bottom
    glNormal3f(0.f, -1.f, 0.f);
    glTexCoord2f(1.f, 1.f);
    glVertex3f( 0.5f, -0.5f,  0.5f);
    glTexCoord2f(0.f, 0.f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(0.f, 1.f);
    glVertex3f(-0.5f, -0.5f,  0.5f);

    glTexCoord2f(1.f, 1.f);
    glVertex3f( 0.5f, -0.5f,  0.5f);
    glTexCoord2f(1.f, 0.f);
    glVertex3f( 0.5f, -0.5f, -0.5f);
    glTexCoord2f(0.f, 0.f);
    glVertex3f(-0.5f, -0.5f, -0.5f);

    if(_materialTest)
        glDisable(GL_COLOR_MATERIAL);

    glEnd();

    if(!_materialTest)
    {
        glBindTexture(GL_TEXTURE_2D,0);
        glDisable(GL_TEXTURE_2D);
    }
}

void gl::DrawSphere(const int& lon, const int& lat)
{
    float r = 0.5f;
    glBegin(GL_QUADS);

    for (int j = 0; j < lat; ++j)
    {
        float theta0 = ((j + 0) / (float)lat) * M_PI;
        float theta1 = ((j + 1) / (float)lat) * M_PI;

        for (int i = 0; i < lon; ++i)
        {
            float phi0 = ((i + 0) / (float)lon) * 2.f * M_PI;
            float phi1 = ((i + 1) / (float)lon) * 2.f * M_PI;

            float3 c0 = getSphericalCoords(r, theta0, phi0);
            float3 c1 = getSphericalCoords(r, theta0, phi1);
            float3 c2 = getSphericalCoords(r, theta1, phi1);
            float3 c3 = getSphericalCoords(r, theta1, phi0);

            glVertex3f(c0.x, c0.y, c0.z);
            glVertex3f(c1.x, c1.y, c1.z);
            glVertex3f(c2.x, c2.y, c2.z);
            glVertex3f(c3.x, c3.y, c3.z);
        }
    }
    glEnd();
}

void gl::DrawPointSphere(const int& lon, const int& lat)
{
    float r = 0.5f;
    glBegin(GL_POINTS);

    for (int j = 0; j < lat; ++j)
    {
        float theta = (j / (float)lat) * M_PI;

        for (int i = 0; i < lon; ++i)
        {
            float phi = (i / (float)lon) * 2.f * M_PI;

            float3 coords = getSphericalCoords(r, theta, phi);

            glVertex3f(coords.x, coords.y, coords.z);
        }
    }
    glEnd();
}

void gl::DrawCone(const int& res)
{
    float angle;
    float3 p1;
    float3 p2;
    float size = .5f;
    float radius = .5f;

    glBegin(GL_TRIANGLES);

    for(int i = 0; i < res; i++)
    {
        angle = i * 2 * M_PI / res;
        p1 = (float3) {radius * cosf(angle), -size, radius * sinf(angle)};
        
        angle = (i+1)%res * 2 * M_PI / res;
        p2 = (float3) {radius * cosf(angle), -size, radius * sinf(angle)};

        glVertex3f(0.f, .5f, 0.f);
        glVertex3f(p1.x, p1.y, p1.z);
        glVertex3f(p2.x, p2.y, p2.z);
        
        glVertex3f(0.f,  -size, 0.f);
        glVertex3f(p1.x, p1.y, p1.z);
        glVertex3f(p2.x, p2.y, p2.z);
    }
    glEnd();
}

void gl::DrawGizmo()
{
    glBegin(GL_LINES);

    glColor3f(0.f, 0.f, 1.f);
    glVertex3f(0.f, -.5f, 0.f);
    glVertex3f(1.f, -.5f, 0.f);

    glColor3f(0.f, 1.f, 0.f);
    glVertex3f(0.f, -.5f, 0.f);
    glVertex3f(0.f, +.5f, 0.f);

    glColor3f(1.f, 0.f, 0.f);
    glVertex3f(0.f, -.5f, 0.f);
    glVertex3f(0.f, -.5f, 1.f);

    glEnd();

    glTranslatef(1.f, -.5f, 0.f);
    glScalef(.1f, .1f, .1f);
    glRotatef(90, 0, 0 ,-1);
    glColor3f(0.f, 0.f, 1.f);
    DrawCone(20);

    glRotatef(90, 0, 0 ,1);
    glScalef(10.f, 10.f, 10.f);
    glTranslatef(-1.f, +.5f, 0.f);

    glTranslatef(0.f, +.5f, 0.f);
    glScalef(.1f, .1f, .1f);
    glColor3f(0.f, 1.f, 0.f);
    DrawCone(20);

    glScalef(10.f, 10.f, 10.f);
    glTranslatef(0.f, -.5f, 0.f);

    glTranslatef(0.f, -.5f, 1.f);
    glScalef(.1f, .1f, .1f);
    glRotatef(90, 1, 0, 0);
    glColor3f(1.f, 0.f, 0.f);
    DrawCone(20);
}

void gl::DrawAllShape(const GLuint& _idTexture)
{
    static float rotation = 0.f;
    rotation += 0.5f;
    
    glPushMatrix();
    glTranslatef(-5.f, -0.5f, -5.f);
    glRotatef(0.f, 0.f, 1.f, 0.f);
    gl::DrawTriangle();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.5f, -0.5f, -5.f);
    glRotatef(0.f, 0.f, 1.f, 0.f);
    gl::DrawQuad(_idTexture);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.f, -0.5f, -5.f);
    glRotatef(0.f, 0.f, 1.f, 0.f);
    glColor3f(1.f, 1.f, 1.f);
    gl::DrawCube(_idTexture);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-.5f, -0.5f, -5.f);
    glRotatef(0.f, 0.f, 1.f, 0.f);
    glColor3f(0.f,0.f,1.f);
    gl::DrawSphere(20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.f, -0.5f, -5.f);
    glRotatef(0.f, 0.f, 1.f, 0.f);
    glColor3f(1.f,1.f,1.f);
    gl::DrawPointSphere(20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.5f, -0.5f, -5.f);
    glRotatef(0.f, 0.f, 1.f, 0.f);
    glColor3f(0.f,1.f,0.f);
    gl::DrawCone(20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5.f, -0.5f, -5.f);
    glRotatef(0.f, 0.f, 1.f, 0.f);
    gl::DrawGizmo();
    glPopMatrix();

    glColor3f(1.f, 1.f, 1.f);
}

void gl::DrawCubeTest(const GLuint& _idTexture)
{
    static float rotation = 0.f;
    rotation += 0.5f;

    glPushMatrix();
    glTranslatef(-5.0f, -2.5f, -5.f);
    glRotatef(rotation, 0.f, 1.f, 0.f);
    gl::DrawCube(_idTexture);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.0f, -2.5f, -5.f);
    glRotatef(rotation, 0.f, 1.f, 0.f);
    gl::DrawCube(_idTexture, true);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(1.5f, -0.5f, -5.f);
    glRotatef(0.f, 0.f, 1.f, 0.f);
    gl::DrawCube(_idTexture);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.5f, -0.5f, -5.f);
    glRotatef(0.f, 0.f, 1.f, 0.f);
    gl::DrawCube(_idTexture, true);
    glPopMatrix();
}

void gl::DrawLabyrinth(const GLuint& _texture)
{
    { // Labyrinth
// 
//20      ---------W9-----------
//19    ||              W8      ||
//18    ||                      ||
//17    ||      ||              ||
//16    ||    --||--W7------    ||
//15    ||      ||    W6        ||
//14    ||      W3    ||        ||
//13    ||      ||              ||
//12    ||                      ||
//11    ||            ||        W12
//10    ||--W11---    ||        ||
//09    ||            W5        ||
//08    ||            ||        ||
//07    W1      ||W10-||----    ||
//06    ||      ||              ||
//05    ||      ||              ||
//04    ||      W2              ||
//03    ||      ||    ||W13-    ||
//02    ||      ||    W4        ||
//01    ||      ||    ||        ||
//00    || (S)  ||(A) ||---W14--||
//      00010203040506070809101112
// 
//(S) : Spawn           (A) : Arrived
    }

    gl::DrawWall(_texture, (float3){00.f, -2.f, -02.f}, 20.f);                   // W1
    gl::DrawWall(_texture, (float3){00.f, -2.f, +02.f}, 08.f);                   // W2
    gl::DrawWall(_texture, (float3){13.f, -2.f, +02.f}, 05.f);                   // W3
    gl::DrawWall(_texture, (float3){00.f, -2.f, +05.f}, 04.f);                   // W4
    gl::DrawWall(_texture, (float3){08.f, -2.f, +05.f}, 04.f);                   // W5
    gl::DrawWall(_texture, (float3){15.f, -2.f, +05.f}, 02.f);                   // W6
    gl::DrawWall(_texture, (float3){16.f, -2.f, +01.f}, 06.f, true);             // W7
    gl::DrawWall(_texture, (float3){19.f, -2.f, +06.f}, 01.f);                   // W8
    gl::DrawWall(_texture, (float3){20.f, -2.f, -02.f}, 12.f, true);             // W9
    gl::DrawWall(_texture, (float3){07.f, -2.f, +03.f}, 05.f, true);             // W10
    gl::DrawWall(_texture, (float3){10.f, -2.f, -01.f}, 04.f, true);             // W11
    gl::DrawWall(_texture, (float3){00.f, -2.f, +10.f}, 20.f);                   // W12
    gl::DrawWall(_texture, (float3){03.f, -2.f, +06.f}, 02.f, true);             // W13
    gl::DrawWall(_texture, (float3){00.f, -2.f, +06.f}, 04.f, true);             // W14
    gl::DrawWall(_texture, (float3){00.f, -2.f, -02.f}, 20.f, false, true);      // Ground
}

void gl::DrawWall(const GLuint& _idTexture, const float3& _positionStart, const float& _length, const bool _perpendicular, const bool _ground)
{
    glPushMatrix();
    glTranslatef(_positionStart.x, _positionStart.y, _positionStart.z);
    if(_ground)
    {
        for(float i = 0.f; i < _length; i++)
        {
            for(float j = 0.f; j < 11.f; j++)
            {
                glTranslatef(0, 0, 1);
                gl::DrawCube(_idTexture);
            }
            glTranslatef(1, 0, -11);
        }
    }
    else if(_perpendicular)
    {
        glRotatef(270, 0 , 1, 0);
        for(float i = 0.f; i < _length; i++)
        {
            for(float j = 0.f; j < 11.f; j++)
            {
                glTranslatef(0, 1, 0);
                gl::DrawCube(_idTexture);
            }
            glTranslatef(1, -11, 0);
        }
    }
    else
    {
        for(float i = 0.f; i < _length; i++)
        {
            for(float j = 0.f; j < 11.f; j++)
            {
                glTranslatef(0, 1, 0);
                gl::DrawCube(_idTexture);
            }
            glTranslatef(1, -11, 0);
        }
    }
    glPopMatrix();
}