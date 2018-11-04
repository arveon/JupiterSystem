/* by Aleksejs Loginovs - October 2018 */

#pragma once
#include "Drawable.h"
#include "Constants.h"

class Cube : public Drawable
{
private:
	const int num_verts = NUM_CUBE_VERTS;

	/* Define vertices for a cube in 12 triangles */
	//changed some values to make sure there are no gaps between the sides of the cube (skybox)
	GLfloat verts[NUM_CUBE_VERTS*VALUES_PER_VERT] =
	{
		// Face 0 back
		-1.f, 1.f, -.99f,//1
		-1.f, -1.f, -.99f,//2
		1.f, -1.f, -.99f,//3

		1.f, -1.f, -.99f,//3
		1.f, 1.f, -.99f,//4
		-1.f, 1.f, -.99f,//1

		// Face 1 right
		0.99f, -1.f, -1.f,//3
		0.99f, -1.f, 1.f,//1
		0.99f, 1.f, -1.f,//4

		0.99f, -1.f, 1.f,
		0.99f, 1.f, 1.f,
		0.99f, 1.f, -1.f,

		// Face 2 front
		1.f, -1.f, 0.99f,
		-1.f, -1.f, 0.99f,
		1.f, 1.f, 0.99f,

		-1.f, -1.f, 0.99f,
		-1.f, 1.f, 0.99f,
		1.f, 1.f, 0.99f,

		// Face 3 left
		-.99f, -1.f, 1.f,
		-.99f, -1.f, -1.f,
		-.99f, 1.f, 1.f,

		-.99f, -1.f, -1.f,
		-.99f, 1.f, -1.f,
		-.99f, 1.f, 1.f,

		// Face 4 bottom
		-1.f, -1.f, 1.f,
		1.f, -1.f, 1.f,
		1.f, -1.f, -1.f,

		1.f, -1.f, -1.f,
		-1.f, -1.f, -1.f,
		-1.f, -1.f, 1.f,

		// Face 5 top
		-1.f, 1.f, -1.f,
		1.f, 1.f, -1.f,
		1.f, 1.f, 1.f,

		1.f, 1.f, 1.f,
		-1.f, 1.f, 1.f,
		-1.f, 1.f, -1.f,
	};

	GLfloat colours[NUM_CUBE_VERTS* VALUES_PER_VERT] =
	{
		/* Manually specified colours for our cube */
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,

		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,

		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,

		1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,

		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f
	};

	/* Manually specified normals for our cube (3 values per coordinate) */
	GLfloat normals[NUM_CUBE_VERTS*VALUES_PER_NORMAL] =
	{
		0, 0, -1.f, 0, 0, -1.f, 0, 0, -1.f,
		0, 0, -1.f, 0, 0, -1.f, 0, 0, -1.f,
		1.f, 0, 0, 1.f, 0, 0, 1.f, 0, 0,
		1.f, 0, 0, 1.f, 0, 0, 1.f, 0, 0,
		0, 0, 1.f, 0, 0, 1.f, 0, 0, 1.f,
		0, 0, 1.f, 0, 0, 1.f, 0, 0, 1.f,
		-1.f, 0, 0, -1.f, 0, 0, -1.f, 0, 0,
		-1.f, 0, 0, -1.f, 0, 0, -1.f, 0, 0,
		0, -1.f, 0, 0, -1.f, 0, 0, -1.f, 0,
		0, -1.f, 0, 0, -1.f, 0, 0, -1.f, 0,
		0, 1.f, 0, 0, 1.f, 0, 0, 1.f, 0,
		0, 1.f, 0, 0, 1.f, 0, 0, 1.f, 0
	};

	GLfloat texcoords[NUM_CUBE_VERTS*2] =
	{
		// ace 0 back
		.25, 0.66,
		0.25, 0.33,
		.5, .33,
		.5, .33,
		0.5, .66,
		.25, 0.66,

		// ace 1 right
		.5, 0.34,
		0.75, 0.34,
		.5, .66,
		0.75, 0.34,
		0.75, .66,
		.50, 0.66,

		// ace 2 front
		0.75, .34,
		1., 0.34,
		0.75, 0.66,
		1., 0.34,
		1., .66,
		0.75, 0.66,

		// ace 3 left
		.0, 0.34,
		0.25, 0.34,
		.0, .66,
		0.25, 0.34,
		0.25, .66,
		.0, .66,

		// ace 4 bottom
		.25, 0.,
		0.50, 0.0,
		.50, .33,
		.50, .33,
		0.25, .33,
		.25, 0.,
		
		// ace 5 top
		.25, 0.66,
		0.50, 0.66,
		.50, 1.,
		.50, 1.,
		0.25, 1.,
		.25, 0.66,
	};

public:
	void init(Shader shader_program, GLuint texture_id = NULL)
	{
		//only pass texcoords to drawable if texture id is provided, otherwise assume no texture should be used
		if (texture_id != NULL)
			Drawable::init(shader_program, verts, num_verts, colours, normals, texcoords, texture_id);
		else
			Drawable::init(shader_program, verts, num_verts, normals, texcoords);
	}
	Cube() 
	{
		this->normals_enabled = true;
		this->colours_enabled = true;
	}
	~Cube() {}
};