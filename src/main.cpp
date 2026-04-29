#include <iostream>
#include <SDL3/SDL.h>
#include <glad/glad.h>
#include "graphics/graphics.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.h"
#include "key_code.h"

namespace
{
	void UpdateViewport(SDL_Window* window, int& width, int& height)
	{
		SDL_GetWindowSizeInPixels(window, &width, &height);
		glViewport(0, 0, width, height);
	}

}

float cube[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
	glm::vec3( 0.0f,  0.0f,   0.0f),
	glm::vec3( 2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f,  -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3( 2.4f, -0.4f,  -3.5f),
	glm::vec3(-1.7f,  3.0f,  -7.5f),
	glm::vec3( 1.3f, -2.0f,  -2.5f),
	glm::vec3( 1.5f,  2.0f,  -2.5f),
	glm::vec3( 1.5f,  0.2f,  -1.5f),
	glm::vec3(-1.3f,  1.0f,  -1.5f)
};

int main()
{
	int width = 800;
	int height = 600;

	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_Window* window = SDL_CreateWindow(
		"SDL3 OpenGL",
		800, 600,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
	);

	if (!window)
	{
		std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(window);

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		SDL_GL_DestroyContext(glContext);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	//OpenGL Settings
	glViewport(0, 0, 800, 600);
	glEnable(GL_DEPTH_TEST);

	// Lock mouse to window for FPS-style camera
	SDL_SetWindowRelativeMouseMode(window, true);

	Texture2D brickTex("assets/textures/container.jpg", GL_CLAMP_TO_EDGE);
	Texture2D faceTex("assets/textures/awesomeface.png");

	Shader shaderProgram("assets/shaders/default.vert", "assets/shaders/default.frag");

	VertexArray  vertArr;
	VertexBuffer vertBuff(cube, sizeof(cube));
	IndexBuffer  indBuff(nullptr, 0); // cube uses glDrawArrays, no indices needed

	vertArr.Bind();
	vertArr.LinkVBO(vertBuff, 0, 3, 5, 0); // position
	vertArr.LinkVBO(vertBuff, 2, 2, 5, 3); // texture coords
	vertBuff.Unbind();
	vertArr.Unbind();

	shaderProgram.use();
	brickTex.Bind(0);
	faceTex.Bind(1);
	shaderProgram.setInt("texture1", 0);
	shaderProgram.setInt("texture2", 1);

	//Camera
	Camera camera;

	float lastX = width / 2.0f;
	float lastY = height/ 2.0f;
	bool firstMouse = true;

	//Wireframe
	bool  wireframe = false;

	//timing
	float lastTime  = static_cast<float>(SDL_GetTicks()) / 1000.0f;

	bool running = true;
	while (running)
	{
		//Delta time
		float currentTime = static_cast<float>(SDL_GetTicks()) / 1000.0f;
		float deltaTime   = currentTime - lastTime;
		lastTime          = currentTime;

		//Inputs
		const bool* keyStates = SDL_GetKeyboardState(NULL);  // Get the current state of all keys

		// Camera movements using keyboard state
		if (keyStates[SDL_SCANCODE_W]) {
			camera.ProcessKeyboard(KeyCode::W, deltaTime);  // Move forward
		}
		if (keyStates[SDL_SCANCODE_A]) {
			camera.ProcessKeyboard(KeyCode::A, deltaTime);  // Move left
		}
		if (keyStates[SDL_SCANCODE_S]) {
			camera.ProcessKeyboard(KeyCode::S, deltaTime);  // Move backward
		}
		if (keyStates[SDL_SCANCODE_D]) {
			camera.ProcessKeyboard(KeyCode::D, deltaTime);  // Move right
		}

		// Wireframe mode toggle (Tab key)
		if (keyStates[SDL_SCANCODE_TAB]) {
			wireframe = !wireframe;
			glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
		}


		//Events
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			//Windows resize
			if (event.type == SDL_EVENT_WINDOW_RESIZED)
				UpdateViewport(window, width, height);

			//Quitting game 
			if (event.type == SDL_EVENT_QUIT ||
				(event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE)) {
				running = false;
			}

			////Mouse Events
			//Move
			if (event.type == SDL_EVENT_MOUSE_MOTION) {
				float xpos = event.motion.xrel; 
				float ypos = -event.motion.yrel;

				//if (firstMouse)
				//{
				//	lastX = xpos;
				//	lastY = ypos;
				//	firstMouse = false;
				//}
				//float xoffset = xpos - lastX;
				//float yoffset = ypos - lastY;

				//lastX = xpos;
				//lastY = ypos;
				//camera.ProcessMouseMovements(xoffset, yoffset, true);

				camera.ProcessMouseMovements(xpos, ypos, true);
			}

			//Scroll
			if (event.type == SDL_EVENT_MOUSE_WHEEL) {
				float scrollY = event.wheel.y;
				camera.ProcessMouseScroll(scrollY);
			}
		}

		// Render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		vertArr.Bind();

		SDL_GetWindowSizeInPixels(window, &width, &height);

		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.fov), (float)width / (float)height, 0.1f, 100.0f);

		shaderProgram.setMat4("view", view);
		shaderProgram.setMat4("projection", projection);

		for (GLuint i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);

			if (i % 3 == 0)
			{
				model = glm::rotate(model, currentTime * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
				model = glm::scale(model, glm::vec3(0.5f));
			}

			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

			shaderProgram.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		SDL_GL_SwapWindow(window);
	}

	vertArr.Delete();
	vertBuff.Delete();
	indBuff.Delete();
	shaderProgram.Delete();
	brickTex.Delete();
	faceTex.Delete();

	SDL_GL_DestroyContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
