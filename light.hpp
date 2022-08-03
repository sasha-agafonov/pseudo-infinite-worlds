#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <glm/ext.hpp>

class light {

    public:

        light(glm :: vec3 light_colour,
              glm :: vec3 light_direction);

        light(glm :: vec3 light_colour,
              glm :: vec3 light_direction,
              glm :: vec3 light_position);

        float ambient;
        float diffuse;
        float specular;

        glm :: vec3 light_direction;
        glm :: vec3 light_position;

};

#endif
