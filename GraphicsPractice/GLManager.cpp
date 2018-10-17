#include "GLManager.h"

float GLManager::movement_x;
float GLManager::movement_z;
float GLManager::rotation_y;

GLfloat GLManager::aspect_ratio;

GLManager::GLManager()
{
	
}


GLManager::~GLManager()
{
}

void GLManager::init()
{
	if (!glfwInit())
	{
		std::cout << "Failed to init GLFW." << std::endl;
		exit(EXIT_FAILURE);
	}
	win = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Simplest", NULL, NULL);
	aspect_ratio = WINDOW_WIDTH / WINDOW_HEIGHT;
	glfwMakeContextCurrent(win);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	events.set_error_callback(error_callback);
	events.set_reshape_callback(win, resize_callback);
	events.set_key_callback(win, key_callback);

	try
	{
		shader = ShaderManager::load_shader("../shaders/basic.vert", "../shaders/basic.frag");
		shader.init_shader(aspect_ratio);
	}
	catch (std::exception e)
	{
		std::cout << "Couldn't load shader: " << e.what() << std::endl;
		std::cin.ignore();
		exit(EXIT_FAILURE);
	}

	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 1);

	init_objects();
}

void GLManager::init_objects()
{
	triangle = Triangle(shader);
	square = Square(shader);
	cube = Cube(shader);
}

void GLManager::loop()
{
	while (!glfwWindowShouldClose(win))
	{
		render();
		glfwSwapBuffers(win);
		glfwPollEvents();
	}
}

void GLManager::render()
{
	static float x_pos = 0;
	static float z_pos = 1;
	static float y_rot = 0;
	static float angle = .0f;
	static float rate = 1.f;
	angle += rate;
	if (angle > 360)
		angle = 0;
	if (y_rot > 360)
		y_rot = 0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//move camera
	glm::mat4 view_matrix = glm::lookAt(
		glm::vec3(0,0,1),
		glm::vec3(0,0,0),
		glm::vec3(0,1,0)
	);
	view_matrix = glm::translate(view_matrix, glm::vec3(x_pos, 0, z_pos));
	view_matrix = glm::rotate(view_matrix, glm::radians(y_rot), glm::vec3(0, 1, 0));
	shader.set_view_matrix(view_matrix);


	std::stack<glm::mat4> transf;
	transf.push(glm::mat4(1.0f));
	transf.top() = glm::translate(transf.top(), glm::vec3(0, 0, -0.25f));
	transf.top() = glm::scale(transf.top(),glm::vec3(.5f, .5f, 1.f));
	transf.top() = glm::rotate(transf.top(), glm::radians(30.f), glm::vec3(0, 0, 1));

	//move square to the left
	transf.push(transf.top());
	{
		transf.top() = glm::translate(transf.top(), glm::vec3(-1.f, 0.f, 0.f));
		square.set_model_matrix(transf.top());
	}
	transf.pop();
	square.draw();
	
	//move triangle to left
	transf.push(transf.top());
	{
		transf.top() = glm::translate(transf.top(), glm::vec3(1.f, 0.f, 0.f));
		triangle.set_model_matrix(transf.top());
	}
	transf.pop();
	triangle.draw();

	//rotate cube
	transf.top() = glm::rotate(transf.top(), glm::radians(angle), glm::vec3(1, 1, 0));
	cube.set_model_matrix(transf.top());
	cube.draw();

	x_pos += movement_x;
	z_pos += movement_z;
	y_rot += rotation_y;

	std::cerr << x_pos << " " << z_pos << " " << y_rot << std::endl;
}

void GLManager::terminate()
{
	glfwTerminate();
}

void GLManager::resize_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	aspect_ratio = float(width) / float(height);
}

void GLManager::error_callback(int error, const char* desc)
{
	fputs(desc, stderr);
}

void GLManager::key_callback(GLFWwindow* window, int key_code, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		if (key_code == GLFW_KEY_W)
			movement_z = 0.01f;
		else if (key_code == GLFW_KEY_S)
			movement_z = -0.01;

		if (key_code == GLFW_KEY_A)
			movement_x = 0.01;
		else if (key_code == GLFW_KEY_D)
			movement_x = -0.01;

		if (key_code == GLFW_KEY_RIGHT)
			rotation_y = 0.5;
		else if (key_code == GLFW_KEY_LEFT)
			rotation_y = -0.5;

	}
	else if(action == GLFW_RELEASE)
	{
		if (key_code == GLFW_KEY_W || key_code == GLFW_KEY_S)
			movement_z = 0;
		if (key_code == GLFW_KEY_A || key_code == GLFW_KEY_D)
			movement_x = 0;

		if (key_code == GLFW_KEY_RIGHT || key_code == GLFW_KEY_LEFT)
			rotation_y = 0;
	}
}


