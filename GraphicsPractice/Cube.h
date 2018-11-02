#pragma once
#include "Drawable.h"
#include "Constants.h"

class Cube : public Drawable
{
private:
	const int num_verts = NUM_CUBE_VERTS;

	//GLfloat vers[NUM_CUBE_VERTS*VALUES_PER_VERT] =
	//{
	//	//face 1
	//	-1, -1, -1,//0
	//	1, -1, -1,//1
	//	-1, 1, -1,//3

	//	-1, 1, -1,//3
	//	1, -1, -1,//1
	//	1, 1, -1,//2

	//	//face 2
	//	1, -1, -1,//1
	//	1, -1, 1,//5
	//	1, 1, -1,//2

	//	1, 1, -1,//2
	//	1, -1, 1,//5
	//	1, 1, 1,//6


	//	//face 3
	//	1, -1, 1,//5
	//	-1, -1, 1,//4
	//	1, 1, 1,//6

	//	1, 1, 1,//6
	//	-1, -1, 1,//4
	//	-1, 1, 1,//7

	//	//face 4
	//	-1, -1, 1,//4
	//	-1, -1, -1,//0
	//	-1, 1, 1,//7

	//	-1, 1, 1,//7
	//	-1, -1, -1,//0
	//	-1, 1, -1,//3

	//	//face 5
	//	-1, 1, -1,//3
	//	1, 1, -1,//2
	//	-1, 1, 1,//7

	//	-1, 1, 1,//7
	//	1, 1, -1,//2
	//	1, 1, 1,//6

	//	//face 6
	//	-1, -1, 1,//4
	//	1, -1, 1,//5
	//	-1, -1, -1,//0

	//	-1, -1, -1,//0
	//	1, -1, 1,//5
	//	1, -1, -1//1
	//};

	/* Define vertices for a cube in 12 triangles */
	GLfloat verts[NUM_CUBE_VERTS*VALUES_PER_VERT] =
	{
		// Face 0 back
		-1.f, 1.f, -1.f,//1
		-1.f, -1.f, -1.f,//2
		1.f, -1.f, -1.f,//3

		1.f, -1.f, -1.f,//3
		1.f, 1.f, -1.f,//4
		-1.f, 1.f, -1.f,//1

		// Face 1 right
		1.f, -1.f, -1.f,//3
		1.f, -1.f, 1.f,//1
		1.f, 1.f, -1.f,//4

		1.f, -1.f, 1.f,
		1.f, 1.f, 1.f,
		1.f, 1.f, -1.f,

		// Face 2 front
		1.f, -1.f, 1.f,
		-1.f, -1.f, 1.f,
		1.f, 1.f, 1.f,

		-1.f, -1.f, 1.f,
		-1.f, 1.f, 1.f,
		1.f, 1.f, 1.f,

		// Face 3 left
		-1.f, -1.f, 1.f,
		-1.f, -1.f, -1.f,
		-1.f, 1.f, 1.f,

		-1.f, -1.f, -1.f,
		-1.f, 1.f, -1.f,
		-1.f, 1.f, 1.f,

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
		// Face 0 back
		.25f, 0.66f,
		0.25f, 0.33f,
		.5f, .33f,
		.5f, .33f,
		0.5f, .66f,
		.25f, 0.66f,

		// Face 1 right
		.5f, 0.33f,
		0.75f, 0.33f,
		.5f, .66f,
		0.75f, 0.33f,
		0.75f, .66f,
		.5f, 0.66f,

		// Face 2 front
		0.75f, .33f,
		1.f, 0.33f,
		0.75f, 0.66f,
		1.f, 0.33f,
		1.f, .66f,
		0.75f, 0.66f,

		// Face 3 left
		.0f, 0.33f,
		0.25f, 0.33f,
		.0f, .66f,
		0.25f, 0.33f,
		0.25f, .66f,
		.0f, .66f,

		// Face 4 bottom
		.25f, 0.f,
		0.5f, 0.0f,
		.5f, .33f,
		.5f, .33f,
		0.25f, .33f,
		.25f, 0.f,
		
		// Face 5 top
		.25f, 0.66f,
		0.5f, 0.66f,
		.5f, 1.f,
		.5f, 1.f,
		0.25f, 1.f,
		.25f, 0.66f,
	};

public:
	void init(Shader shader_program, GLuint texture_id = NULL)
	{
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