#include "camera.hpp"
#include <iostream>
#include <math.h>


camera :: camera(glm :: vec3 look_from, glm :: vec3 look_at, glm :: vec3 look_up, int chunk_side_length) {

    this -> look_from = look_from;
    this -> look_at = look_at;
    this -> look_up = look_up;

    this -> chunk_side_length = chunk_side_length;
    discrete_position = look_from;
    previous_time = 0;
}


glm :: mat4 camera :: get_view_mx(double time) {

    previous_time = time;
    return glm :: lookAt(look_from, look_at, look_up);
}


glm :: mat4 camera :: auto_move_forward(double time) {

    float delta_time = time - previous_time;
    previous_time = time;
    look_from.z -= delta_time;
    look_at.z -= delta_time;
    //std :: cout << look_from.z << std :: endl;
    return glm :: lookAt(look_from, look_at, look_up);
}


glm :: mat4 camera :: auto_move_backwards(double time) {

    float delta_time = time - previous_time;
    previous_time = time;
    look_from.z += delta_time;
    look_at.z += delta_time;
    //std :: cout << look_from.z << std :: endl;
    return glm :: lookAt(look_from, look_at, look_up);
}


void camera :: process_position() {

    // std :: cout << remainder(14, 4) << std ::endl;
    // std :: cout << 14 / 4 << std :: endl;

    // std :: cout << "position: "<< look_from.x << " " <<look_from.y << " " << look_from.z << std :: endl;
    //
    // glm ::
    // std :: cout << "discretized_position " << std :: endl;
    float allowed_position_change = float(chunk_side_length) / 2.f;
    //std :: cout << allowed_position_change << std :: endl;

    glm :: vec3 position_change = discrete_position - look_from;

    //std :: cout << position_change.z << std :: endl;

    if (position_change.x > allowed_position_change
    ||  position_change.x < -allowed_position_change
    ||  position_change.z > allowed_position_change
    ||  position_change.z > -allowed_position_change) {

        // std :: cout << "sadasad" << std :: endl;

        glm :: ivec2 discrete_direction(0.f, 0.f);

        if (position_change.x > allowed_position_change) discrete_direction.x += chunk_side_length;
        if (position_change.x < -allowed_position_change) discrete_direction.x -= chunk_side_length;
        if (position_change.z > allowed_position_change) discrete_direction.y += chunk_side_length;
        if (position_change.z > -allowed_position_change) discrete_direction.y -= chunk_side_length;

        discrete_position.x += discrete_direction.x;
        discrete_position.z += discrete_direction.y;

        polite_terrain -> update_scene(discrete_direction);
    }

}


// glm :: ivec3 camera :: discretise_direction(glm :: vec3 direction) {
//
// }
