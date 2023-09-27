#ifndef GAME_HPP
# define GAME_HPP

# include "../header.hpp"
# include <vector>

typedef struct s_vec3
{
	float x, y, z;
}				t_vec3;

typedef struct s_triangle
{
	unsigned int v[3];
}				t_triangle;

typedef struct s_mesh
{
	std::vector<t_vec3> to_vbo;
	std::vector<t_triangle> to_ebo;
}	t_mesh;


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


	void			addColorTo_vbo();

	unsigned int 	getVAO();
	unsigned int 	getVBO();
	unsigned int 	getEBO();
	unsigned int 	getTexture();

	unsigned int 	getShaderProgram();

	bool	 		getIsRunning();
	void 			updateIsRunning(bool tmp);

	t_mesh 			getMesh();
	void 			upDateMesh(t_mesh tmp);

	GLFWwindow* 	getWindow();
	void 			upDateWindow(GLFWwindow *tmp);

	float* 			vbo_to_vertexes();
	unsigned int* 	ebo_to_indices();

	

	void			setBool(const std::string &name, bool value) const;
	void 			setInt(const std::string &name, int value) const;
	void			setFloat(const std::string &name, float value) const;
};






#endif