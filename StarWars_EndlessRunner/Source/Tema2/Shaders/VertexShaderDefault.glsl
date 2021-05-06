#version 330

// TODO: get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 2) in vec3 v_normal;
layout(location = 1) in vec3 v_color;


// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

// TODO: output values to fragment shader
out vec3 f_position;
out vec3 f_normal;
out vec3 f_color;


void main()
{
	// TODO: send output to fragment shader
	f_position = v_position;
	f_normal = v_normal;
	f_color = v_color;

	// TODO: compute gl_Position

	gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}

