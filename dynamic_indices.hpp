#ifndef DYNAMIC_INDICES_HPP
#define DYNAMIC_INDICES_HPP

#include <glm/ext.hpp>
#include "terrain.hpp"


class dynamic_indices {

    public:

        dynamic_indices(int chunk_side_vertices);

        int get_num_indices(int lod);
        void bind_index_buffer(int lod);
        void print_info(int lod);
        void print_info();

    private:

        void build_index_buffer(int lod);
        void build_index_vector(int lod, int chunk_side_vertices);

        std :: vector <GLuint> index_buffer_ids;
        std :: vector <std :: vector <GLuint>> raw_indices;
        

};

#endif