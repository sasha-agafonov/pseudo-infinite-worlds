#define GL_GLEXT_PROTOTYPES
#include "terrain.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

terrain :: terrain(glm :: ivec3 chunk_parameters, glm :: vec3 observer_position) {

    this -> chunk_side_length = chunk_parameters.z;
    this -> num_chunks = chunk_parameters.x * chunk_parameters.y;
    //initialise_chunk_layout(chunk_parameters.x, chunk_parameters.y);
    initialise_chunks(chunk_parameters.x, chunk_parameters.y);

}

// void terrain :: initialise_chunk_layout(int chunks_x, int chunks_y) {
//
//     for (int i = 0; i < chunks_x; i++) {
//         std :: vector <glm :: ivec2> layout_row;
//         for (int k = 0; k < chunks_y; k++) layout_row.push_back(glm :: ivec2(i * chunk_side_length, k * chunk_side_length));
//         chunk_layout.push_back(layout_row);
//     }
// }

void terrain :: initialise_chunks(int chunks_x, int chunks_y) {

    for (int i = 0; i < chunks_y; i++) {
        std :: vector <chunk> chunk_row;

        for (int k = 0; k < chunks_x; k++) {
            chunk_row.emplace_back(chunk_side_length, chunk_side_length * i, chunk_side_length * k);
        }
        chunks.push_back(chunk_row);
    }
}

void terrain :: update_scene(glm :: ivec2 position_change) {

    for (int i = 0; i < chunks.size(); i++) {
        for (int k = 0; k < chunks[0].size(); k++) {
            chunks[i][k].update_vertices(position_change.y, 0);

            // chunk_layout[i][k].x += position_change.x;
            // chunk_layout[i][k].y += position_change.y;
            // chunks[i * k + k]

        }
    }
}

    // std :: vector <std :: vector <glm :: vec2>> negator = chunk_layout;
    //
    // for (int i = 0; i < chunk_layout.size(); i++) {
    //     for (int k = 0; k < chunk_layout[0].size(); k++) {
    //         negator[i][k].x += position_change.x;
    //         negator[i][k].y += position_change.y;
    //     }
    // }
    //
    // for (int i = 0; i < chunk_layout.size(); i++) {
    //     for (int k = 0; k < chunk_layout[0].size(); k++) {
    //
    //         for (int n = 0; n < chunk_layout.size(); n++) {
    //             for(int m = 0; m < chunk_layout[0].size(); m++) {
    //
    //                 if (!(equal(negator[i][k], chunk_layout[n][m])))
    //             }
    //         }
    //     }
    // }

    // chunk_layout = negator;


//
//
//
//
//
//     //chunk_translation.z = chunk_translation.z + float(discrete_position.z);
//     //chunk_translation = chunk_translation + (glm :: vec3)discrete_position;
//     // std :: cout << "!!!!!!!!!" << std :: endl;
//     // chunk_translation.z += 1;
//     // std :: cout << chunk_translation.x << std :: endl;
//     // std :: cout << chunk_translation.y << std :: endl;
//     // std :: cout << chunk_translation.z << std :: endl;
// }
