#include "GLManager.h"

glm::vec3 GLManager::light_movement;

GLfloat GLManager::aspect_ratio;

float GLManager::unaffected_time = 0;
int GLManager::speed = 300;

Camera GLManager::camera;

bool GLManager::reset = false;
bool GLManager::close = false;
bool GLManager::show_cursor = false;
bool GLManager::attenuation_enabled = true;
bool GLManager::texture_enabled = true;

glm::vec2 GLManager::cursor_movement;

///Function used to reset the scene (camera,  sun, time speed)
void GLManager::reset_scene()
{
	sun.move_to(glm::vec4(0, 0, 0, 1));
	camera.reset();
	reset = false;
	speed = 300;
}

GLManager::GLManager()
{
	srand(time(0));

	std::cout << "Hello and welcome to this very inaccurate Jupiter system simulator." << std::endl;
	std::cout << "You are playing as a god. You can freely fly around and control the flow of time and the behavior of light." << std::endl;
	std::cout << "You can also move the Sun if you wish to." << std::endl;

	std::cout << "Use the mouse to look around." << std::endl;
	std::cout << "WASD - fly around." << std::endl;
	std::cout << "Space/Ctrl - to fly up and down." << std::endl;
	std::cout << "< > - to speed up/slow down the time." << std::endl;
	std::cout << "Arrow keys - To move the Sun along the x and y axis." << std::endl;
	std::cout << "Keypad + and - - To move the Sun along the z axis." << std::endl;
	std::cout << "Tab - To gain control of the mouse. And to return back to mouse captured mode." << std::endl;
	std::cout << "R - To reset the world to it's initial state in case something goes wrong (and the camera position and rotation)." << std::endl;
	std::cout << "T - To toggle the surface textures on and off." << std::endl;
	std::cout << "X - To toggle attenuation on and off." << std::endl;
	std::cout << "Esc - To close the simulator." << std::endl;
	std::cout << "Please wait a few seconds while the simulation loads all your godly powers." << std::endl;
}


GLManager::~GLManager()
{
}

///Function used to initialise all of the required opengl components and load the required textures
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

	events.set_error_callback(error_callback);
	events.set_reshape_callback(win, resize_callback);
	events.set_key_callback(win, key_callback);
	events.set_cursor_callback(win, cursor_moved_callback);

	//load required shaders
	try
	{
		basic_shader = ShaderManager::load_shader("../shaders/basic.vert", "../shaders/basic.frag");
		basic_shader.init_shader(aspect_ratio, BASIC_SHADER);
		basic_shader.set_shininess(2);

		lightsource_shader = ShaderManager::load_shader( "../shaders/lightsource.vert","../shaders/lightsource.frag");
		lightsource_shader.init_shader(aspect_ratio, LIGHTSOURCE_SHADER);

		unlit_texture_shader = ShaderManager::load_shader("../shaders/unlit_textured.vert", "../shaders/unlit_textured.frag");
		unlit_texture_shader.init_shader(aspect_ratio, LIGHTSOURCE_SHADER);
	}
	catch (std::exception e)
	{
		std::cout << "Couldn't load shader: " << e.what() << std::endl;
		std::cin.ignore();
		exit(EXIT_FAILURE);
	}

	//load required textures
	try
	{
		skybox_tex = SOIL_load_OGL_texture("..\\textures\\skybox.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
		jupiter_tex = SOIL_load_OGL_texture("..\\textures\\jupiter.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
		big_moons_tex[0] = SOIL_load_OGL_texture("..\\textures\\io.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
		big_moons_tex[1] = SOIL_load_OGL_texture("..\\textures\\europa.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
		big_moons_tex[2] = SOIL_load_OGL_texture("..\\textures\\ganymede.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
		big_moons_tex[3] = SOIL_load_OGL_texture("..\\textures\\callisto.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

		asteroids_tex[0] = SOIL_load_OGL_texture("..\\textures\\asteroid1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
		asteroids_tex[1] = SOIL_load_OGL_texture("..\\textures\\asteroid2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
		asteroids_tex[2] = SOIL_load_OGL_texture("..\\textures\\asteroid3.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

		if (jupiter_tex == 0 || big_moons_tex[0] == 0 || big_moons_tex[1] == 0 || big_moons_tex[2] == 0 || big_moons_tex[3] == 0
			|| asteroids_tex[0] == 0 || asteroids_tex[1] == 0 || asteroids_tex[2] == 0 || skybox_tex == 0)
			std::cerr << "Error loading texture: " << SOIL_last_result() << std::endl;

		int loc = glGetUniformLocation(basic_shader.get_program_id(), "tex");
		if (loc >= 0) glUniform1i(loc, 0);
	}
	catch (std::exception &e)
	{
		std::cerr << "Couldn't load a texture." << std::endl;
	}

	//enable depth texting
	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 1);

	// Enable face culling. This will cull the back faces of all
	// triangles. Be careful to ensure that triangles are drawn
	// with correct winding.
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	init_objects();
}

///Function used to separate the object initialisation logic out
void GLManager::init_objects()
{
	cube = new Cube();
	cube->colours_enabled = false;
	cube->normals_enabled = false;
	cube->init(unlit_texture_shader, skybox_tex);

	//sphere that will represent Jupiter
	Sphere* sp = new Sphere(basic_shader, jupiter_tex);
	sp->makeSphere(NUM_LATS_SPHERE, NUM_LONGS_SPHERE);
	bodies.push_back(new Planet(.1f, .2f, 0, sp, nullptr, 10.f));

	//make 4 big normal moons
	for (int i = 0; i < 4; i++)
	{
		float speed = (rand()%10/100.f + 0.3f);
		Sphere* sp = new Sphere(basic_shader, big_moons_tex[i]);
		sp->makeSphere(NUM_LATS_SPHERE, NUM_LONGS_SPHERE);
		bodies.push_back(new Planet(speed, .1f, rand() % 360, sp, bodies.at(0), 3.f+(i*2.5f)));
	}

	//a sphere that will rotate around the second moon of jupiter
	Sphere* test = new Sphere(basic_shader, jupiter_tex);
	test->makeSphere(NUM_LATS_SPHERE, NUM_LONGS_SPHERE);
	bodies.push_back(new Planet(.5f, .05f, 0, test, bodies.at(2), 5.f));

	//make 20 small moons
	for (int i = 0; i < 20; i++)
	{
		float speed = (rand() % 20 / 100.f + 0.1f);
		Sphere* sp = new Sphere(basic_shader, asteroids_tex[rand()%3]);
		sp->makeSphere(NUM_LATS_SPHERE, NUM_LONGS_SPHERE);
		bodies.push_back(new Planet(speed, rand()%3/100 + 0.03, rand() % 360, sp, bodies.at(0), 20.f + rand()%15+10.f));
	}

	sun = Lightsource(lightsource_shader);
	sun.set_scale(glm::vec3( .3f, .3f, .3f));

	
}

void GLManager::loop()
{
	glfwSetTime(0);
	while (!glfwWindowShouldClose(win))
	{
		//calculate time from last tick
		static float prev_time = 0;
		unaffected_time = (glfwGetTime() - prev_time);
		float delta_time = unaffected_time * speed;
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera.update(unaffected_time, cursor_movement);
	cursor_movement = glm::vec2(0);//reset cursor delta movement every tick

	//set projection matrix in all shaders
	glm::mat4 projection = glm::perspective(glm::radians(12.f), aspect_ratio, 0.1f, 200.f);
	basic_shader.set_projection_matrix(projection);
	lightsource_shader.set_projection_matrix(projection);
	unlit_texture_shader.set_projection_matrix(projection);

	//set view matrix in objects that need it
	cube->set_view_matrix(camera.get_view_matrix());
	sun.set_view_matrix(camera.get_view_matrix());

	//draw all planets
	for (Planet* p : bodies)
		p->draw(camera.get_view_matrix(), delta_time);

	//manipulate and draw other objects
	cube->scale(glm::vec3(100, 50, 100));
	cube->draw();
	sun.shift(glm::vec3(light_movement.x*delta_time, light_movement.y*delta_time, light_movement.z*delta_time));
	sun.draw();

	//set the light position in lit shader
	basic_shader.set_light_position(camera.get_view_matrix()*sun.get_position());

	//apply scene changes if specific flags were set
	if (reset)
		reset_scene();
	if(!show_cursor)
		glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	else
		glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	basic_shader.set_attenuation_enabled(attenuation_enabled);
	basic_shader.set_texture_enabled(texture_enabled);
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

		//reset
		if (key_code == GLFW_KEY_R)
			reset = true;

		//close window
		if (key_code == GLFW_KEY_ESCAPE)
			close = true;

		//toggle cursor
		if (key_code == GLFW_KEY_TAB)
			show_cursor = !show_cursor;

		//toggle attenuation
		if (key_code == GLFW_KEY_X)
			attenuation_enabled = !attenuation_enabled;

		//toggle texture
		if (key_code == GLFW_KEY_T)
			texture_enabled = !texture_enabled;

		//time speed changes
		if (key_code == GLFW_KEY_PERIOD)
			speed += 30;
		if (key_code == GLFW_KEY_COMMA)
			speed -= 30;
		
	}
	else if(action == GLFW_RELEASE)
	{
		//reset speeds on key releases
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
	static int prev_xpos = NULL;
	static int prev_ypos = NULL;

	if (!show_cursor)//only keep track of cursor movement if its captured by window
	{
		if (prev_xpos == NULL)
		{//safeguard against a jump at the first call, when these values aren't set yet (=> equal to 0)
			prev_xpos = xpos;
			prev_ypos = ypos;
		}

		cursor_movement.x = floor(xpos) - prev_xpos;
		cursor_movement.y = floor(ypos) - prev_ypos;
	}

	prev_xpos = floor(xpos);
	prev_ypos = floor(ypos);
}


