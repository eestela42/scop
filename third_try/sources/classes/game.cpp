#include "../../includes/header.hpp"
#include "../../includes/classes/game.hpp"

game::~game()
{
}

game::game()
{
	this->width = 600;
	this->height = 450;
	this->isRunning = false;
	this->window = NULL;
}

game::game(int width, int height): game()
{
	this->width = width;
	this->height = height;
}

int game::init(int ac, char **av)
{

	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "SCOP LE PROJET COOL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return 2;
	}

	this->mesh = ft_parsing(av[1]);
	this->window = glfwCreateWindow(this->width, this->height, "SCOP LE PROJET COOL", NULL, NULL);
	this->updateIsRunning(true);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return 3;
	}
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(this->window, framebuffer_size_callback);
	return (0);
}


int game::initShadder()
{
	/*Vertex Shader*/
	const char *vertexShaderSource = ft_get_file("shaders/vertex_shader.glsl");

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	if (!vertexShader)
	{
		std::cout << "vertex shadder fail" << std::endl;
		return 1;
	}
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	/*Fragment Shader*/
	const char *fragmentShaderSource = ft_get_file("shaders/fragment_shader.glsl");
	
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	if (!fragmentShader)
	{
		std::cout << "fragmentShader shadder fail" << std::endl;
		return 2;
	}
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	/*Shader Program Finalisation*/
	
	this->shaderProgram = glCreateProgram();
	if (!this->shaderProgram)
	{
		std::cout << "this->shaderProgram shadder fail" << std::endl;
		return 3;
	}

	glAttachShader(this->shaderProgram, vertexShader);
	glAttachShader(this->shaderProgram, fragmentShader);
	glLinkProgram(this->shaderProgram);
	glUseProgram(this->shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);  

	return (0);
}

int game::initBuffers()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0); 

	glGenBuffers(1, &this->VBO);
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->EBO);

	glBindVertexArray(this->VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->mesh.to_vbo), this->mesh.to_vbo.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->mesh.to_ebo), this->mesh.to_ebo.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0); 
	return (0);
}

void game::gameLoop()
{	
    while (this->isRunning)
    {
	
	}	
}


unsigned int game::getVAO()
{
	return (this->VAO);
}

unsigned int game::getVBO()
{
	return (this->VBO);
}

unsigned int game::getEBO()
{
	return (this->EBO);
}

unsigned int game::getShaderProgram()
{
	return (this->shaderProgram);
}

bool game::getIsRunning()
{
	return (this->isRunning);
}

void game::updateIsRunning(bool tmp)
{
	this->isRunning = tmp;
}

t_mesh game::getMesh()
{
	return (this->mesh);
}

// void game::upDateMesh(t_mesh tmp)
// {
// 	this->mesh = tmp;
// }

GLFWwindow* game::getWindow()
{
	return (this->window);
}

void game::upDateWindow(GLFWwindow* tmp)
{
	this->window = tmp;
}


