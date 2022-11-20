#include <GL/glu.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <climits>

#include "Planet.h"
#include "Sun.h"
#include "Orbits.h"


struct{
	float eyeX;
	float eyeY;
	float eyeZ;
	float centerX;
	float centerY;
	float centerZ;
} camera {1000, 100, 0, 0, 0, 0};

const GLint w = 1280, h = 720;

void initValues()
{
    glClearColor(0.0,0.0,0.0,0.0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    const GLfloat params[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, params);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glViewport (0, 0, w, h);
}


int main(int argc, char **argv)
{

    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;

    sf::Window window(sf::VideoMode(w, h), "Trabalho 2 de Computacao Grafica", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);

    initValues();
    
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)w/(float)h, 0.2, INT_MAX);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(camera.eyeX, camera.eyeY, camera.eyeZ, camera.centerX, camera.centerY, camera.centerZ, 0, 1, 0);


    Sun sun(100, LightParameters{1.0, 0.0, 1.0, 0.2}, "textures/sun.jpg");
    Planet earth(2.4, 0.6, 700, 30, "textures/earth.jpg");
    Planet mars(2.4, 0.7, 800, 30, "textures/mars.jpg");

    Orbits orbits;
    orbits.add(earth.getOrbitValue());
    orbits.add(mars.getOrbitValue());


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
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
        earth.show();
        mars.show();
        orbits.show();

        window.display();
    }

    return EXIT_SUCCESS;
}