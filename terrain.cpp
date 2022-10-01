#define GL_GLEXT_PROTOTYPES
#include "terrain.hpp"
#include <GLFW/glfw3.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <cmath>

terrain :: terrain(glm :: ivec3 chunk_parameters, glm :: vec3 observer_position) {

    this -> chunk_side_length = chunk_parameters.z;
    this -> chunks_x = chunk_parameters.x;
    this -> chunks_y = chunk_parameters.y;
    this -> num_chunks = this -> chunks_x * this -> chunks_y;
    this -> terrain_side_chunks = chunk_parameters.x;
    this -> chunk_side_vertices = chunk_parameters.z + 1;

    build_gradient_fields();
    build_chunks();
    // build_elements();

}


terrain :: terrain(int terrain_side_chunks, int chunk_side_vertices, glm :: vec3 camera_pos) {

    int chunk_len = chunk_side_vertices - 1;

    // check for correct chunk size
    if (chunk_len <= 0 || (chunk_len & (chunk_len - 1)) != 0) {
        std :: cerr << "Error: a chunk must have 2^n + 1 vertices per side (with a minimum of 2)." <<
        std :: endl << "However, you specified " <<  chunk_side_vertices  << " vertices per side." <<
        std :: endl;
        exit(1);
    }

    this -> terrain_side_chunks = terrain_side_chunks;
    this -> chunk_side_vertices = chunk_side_vertices;

    // there has to be at least one LOD
    this -> det_levels = 1;

    // but it is better to have several
    while (chunk_len >>= 1) ++det_levels;

    build_gradient_fields();
    build_chunks();

    //set_buffers();

}

// void terrain :: build_elements() {
//
//     glGenVertexArrays(1, &vertex_array);
//     glGenBuffers(det_levels, element_buffers.data());
// }
//
//
// void terrain :: build_indices() {
//
//     for (int index_y = 0; index_y < vertices_per_side - 1; index_y++) {
//
//         for (int index_x = 0; index_x < vertices_per_side - 1; index_x++) {
//
//             indices.push_back(index_x + (index_y) * vertices_per_side);
//             indices.push_back(index_x + (index_y) * vertices_per_side + 1);
//             indices.push_back(index_x + (index_y + 1) * vertices_per_side);
//
//             indices.push_back(index_x + (index_y) * vertices_per_side + 1);
//             indices.push_back(index_x + (index_y + 1) * vertices_per_side + 1);
//             indices.push_back(index_x + (index_y + 1) * vertices_per_side);
//         }
//     }
//
// }

void terrain :: build_chunks() {

    for (int i = 0; i < terrain_side_chunks; i++) {
        std :: vector <chunk> chunk_row;

        for (int k = 0; k < terrain_side_chunks; k++) chunk_row.emplace_back(chunk_side_length, chunk_side_length * i, chunk_side_length * k, this);
        chunks.push_back(chunk_row);
    }

    chunk_selector_x = chunks_x - 1;
    chunk_selector_y = chunks_y - 1;

}


void terrain :: build_gradient_fields() {

    //gradient_fields.emplace_back(0, 0, terrain_side_chunks, chunk_side_vertices - 1, 4400, 155.f);
    gradient_fields.emplace_back(0, 0, terrain_side_chunks, chunk_side_vertices - 1, 800, 55.f);
    gradient_fields.emplace_back(0, 0, terrain_side_chunks, chunk_side_vertices - 1, 77, 22.f);
    gradient_fields.emplace_back(0, 0, terrain_side_chunks, chunk_side_vertices - 1, 120, 31.f);
    gradient_fields.emplace_back(0, 0, terrain_side_chunks, chunk_side_vertices - 1, 5, 1.f);

}


// float terrain :: get_max_height() {
//     if (!gradient_fields.size()) return 0.f;
//     float height = 0;
//     for (auto& field : gradient_fields) height += field.amplitude;
//     return height;
// }


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


float terrain :: fractional_bm(float pos_x, float pos_y) {
    float terrain_height = 0;
    for (auto& gradient_field : gradient_fields) terrain_height += gradient_field.get_height(pos_x, pos_y);
    return terrain_height;
}


float terrain :: get_terrain_height(float pos_x, float pos_y) {
    float warp_x = fractional_bm(pos_x + 12, pos_y);
    float warp_y = fractional_bm(pos_x, pos_y + 52);
    return pow(0.1 * fractional_bm(pos_x + 4 * warp_x, pos_y + 4 * warp_y), 2) + pow(0.1 * fractional_bm(pos_y + 4 * warp_y, pos_x + 4 * warp_x), 2);
}


void terrain :: draw() {
    for (auto row : chunks) for (auto chunk : row) chunk.draw();
}
