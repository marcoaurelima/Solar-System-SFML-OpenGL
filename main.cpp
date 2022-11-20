#include <GL/glu.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>

#include "Planet.h"
#include "Sun.h"

/*
const float DIFUSE = 1;
const float SPECULAR = 0;
const float POSITIONAL = 1;
const float GLOBAL = 0.2;
*/

struct{
	float eyeX;
	float eyeY;
	float eyeZ;
	float centerX;
	float centerY;
	float centerZ;
} camera {1000, 0, 0, 0, 0, 0};

/*
void illuminate()
{

    float ambientLight[]{0.0, 0.0, 0.0, 1.0};
    float diffuseLight[]{DIFUSE, DIFUSE, DIFUSE, 1.0};
    float specularlight[]{SPECULAR, SPECULAR, SPECULAR, 1.0};
    float positionalLight[]{0.0, 0.0, 3.0, POSITIONAL};
    float globalLight[]{GLOBAL, GLOBAL, GLOBAL, 1.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularlight);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalLight);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, false);
    glEnable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glRotatef(0, 1.0, 0.0, 0.0);
    glRotatef(0, 0.0, 1.0, 0.0);
    glLightfv(GL_LIGHT0, GL_POSITION, positionalLight);
    glTranslatef(positionalLight[0], positionalLight[1], positionalLight[2]);
    glColor3f(DIFUSE, DIFUSE, DIFUSE);
    glPopMatrix();

    glEnable(GL_LIGHTING);
}*/

int main(int argc, char **argv)
{

    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;

    sf::Window window(sf::VideoMode(1280, 720), "Title", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);

    glClearColor(0.1f, 0.1f, 0.1f, 1.f);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    int w = 1280, h = 720;

    glViewport (0, 0, w, h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)w/(float)h, 0.2, 2147483647.0);
    glMatrixMode(GL_MODELVIEW);

    gluLookAt(camera.eyeX-100, camera.eyeY, camera.eyeZ, camera.centerX, camera.centerY, camera.centerZ, 0, 1, 0);

    glClearColor(0,0,0, 0.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Planet planet(2.4, 0.6, 700, 30, "textures/earth.jpg");
    Sun sun(100, "textures/sun.jpg", LightParameters{1.0, 0.0, 1.0, 0.2});

    const float params[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, params);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }

             else if (event.type == sf::Event::Resized)
            {
                glViewport(0, 0, event.size.width, event.size.height);
                glViewport (0, 0, w, h);
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        sun.illuminate();
        planet.show();

        window.display();
    }

    return EXIT_SUCCESS;
}