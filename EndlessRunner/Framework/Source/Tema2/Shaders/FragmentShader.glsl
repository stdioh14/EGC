#version 330

// TODO: get values from fragment shader
in vec3 f_position;
in vec3 f_color;
in vec3 f_normal;

layout(location = 0) out vec4 out_color;
layout(location = 1) out vec4 out_normal;

void main()
{
	// TODO: write pixel out color
	out_color = vec4(f_color, 1);
	out_normal = vec4(f_normal, 1);
}