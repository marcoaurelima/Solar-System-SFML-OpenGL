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
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {100.0};
    GLfloat light_position[] = {0, 0, 0, 0.0};
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

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

    Object obj;
    obj.loadFromFile("models/esfera.obj");
    obj.loadTextureFile("textures/earth.jpg");

    /*glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, w / h, 0.2, INT_MAX);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glm::mat4 matrizCamera = glm::lookAt(glm::vec3{3, 3, 0}, glm::vec3{0, 0, 0}, glm::vec3{0, 1, 0});
    glMultMatrixf(glm::value_ptr(matrizCamera));*/

    //Sun sun(10, LightParameters{1.0, 0.0, 1.0, 0.2}, "textures/sun.jpg");

    Planet mercury(0.011, 0.1, 20, 4.879, "textures/mercury.jpg");

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

        //sun.illuminate();
        mercury.show();

        ship.show(window);
        // obj.show();
        orbits.show();

        window.display();
    }

    return EXIT_SUCCESS;
}
