#version 330
 
uniform sampler2D texture;
uniform float speed;
uniform int type;

uniform vec3 light_position;
uniform vec3 eye_position;
uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;
uniform vec3 light_direction;

 
in vec2 texcoord;
in vec3 world_position;
in vec3 world_normal;

layout(location = 0) out vec4 out_color;

void main()
{
	// TODO : calculate the out_color using the texture2D() function
	vec2 texcoord2 = texcoord;
	vec4 color = texture2D(texture, texcoord2);


	out_color =  color;
}