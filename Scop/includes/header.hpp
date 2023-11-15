#ifndef HEADER_HPP
# define HEADER_HPP


# include "base_header.hpp"

# include "classes/vec3.hpp"
# include "classes/mat4.hpp"
# include "classes/mesh.hpp"
# include "classes/game.hpp"



#include "stb_image.h"

# define STB_IMAGE_IMPLEMENTATION



typedef struct s_mat4x4
{
	float v[4][4] = { 0 };
}				t_mat4x4;


ee::mesh		ft_parsing(std::string file_name);
void		MultiMatrixVector(t_vec3 &i, t_vec3 &o, t_mat4x4 &m);
char* ft_get_file(std::string file_name);
void		DrawTriangle(t_triangle tri);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
t_vec3 sub_vec(t_vec3& a, t_vec3& b);

#endif
