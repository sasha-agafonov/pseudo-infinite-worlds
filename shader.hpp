#ifndef SHADER_HPP
#define SHADER_HPP


class shader {

public:
    unsigned int program_id;

    shader(const char* vert_shader_path,
           const char* frag_shader_path);

    shader(const char* vert_shader_path,
           const char* geo_shader_path,
           const char* frag_shader_path);

    void create_program(const char* vert_shader_source,
                        const char* frag_shader_source);

    void create_program(const char* vert_shader_source,
                        const char* geo_shader_source,
                        const char* frag_shader_source);

    void use_program();
};

#endif
