#include "Orbits.h"

Orbits::Orbits()
{
}

Orbits::~Orbits()
{
}

void Orbits::add(GLdouble size)
{
    sizes.push_back(size);
}

void Orbits::show()
{
    for (GLdouble s : sizes)
    {
        // Desenhar orbita
        GLUquadric *quadric;
        quadric = gluNewQuadric();

        glPushMatrix();
        glRotatef(0, 0, -1, 0);
        glRotatef(90, 1, 0, 0);
        glTranslatef(0, 0, 0);
        gluDisk(quadric, s, s + 1, 600, 600);
        glPopMatrix();
        gluDeleteQuadric(quadric);
    }
}
