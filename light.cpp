#include "light.hpp"


light :: light(glm :: vec3 light_colour, glm :: vec3 light_direction) {

    ambient = light_colour.x;
    diffuse = light_colour.y;
    specular = light_colour.z;

    this -> light_direction = light_direction;
}


light :: light(glm :: vec3 light_colour, glm :: vec3 light_direction, glm :: vec3 light_position) {

    ambient = light_colour.x;
    diffuse = light_colour.y;
    specular = light_colour.z;

    this -> light_direction = light_direction;
    this -> light_position = light_position;
}
