#ifndef GAME_HPP
# define GAME_HPP

# include "../header.hpp"

struct t_mesh;


class game
{
private:
	int width;
	int height;
	bool isRunning;
	t_mesh mesh;
	GLFWwindow *window;
	unsigned int VBO, VAO, EBO;
	unsigned int shaderProgram;




public:
	~game();
	game(/* args */);
	game(int width, int height);

	int 			init(int ac, char **av);
	int 			initShadder();
	int				initBuffers();
	void 			gameLoop();

	unsigned int 	getVAO();
	unsigned int 	getVBO();
	unsigned int 	getEBO();

	unsigned int 	getShaderProgram();

	bool	 		getIsRunning();
	void 			updateIsRunning(bool tmp);

	t_mesh 			getMesh();
	// void 			upDateMesh(t_mesh tmp);

	GLFWwindow* 		getWindow();
	void 			upDateWindow(GLFWwindow *tmp);

};




#endif