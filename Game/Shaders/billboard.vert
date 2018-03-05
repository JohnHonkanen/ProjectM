#version 330
layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec2 in_UV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 cameraRight_worldspace;
uniform vec3 cameraUp_worldspace;
uniform vec3 billboardPos;
uniform vec2 billboardSize;

out vec2 out_UV;

void main(void) {

	vec3 particleCenter_worldspace = billboardPos;
	
	vec3 vertexPosition_worldspace =
		particleCenter_worldspace
		+ cameraRight_worldspace * in_Position.x * billboardSize.x
		+ cameraUp_worldspace * in_Position.y * billboardSize.y;
	
	out_UV = in_UV;
	gl_Position = projection * view * vec4(vertexPosition_worldspace,1.0);
}