#ifndef MESH_HPP
# define MESH_HPP

# include <iostream>
# include <string.h>
# include <sstream>
# include <fstream>
# include <math.h>
# include "../glad/glad.h" 
# include <GL/glut.h>
// # include <glew.h> 
# include <GLFW/glfw3.h>
# include <vector>
# include "../types.hpp"

class my_mesh
{
public:

	std::vector<t_vec3> base_vertexes;
	std::vector<std::vector<unsigned int>> base_faces;

	std::vector<t_vec3> vertexes;
	std::vector<t_triangle> triangles;

	~my_mesh();
	my_mesh();
	my_mesh(const my_mesh &copy);
	my_mesh(std::string file_name);

	void	parseFromFile(std::string file_name);


	std::vector<t_triangle> facesToTriangles();
	void	facesToTrianglesDupVertexes();
	void	addInfoToVertexes();

	my_mesh&	operator=(const my_mesh &copy);
};


#endif