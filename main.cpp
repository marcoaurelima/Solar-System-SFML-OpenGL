#include <GL/glu.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <climits>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Planet.h"
#include "Sun.h"
#include "Orbits.h"
#include "SpaceShip.h"
#include "Object.h"

const GLint w = 1280, h = 720;

void initValues()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    const GLfloat params[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, params);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glViewport(0, 0, w, h);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    
}

int main(int argc, char **argv)
{
    initValues();
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;

    sf::Window window(sf::VideoMode(w, h), "Trabalho 2 de Computacao Grafica", sf::Style::Default, settings);
    window.setMouseCursorVisible(false);
    window.setVerticalSyncEnabled(true);


    Sun sun(10, LightParameters{1.0, 0.0, 1.0, 0.2}, "textures/sun.jpg");

    Planet mercury(5, 0.1, 20, 4.879, "textures/mercury.jpg");

    Orbits orbits;
    orbits.add(mercury.getOrbitValue());

    SpaceShip ship(glm::vec3(3, 3, 3), Size(w, h));

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

            if (event.type == sf::Event::Resized)
            {
                glViewport(0, 0, (GLsizei)w, (GLsizei)h);
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        sun.illuminate();
        
        mercury.show();

        ship.show(window);
        // obj.show();
        orbits.show();

        window.display();
    }

    return EXIT_SUCCESS;
}
