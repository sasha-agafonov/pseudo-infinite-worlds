#include "texture.hpp"
#include "stb_image.h"


texture :: texture(const char* image_path) {
    // fix this mess
    // texture_data = stbi_image(image_path, &width, &height, &channels, 0);
}


int texture :: get_width() {
    return width;
}


int texture :: get_height() {
    return height;
}


int texture :: get_channels() {
    return channels;
}
