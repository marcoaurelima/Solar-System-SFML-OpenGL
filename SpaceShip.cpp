#include "SpaceShip.h"

const float MIN_TOLERANCE_JOYSTICK_R = 12;
const float MIN_TOLERANCE_JOYSTICK_L = -10;
const float MAX_TOLERANCE_JOYSTICK_L = 10;

SpaceShip::SpaceShip(glm::vec3 initialPosition, Size windowSize)
    : camPosition(initialPosition), windowSize(windowSize) {

    std::string texturePath = "textures/cockpit.png";
    textureCockpit = SOIL_load_OGL_texture(
            texturePath.c_str(),
            SOIL_LOAD_RGBA,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_INVERT_Y);

    if (textureCockpit == 0)
    {
        std::cout << "Erro ao carregar a textura: " << texturePath << "\n"
                  << SOIL_last_result() << "\n";
    }

    spaceShipObj.loadFromFile("models/star_destroyer.obj");
}

SpaceShip::~SpaceShip(){}

float max(float x, float y){
    if(x > y){
        return x;
    } return y;
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
        this->velocity = max(0.01, this->velocity - (this->velocity * 0.5));
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
        if(sf::Joystick::isButtonPressed(0, 0)){
            this->velocity += 1.5;
        } else if(sf::Joystick::isButtonPressed(0, 1)){
            this->velocity = max(0.01, this->velocity - (this->velocity * 0.5));
        }
        this->handleJoystickInput();
    } else {
        handleKeyboardInput();
        this->moveCameraView(mousePos);
    }

}

glm::vec3 SpaceShip::getCamPosition(){
    return camPosition;
}

void SpaceShip::drawCockpit(glm::vec3 pos){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureCockpit);

    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);
    glTranslatef(0, 0, 0);
    glRotatef(45, 0, 1, 0);
    glRotatef(-90, 1, 0, 0); // Calibração para os polos ficarem em cima
    glTranslatef(0,0,0);

    GLUquadric* quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluQuadricNormals(quadric, GLU_SMOOTH);
    gluQuadricTexture(quadric, GL_TRUE);
    gluSphere(quadric, 2.5, 200, 200);
    gluDeleteQuadric(quadric);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
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

    glPushMatrix();
    glTranslatef(camPosition.x, camPosition.y-5, camPosition.z);
    glTranslatef(0,0,0);
    glRotatef(-angleX, 0, 1, 0);
    glTranslatef(0,0,0);
    spaceShipObj.show();
    glPopMatrix();

    drawCockpit(camPosition);
}