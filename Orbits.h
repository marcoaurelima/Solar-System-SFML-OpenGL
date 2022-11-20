#ifndef ORBITS_H
#define ORBITS_H

#pragma once

#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>

class Orbits
{
public:
    Orbits();
    ~Orbits();

    void add(GLdouble size);

    void show();
private:
    std::vector<GLdouble> sizes;
};

#endif