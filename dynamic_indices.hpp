#ifndef DYNAMIC_INDICES_HPP
#define DYNAMIC_INDICES_HPP

#include <glm/ext.hpp>
#include "terrain.hpp"

class dynamic_indices {

    public:

        dynamic_indices(int chunk_side_vertices);

        std :: vector <GLuint> index_buffer_ids;
        std :: vector <std :: vector <std :: vector <GLuint>>> index_buffers;

        int lods;
        int curr_lod;

    private:
};
