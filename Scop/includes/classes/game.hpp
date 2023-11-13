#ifndef GAME_HPP
# define GAME_HPP

# include <iostream>
# include <string.h>
# include <sstream>
# include <fstream>
# include <math.h>
# include "../glad/glad.h" 
# include <GL/glut.h>
# include "mesh.hpp"
# include <vector>
# include "../types.hpp"





class game
{
private:
	int width;
	int height;
	bool isRunning;
	my_mesh mesh;
	GLFWwindow *window;
	unsigned int VBO, VAO, EBO;
	unsigned int shaderProgram;
	unsigned int texture;




public:
	~game();
	game(/* args */);
	game(int width, int height);

	int 			init(int ac, char **av);
	int 			initShadder();
	int				initBuffers();
	int				initTexture();
	void 			gameLoop();



	unsigned int 	getVAO();
	unsigned int 	getVBO();
	void			upDateVBO(std::vector<t_vec3> tmp);
	unsigned int 	getEBO();
	unsigned int 	getTexture();

	unsigned int 	getShaderProgram();

	bool	 		getIsRunning();
	void 			updateIsRunning(bool tmp);

	my_mesh 		getMesh();
	void 			upDateMesh(my_mesh tmp);

	GLFWwindow* 	getWindow();
	void 			upDateWindow(GLFWwindow *tmp);

	float* 			vbo_to_vertexes();
	unsigned int* 	ebo_to_indices();

	

	void			setBool(const std::string &name, bool value) const;
	void 			setInt(const std::string &name, int value) const;
	void			setFloat(const std::string &name, float value) const;

	void 			displayEBO();
	void 			displayVBO();
};






#endif