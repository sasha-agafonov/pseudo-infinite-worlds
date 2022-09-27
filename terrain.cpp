#define GL_GLEXT_PROTOTYPES
#include "terrain.hpp"
#include <GLFW/glfw3.h>
#include <algorithm>
#include <iostream>
#include <iterator>

// gradient grid size
#define GRADIENTS_PER_SIDE 2

// shortest distance between consequtive gradients
#define GRADIENT_OFFSET 12

terrain :: terrain(glm :: ivec3 chunk_parameters, glm :: vec3 observer_position) {

    this -> chunk_side_length = chunk_parameters.z;
    this -> chunks_x = chunk_parameters.x;
    this -> chunks_y = chunk_parameters.y;
    this -> num_chunks = this -> chunks_x * this -> chunks_y;

    initialise_gradient_fields();
    initialise_chunks();

}


void terrain :: initialise_chunks() {

    for (auto i = 0; i < chunks_y; i++) {

        std :: vector <chunk> chunk_row;

        for (auto k = 0; k < chunks_x; k++) chunk_row.emplace_back(chunk_side_length, chunk_side_length * i, chunk_side_length * k, this);

        chunks.push_back(chunk_row);
    }

    chunk_selector_x = chunks_x - 1;
    chunk_selector_y = chunks_y - 1;

}


void terrain :: initialise_gradient_fields()
{
    gradient_fields.emplace_back(0, 0, chunks_x, chunk_side_length, 800, 55.f);
    gradient_fields.emplace_back(0, 0, chunks_x, chunk_side_length, 77, 22.f);
    gradient_fields.emplace_back(0, 0, chunks_x, chunk_side_length, 120, 31.f);
    gradient_fields.emplace_back(0, 0, chunks_x, chunk_side_length, 5, 1.f);

}


void terrain :: update_scene(glm :: ivec2 position_change) {

//    std :: cout << "pos ch x: " << position_change.x << "pos ch y: " << position_change.y << std :: endl;

    //std :: cout << "chunk x pos: " << chunks[chunk_selector_x][chunk_selector_y].chunk_start.x << " pos Y: " << chunks[chunk_selector_x][chunk_selector_y].chunk_start.y << std ::endl;


    // forward
    if (position_change.y < 0) {
    //    std :: cout << "fw" << std :: endl;
        for (auto& chunk : chunks[chunk_selector_y]) chunk.update_vertices(position_change.y * chunks_y, 0);
        (chunk_selector_y == 0) ? chunk_selector_y = chunks_y - 1 : chunk_selector_y--;
    }

    // backwards
    if (position_change.y > 0) {
    //    std :: cout << "bw" << std :: endl;
        for (auto& chunk : chunks[chunk_selector_y]) chunk.update_vertices(position_change.y * chunks_y, 0);
        (chunk_selector_y == chunks_y - 1) ? chunk_selector_y = 0 : chunk_selector_y++;
    }

    if (position_change.x > 0) {
        std :: cout << "lt" << std :: endl;
        for (auto& row : chunks) std :: rotate(chunks.begin(), std :: next(chunks.begin()), chunks.end());
        for (auto& row : chunks) for (auto& chunk : row) chunk.update_vertices(0, position_change.x);
    }

    if (position_change.x < 0) {
        std :: cout << "rt" << std :: endl;
        for (auto& row : chunks) std :: rotate(chunks.rbegin(), std :: next(chunks.rbegin()), chunks.rend());
        for (auto& row : chunks) for (auto& chunk : row) chunk.update_vertices(0, position_change.x);
    }
}

float terrain :: fractional_bm(int pos_x, int pos_y) {
    float terrain_height = 0;
    for (auto& gradient_field : gradient_fields) terrain_height += gradient_field.get_height(pos_x, pos_y);
    return terrain_height;
}


float terrain :: get_terrain_height(int pos_x, int pos_y) {
    //return -fabs(fractional_bm(pos_x, pos_y));

    float warp_x = fractional_bm(pos_x + 12, pos_y);
    float warp_y = fractional_bm(pos_x, pos_y + 52);

    // float fbm = fractional_bm(pos_x, pos_y);
    // for (int i = 1; i < 10; i++) fbm = fractional_bm(pos_x + fbm, pos_y + fbm);

    return pow(0.1 * fractional_bm(pos_x + 4 * warp_x, pos_y + 4 * warp_y), 2) + pow(0.1 * fractional_bm(pos_y + 4 * warp_y, pos_x + 4 * warp_x), 2);
    //return fractional_bm(fbm * 12 + pos_x, fbm * 12 + pos_y);
    //return fractional_bm(pos_x + fractional_bm(pos_x, pos_y), pos_y + fractional_bm(pos_x, pos_y));
    // float terrain_height = 0;
    //
    // for (auto& gradient_field : gradient_fields) terrain_height += gradient_field.get_height(pos_x, pos_y);
    // //terrain_height += gradient_fields[0].get_height(3 + pos_x, 3 + pos_y);
    // return terrain_height; //get_terrain_height(int pos_x, int pos_y);
}


void terrain :: draw() {
    for (auto row : chunks) for (auto chunk : row) chunk.draw();
}
