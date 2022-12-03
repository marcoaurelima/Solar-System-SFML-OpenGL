#include "SpaceShip.h"

const float MIN_TOLERANCE_JOYSTICK_R = 12;
const float MIN_TOLERANCE_JOYSTICK_L = -10;
const float MAX_TOLERANCE_JOYSTICK_L = 10;

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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
        this->velocity += 1.5;
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
        this->velocity -= 1.5;
    }

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
    float v = sf::Joystick::getAxisPosition(0, sf::Joystick::V) * -1;

    if (u < MIN_TOLERANCE_JOYSTICK_R && u > 0)
        u = 0;
    if(v < MIN_TOLERANCE_JOYSTICK_R && v > 0)
        v = 0;

    if(u != 0 && v != 0){
        angleX += u * sensibility;
        angleY += v * sensibility;

        glm::vec3 front;
        front.x = (float)(cos(glm::radians(angleX)) * cos(glm::radians(angleY)));
        front.y = (float)(sin(glm::radians(angleY)));
        front.z = (float)(sin(glm::radians(angleX)) * cos(glm::radians(angleY)));
        camAt = glm::normalize(front);
    }

    std::cout << y << std::endl;
    if(y < MIN_TOLERANCE_JOYSTICK_L){
        camPosition += velocity * camAt;
    } else if(y > MAX_TOLERANCE_JOYSTICK_L){
        camPosition -= velocity * camAt;
    }

    if (x < MIN_TOLERANCE_JOYSTICK_L)
    {
        camPosition -= glm::normalize(glm::cross(camAt, camUp)) * velocity;
    }else if(x > MAX_TOLERANCE_JOYSTICK_L){
        camPosition += glm::normalize(glm::cross(camAt, camUp)) * velocity;
    }
}

void SpaceShip::moveCameraPosition(sf::Vector2i mousePos) {
    if (sf::Joystick::isConnected(0))
    {
        this->handleJoystickInput();
        if(sf::Joystick::isButtonPressed(0, 0)){
            this->velocity += 1.5;
        } else if(sf::Joystick::isButtonPressed(0, 1)){
            this->velocity -= 1.5;
        }
    } else {
        handleKeyboardInput();
        this->moveCameraView(mousePos);
    }

}

glm::vec3 SpaceShip::getCamPosition(){
    return camPosition;
}

void SpaceShip::show(sf::Window &window)
{
    this->moveCameraPosition(sf::Mouse::getPosition(window));

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, windowSize.w / windowSize.h, 0.2, INT_MAX);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glm::mat4 matrizCamera = glm::lookAt(camPosition, camPosition + camAt, camUp);
    glMultMatrixf(glm::value_ptr(matrizCamera));
}