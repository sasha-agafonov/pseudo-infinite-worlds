#version 460 core

layout (location = 0) in vec3 vertex_position;

out vec3 vex_pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 position;


void main() {

   gl_Position = position * projection * view * model * vec4(vertex_position, 1.0);
   vex_pos = vertex_position;
	
}