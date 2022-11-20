#include "SpaceShip.h"

SpaceShip::SpaceShip(glm::vec3 initialPosition, Size windowSize)
: position(initialPosition), windowSize(windowSize){}

SpaceShip::~SpaceShip()
{
}

void SpaceShip::show(sf::Window& window)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, windowSize.w / windowSize.h, 0.2, INT_MAX);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glm::mat4 matrizCamera = glm::lookAt(position, at, glm::vec3(0, 1, 0));
    glMultMatrixf(glm::value_ptr(matrizCamera));


    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        position.x -= 5;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        position.x += 5;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        position.z -= 5;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        position.z += 5;
    }


    sf::Vector2i mousepos = sf::Mouse::getPosition(window);

    std::cout << "mousepos: " << mousepos.x << " - " << mousepos.y << std::endl;

}