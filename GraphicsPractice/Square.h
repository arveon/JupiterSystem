/* by Aleksejs Loginovs - October 2018 */

#pragma once
#include "Drawable.h"
#include "Constants.h"

class Square : public Drawable
{
private:
	const int num_verts = NUM_SQR_VERTS;
	float square[NUM_SQR_VERTS*VALUES_PER_VERT] =
	{
		-0.5f, 0.5f, 0.0f, 1.0f,
		.5f, .5f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 1.0f,
	};

	float colours[NUM_SQR_VERTS*VALUES_PER_VERT] =
	{
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f
	};

	/* Manually specified normals for our triangle (3 values per coordinate) */
	float normals[NUM_SQR_VERTS*VALUES_PER_NORMAL] =
	{
		0, 0, -1.f,
		0, 0, -1.f,
		0, 0, -1.f,
		0, 0, -1.f
	};

public:
	Square(Shader shader_program) : Drawable()
	{
		this->init(shader_program, square, num_verts, colours, normals);
	}
	~Square() {}
};

