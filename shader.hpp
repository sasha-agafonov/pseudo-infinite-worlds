#ifndef SHADER_HPP
#define SHADER_HPP


class shader {

    public:

        unsigned int program_id;

        shader(const char* vert_shader_path,
               const char* frag_shader_path);

        shader(const char* vert_shader_path,
               const char* geom_shader_path,
               const char* frag_shader_path);

        void use_program();

    private:

        void create_program(const char* vert_shader_source,
                            const char* frag_shader_source);

        void create_program(const char* vert_shader_source,
                            const char* geom_shader_source,
                            const char* frag_shader_source);

};

#endif
