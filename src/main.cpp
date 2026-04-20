#include <iostream>
#include <SDL3/SDL.h>
#include <glad/glad.h>
#include "graphics/graphics.h"

namespace
{
	void UpdateViewport(SDL_Window* window)
	{
		int width = 0;
		int height = 0;
		SDL_GetWindowSizeInPixels(window, &width, &height);
		glViewport(0, 0, width, height);
	}
}

// Triangle
GLfloat triangleVertices[] = {
	//Positions				//Colors				//Texture Coordinates
	-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,										// 0 - Left
	 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,										// 1 - Right
	 0.0f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f,										// 2 - Top
	 -0.25f, 0.0f, 0.0f,	1.0f, 1.0f, 0.0f,										// 3 - Mid_LT
	 0.0f, -0.5f, 0.0f,		0.0f, 1.0f, 1.0f,										// 4 - Mid_LR
	 0.25f, 0.0f, 0.0f,		1.0f, 0.0f, 1.0f										// 5 - Mid_RT
};

GLuint triangleIndices[] = {
	0, 4, 3, // Left Bottom
	4, 1, 5, // Right Bottom
	3, 5, 2// Top Triangle
};


GLfloat rectVertices[] = {
	// positions          // colors           // texture coords
	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};

GLuint rectIndices[]{
	0, 1, 2,
	0, 3, 2
};

int main()
{
	//Initialize SDL
	if(!SDL_Init(SDL_INIT_VIDEO))
	{
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	//Setting up OpenGL context attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);



	// Create SDL window with OpenGL context
	SDL_Window* window = SDL_CreateWindow(
		"SDL3 OpenGL",
		800,
		600,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
	);

	if (!window) {
		std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}



	// Create OpenGL context
	SDL_GLContext glContext = SDL_GL_CreateContext(window);

	// Load OpenGL functions using glad
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		SDL_GL_DestroyContext(glContext);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}



	// Set Drawing size and position
	glViewport(0, 0, 800, 600);
	
	Texture2D brickTex("assets/textures/container.jpg", GL_CLAMP_TO_EDGE);
	Texture2D faceTex("assets/textures/awesomeface.png");

	Shader shaderProgram("assets/shaders/default.vert", "assets/shaders/default.frag");

	VertexArray vertArr;
	vertArr.Bind();

	VertexBuffer vertBuff(rectVertices, sizeof(rectVertices));
	IndexBuffer indBuff(rectIndices, sizeof(rectIndices));

	vertArr.LinkVBO(vertBuff, 0, 3, 8, 0);
	vertArr.LinkVBO(vertBuff, 1, 3, 8, 3);
	vertArr.LinkVBO(vertBuff, 2, 2, 8, 6);

	vertBuff.Unbind();
	vertArr.Unbind();
	indBuff.Unbind();
	faceTex.Unbind();


	//Control variables
	bool mode = false;
	float xoffset = 0.0f;
	float yoffset = 0.0f;
	//float proportion = 0.2f;

	shaderProgram.use();

	brickTex.Bind(0);
	faceTex.Bind(1);

	shaderProgram.setInt("texture1", 0);
	shaderProgram.setInt("texture2", 1);

	vertArr.Bind();

	bool running = true;
	while (running) {
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			// Handle quit event
			if (event.type == SDL_EVENT_QUIT) 
				running = false;
			// Handle window resize event
			if (event.window.type == SDL_EVENT_WINDOW_RESIZED)
				UpdateViewport(window);
			// Space to change between wireframe and fill modes
			if (event.key.type == SDL_EVENT_KEY_DOWN) {
				if (event.key.key == SDLK_SPACE) {
					mode = !mode;
					glPolygonMode(GL_FRONT_AND_BACK, mode ? GL_FILL : GL_LINE);
				}
				if (event.key.key == SDLK_RIGHT)
				{
					xoffset += 0.05f;
					shaderProgram.setFloat("xOffset", xoffset);
				}
				if (event.key.key == SDLK_LEFT)
				{
					xoffset -= 0.05f;
					shaderProgram.setFloat("xOffset", xoffset);
				}
				if (event.key.key == SDLK_UP)
				{
					//proportion += 0.05f;
					yoffset += 0.05f;
					shaderProgram.setFloat("yOffset", yoffset);
				}
				if (event.key.key == SDLK_DOWN)
				{
					//proportion -= 0.05f;
					yoffset -= 0.05f;
					shaderProgram.setFloat("yOffset", yoffset);
				}
			}
		}

		//Draw Background
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		//Draw Triangle
		//glDrawArrays(GL_TRIANGLES, 0, 6);

		//Draw from IndexBuffer/Element Array
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


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
