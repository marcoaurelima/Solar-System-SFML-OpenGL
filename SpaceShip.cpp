#include "SpaceShip.h"

SpaceShip::SpaceShip(glm::vec3 initialPosition, Size windowSize)
    : camPosition(initialPosition), windowSize(windowSize) {}

SpaceShip::~SpaceShip()
{
}

void SpaceShip::moveCameraView(sf::Vector2i mousePos)
{
    if(mousePos.x < 0){ mousePos.x = 0; }
    if(mousePos.y < 0){ mousePos.y = 0; }

    if (firstMouse)
    {
        lastX = (float)mousePos.x;
        lastY = (float)mousePos.y;
        firstMouse = false;
    }

    float xOffset = (float)mousePos.x - lastX;
    float yOffset = lastY - (float)mousePos.y; // reversed since y-coordinates go from bottom to top
    lastX = (float)mousePos.x;
    lastY = (float)mousePos.y;

    xOffset *= sensibility;
    yOffset *= sensibility;

    angleX += xOffset;
    angleY += yOffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (angleY > 89.0f)
        angleY = 89.0f;
    if (angleY < -89.0f)
        angleY = -89.0f;

    glm::vec3 front;
    front.x = (float)(cos(glm::radians(angleX)) * cos(glm::radians(angleY)));
    front.y = (float)(sin(glm::radians(angleY)));
    front.z = (float)(sin(glm::radians(angleX)) * cos(glm::radians(angleY)));
    camAt = glm::normalize(front);
}

void SpaceShip::moveCameraPosition() {
    float cameraSpeed = 2.5;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        camPosition += cameraSpeed * camAt;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        camPosition -= cameraSpeed * camAt;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        camPosition -= glm::normalize(glm::cross(camAt, camUp)) * cameraSpeed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        camPosition += glm::normalize(glm::cross(camAt, camUp)) * cameraSpeed;
    }
}

void SpaceShip::show(sf::Window &window)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, windowSize.w / windowSize.h, 0.2, INT_MAX);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    glm::mat4 matrizCamera = glm::lookAt(camPosition, camPosition + camAt, camUp);
    glMultMatrixf(glm::value_ptr(matrizCamera));

    this->moveCameraPosition();
    this->moveCameraView(sf::Mouse::getPosition(window));
}