#ifndef TERRAIN_HPP
#define TERRAIN_HPP
#define CHUNKS 1

#include <vector>
#include <array>
#include "chunk.hpp"

class terrain {

    public:

        terrain(glm :: ivec3 chunk_parameters, glm :: vec3 observer_position);

        void initialise_chunks(int chunks_x, int chunks_y);
        //void initialise_chunk_layout(int chunks_x, int chunks_y);
        void update_scene(glm :: ivec2 position_change);

        int num_chunks;
        int chunk_side_length;

        std :: vector <std :: vector <chunk>> chunks;
        //std :: vector <std :: vector <glm :: ivec2>> chunk_layout;

};

#endif
