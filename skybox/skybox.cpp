#include "skybox.hpp"

skybox :: skybox() {
   
   sky_shader = new shader("./skybox_vertex_shader.glsl", "./skybox_fragment_shader.glsl");

   build_cubemap();
 
}

void skybox :: build_cubemap() {

   // generate buffers
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    // bind vertex array
    glBindVertexArray(vao);

    // bind and initialise vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    // bind and initialise element buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    // set vertex attributes

    // vertex positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)(0));
    glEnableVertexAttribArray(0);

    // // tex coords
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(vertices.size());
    // glEnableVertexAttribArray(1);

    // // perlin gradients
    // glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)(vertices.size() + );
    // glEnableVertexAttribArray(2);

    // unbind vertex array
    glBindVertexArray(0); 

}


// void skybox :: set_texture() {
// 	glGenTextures(1, &tex);
// 	glBindTexture(GL_TEXTURE_CUBE_MAP, tex);

// }


void skybox :: draw() {

   sky_shader -> use_program();
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());

}