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
	//Coord						//Textures			//Normals
	-0.5f, -0.5f, -0.5f,		0.0f, 0.0f,			0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,		1.0f, 0.0f,			0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,		1.0f, 1.0f,			0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,		1.0f, 1.0f,			0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,		0.0f, 1.0f,			0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,		0.0f, 0.0f,			0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,		0.0f, 0.0f,			0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,		1.0f, 0.0f,			0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,		1.0f, 1.0f,			0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,		1.0f, 1.0f,			0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,		0.0f, 1.0f,			0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,		0.0f, 0.0f,			0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f,		1.0f, 0.0f,			-1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,		1.0f, 1.0f,			-1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,		0.0f, 1.0f,			-1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,		0.0f, 1.0f,			-1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,		0.0f, 0.0f,			-1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,		1.0f, 0.0f,			-1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,		1.0f, 0.0f,			1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,		1.0f, 1.0f,			1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,		0.0f, 1.0f,			1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,		0.0f, 1.0f,			1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,		0.0f, 0.0f,			1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,		1.0f, 0.0f,			1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,		0.0f, 1.0f,			0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,		1.0f, 1.0f,			0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,		1.0f, 0.0f,			0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,		1.0f, 0.0f,			0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,		0.0f, 0.0f,			0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,		0.0f, 1.0f,			0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,		0.0f, 1.0f,			0.0f, 1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,		1.0f, 1.0f,			0.0f, 1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,		1.0f, 0.0f,			0.0f, 1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,		1.0f, 0.0f,			0.0f, 1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,		0.0f, 0.0f,			0.0f, 1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,		0.0f, 1.0f,			0.0f, 1.0f,  0.0f
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
	//////    Setting Up SDL3 & OpenGL    ///////

	int width = 800;
	int height = 600;

	//SDL Initializing
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	//Getting OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//Creating Window
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

	//Creating GL context and Loading
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
	


	//////    Creating VAO, VBA, EBO for CUBE object   //////
	VertexArray  vertArr;
	VertexBuffer vertBuff(cube, sizeof(cube));
	IndexBuffer  indBuff(nullptr, 0); // Needed for drawing Element by indices

	//Creating attribute pointers in Vertex Array
	vertArr.Bind();
	vertArr.LinkVBO(vertBuff, 0, 3, 8, 0); // position
	vertArr.LinkVBO(vertBuff, 1, 2, 8, 3); // texture coords
	vertArr.LinkVBO(vertBuff, 2, 3, 8, 5); // Normals
	vertBuff.Unbind();
	vertArr.Unbind();

	//Creating shader program and textures
	Shader shaderProgram("assets/shaders/cube.vert", "assets/shaders/cube.frag");
	Texture2D legoTex("assets/textures/lego.jpg", GL_CLAMP_TO_EDGE);
	Texture2D faceTex("assets/textures/awesomeface.png");

	//Binding textures to shader
	shaderProgram.use();
	legoTex.Bind(0);
	//faceTex.Bind(1);
	shaderProgram.setInt("texture1", 0);
	//shaderProgram.setInt("texture2", 1);

	///// Creating light VAO (with same cube buffer)   /////
	VertexArray lightVAO;
	lightVAO.Bind();
	lightVAO.LinkVBO(vertBuff, 0, 3, 8, 0);
	lightVAO.Unbind();
	Shader lightShader("assets/shaders/cube.vert", "assets/shaders/light.frag");
	

	//Camera
	Camera camera;

	float lastX = width / 2.0f;
	float lastY = height/ 2.0f;
	bool rightClick = false;

	//Wireframe
	bool  wireframe = false;

	//timing
	float lastTime = (float)(SDL_GetTicks() / 1000.0f);
	bool running = true;
	while (running)
	{
		//Delta time
		float currentTime = (float)(SDL_GetTicks() / 1000.0f);
		float deltaTime   = currentTime - lastTime;
		lastTime          = currentTime;

		//Inputs
		const bool* keyStates = SDL_GetKeyboardState(NULL);  // Get the current state of all keys
		
		//Right click holding enables camera movement
		if (rightClick) {

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
			
			//Wireframe mode
			if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_TAB) {
				wireframe = !wireframe;
				glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
			}


			////////  Mouse ///////////
			//Righ click enabling/disabling
			if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
				if (event.button.button == SDL_BUTTON_RIGHT) {
					// Lock mouse to window for FPS-style camera
					rightClick = !rightClick;
					SDL_SetWindowRelativeMouseMode(window, rightClick);
				}
			}
			
			//Rotation
			if (rightClick && event.type == SDL_EVENT_MOUSE_MOTION) {
				float xpos = event.motion.xrel; 
				float ypos = -event.motion.yrel;

				camera.ProcessMouseMovements(xpos, ypos, true);
			}

			//Scroll
			if (event.type == SDL_EVENT_MOUSE_WHEEL) {
				float scrollY = event.wheel.y;
				camera.ProcessMouseScroll(scrollY);
			}
		}

		//////////    Render   ////////////
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Uniform veiw and projections matrix
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.fov), (float)width / (float)height, 0.1f, 100.0f);
		glm::mat4 model;

		////    LIGHT Object    ////
		lightShader.use();
		lightShader.setMat4("view", view);
		lightShader.setMat4("projection", projection);

		// Circling lights
		float radius = 2.0f;
		float speed = 2.0f;

		//light 1  
		lightVAO.Bind();
		glm::vec3 lightPos1;
		lightPos1.x = cos(currentTime * speed + 30.0f) * radius;
		lightPos1.z = sin(currentTime * speed + 30.0f) * radius;
		lightPos1.y = 0.5f;

		glm::vec3 lightColor1(0.8f, 0.2f, 0.6f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos1);
		model = glm::scale(model, glm::vec3(0.2f));
		lightShader.setMat4("model", model);
		lightShader.setVec3("color",lightColor1);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		lightVAO.Unbind();

		
		//light 2 
		lightVAO.Bind();
		glm::vec3 lightPos2;
		lightPos2.x = cos(currentTime * speed) * radius;
		lightPos2.z = 0.0f;
		lightPos2.y = sin(currentTime * speed) * radius;
		glm::vec3 lightColor2(0.2f, 0.9f, 0.6f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos2);
		model = glm::scale(model, glm::vec3(0.2f));
		lightShader.setVec3("color", lightColor2);
		lightShader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		lightVAO.Unbind();


		/////   CUBE Object   /////
		shaderProgram.use();
		shaderProgram.setMat4("view", view);
		shaderProgram.setMat4("projection", projection);
		shaderProgram.setVec3("objectColor", glm::vec3(0.5f, 0.5f, 0.5f));
		shaderProgram.setVec3("lightColor1", lightColor1);
		shaderProgram.setVec3("lightPos1", lightPos1);
		shaderProgram.setVec3("lightColor2", lightColor2);
		shaderProgram.setVec3("lightPos2", lightPos2);
		shaderProgram.setVec3("viewPos", camera.position);

		//Transform
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		shaderProgram.setMat4("model", model);
		//Draw
		vertArr.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);
		vertArr.Unbind();

		SDL_GL_SwapWindow(window);
	}

	vertArr.Delete();
	lightVAO.Delete();

	vertBuff.Delete();
	indBuff.Delete();

	shaderProgram.Delete();
	lightShader.Delete();

	legoTex.Delete();
	faceTex.Delete();

	SDL_GL_DestroyContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
