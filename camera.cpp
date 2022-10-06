#include "camera.hpp"
#include "extern.hpp"
#include <iostream>
#include <cmath>
#include <GLFW/glfw3.h>

#define STAB_RATE 0.01

camera :: camera(glm :: vec3 look_from, glm :: vec3 look_at, glm :: vec3 look_up, terrain* polite_terrain) {

    this -> look_from = look_from;
    this -> look_at = look_at;
    this -> look_up = look_up;

    this -> polite_terrain = polite_terrain;
    this -> chunk_side_length = polite_terrain -> chunk_side_vertices - 1;
    this -> camera_shake = false;

    discrete_position = look_from;
    prev_time = 0;
}


glm :: mat4 camera :: get_view_mx() {

    return glm :: lookAt(look_from, look_at, look_up);

}


void camera :: auto_move_forward() {

    float delta_time = curr_time - prev_time;
    look_from.z -= delta_time;
    look_at.z -= delta_time;

}


void camera :: auto_move_backwards() {

    float delta_time = curr_time - prev_time;
    look_from.z += delta_time;
    look_at.z += delta_time;

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


void camera :: shake() {

    if (!disaligned) disaligned = true;

    // sideways
    look_up.x = 0.015f * (std :: sin(0.2f * curr_time));

    // up/down
    look_from.y += 0.3f * (std :: sin(0.65f * curr_time));
    look_at.y = look_from.y;

}

void camera :: toggle_camera_shake() {

    camera_shake ? camera_shake = false : camera_shake = true;

}


void camera :: run() {

    if (extern_movement_mode == AUTO_FORWARD || extern_movement_mode == AUTO_BACKWARDS) shake();
    else if (disaligned) stabilise();

    switch(extern_movement_mode) {

        case AUTO_FORWARD:
            auto_move_forward();
            break;

        case AUTO_BACKWARDS:
            auto_move_backwards();
            break;
    }
}


void camera :: update_chunk_distances() {

    for (auto& chunk_row : polite_terrain -> chunks) {
        for (auto& chunk : chunk_row) {
            chunk.update_distance(glm :: vec2(look_from.x, look_from.z));
        }
    }
}


void camera :: process_position() {

    // if (extern_movement_mode == FULL_STOP) {
    //     curr_time = glfwGetTime() * 34;
    //     prev_time = curr_time;
    //     return;
    //
    // }

    curr_time = glfwGetTime() * 34;
    adjust_height();

    if (extern_movement_mode != FULL_STOP) {


        run();

    }


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

    prev_time = curr_time;

        if (!extern_movement_mode == FULL_STOP) update_chunk_distances();

}
