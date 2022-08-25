#define GL_GLEXT_PROTOTYPES
#include "terrain.hpp"
#include <GLFW/glfw3.h>
#include <algorithm>
#include <iostream>
#include <iterator>

#define GRADIENTS_PER_SIDE 4

// shortest distance between consequtive gradients
#define GRADIENT_OFFSET 12

terrain :: terrain(glm :: ivec3 chunk_parameters, glm :: vec3 observer_position) {

    this -> chunk_side_length = chunk_parameters.z;
    this -> chunks_x = chunk_parameters.x;
    this -> chunks_y = chunk_parameters.y;
    this -> num_chunks = this -> chunks_x * this -> chunks_y;

    initialise_chunks();
    initialise_gradients();

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
        for (auto k = 0; k < chunks_x; k++) {
            chunk_row.emplace_back(chunk_side_length, chunk_side_length * i, chunk_side_length * k);

        }
        chunks.push_back(chunk_row);
    }

    chunk_selector_x = chunks_x - 1;
    chunk_selector_y = chunks_y - 1;

}


void terrain :: initialise_gradients() {
    for (int i = 0; i < 3; i++) {
            gradient_fields.emplace_back(0, 0, chunks_x, chunk_side_length, 2, 1.f);
        }
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

    if (position_change.x < 0) {

        for (auto& chunk : chunks[chunk_selector_y]) chunk.update_vertices(position_change.x * chunks_y, 0);
        (chunk_selector_y == 0) ? chunk_selector_y = chunks_y - 1 : chunk_selector_y--;
        // if (chunk_selector_y == 0) chunk_selector_y = chunks_y - 1;
        // else chunk_selector_y--;
    }

    if (position_change.x > 0) {
        for (auto& chunk : chunks[chunk_selector_y]) chunk.update_vertices(position_change.x * chunks_y, 0);
        (chunk_selector_y == chunks_y - 1) ? chunk_selector_y = 0 : chunk_selector_y++;

        // if (chunk_selector_y == chunks_y - 1) chunk_selector_y = 0;
        // else chunk_selector_y++;
    }


    // for (auto& row : chunks) for (auto& chunk : row) chunk.update_vertices(position_change.x, 0);

        // std :: rotate(chunks.rbegin(), std :: prev(chunks.rend()), chunks.rend());
        // for (auto& chunk : chunks[0]) chunk.update_vertices(position_change.x, 0);


    if (position_change.y > 0) {
        for (auto& row : chunks) std :: rotate(chunks.begin(), std :: next(chunks.begin()), chunks.end());
        for (auto& row : chunks) for (auto& chunk : row) chunk.update_vertices(0, position_change.y);
    }

    if (position_change.y < 0) {
        for (auto& row : chunks) std :: rotate(chunks.rbegin(), std :: next(chunks.rbegin()), chunks.rend());
        for (auto& row : chunks) for (auto& chunk : row) chunk.update_vertices(0, position_change.y);
    }
        //    std :: cout << "pos cha x: "<< position_change.x << "pos cha y " << position_change.y << std ::endl;

}




void terrain :: draw() {

    for (auto& row : chunks) for (auto& chunk : row) chunk.draw();

}
