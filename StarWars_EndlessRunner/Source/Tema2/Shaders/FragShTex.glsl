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

uniform vec3 light_position_bb8;
uniform vec3 light_direction_bb8;



 
in vec2 texcoord;
in vec3 world_position;
in vec3 world_normal;

layout(location = 0) out vec4 out_color;

void main()
{
	// TODO : calculate the out_color using the texture2D() function
	vec2 texcoord2 = texcoord;
	vec4 color = texture2D(texture, texcoord2);
	
	float light_g;
	float light_g2;
	float light_bb8;
	{
		vec3 L = normalize(light_position - world_position);
		vec3 R = normalize(reflect (-L, world_normal));
		vec3 V = normalize(eye_position - world_position);

		// TODO: define ambient light component
		float ambient_light = material_kd * 0.25;

		// TODO: compute diffuse light component
		float diffuse_light = material_kd * max (dot(world_normal, L), 0);

		// TODO: compute specular light component
	


		float specular_light = 0;

		if (diffuse_light > 0)
		{
			specular_light = material_ks * pow(max(dot(V, R), 0), material_shininess);
		}

		// TODO: compute light
		light_g = ambient_light + diffuse_light + specular_light;
	}

	{
		vec3 L = normalize(vec3(-light_position.x,light_position.y, light_position.z) - world_position);
		vec3 R = normalize(reflect (-L, world_normal));
		vec3 V = normalize(eye_position - world_position);

		// TODO: define ambient light component
		float ambient_light = material_kd * 0.25;

		// TODO: compute diffuse light component
		float diffuse_light = material_kd * max (dot(world_normal, L), 0);

		// TODO: compute specular light component
	


		float specular_light = 0;

		if (diffuse_light > 0)
		{
			specular_light = material_ks * pow(max(dot(V, R), 0), material_shininess);
		}

		// TODO: compute light
		light_g2 = ambient_light + diffuse_light + specular_light;
	}

	{
		vec3 L = normalize(light_position_bb8 - world_position);
		vec3 R = normalize(reflect (-L, world_normal));
		vec3 V = normalize(eye_position - world_position);

		// TODO: define ambient light component
		float ambient_light = material_kd * 0.25;

		// TODO: compute diffuse light component
		float diffuse_light = material_kd * max (dot(world_normal, L), 0);

		// TODO: compute specular light component
	


		float specular_light = 0;

		if (diffuse_light > 0)
		{
			specular_light = material_ks * pow(max(dot(V, R), 0), material_shininess);
		}

		float cut_off = 1.04f;
		float spot_light = dot(-L, light_direction_bb8);
		float spot_light_limit = cos(cut_off);
 
		// Quadratic attenuation
		float linear_att = (spot_light - spot_light_limit) / (1.0f - spot_light_limit);
		float light_att_factor = linear_att;

		if(spot_light > spot_light_limit) {
			float d = distance(light_position_bb8, world_position);
			float atenuare = 1 / (log(d + 1) + 1) ;
			light_bb8 = ambient_light + atenuare * light_att_factor * (diffuse_light + specular_light);
		} else {
			light_bb8 = ambient_light;
		}
	}
	
	
	out_color =  color * (light_g + light_g2 + light_bb8);
}