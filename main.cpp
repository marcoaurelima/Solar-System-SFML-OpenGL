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
}

void drawCockpit(GLuint texture, glm::vec3 pos){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);
    glTranslatef(0, 0, 0);
    glRotatef(-90, 1, 0, 0); // Calibração para os polos ficarem em cima
    glTranslatef(0,0,0);

    GLUquadric* quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluQuadricNormals(quadric, GLU_SMOOTH);
    gluQuadricTexture(quadric, GL_TRUE);
    gluSphere(quadric, 50, 200, 200);
    gluDeleteQuadric(quadric);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
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
    window.setMouseCursorVisible(false);
    window.setVerticalSyncEnabled(true);
    window.setJoystickThreshold(10);

    initValues();
    float k = 1;
    float distance = 5;

    std::string texturePath = "textures/cockpit.png";
    GLuint texture = SOIL_load_OGL_texture(
            texturePath.c_str(),
            SOIL_LOAD_RGBA,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_INVERT_Y);

    if (texture == 0)
    {
        std::cout << "Erro ao carregar a textura: " << texturePath << "\n"
                  << SOIL_last_result() << "\n";
    }

    Sun sun(1000, LightParameters{1.0, 0.0, 1.0, 0.2}, "textures/sun.jpg");

    Planet mercury(0.011, (2.500*k), 600 * distance, 4.879, "textures/mercury.jpg");
    Planet venus(0.006, (0.9836*k), 652* distance, 12.104, "textures/venus.jpg");
    Planet earth(0.1574, (0.6000*k), 693* distance, 12.742, "textures/earth.jpg");
    Planet mars(0.0866, (0.3157*k), 772* distance, 6.779, "textures/mars.jpg");
    Planet jupyter(4.5583, (0.0499*k), 1322* distance, 139.820, "textures/jupiter.jpg");
    Planet saturn(3.6840, (0.0207*k), 1971* distance, 116.460, "textures/saturn.jpg");
    Planet uranus(1.4794, (0.0071*k), 3413* distance, 50.724, "textures/uranus.jpg");
    Planet neptune(0.9719, (0.0036*k), 5040* distance, 49.244, "textures/neptune.jpg");


    Orbits orbits;
    orbits.add(mercury.getOrbitValue());
    orbits.add(venus.getOrbitValue());
    orbits.add(earth.getOrbitValue());
    orbits.add(mars.getOrbitValue());
    orbits.add(jupyter.getOrbitValue());
    orbits.add(saturn.getOrbitValue());
    orbits.add(uranus.getOrbitValue());
    orbits.add(neptune.getOrbitValue());

    SpaceShip ship(glm::vec3(1000, 100, 0.0), Size(w, h));

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
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ship.show(window);

        sun.illuminate();

        mercury.show();
        venus.show();
        earth.show();
        mars.show();
        jupyter.show();
        saturn.show();
        uranus.show();
        neptune.show();

        orbits.show();

        drawCockpit(texture, ship.getCamPosition());

        window.display();
    }

    return EXIT_SUCCESS;
}