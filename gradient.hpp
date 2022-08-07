#ifndef GRADIENT_HPP
#define GRADIENT_HPP

#include <vector>
#include <glm/ext.hpp>

class gradient {

    public:

        gradient(int x, int y);
        // void reload(int x, int y);
        // void reload(int x, int y, int px, int py)
        glm :: vec2 unit_vector;
        glm :: ivec2 position;

};

#endif
