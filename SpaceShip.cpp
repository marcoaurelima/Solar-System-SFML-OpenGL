#include "SpaceShip.h"

SpaceShip::SpaceShip(glm::vec3 initialPosition, Size windowSize)
    : camPosition(initialPosition), windowSize(windowSize) {}

SpaceShip::~SpaceShip()
{
}

void SpaceShip::moveCameraView(sf::Vector2i mousePos)
{
    mousePos.x = abs(mousePos.x);
    mousePos.y = abs(mousePos.y);

    if (firstMouse)
    {
        lastX = (float)mousePos.x;
        lastY = (float)mousePos.y;
        firstMouse = false;
    }

    float newPosX = ((float)mousePos.x / (windowSize.w / 2)) * 1700;

    float xOffset = newPosX - lastX;
    float yOffset = lastY - (float)mousePos.y; // reversed since y-coordinates go from bottom to top
    lastX = newPosX;
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

void SpaceShip::handleKeyboardInput(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        camPosition += velocity * camAt;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        camPosition -= velocity * camAt;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        camPosition -= glm::normalize(glm::cross(camAt, camUp)) * velocity;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        camPosition += glm::normalize(glm::cross(camAt, camUp)) * velocity;
    }
}

void SpaceShip::handleJoystickInput(){
    float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
    float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
    float u = sf::Joystick::getAxisPosition(0, sf::Joystick::U);
    float v = sf::Joystick::getAxisPosition(0, sf::Joystick::V);
    std::cout << "x: " << x << " y: " << y << std::endl;
    std::cout << "u: " << u << " v: " << v << std::endl;

    //camPosition += glm::vec3(y, x, 0);
    camAt += glm::vec3(u*100,v*100, 1);
}

void SpaceShip::moveCameraPosition() {
    if (sf::Joystick::isConnected(0))
    {
        std::cout << "joystick is connected" << std::endl;
        handleJoystickInput();
    } else {
        handleKeyboardInput();
    }

}

glm::vec3 SpaceShip::getCamPosition(){
    return camPosition;
}

void SpaceShip::show(sf::Window &window)
{
    this->moveCameraPosition();
    this->moveCameraView(sf::Mouse::getPosition(window));

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, windowSize.w / windowSize.h, 0.2, INT_MAX);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glm::mat4 matrizCamera = glm::lookAt(camPosition, camPosition + camAt, camUp);
    glMultMatrixf(glm::value_ptr(matrizCamera));
}