//Two triange with different fragment shaders with different VAOs and VBOs

//#include <iostream>
//#include <glad/glad.h>
//#include <SDL3/SDL.h>
//
//void UpdateViewport(SDL_Window* window)
//{
//	int width = 0;
//	int height = 0;
//	SDL_GetWindowSizeInPixels(window, &width, &height);
//	glViewport(0, 0, width, height);
//}
//
//// Vertex shader source code - Position
//const char* vertexShaderSource = "#version 330 core\n"
//"layout (location = 0) in vec3 aPos;\n"
//"void main()\n"
//"{\n"
//" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//"}\0";
//
//// Fragment shader source code - Color Orange
//const char* fragmentShaderSourceOrange = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"void main()\n"
//"{\n"
//" FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//"}\n\0";
//
//// Fragment shader source code - Color Yellow
//const char* fragmentShaderSourceYellow= "#version 330 core\n"
//"out vec4 FragColor;\n"
//"void main()\n"
//"{\n"
//" FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
//"}\n\0";
//
//int main()
//{
//	//Initialize SDL
//	if (!SDL_Init(SDL_INIT_VIDEO))
//	{
//		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
//		return 1;
//	}
//
//
//
//	//Setting up OpenGL context attributes
//	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
//	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
//	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
//
//
//
//	// Create SDL window with OpenGL context
//	SDL_Window* window = SDL_CreateWindow(
//		"SDL3 OpenGL",
//		800,
//		600,
//		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
//	);
//
//	if (!window) {
//		std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
//		SDL_Quit();
//		return 1;
//	}
//
//
//
//	// Create OpenGL context
//	SDL_GLContext glContext = SDL_GL_CreateContext(window);
//
//	// Load OpenGL functions using glad
//	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		SDL_GL_DestroyContext(glContext);
//		SDL_DestroyWindow(window);
//		SDL_Quit();
//		return -1;
//	}
//
//
//
//
//	// Set Drawing size and position
//	glViewport(0, 0, 800, 600);
//
//	GLfloat triangle1[] = {
//		//1st triangle
//		-0.5f, 0.0f, 0.0f,
//		-0.1f, 0.0f, 0.0f,
//		-0.1f, 0.5f, 0.0f
//	};
//
//	GLfloat triangle2[] = {
//		//2nd triangle
//		0.1f, 0.0f, 0.0f,
//		0.5f, 0.0f, 0.0f,
//		0.1f, 0.5f, 0.0f,
//	};
//
//	//Create vertex shader & fragment shader
//	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
//	glCompileShader(vertexShader);
//
//	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader, 1, &fragmentShaderSourceOrange, nullptr);
//	glCompileShader(fragmentShader);
//
//	GLuint fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShaderYellow, 1, &fragmentShaderSourceYellow, nullptr);
//	glCompileShader(fragmentShaderYellow);
//
//	// Create shader program and link shaders
//	GLuint shaderProgram = glCreateProgram();
//	glAttachShader(shaderProgram, vertexShader);
//	glAttachShader(shaderProgram, fragmentShader);
//	glLinkProgram(shaderProgram);
//
//	GLuint shaderProgramYellow = glCreateProgram();
//	glAttachShader(shaderProgramYellow, vertexShader);
//	glAttachShader(shaderProgramYellow, fragmentShaderYellow);
//	glLinkProgram(shaderProgramYellow);
//
//	// Delete shaders as they are linked into our program now and no longer necessary
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//	glDeleteShader(fragmentShaderYellow);
//
//	// Create vertex array object (VAO) - stores VBOs and how to use them
//	// Create vertex buffer object (VBO) - stores our vertices in GPU memory
//	GLuint VAO[2], VBO[2];
//
//	//Generate VAO and VBO
//	glGenVertexArrays(2, VAO);
//	glGenBuffers(2, VBO);
//
//	//Bind VAO and VBO to use them
//	glBindVertexArray(VAO[0]);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	glBindVertexArray(VAO[1]);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	//Bind VAO and VBO to 0 to prevent accidental modification
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
//
//	//Wireframe mode
//	bool mode = false;
//
//
//	bool running = true;
//	while (running) {
//		// Handle events
//		SDL_Event event;
//		while (SDL_PollEvent(&event))
//		{
//			// Handle quit event
//			if (event.type == SDL_EVENT_QUIT)
//				running = false;
//			// Handle window resize event
//			if (event.window.type == SDL_EVENT_WINDOW_RESIZED)
//				UpdateViewport(window);
//			// Space to change between wireframe and fill modes
//			if (event.key.type == SDL_EVENT_KEY_DOWN) {
//				if (event.key.key == SDLK_SPACE) {
//					mode = !mode;
//					glPolygonMode(GL_FRONT_AND_BACK, mode ? GL_FILL : GL_LINE);
//				}
//			}
//		}
//
//		//Draw Background
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		//Draw Triangle  
//		glUseProgram(shaderProgram);
//		glBindVertexArray(VAO[0]);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//
//		glUseProgram(shaderProgramYellow);
//		glBindVertexArray(VAO[1]);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//
//		SDL_GL_SwapWindow(window);
//	}
//
//	glDeleteVertexArrays(2, VAO);
//	glDeleteBuffers(2, VBO);
//	glDeleteProgram(shaderProgram);
//
//	SDL_GL_DestroyContext(glContext);
//	SDL_DestroyWindow(window);
//	SDL_Quit();
//	return 0;
//}
