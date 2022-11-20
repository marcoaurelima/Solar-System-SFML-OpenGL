#include "Object.h"

Object::Object()
{
}

Object::~Object()
{
}

void Object::loadFromFile(std::string filename)
{
    std::ifstream file(filename);

    std::string str;
    if (file.is_open())
    {
        while (file >> str)
        {
            // Leitura dos vertices
            if (str == "v")
            {
                std::vector<float> verticesTEMP;
                for (unsigned int i = 0; i < 3; i++)
                {
                    file >> str;
                    verticesTEMP.push_back(std::stof(str));
                }
                vertices.push_back(verticesTEMP);
            }
            // leitura dos vertices de textura
            else if (str == "vt")
            {
                std::vector<float> verticesTEMP;
                for (unsigned int i = 0; i < 2; i++)
                {
                    file >> str;
                    verticesTEMP.push_back(std::stof(str));
                }
                textures.push_back(verticesTEMP);
            }
            // leitura dos valores das normais
            else if (str == "vn")
            {
                std::vector<float> verticesTEMP;
                for (unsigned int i = 0; i < 3; i++)
                {
                    file >> str;
                    verticesTEMP.push_back(std::stof(str));
                }
                normal.push_back(verticesTEMP);
            }
            // Leitura das faces
            else if (str == "f")
            {
                std::vector<Face> faceTEMP;
                while (file >> str)
                {
                    if (str[0] == '#' || str[0] == 'm' || str[0] == 'o' || str[0] == 'v' || str[0] == 'f' || str[0] == 's' || str[0] == 'u')
                    {
                        // Voltar 1 caractere do estream para não pular linha na proxima interação global
                        unsigned g = file.tellg();
                        file.seekg(g - 1);
                        break;
                    }

                    std::string values[3];

                    unsigned val_idx = 0;
                    for (unsigned int i = 0; i < str.size(); i++)
                    {
                        if (str[i] == '/')
                        {
                            val_idx++;
                            continue;
                        }
                        values[val_idx] += str[i];
                    }

                    Face face;
                    face.v = std::stoi(values[0]);
                    face.vt = std::stoi(values[1]);
                    face.vn = std::stoi(values[2]);

                    faceTEMP.push_back(face);
                }
                faces.push_back(faceTEMP);
            }
        }
    }
}

void Object::showOBJValues()
{

    std::cout << "------------------------------ vertices ------------------------------\n";
    for (unsigned int i = 0; i < vertices.size(); i++)
    {
        // std::cout << vertices[i][0] << "  " << vertices[i][1] << "  " << vertices[i][2] << std::endl;
    }

    std::cout << "\n------------------------------ textures ------------------------------\n";
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        // std::cout << textures[i][0] << "  " << textures[i][1] << std::endl;
    }

    std::cout << "\n------------------------------ normal ------------------------------\n";
    for (unsigned int i = 0; i < normal.size(); i++)
    {
        // std::cout << normal[i][0] << "  " << normal[i][1] << "  " << normal[i][2] << std::endl;
    }

    std::cout << "\n------------------------------ faces ------------------------------\n";
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        for (unsigned int j = 0; j < faces[i].size(); j++)
        {
            // std::cout << faces[i][j].v << " " << faces[i][j].vt << " " << faces[i][j].vn << " ";
        }
        // std::cout << std::endl;
    }
}

void Object::show()
{

    for (unsigned i = 0; i < faces.size(); i++)
    {
        if(i%100000==0)
        glColor3b(rand() % 255, rand() % 255, rand() % 255);

        glBegin(GL_TRIANGLES);
        for (unsigned j = 0; j < faces[i].size(); j++)
        {
            unsigned index = faces[i][j].v - 1;

            GLfloat x = vertices[index][0];
            GLfloat y = vertices[index][1];
            GLfloat z = vertices[index][2];

            glVertex3f(x, y, z);
        }
        glEnd();
    }

    glFlush();
}