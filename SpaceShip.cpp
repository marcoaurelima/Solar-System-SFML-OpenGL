#include "SpaceShip.h"

SpaceShip::SpaceShip(glm::vec3 initialPosition, Size windowSize)
    : position(initialPosition), windowSize(windowSize) {}

SpaceShip::~SpaceShip()
{
}

void SpaceShip::show(sf::Window &window)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, windowSize.w / windowSize.h, 0.2, INT_MAX);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(cameraAngleX, 0, 1, 0);
    glRotatef(cameraAngleY, 1, 0, 0);
    glm::mat4 matrizCamera = glm::lookAt(position, at, glm::vec3(0, 1, 0));
    glMultMatrixf(glm::value_ptr(matrizCamera));

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        position.x -= 5;
        at.x -= 5;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        position.x += 5;
        at.x += 5;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        position.z -= 5;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        position.z += 5;
    }

    sf::Vector2i mousepos = sf::Mouse::getPosition(window);

    if(mousepos.x < 0){ mousepos.x = 0; }
    if(mousepos.y < 0){ mousepos.y = 0; }

    int centerX = window.getSize().x/2;
    int centerY = window.getSize().y/2;


    cameraAngleX = ((GLfloat) centerX - mousepos.x)/2;
    cameraAngleY = ((GLfloat) centerY - mousepos.y)/1;
    
}