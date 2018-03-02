#version 330
layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec2 in_UV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 out_UV;

void main(void) {
	out_UV = in_UV;
	gl_Position = projection * view * model * vec4(in_Position,1.0);
}