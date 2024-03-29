#define GLFW_INCLUDE_NONE

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "shader.hpp"


shader :: shader(const char* vert_shader_path, const char* frag_shader_path) {

    std :: string vert_shader_source, frag_shader_source;
    std :: ifstream vert_shader_ifstream, frag_shader_ifstream;

    vert_shader_ifstream.exceptions(std :: ifstream :: badbit | std :: ifstream :: failbit);
    frag_shader_ifstream.exceptions(std :: ifstream :: badbit | std :: ifstream :: failbit);

    try {
        vert_shader_ifstream.open(vert_shader_path);
        frag_shader_ifstream.open(frag_shader_path);

        std :: stringstream vert_shader_sstream, frag_shader_sstream;

        vert_shader_sstream << vert_shader_ifstream.rdbuf();
        frag_shader_sstream << frag_shader_ifstream.rdbuf();

        vert_shader_ifstream.close();
        frag_shader_ifstream.close();

        vert_shader_source = vert_shader_sstream.str();
        frag_shader_source = frag_shader_sstream.str();

    } catch (std :: ifstream :: failure exception) {
        std :: cout << "Error: could not load one or more shaders!" << std :: endl;
    }

    create_program(vert_shader_source.c_str(), frag_shader_source.c_str());
}


shader :: shader(const char* vert_shader_path, const char* geom_shader_path, const char* frag_shader_path) {

    std :: string vert_shader_source, geom_shader_source, frag_shader_source;
    std :: ifstream vert_shader_ifstream, geom_shader_ifstream, frag_shader_ifstream;

    vert_shader_ifstream.exceptions(std :: ifstream :: badbit | std :: ifstream :: failbit);
    geom_shader_ifstream.exceptions(std :: ifstream :: badbit | std :: ifstream :: failbit);
    frag_shader_ifstream.exceptions(std :: ifstream :: badbit | std :: ifstream :: failbit);


    try {
        vert_shader_ifstream.open(vert_shader_path);
        geom_shader_ifstream.open(geom_shader_path);
        frag_shader_ifstream.open(frag_shader_path);

        std :: stringstream vert_shader_sstream, geom_shader_sstream, frag_shader_sstream;

        vert_shader_sstream << vert_shader_ifstream.rdbuf();
        geom_shader_sstream << geom_shader_ifstream.rdbuf();
        frag_shader_sstream << frag_shader_ifstream.rdbuf();

        vert_shader_ifstream.close();
        geom_shader_ifstream.close();
        frag_shader_ifstream.close();

        vert_shader_source = vert_shader_sstream.str();
        geom_shader_source = geom_shader_sstream.str();
        frag_shader_source = frag_shader_sstream.str();

    } catch (std :: ifstream :: failure exception) {
        std :: cout << "Error: could not load one or more shaders!" << std :: endl;
    }

    create_program(vert_shader_source.c_str(), geom_shader_source.c_str(), frag_shader_source.c_str());
}


void shader :: create_program(const char* vert_shader_source, const char* frag_shader_source) {

    unsigned int vert_shader, frag_shader;

    vert_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert_shader, 1, &vert_shader_source, NULL);
    glCompileShader(vert_shader);

    frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_shader, 1, &frag_shader_source, NULL);
    glCompileShader(frag_shader);

    program_id = glCreateProgram();
    glAttachShader(program_id, vert_shader);
    glAttachShader(program_id, frag_shader);
    glLinkProgram(program_id);

    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);
}


void shader :: create_program(const char* vert_shader_source, const char* geom_shader_source, const char* frag_shader_source) {

    unsigned int vert_shader, geom_shader, frag_shader;

    vert_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert_shader, 1, &vert_shader_source, NULL);
    glCompileShader(vert_shader);

    geom_shader = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geom_shader, 1, &geom_shader_source, NULL);
    glCompileShader(geom_shader);

    frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_shader, 1, &frag_shader_source, NULL);
    glCompileShader(frag_shader);

    program_id = glCreateProgram();

    glAttachShader(program_id, vert_shader);
    glAttachShader(program_id, geom_shader);
    glAttachShader(program_id, frag_shader);

    glLinkProgram(program_id);

    glDeleteShader(vert_shader);
    glDeleteShader(geom_shader);
    glDeleteShader(frag_shader);
}


void shader :: use_program() {
    glUseProgram(this -> program_id);
}
