#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform int skyBox;

out vec2 texcoord;
out vec3 world_position;
out vec3 world_normal;


void main()
{
	// TODO: compute world space vertex position and normal
	// TODO: send world position and world normal to Fragment Shader
	world_position = vec3 (Model * vec4(v_position,1));
	world_normal = normalize(vec3 (Model * vec4(v_normal, 0)));

	// TODO : pass v_texture_coord as output to Fragment Shader

	texcoord = v_texture_coord;
	vec4 pos = Projection * View * Model * vec4(v_position, 1.0);
	if(skyBox == -1) gl_Position = pos.xyww;
	else gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}
