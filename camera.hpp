#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/ext.hpp>
#include "terrain.hpp"


class camera {

    public:

        camera(glm :: vec3, glm :: vec3, glm :: vec3, int);

        glm :: mat4 get_view_mx(double time);
        glm :: mat4 auto_move_forward(double time);
        glm :: mat4 auto_move_backwards(double time);
        glm :: ivec3 discretise_direction(glm :: vec3 direction);

        void process_position();

        double previous_time;
        terrain* polite_terrain;

        glm :: vec3 look_from;
        glm :: vec3 look_at;
        glm :: vec3 look_up;

        int chunk_side_length;

        glm :: vec3 discrete_position;

};

#endif
