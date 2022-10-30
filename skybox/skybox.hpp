#ifndef SKYBOX_HPP
#define SKYBOX_HPP

#include <array>
#include "shader.hpp"

class skybox {

	public:

		skybox();
		void draw();
		void build_cubemap();

	private:

		std :: array <GLfloat, 36> vertices = {

			// front
		   -1.f, -1.f,  1.f,
     		1.f, -1.f,  1.f,
     		1.f,  1.f,  1.f,
    	   -1.f,  1.f,  1.f,

    		// back
		   -1.f, -1.f, -1.f,
		    1.f, -1.f, -1.f,
		    1.f,  1.f, -1.f,
		   -1.f,  1.f, -1.f

		};

		std :: array <GLuint, 36> indices = {

			// front
			0, 1, 2,
			2, 3, 0,

			// right
			1, 5, 6,
			6, 2, 1,

			// back
			7, 6, 5,
			5, 4, 7,

			// left
			4, 0, 3,
			3, 7, 4,

			// bottom
			4, 5, 1,
			1, 0, 4,

			// top
			3, 2, 6,
			6, 7, 3

		};

		GLuint vao;
		GLuint vbo;
		GLuint ebo;
		GLuint tex;

		shader* sky_shader;

};

#endif