// GLAD inclusion
#include <glad/glad.h>

// GLFW inclusion
#include <GLFW/glfw3.h>

// io
#include <stdio.h>

// Trivial config namespace; this isn't a wonderful idea in practice
// but can be useful if you want to just lock some variables away.
namespace // local-only
{
	namespace config
	{
		const GLuint window_width = 800;
		const GLuint window_height = 600;
	}

	// GLFW window
	GLFWwindow* window;
}

// Callback code for GLFW3.
void keyboard_callback(GLFWwindow* window,
	int key, int scancode,
	int action, int mode)
{
	// Kill the window on escape being pressed down.
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

// The main function
// from here we start the application and run the game loop
int main()
{
	printf("Initialising glfw...");

	// Init GLFW
	if(!glfwInit())
	{
		printf("Failed to initialise glfwInit.");
	}

	// OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Disable the resize functionality because it's not useful here.
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create the window
	window = glfwCreateWindow(
		config::window_width,
		config::window_height,
		"deps-glfw-glad sample",
		nullptr,
		nullptr
	);

	// If the window is nullptr.
	if (window == nullptr)
	{
		printf("Failed to create a GLFW window.\n");
		glfwTerminate();
		return -1;
	}

	// Make it current.
	glfwMakeContextCurrent(window);

	// Setup keyboard callback.
	glfwSetKeyCallback(window, keyboard_callback);

	// Glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("glad loading failed (no valid context created).\n");
		return -1;
	}

	// gl setup
	glViewport(0, 0, config::window_width, config::window_height);

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		// Check for any events.
		glfwPollEvents();

		// Clear
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw here

		// Swap buffers.
		glfwSwapBuffers(window);
	}

	// Terminate.
	glfwTerminate();

	// Return 0
	return 0;
}