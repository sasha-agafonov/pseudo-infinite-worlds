#ifndef LOD_CONTROLLER_HPP
#define LOD_CONTROLLER_HPP

#include <glm/ext.hpp>
#include "terrain.hpp"
#include "lod_object.hpp"


class lod_controller {

    public:

        lod_controller(int chunk_side_vertices);

        int get_num_indices(int lod);
        void bind_index_buffer(int lod);
        void print_info(int lod);
        void print_info();

    private:

        void build_index_buffer(int lod);
        void build_index_vector(int lod, int chunk_side_vertices);

       // std :: vector <lod_object> lod_objects;

        std :: vector <GLuint> index_buffer_ids;
        std :: vector <std :: vector <GLuint>> raw_indices;

        int min_lod;
        
};

#endif