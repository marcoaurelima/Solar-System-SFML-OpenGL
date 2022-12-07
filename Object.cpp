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
        std::cout << textures[i][0] << "  " << textures[i][1] << std::endl;
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
             //std::cout << faces[i][j].v << " " << faces[i][j].vt << " " << faces[i][j].vn << " ";
        }
         //std::cout << std::endl;
    }
}

void Object::loadTextureFile(std::string filename)
{
    // Fazer leitura da textura
    texture = SOIL_load_OGL_texture(
        filename.c_str(),
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y);

    if (texture == 0)
    {
        std::cout << "Erro ao carregar a textura: " << filename << "\n"
                  << SOIL_last_result() << "\n";
    }
}

void Object::show()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for (unsigned i = 0; i < faces.size(); i++)
    {
        glBegin(GL_TRIANGLES);
        for (unsigned j = 0; j < faces[i].size(); j++)
        {
            GLfloat x, y, z;
            unsigned index;

            index = faces[i][j].vn - 1;
            x = normal[index][0];
            y = normal[index][1];
            z = normal[index][2];
            glNormal3f(x, y, z);

            index = faces[i][j].vt - 1;
            x = textures[index][0];
            y = textures[index][1];
            glTexCoord2f(x, y);
            
            index = faces[i][j].v - 1;
            x = vertices[index][0];
            y = vertices[index][1];
            z = vertices[index][2];
            glVertex3f(x, y, z);

        }

        glEnd();
    }

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);

    glFlush();
}