#include "camera.hpp"
#include <iostream>
#include <cmath>
#include "extern.hpp"

#define STAB_RATE 0.01

camera :: camera(glm :: vec3 look_from, glm :: vec3 look_at, glm :: vec3 look_up, int chunk_side_length, terrain* polite_terrain) {

    this -> look_from = look_from;
    this -> look_at = look_at;
    this -> look_up = look_up;
    this -> chunk_side_length = chunk_side_length;
    this -> polite_terrain = polite_terrain;

    adjust_rate = 23;
    adjust_step = 0;

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


void camera :: adjust_height() {

        look_from.y = 4 + polite_terrain -> get_terrain_height(look_from.x, look_from.z);

}


// void camera :: shake() {
//
// }

void camera :: stabilise() {

    if (look_up.x <= STAB_RATE && look_up.x >= -STAB_RATE) look_up.x = 0.f;

    if (look_up.x < 0.f) look_up.x += STAB_RATE;

    else if (look_up.x > 0.f) look_up.x -= STAB_RATE;

    else disaligned = false;

}


void camera :: shake(double time) {

    if (!disaligned) disaligned = true;

    // sideways
    look_up.x = 0.015f * (std :: sin(0.2f * time));

    // up/down
    look_from.y += 0.5f * (std :: sin(0.5f * time));
    look_at.y = look_from.y;

}

void camera :: process_position(double time) {

    adjust_height();

    if (extern_movement_mode == AUTO_FORWARD || extern_movement_mode == AUTO_BACKWARDS) shake(time);
    else if (disaligned) stabilise();




    float allowed_position_change = float(chunk_side_length) / 2.f;

    glm :: vec3 position_change = discrete_position - look_from;

    if (position_change.x > allowed_position_change
    ||  position_change.x < - allowed_position_change
    ||  position_change.z > allowed_position_change
    ||  position_change.z < - allowed_position_change) {

        glm :: ivec2 discrete_direction(0, 0);

        if (position_change.x > allowed_position_change) discrete_direction.x -= chunk_side_length;
        if (position_change.x < - allowed_position_change) discrete_direction.x += chunk_side_length;
        if (position_change.z > allowed_position_change) discrete_direction.y -= chunk_side_length;
        if (position_change.z < - allowed_position_change) discrete_direction.y += chunk_side_length;

        discrete_position.x += discrete_direction.x;
        discrete_position.z += discrete_direction.y;

        polite_terrain -> update_scene(glm :: ivec2(discrete_direction.x, discrete_direction.y));
    }

}
