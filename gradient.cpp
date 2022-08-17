#include "gradient.hpp"


gradient :: gradient (int ix, int iy) {

    position = glm :: vec2(ix, iy);
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2;
    unsigned a = ix, b = iy;
    a *= 3284157443; b ^= a << s | a >> w-s;
    b *= 1911520717; a ^= b << s | b >> w-s;
    a *= 2048419325;
    float random = a * (3.14159265 / ~(~0u >> 1));
    component = glm :: vec2(cos(random), sin(random));

}

//
// void gradient :: reload(int ix, int iy) {
//     const unsigned w = 8 * sizeof(unsigned);
//     const unsigned s = w / 2;
//     unsigned a = ix, b = iy;
//     a *= 3284157443; b ^= a << s | a >> w-s;
//     b *= 1911520717; a ^= b << s | b >> w-s;
//     a *= 2048419325;
//     float random = a * (3.14159265 / ~(~0u >> 1));
//     unit_vector = glm :: vec2(cos(random), sin(random));
// }
//
//
// void gradient :: reload(int ix, int iy, int px, int py) {
//     const unsigned w = 8 * sizeof(unsigned);
//     const unsigned s = w / 2;
//     unsigned a = ix, b = iy;
//     a *= 3284157443; b ^= a << s | a >> w-s;
//     b *= 1911520717; a ^= b << s | b >> w-s;
//     a *= 2048419325;
//     float random = a * (3.14159265 / ~(~0u >> 1));
//     unit_vector = glm :: vec2(cos(random), sin(random));
//     position = glm :: vec2(px, py);
// }
