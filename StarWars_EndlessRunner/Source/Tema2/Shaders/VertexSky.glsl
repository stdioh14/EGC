#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec2 texcoord;


void main()
{
	texcoord = v_texture_coord;
	vec4 pos = Projection * View * Model * vec4(v_position, 1.0);
	gl_Position = pos.xyww;
}
