#ifndef HEADER_HPP
# define HEADER_HPP

# include <iostream>
# include <string.h>
# include <sstream>
# include <fstream>
# include <math.h>
# include "glad/glad.h" 
# include <GL/glut.h>
// # include <glew.h> 
# include <GLFW/glfw3.h>
# include <vector>
# include "classes/game.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"

# define STB_IMAGE_IMPLEMENTATION


// typedef struct s_vec3
// {
// 	float x, y, z;
// }				t_vec3;

// typedef struct s_triangle
// {
// 	int v[3];
// }				t_triangle;

// typedef struct s_mesh
// {
// 	std::vector<t_vec3> to_vbo;
// 	std::vector<t_triangle> to_ebo;
// }				t_mesh;

// class t_mesh
// {
// 	public:
// 		std::vector<t_vec3> to_vbo;
// 		std::vector<t_triangle> to_ebo;
// };

typedef struct s_mat4x4
{
	float v[4][4] = { 0 };
}				t_mat4x4;


t_mesh		ft_parsing(std::string file_name);
void		MultiMatrixVector(t_vec3 &i, t_vec3 &o, t_mat4x4 &m);
char* ft_get_file(std::string file_name);
void		DrawTriangle(t_triangle tri);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#endif
