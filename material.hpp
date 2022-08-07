#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <glm/ext.hpp>

class material {

    public:

        material(glm :: vec3 ambient, glm :: vec3 diffuse, glm :: vec3 specular, float shininess);

        glm :: vec3 ambient;
        glm :: vec3 diffuse;
        glm :: vec3 specular;

        float shininess;

};

#endif
