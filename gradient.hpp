#ifndef GRADIENT_HPP
#define GRADIENT_HPP

#include <vector>
#include <glm/ext.hpp>

class gradient {

    public:

        gradient(int x, int y);
        void reload(int x, int y);
        glm :: vec2 component;
        glm :: ivec2 position;

};

#endif
