#version 330
 
uniform sampler2D texture_1;
uniform sampler2D texture_2;
uniform int f_pamant;
uniform float f_time;
 
in vec2 texcoord;

layout(location = 0) out vec4 out_color;

void main()
{
	// TODO : calculate the out_color using the texture2D() function


	vec2 texcoord2 = texcoord - vec2(f_time / 10, 0) * f_pamant;
	vec4 color1 = texture2D(texture_1, texcoord2);
	vec4 color2 = texture2D(texture_2, texcoord2);



	vec4 color = mix(color1, color2, 0.3f);

	if(color.a < 0.5f){
		discard;
	}

	out_color = color;
}