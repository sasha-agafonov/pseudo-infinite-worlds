#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/ext.hpp>
#include "terrain.hpp"


class camera {

    public:

        camera(glm :: vec3, glm :: vec3, glm :: vec3, terrain*);

        glm :: mat4 get_view_mx();
        glm :: ivec3 discretise_direction(glm :: vec3 direction);

        void process_position();
        void adjust_height();
        void toggle_camera_shake();
        void run();

        int adjust_rate;
        int adjust_step;
        int chunk_side_length;

        glm :: vec3 look_from;
        glm :: vec3 look_at;
        glm :: vec3 look_up;
        glm :: vec3 discrete_position;

    private:

        bool camera_shake;
        bool disaligned;

        double curr_time;
        double prev_time;

        terrain* polite_terrain;

        void shake();
        void stabilise();
        void update_chunk_distances();

        void auto_move_forward();
        void auto_move_backwards();


};

#endif
