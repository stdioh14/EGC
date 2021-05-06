#version 330

// TODO: get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 2) in vec3 v_normal;
layout(location = 1) in vec3 v_color;


// Uniform properties
uniform mat4 Model;

// TODO: output values to fragment shader
out vec3 f_position;
out vec3 f_color;
out vec3 f_normal;

void main()
{
	// TODO: send output to fragment shader
	f_position = v_position;
	f_normal = v_normal;
	f_color = vec3((0.6 - Model[1][1])/0.6, Model[1][1]/0.6, 0);

	// TODO: compute gl_Position

	gl_Position = Model * vec4(v_position, 1.0);
}
