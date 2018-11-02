#pragma once
#include <GL/glew.h>
#include "Drawable.h"
#include "Constants.h"


class Triangle : public Drawable
{
private:
	const int num_verts = NUM_TRIANGLE_VERTS;
	float triangle[VALUES_PER_VERT * NUM_TRIANGLE_VERTS] =
	{
		-1.0f, -1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 1.0f,
		.0f, 1.0f, 0.0f, 1.0f,
	};

	float colours[VALUES_PER_VERT * NUM_TRIANGLE_VERTS] =
	{
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f
	};

	/* Manually specified normals for our triangle (3 values per coordinate) */
	float normals[NUM_TRIANGLE_VERTS*VALUES_PER_NORMAL] =
	{
		0, 0, -1.f, 
		0, 0, -1.f, 
		0, 0, -1.f,
	};

	
public:
	Triangle(Shader shader_program) : Drawable()
	{
		this->init(shader_program, triangle, num_verts, colours, normals);
	}
	~Triangle() {}
};

