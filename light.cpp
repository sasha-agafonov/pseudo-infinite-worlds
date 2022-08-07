#include "light.hpp"


light :: light(glm :: vec3 direction, glm :: vec3 ambient,
               glm :: vec3 diffuse,   glm :: vec3 specular) {

    this -> direction = direction;
    this -> ambient = ambient;
    this -> diffuse = diffuse;
    this -> specular = specular;

}
