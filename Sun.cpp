#include "Sun.h"


Sun::Sun(GLdouble size, LightParameters lp, std::string texturePath)
{
    
    ambientLight =    new GLfloat[4]{0.0, 0.0, 0.0, 1.0};
    diffuseLight =    new GLfloat[4]{lp.diffuse, lp.diffuse, lp.diffuse, 1.0};
    specularlight =   new GLfloat[4]{lp.specular, lp.specular, lp.specular, 1.0};
    positionalLight = new GLfloat[4]{0.0, 0.0, 3.0, lp.positional};
    globalLight =     new GLfloat[4]{lp.global, lp.global, lp.global, 1.0};

    this->lp = lp;
    this->size = size;

    // Fazer leitura da textura
    texture = SOIL_load_OGL_texture(
        texturePath.c_str(),
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y);

    if (texture == 0)
    {
        std::cout << "Erro ao carregar a textura: " << texturePath << "\n"
                  << SOIL_last_result() << "\n";
    }
}

Sun::~Sun()
{
}

void Sun::createSphere(GLdouble radius)
{
    GLUquadric *quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluQuadricNormals(quadric, GLU_SMOOTH);
    gluQuadricTexture(quadric, GL_TRUE);
    gluSphere(quadric, radius, QTD_FACES, QTD_FACES);
    gluDeleteQuadric(quadric);
}

void Sun::illuminate()
{
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularlight);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalLight);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, false);
    glEnable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
    
    glPushMatrix();
    glRotatef(0, 1.0, 0.0, 0.0);
    glRotatef(0, 0.0, 1.0, 0.0);
    glLightfv(GL_LIGHT0, GL_POSITION, positionalLight);
    glTranslatef(positionalLight[0], positionalLight[1], positionalLight[2]);
    glColor3f(lp.diffuse, lp.diffuse, lp.diffuse);

    // Renderizar o sol
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    createSphere(size);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();

    glEnable(GL_LIGHTING);
}