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
		1.0f, 0.0f, 0.0f, 1.0f,

		.5f, .5f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,

		0.5f, -0.5f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,

		0.5f, -0.5f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,

		-0.5f, -0.5f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,

		-0.5f, 0.5f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f
	};

public:
	Square(const char* shader_path, const char* fragment_shader_path) : Drawable()
	{
		this->init(shader_path, fragment_shader_path, square, num_verts);
	}
	~Square() {}
};

