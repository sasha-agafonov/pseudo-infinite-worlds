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

    initialise_gradients();
    initialise_chunks();


}

// void terrain :: initialise_chunk_layout(int chunks_x, int chunks_y) {
//
//     for (int i = 0; i < chunks_x; i++) {
//         std :: vector <glm :: ivec2> layout_row;
//         for (int k = 0; k < chunks_y; k++) layout_row.push_back(glm :: ivec2(i * chunk_side_length, k * chunk_side_length));
//         chunk_layout.push_back(layout_row);
//     }
// }

void terrain :: initialise_chunks() {

    for (auto i = 0; i < chunks_y; i++) {

        std :: vector <chunk> chunk_row;

        for (auto k = 0; k < chunks_x; k++) chunk_row.emplace_back(chunk_side_length, chunk_side_length * i, chunk_side_length * k, this);

        chunks.push_back(chunk_row);
    }

    chunk_selector_x = chunks_x - 1;
    chunk_selector_y = chunks_y - 1;

}


void terrain :: initialise_gradients() {


    gradient_fields.emplace_back(0, 0, chunks_x, chunk_side_length, 1, 44.f);
    gradient_fields.emplace_back(0, 0, chunks_x, chunk_side_length, 4, 4.f);
    gradient_fields.emplace_back(0, 0, chunks_x, chunk_side_length, 2, 1.f);

}

// void terrain :: initialise_gradients() {
//
//     int totall = chunks_x * chunk_side_length;
//
//
//     for (auto i = 0; i < chunks_y * chunk_side_length; i++) {
//         std :: vector <gradient> gradient_row;
//         for (auto k = 0; k < GRADIENTS_PER_SIDE; k++) {
//             gradient_row.emplace_back();
//         }
//     }
// }


// void terrain :: initialise_gradients(int chunks_x, int chunks_x) {
//
//     for (int i = 0; i < chunk_side_length * sqrt(num_chunks); i += GRADIENT_OFFSET) {
//
//         std :: vector <gradient> gradient_row;
//
//         for (int k = 0; k < chunk_side_length * sqrt(num_chunks); k += GRADIENT_OFFSET) {
//
//             gradient_row.emplace_back(i, k);
//
//         }
//
//         gradients.push_back(gradient_row);
//     }
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


float terrain :: get_terrain_height(int pos_x, int pos_y) {

    float terrain_height = 0;

    for (auto& gradient_field : gradient_fields) terrain_height += gradient_field.get_height(pos_x, pos_y);

    return terrain_height;
}




void terrain :: draw() {
    for (auto row : chunks) for (auto chunk : row) chunk.draw();
}
