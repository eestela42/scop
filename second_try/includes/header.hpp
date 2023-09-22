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


typedef struct s_vec3
{
	float x, y, z;
}				t_vec3;

typedef struct s_triangle
{
	t_vec3 v[3];
}				t_triangle;

typedef struct s_mesh
{
	std::vector<t_triangle> triangles;
}				t_mesh;

typedef struct s_mat4x4
{
	float v[4][4] = { 0 };
}				t_mat4x4;


t_mesh		ft_parsing(std::string file_name);
void		MultiMatrixVector(t_vec3 &i, t_vec3 &o, t_mat4x4 &m);
char* ft_get_file(std::string file_name);
void		DrawTriangle(t_triangle tri);

#endif
