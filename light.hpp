#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <glm/ext.hpp>

class light {

    public:

        light(glm :: vec3 direction,
              glm :: vec3 ambient,
              glm :: vec3 diffuse,
              glm :: vec3 specular);

        glm :: vec3 direction;
        glm :: vec3 position;
        glm :: vec3 ambient;
        glm :: vec3 diffuse;
        glm :: vec3 specular;

};

#endif
