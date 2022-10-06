#include "dynamic_indices.hpp"

dynamic_indices :: dynamic_indices(int chunk_side_vertices) {

    lods = 0;

    while(chunk_side_vertices > 0) {
        lods++;
        chunk_side_vertices /= 2;
    }

    glGenBuffers(lods, &index_buffer_ids);

    for (int i = 0; i < lods; i++) build_indices(i, index_buffers_ids[i]);
}


void dynamic_indices :: build_index_buffer(int i, int buffer_id ) {
    
    for (int index_y = 0; index_y < vertices_per_side - 1; index_y++) {

        for (int index_x = 0; index_x < vertices_per_side - 1; index_x++) {

            indices.push_back(index_x + (index_y) * vertices_per_side);
            indices.push_back(index_x + (index_y) * vertices_per_side + 1);
            indices.push_back(index_x + (index_y + 1) * vertices_per_side);

            indices.push_back(index_x + (index_y) * vertices_per_side + 1);
            indices.push_back(index_x + (index_y + 1) * vertices_per_side + 1);
            indices.push_back(index_x + (index_y + 1) * vertices_per_side);
        }
    }

}


void dynamic_indices :: bind_index_buffer(int lod) {

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_ids[lod]);

}
