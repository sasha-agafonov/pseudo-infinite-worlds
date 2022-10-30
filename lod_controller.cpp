#define GL_GLEXT_PROTOTYPES

#include <GLFW/glfw3.h>

#include "lod_controller.hpp"
#include <iostream>


lod_controller :: lod_controller(int chunk_side_vertices) {

    int chunk_len = chunk_side_vertices - 1;
    int chunk_side_vertices2 = chunk_side_vertices;
    int lod = 0;

    // confused num vertices with actual chunk len
    while(chunk_len >= 2) {

        GLuint buffer_id;
        glGenBuffers(1, &buffer_id);
        index_buffer_ids.push_back(buffer_id);
        build_index_vector(lod, chunk_side_vertices2);
        build_index_buffer(lod++);
        chunk_len /= 2;

    }

    min_lod = lod;
}


void lod_controller :: build_index_buffer(int lod) {

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_ids[lod]);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, raw_indices[lod].size() * sizeof(GLuint), raw_indices[lod].data(), GL_STATIC_DRAW);

}


void lod_controller :: build_index_vector(int lod, int chunk_side_vertices) {

    std :: vector <GLuint> indices;
    
    for (int index_y = 0, diamond = 0; index_y < chunk_side_vertices - 1; index_y += pow(2, lod), ++diamond) {

        for (int index_x = 0; index_x < chunk_side_vertices - 1; index_x += pow(2, lod), ++diamond) {

            if (diamond & 1) {

                indices.push_back(index_x +  index_y * chunk_side_vertices);
                indices.push_back(index_x +  index_y * chunk_side_vertices + pow(2, lod));
                indices.push_back(index_x + (index_y + pow(2, lod)) * chunk_side_vertices);

                indices.push_back(index_x +  index_y * chunk_side_vertices + pow(2, lod));
                indices.push_back(index_x + (index_y + pow(2, lod)) * chunk_side_vertices + pow(2, lod));
                indices.push_back(index_x + (index_y + pow(2, lod)) * chunk_side_vertices);

            }

            else {

                indices.push_back(index_x +  index_y * chunk_side_vertices);
                indices.push_back(index_x + (index_y + pow(2, lod)) * chunk_side_vertices + pow(2, lod));
                indices.push_back(index_x + (index_y + pow(2, lod)) * chunk_side_vertices);

                indices.push_back(index_x +  index_y * chunk_side_vertices);
                indices.push_back(index_x +  index_y * chunk_side_vertices + pow(2, lod));
                indices.push_back(index_x + (index_y + pow(2, lod)) * chunk_side_vertices + pow(2, lod));
  
            }
        }
    }

    raw_indices.push_back(indices);

}   


void lod_controller :: bind_index_buffer(int lod) {

    if (lod > index_buffer_ids.size() - 1) lod = index_buffer_ids.size() - 1;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_ids[lod]);

}


// print info for all lod objects
void lod_controller :: print_info() {

    for (GLuint buffer_id : index_buffer_ids) print_info(buffer_id);

    //for (int i = 0; i < index_buffer_ids.size(); i++) print_info(i);
    
}


// print info for specific lod object
void lod_controller :: print_info(int lod) {

    std :: cout << "current LOD = " << lod << std :: endl;
    std :: cout << "minimum LOD = " << min_lod << std :: endl;
    std :: cout << "index buffer id = " << index_buffer_ids[lod] << std :: endl;
    std :: cout << "index buffer size = " << raw_indices[lod].size() << std :: endl;

    for (auto inx : raw_indices[lod]) std :: cout << inx << " ";

    std :: cout << std :: endl;  

}


int lod_controller :: get_num_indices(int lod) {

    if (lod > index_buffer_ids.size() - 1) lod = index_buffer_ids.size() - 1;

    return raw_indices[lod].size();
}