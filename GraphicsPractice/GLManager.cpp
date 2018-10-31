#include "GLManager.h"

glm::vec3 GLManager::light_movement;

GLfloat GLManager::aspect_ratio;

GLuint GLManager::colour_mode;
GLuint GLManager::sphere_drawmode;

bool GLManager::reset = false;

GLshort GLManager::delta_time = 0;

Camera GLManager::camera;

bool GLManager::close = false;

bool GLManager::show_cursor = false;

glm::vec2 GLManager::cursor_movement;

void GLManager::reset_scene()
{
	sun.move_to(glm::vec4(0, 0, 0, 1));
	reset = false;
}

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
	glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	

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
	events.set_cursor_callback(win, cursor_moved_callback);

	try
	{
		basic_shader = ShaderManager::load_shader("../shaders/basic.vert", "../shaders/basic.frag");
		basic_shader.init_shader(aspect_ratio, BASIC_SHADER);
		basic_shader.set_shininess(20);

		lightsource_shader = ShaderManager::load_shader( "../shaders/lightsource.vert","../shaders/lightsource.frag");
		lightsource_shader.init_shader(aspect_ratio, LIGHTSOURCE_SHADER);
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
	Sphere* sp = new Sphere(basic_shader);
	sp->makeSphere(NUM_LATS_SPHERE, NUM_LONGS_SPHERE);
	bodies.push_back(new Planet(.1f, .2f, 0, sp, nullptr, 10.f));

	//make 4 big normal moons
	for (int i = 0; i < 4; i++)
	{
		float speed = (rand()%20/100.f + 0.1f);
		std::cout << speed << std::endl;
		Sphere* sp = new Sphere(basic_shader);
		sp->makeSphere(NUM_LATS_SPHERE, NUM_LONGS_SPHERE);
		bodies.push_back(new Planet(speed, .1f, rand() % 360, sp, bodies.at(0), 3.f+(i*2.5f)));
	}

	//make 10 small moons
	for (int i = 0; i < 70; i++)
	{
		float speed = (rand() % 20 / 100.f + 0.1f);
		std::cout << speed << std::endl;
		Sphere* sp = new Sphere(basic_shader);
		sp->makeSphere(NUM_LATS_SPHERE, NUM_LONGS_SPHERE);
		bodies.push_back(new Planet(speed, rand()%3/100 + 0.03, rand() % 360, sp, bodies.at(0), 20.f + rand()%5+10.f));
	}

	sun = Lightsource(lightsource_shader);
	sun.set_scale(glm::vec3( .3f, .3f, .3f));
	
}

void GLManager::loop()
{
	glfwSetTime(0);
	while (!glfwWindowShouldClose(win))
	{
		static float prev_time = 0;
		float delta_time = (glfwGetTime() - prev_time) * 300;
		prev_time = glfwGetTime();

		render(delta_time);
		glfwSwapBuffers(win);
		glfwPollEvents();

		if(close == true)
			glfwSetWindowShouldClose(GLManager::win, GL_TRUE);
	}
}

void GLManager::render(float delta_time)
{
	static float jp_scale = 0.3;
	static float mn_scale = 0.1;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera.update(delta_time, cursor_movement);
	cursor_movement = glm::vec2(0);

	//set projection and view matrix inside the shader
	glm::mat4 projection = glm::perspective(glm::radians(12.f), aspect_ratio, 0.1f, 100.f);
	basic_shader.set_projection_matrix(projection);
	lightsource_shader.set_projection_matrix(projection);

	sun.set_view_matrix(camera.get_view_matrix());
	for (Planet* p : bodies)
		p->draw(camera.get_view_matrix(), delta_time, sphere_drawmode);
	sun.shift(glm::vec3(light_movement.x*delta_time, light_movement.y*delta_time, light_movement.z*delta_time));
	sun.draw();

	basic_shader.set_color_mode(colour_mode);
	basic_shader.set_light_position(sun.get_position());

	if (reset)
		reset_scene();

	if(!show_cursor)
		glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	else
		glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void GLManager::terminate()
{
	glfwTerminate();
}

void GLManager::resize_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	aspect_ratio = float(width) / float(height);
	//aspect_ratio = ((float)width / 640.f*4.f) / ((float)height / 480.f*3.f);
}

void GLManager::error_callback(int error, const char* desc)
{
	fputs(desc, stderr);
}

void GLManager::key_callback(GLFWwindow* window, int key_code, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		//camera movement
		if (key_code == GLFW_KEY_W)
			camera.set_z_mov(1);
		else if (key_code == GLFW_KEY_S)
			camera.set_z_mov(-1);

		if (key_code == GLFW_KEY_A)
			camera.set_x_mov(1);
		else if (key_code == GLFW_KEY_D)
			camera.set_x_mov(-1);

		if (key_code == GLFW_KEY_LEFT_CONTROL)
			camera.set_y_mov(1);
		else if (key_code == GLFW_KEY_SPACE)
			camera.set_y_mov(-1);

		//camera look rotation
		if (key_code == GLFW_KEY_E)
			camera.set_y_rot(1);
		else if (key_code == GLFW_KEY_Q)
			camera.set_y_rot(-1);

		//light movement
		if (key_code == GLFW_KEY_UP)
			light_movement.z = -LIGHT_MOVEMENT_SPEED;
		else if (key_code == GLFW_KEY_DOWN)
			light_movement.z = LIGHT_MOVEMENT_SPEED;
		if (key_code == GLFW_KEY_RIGHT)
			light_movement.x = LIGHT_MOVEMENT_SPEED;
		else if (key_code == GLFW_KEY_LEFT)
			light_movement.x = -LIGHT_MOVEMENT_SPEED;
		if (key_code == GLFW_KEY_KP_ADD)
			light_movement.y = LIGHT_MOVEMENT_SPEED;
		else if (key_code == GLFW_KEY_KP_SUBTRACT)
			light_movement.y = -LIGHT_MOVEMENT_SPEED;

		//color mode
		if (key_code == GLFW_KEY_0)
			colour_mode = 0;
		else if (key_code == GLFW_KEY_1)
			colour_mode = 1;

		//reset
		if (key_code == GLFW_KEY_R)
			reset = true;

		if (key_code == GLFW_KEY_M)
			sphere_drawmode = (sphere_drawmode > NUM_DRAWMODES) ? 1 : sphere_drawmode+1;

		if (key_code == GLFW_KEY_ESCAPE)
			close = true;

		if (key_code == GLFW_KEY_TAB)
			show_cursor = !show_cursor;
		
	}
	else if(action == GLFW_RELEASE)
	{
		if (key_code == GLFW_KEY_W || key_code == GLFW_KEY_S)
			camera.set_z_mov(0);
		if (key_code == GLFW_KEY_A || key_code == GLFW_KEY_D)
			camera.set_x_mov(0);

		if (key_code == GLFW_KEY_Q || key_code == GLFW_KEY_E)
			camera.set_y_rot(0);

		if (key_code == GLFW_KEY_RIGHT || key_code == GLFW_KEY_LEFT)
			light_movement.x = 0;
		if (key_code == GLFW_KEY_UP || key_code == GLFW_KEY_DOWN)
			light_movement.z = 0;
		if (key_code == GLFW_KEY_KP_ADD || key_code == GLFW_KEY_KP_SUBTRACT)
			light_movement.y = 0;

		if (key_code == GLFW_KEY_LEFT_CONTROL || key_code == GLFW_KEY_SPACE)
			camera.set_y_mov(0);
	}
}

void GLManager::cursor_moved_callback(GLFWwindow * window, double xpos, double ypos)
{
	static int prev_xpos = 0;
	static int prev_ypos = 0;

	cursor_movement.x = floor(xpos) - prev_xpos;
	cursor_movement.y = floor(ypos) - prev_ypos;

	prev_xpos = floor(xpos);
	prev_ypos = floor(ypos);
}


