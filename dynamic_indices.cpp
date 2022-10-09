#define GL_GLEXT_PROTOTYPES

#include <GLFW/glfw3.h>

#include "dynamic_indices.hpp"
#include <iostream>


dynamic_indices :: dynamic_indices(int chunk_side_vertices) {

    int chunk_len = chunk_side_vertices - 1;
    int chunk_side_vertices2 = chunk_side_vertices;
    int lod = 0;

    // confused num vertices with actual chunk len
    while(chunk_len >= 1) {

        GLuint buffer_id;
        glGenBuffers(1, &buffer_id);
        index_buffer_ids.push_back(buffer_id);
        build_index_vector(lod, chunk_side_vertices2);
        build_index_buffer(lod++);
        chunk_len /= 2;

    }
}


void dynamic_indices :: build_index_buffer(int lod) {

    // should (technically) be gl_element_array_buffer, 
    // but opengl might not allow this since no vao was specified.
    // we only need to initialise the element buffers at this stage.

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_ids[lod]);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, raw_indices[lod].size() * sizeof(GLuint), raw_indices[lod].data(), GL_STATIC_DRAW);

}



// void chunk :: build_indices() {

//     for (int index_y = 0; index_y < vertices_per_side - 1; index_y++) {

//         for (int index_x = 0; index_x < vertices_per_side - 1; index_x++) {

//             indices.push_back(index_x + (index_y) * vertices_per_side);
//             indices.push_back(index_x + (index_y) * vertices_per_side + 1);
//             indices.push_back(index_x + (index_y + 1) * vertices_per_side);

//             indices.push_back(index_x + (index_y) * vertices_per_side + 1);
//             indices.push_back(index_x + (index_y + 1) * vertices_per_side + 1);
//             indices.push_back(index_x + (index_y + 1) * vertices_per_side);
//         }
//     }
// }



void dynamic_indices :: build_index_vector(int lod, int chunk_side_vertices) {

    std :: vector <GLuint> indices;
    
    for (int index_y = 0; index_y < chunk_side_vertices - 1; index_y += pow(2, lod)) {

        for (int index_x = 0; index_x < chunk_side_vertices - 1; index_x += pow(2, lod)) {

            indices.push_back(index_x + (index_y) * chunk_side_vertices);
            indices.push_back(index_x + (index_y) * chunk_side_vertices + pow(2, lod));
            indices.push_back(index_x + (index_y + pow(2, lod)) * chunk_side_vertices);

            indices.push_back(index_x + (index_y) * chunk_side_vertices + pow(2, lod));
            indices.push_back(index_x + (index_y + pow(2, lod)) * chunk_side_vertices + pow(2, lod));
            indices.push_back(index_x + (index_y + pow(2, lod)) * chunk_side_vertices);
        }
    }

    raw_indices.push_back(indices);

}


void dynamic_indices :: bind_index_buffer(int lod) {

    if (lod > index_buffer_ids.size() - 1) lod = index_buffer_ids.size() - 1;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_ids[lod]);

}


void dynamic_indices :: print_info() {

    for (int i = 0; i < index_buffer_ids.size(); i++) print_info(i);
    
}


void dynamic_indices :: print_info(int lod) {

    std :: cout << "LOD = " << lod << std :: endl;
    std :: cout << "index buffer id = " << index_buffer_ids[lod] << std :: endl;
    std :: cout << "index buffer size = " << raw_indices[lod].size() << std :: endl;

    for (auto inx : raw_indices[lod]) std :: cout << inx << " ";

    std :: cout << std :: endl;  

}


int dynamic_indices :: get_num_indices(int lod) {

    if (lod > index_buffer_ids.size() - 1) lod = index_buffer_ids.size() - 1;

    return raw_indices[lod].size();
}