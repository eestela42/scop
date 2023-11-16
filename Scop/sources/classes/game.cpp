#include "../../includes/header.hpp"
#include "../../includes/classes/game.hpp"

using namespace ee;

game::~game()
{
	glfwDestroyWindow(this->window);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteTextures(1, &this->texture);
	glDeleteProgram(this->shaderProgram);

	
	
	glfwTerminate();

}

game::game()
{
	this->width = 600;
	this->height = 450;
	this->isRunning = false;
	this->window = NULL;
	this->mesh = ee::mesh();
}

game::game(int width, int height): game()
{
	this->width = width;
	this->height = height;
}


int game::init(int ac, char **av)
{
	(void)ac;
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->window = glfwCreateWindow(this->width, this->height, "SCOP LE PROJET COOL", NULL, NULL);
	if (this->window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return 2;
	}

	mesh = ee::mesh(av[1]);

	


	glfwMakeContextCurrent(this->window);
	this->updateIsRunning(true);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return 3;
	}
	glViewport(0, 0, this->width, this->height);
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
	
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
	
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh.vertexes.size() * sizeof(t_vec3), &mesh.vertexes[0], GL_STATIC_DRAW);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.triangles.size() * sizeof(t_triangle), &mesh.triangles[0], GL_STATIC_DRAW);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);


	
	

	

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    // glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 

	
	return (0);
}

int game::initTexture()
{


	glGenTextures(1, &this->texture);  
	glBindTexture(GL_TEXTURE_2D, this->texture); 

	// set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char *data = stbi_load("../resources_42/poney.jpg", &width, &height, &nrChannels, 0);


	
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
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

void	game::upDateVBO(std::vector<vec3> tmp)
{
	this->mesh.vertexes = tmp;
}

unsigned int game::getEBO()
{
	return (this->EBO);
}

unsigned int game::getTexture()
{
	return (this->texture);
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

mesh game::getMesh()
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

float* game::vbo_to_vertexes()
{
	float *tmp = new float[this->mesh.vertexes.size() * 3];
	int i = 0;
	for	(std::vector<vec3>::iterator it = this->mesh.vertexes.begin(); it != this->mesh.vertexes.end(); ++it)
	{
		tmp[i] = (*it)[0];
		tmp[i + 1] = (*it)[1];
		tmp[i + 2] = (*it)[2];
		i += 3;
	}
	return (tmp);
}

unsigned int* game::ebo_to_indices()
{
	unsigned int *tmp = new unsigned int[this->mesh.triangles.size() * 3];
	int i = 0;
	for	(std::vector<t_triangle>::iterator it = this->mesh.triangles.begin(); it != this->mesh.triangles.end(); ++it)
	{
		tmp[i] = it->v[0];
		tmp[i + 1] = it->v[1];
		tmp[i + 2] = it->v[2];
		i += 3;
	}
	return (tmp);
}


void game::setBool(const std::string &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(this->shaderProgram, name.c_str()), (int)value); 
}
void game::setInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(this->shaderProgram, name.c_str()), value); 
}
void game::setFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(this->shaderProgram, name.c_str()), value); 
}

void game::displayEBO()
{
	for (std::vector<t_triangle>::iterator it = this->mesh.triangles.begin(); it != this->mesh.triangles.end(); ++it)
	{
		std::cout << it->v[0] << " " << it->v[1] << " " << it->v[2] << std::endl;
	}
}

void game::displayVBO()
{
	for (std::vector<vec3>::iterator it = this->mesh.vertexes.begin(); it != this->mesh.vertexes.end(); ++it)
	{
		std::cout << (*it)[0] << " " << (*it)[1] << " " << (*it)[2] << std::endl;
	}
}


