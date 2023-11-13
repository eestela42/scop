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

	std::vector<std::vector<t_triangle>> base_triangles;

	std::vector<std::vector<unsigned int>> vertByFace;

	~my_mesh();
	my_mesh();
	my_mesh(const my_mesh &copy);
	my_mesh(std::string file_name);

	void	parseFromFile(std::string file_name);


	std::vector<t_triangle> facesToTriangles();
	void	facesToTrianglesDupVertexes();
	void	addInfoToVertexesDup();




	void 					EcoDupVertex();
	t_triangle 				getSemioptiVerticesTriangle(t_triangle &triangle, int pos,  std::vector<t_vec3> *new_vertexes,
												std::vector<t_triangle> *base_face_triangles, std::vector<t_triangle> *new_face_triangles);
	std::vector<t_triangle> createTriangleFromFace(std::vector<unsigned int> face);
	void 					addInfoToVertexesEco();


	void 	center_around_orgin();
	void	min_max_bounds(t_vec3& min_bound, t_vec3& max_bound);

	my_mesh&	operator=(const my_mesh &copy);
};


#endif