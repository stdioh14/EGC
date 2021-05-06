#version 330
 
uniform sampler2D texture;
uniform float f_time;
 
in vec2 texcoord;

layout(location = 0) out vec4 out_color;

void main()
{
	// TODO : calculate the out_color using the texture2D() function


	vec2 texcoord2 = texcoord;
	vec4 color = texture2D(texture, texcoord2);





	out_color = color;
}