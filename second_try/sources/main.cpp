#include "../includes/header.hpp"
//g++ openGL.cpp -lglut -lGLU -lGL; ./a.out
#include "../includes/stb_image.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	(void)window;
    glViewport(0, 0, width, height);
}  



int main(int ac, char** av)
{
    

	t_mesh mesh;
	

	if (ac != 2)
	{
		std::cout << "Usage : ./scop file.obj" << std::endl;
		return 1;
	}

	mesh = ft_parsing (av[1]);

	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// unsigned int VBO;
	// glGenBuffers(1, &VBO);
	// glBindBuffer(GL_ARRAY_BUFFER, VBO);  


	GLFWwindow* window = glfwCreateWindow(800, 600, "SCOP LE PROJET COOL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return 2;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return 3;
	}
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	const char *vertexShaderSource = ft_get_file("shaders/vertex_shader.glsl");
	const char *fragmentShaderSource = ft_get_file("shaders/fragment_shader.glsl");

	std::cout << vertexShaderSource << std::endl;
	std::cout << fragmentShaderSource << std::endl;

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	if (!vertexShader)
	{
		std::cout << "vertex shadder fail" << std::endl;
		return 1;
	}

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);


	
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);  

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0); 

	unsigned int VBO, VAO, EBO;
    glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mesh), mesh.to_vbo.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

	

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mesh.to_ebo), mesh.to_ebo.data(), GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	glBindVertexArray(0); 

	// only lines
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// rotation

	float fTheta = 1.0f;
	t_mat4x4 matRotZ, matRotX;

	// glm::vec3 cubePositions[] = {
    //     glm::vec3( 0.0f,  0.0f,  0.0f),
    //     glm::vec3( 2.0f,  5.0f, -15.0f),
    //     glm::vec3(-1.5f, -2.2f, -2.5f),
    //     glm::vec3(-3.8f, -2.0f, -12.3f),
    //     glm::vec3( 2.4f, -0.4f, -3.5f),
    //     glm::vec3(-1.7f,  3.0f, -7.5f),
    //     glm::vec3( 1.3f, -2.0f, -2.5f),
    //     glm::vec3( 1.5f,  2.0f, -2.5f),
    //     glm::vec3( 1.5f,  0.2f, -1.5f),
    //     glm::vec3(-1.3f,  1.0f, -1.5f)
    // };

	// glm::mat4 view = glm::mat4(1.0f);
	// // note that we're translating the scene in the reverse direction of where we want to move
	// view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	// unsigned int viewInt = glGetUniformLocation(shaderProgram, "model");
	// glUniformMatrix4fv(viewInt, 1, GL_FALSE, &view[0][0]);

	// glm::mat4 projection;
	// projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	// unsigned int projectionInt = glGetUniformLocation(shaderProgram, "model");
	// glUniformMatrix4fv(projectionInt, 1, GL_FALSE, &projection[0][0]);



	// textures
	float texCoords[] = {
		0.0f, 0.0f,  // lower-left corner  
		1.0f, 0.0f,  // lower-right corner
		0.5f, 1.0f   // top-center corner
	};
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char *data = stbi_load("../resources_42/wall.jpg", &width, &height, &nrChannels, 0);


	unsigned int texture;
	glGenTextures(1, &texture);  
	glBindTexture(GL_TEXTURE_2D, texture); 
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	float vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2); 


	

	std::cout << "size : " << mesh.to_ebo.size() * 3 << std::endl; 
 	while(!glfwWindowShouldClose(window))
	{
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			// matRotZ.v[0][0] = cosf(fTheta);
			// matRotZ.v[0][1] = sinf(fTheta);
			// matRotZ.v[1][0] = -sinf(fTheta);
			// matRotZ.v[1][1] = cosf(fTheta);
			// matRotZ.v[2][2] = 1;
			// matRotZ.v[3][3] = 1;

			// // Rotation X
			// matRotX.v[0][0] = 1;
			// matRotX.v[1][1] = cosf(fTheta * 0.5f);
			// matRotX.v[1][2] = sinf(fTheta * 0.5f);
			// matRotX.v[2][1] = -sinf(fTheta * 0.5f);
			// matRotX.v[2][2] = cosf(fTheta * 0.5f);
			// matRotX.v[3][3] = 1;

			// // render
			// // ------
			// glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			// glClear(GL_COLOR_BUFFER_BIT);

			// // draw our first triangle
			// glUseProgram(shaderProgram);

			// float timeValue = glfwGetTime();
			// float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
			// int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
			// glUseProgram(shaderProgram);
			// glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		// int vertexMatrixLocation = glGetUniformLocation(shaderProgram, "matRotZ");
		// glUniformMatrix4fv(vertexMatrixLocation, 1, GL_TRUE, (const GLfloat*)matRotZ.v);

		// vertexMatrixLocation = glGetUniformLocation(shaderProgram, "matRotX");
		// glUniformMatrix4fv(vertexMatrixLocation, 1, GL_TRUE, (const GLfloat*)matRotX.v);


		glm::mat4 model = glm::mat4(1.0f);
		float angle = 20.0f + fTheta; 
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		unsigned int vertexMatrixLocation = glGetUniformLocation(shaderProgram, "model");
		glUniformMatrix4fv(vertexMatrixLocation, 1, GL_FALSE, &model[0][0]);


        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawElements(GL_TRIANGLES, mesh.to_ebo.size() * 3, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // no need to unbind it every time 
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();

		fTheta += 1.f;
    } 

  
    glfwTerminate();
	return 0;
}