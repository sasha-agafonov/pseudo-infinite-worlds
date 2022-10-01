#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/ext.hpp>
#include "terrain.hpp"


class camera {

    public:

        camera(glm :: vec3, glm :: vec3, glm :: vec3, int, terrain*);

        glm :: mat4 get_view_mx(double time);
        glm :: mat4 auto_move_forward(double time);
        glm :: mat4 auto_move_backwards(double time);
        glm :: ivec3 discretise_direction(glm :: vec3 direction);

        void process_position(double time);
        void adjust_height();


        int adjust_rate;
        int adjust_step;

        double previous_time;


        glm :: vec3 look_from;
        glm :: vec3 look_at;
        glm :: vec3 look_up;

        int chunk_side_length;

        glm :: vec3 discrete_position;

    private:

        bool disaligned;

        terrain* polite_terrain;

        void shake(double time);
        void stabilise();


};

#endif
