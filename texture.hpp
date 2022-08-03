#ifndef TEXTURE_HPP
#define TEXTURE_HPP

class texture {

public:
    texture(const char* image_path);

    unsigned int texture_id;
    unsigned char* texture_data;
    int width, height, channels;

    int get_width();
    int get_height();
    int get_channels();
};

#endif
