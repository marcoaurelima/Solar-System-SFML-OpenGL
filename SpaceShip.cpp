#include "SpaceShip.h"

SpaceShip::SpaceShip(glm::vec3 initialPosition, Size windowSize)
: position(initialPosition), windowSize(windowSize){}

SpaceShip::~SpaceShip()
{
}

void SpaceShip::show()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, windowSize.w / windowSize.h, 0.2, INT_MAX);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glm::mat4 matrizCamera = glm::lookAt(position, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glMultMatrixf(glm::value_ptr(matrizCamera));
}