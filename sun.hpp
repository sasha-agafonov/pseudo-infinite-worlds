#ifndef SUN_HPP
#define SUN_HPP

#include <glm/ext.hpp>
#include <vector>
#include "light.hpp"


class sun : public light {

    public:

        sun(glm :: vec3 sun_position,
            glm :: vec3 sun_colour,
            glm :: vec3 light_direction,
            glm :: vec3 light_ambient,
            glm :: vec3 light_diffuse,
            glm :: vec3 light_specular);

        void build_vertices();
        void build_indices();
        void set_buffers();

        int number_vertices;
        unsigned int vao, vbo, ebo;

        glm :: vec3 sun_position;
        glm :: vec3 sun_colour;
        std :: vector <float> sun_vertices;
        std :: vector <unsigned int> sun_indices;

};

#endif
