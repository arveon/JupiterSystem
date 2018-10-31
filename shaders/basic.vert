#version 420

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 colour;
layout(location = 2) in vec3 normal;
out vec4 fcolour;

vec4 ambient_colour = vec4(0, 0, 0.2, 1);
vec4 diffuse_colour = vec4(0.5, 0.1, 0.2, 1);
vec4 specular_colour = vec4(0.8, 0.8, 0.8, 1);

uniform mat4 model_view, view, projection;
uniform uint colour_mode;

uniform vec4 light_position;

out vec3 fposition, fnormal, flightpos;
out vec4 fdiffuse, fspecular, fambient;

uniform float shininess = 10;


void main()
{	
	fposition = (model_view * position).xyz;
	fnormal = transpose(inverse(mat3(model_view)))*normal;
	flightpos = (view * light_position).xyz;
	fdiffuse = diffuse_colour;
	fambient = ambient_colour;
	fspecular = specular_colour;


//	//CALCULATING_DIFFUSE
//	//transform normals so they aren't affected by scaling anymore and normalize them
//	mat3 n_matrix = transpose(inverse(mat3(model_view)));
//	vec3 transf_normal = normalize(n_matrix * normal);
//	//get position of vertex in modelview space
//	vec4 vert_pos = model_view * position;
//
//	//get vector from vert to light
//	vec4 mod_light_pos = view * light_position;
//	vec3 to_light = mod_light_pos.xyz - vert_pos.xyz;
//	//get distance between light and vertex
//	float distance_to_light = length(to_light);
//	//make sure light is normalised
//	to_light = normalize(to_light);
//
//	//calculate diffuse
//	vec4 diffuse = vec4(max(dot(transf_normal, to_light), 0) * diffuse_colour.xyz,1);//get cos of angle between vectors
//
//	//calculate specular
//	vec3 normalised_vert = normalize(-vert_pos.xyz);
//	vec3 reflection = reflect(-to_light, transf_normal);
//	vec4 specular = vec4((pow(max(dot(reflection, normalised_vert), 0), shininess) * specular_colour.xyz), 1);
//
//	//attenuation
//	float k1 = 0.5;
//	float attenuation = 1.0 / (k1+k1*distance_to_light + pow(k1*distance_to_light,2));
//	fcolour = specular + diffuse + ambient_colour * 0.5;

	gl_Position = projection * model_view * position;
}