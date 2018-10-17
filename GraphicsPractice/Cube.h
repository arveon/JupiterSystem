#pragma once
#include "Drawable.h"
#include "Constants.h"

class Cube : public Drawable
{
private:
	const int num_verts = NUM_CUBE_VERTS;
	/* Define vertices for a cube in 12 triangles */
	GLfloat vertexPositions[NUM_CUBE_VERTS*VALUES_PER_VERT] =
	{
		-0.25f, 0.25f, -0.25f,1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		-0.25f, -0.25f, -0.25f,1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.25f, -0.25f, -0.25f,1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,

		0.25f, -0.25f, -0.25f,1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.25f, 0.25f, -0.25f,1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		-0.25f, 0.25f, -0.25f,1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,

		0.25f, -0.25f, -0.25f,1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.25f, -0.25f, 0.25f,1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.25f, 0.25f, -0.25f,1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,

		0.25f, -0.25f, 0.25f,1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.25f, 0.25f, 0.25f,1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.25f, 0.25f, -0.25f,1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,

		0.25f, -0.25f, 0.25f,1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		-0.25f, -0.25f, 0.25f,1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		0.25f, 0.25f, 0.25f,1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,

		-0.25f, -0.25f, 0.25f,1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		-0.25f, 0.25f, 0.25f,1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		0.25f, 0.25f, 0.25f,1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,

		-0.25f, -0.25f, 0.25f,1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		-0.25f, -0.25f, -0.25f,1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		-0.25f, 0.25f, 0.25f,1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,

		-0.25f, -0.25f, -0.25f,1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		-0.25f, 0.25f, -0.25f,1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		-0.25f, 0.25f, 0.25f,1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,

		-0.25f, -0.25f, 0.25f,1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,
		0.25f, -0.25f, 0.25f,1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,
		0.25f, -0.25f, -0.25f,1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,

		0.25f, -0.25f, -0.25f,1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,
		-0.25f, -0.25f, -0.25f,1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,
		-0.25f, -0.25f, 0.25f,1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,

		-0.25f, 0.25f, -0.25f,1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		0.25f, 0.25f, -0.25f,1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		0.25f, 0.25f, 0.25f,1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,

		0.25f, 0.25f, 0.25f,1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		-0.25f, 0.25f, 0.25f,1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		-0.25f, 0.25f, -0.25f,1.0f,
		0.0f, 1.0f, 1.0f, 1.0f
	};

public:
	Cube(Shader shader_program) : Drawable()
	{
		this->init(shader_program, vertexPositions, num_verts);
	}
	~Cube() {}
};