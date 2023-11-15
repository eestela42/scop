#include "../includes/header.hpp"


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	(void)window;
    glViewport(0, 0, width, height);
} 



// void MultiMatrixVector(t_vec3 &i, t_vec3 &o, t_mat4x4 &m)
// {
//     o.x = i.x * m.v[0][0] + i.y * m.v[1][0] + i.z * m.v[2][0] + m.v[3][0];
//     o.y = i.x * m.v[0][1] + i.y * m.v[1][1] + i.z * m.v[2][1] + m.v[3][1];
//     o.z = i.x * m.v[0][2] + i.y * m.v[1][2] + i.z * m.v[2][2] + m.v[3][2];
//     float w = i.x * m.v[0][3] + i.y * m.v[1][3] + i.z * m.v[2][3] + m.v[3][3];
//     if (w != 0.0f)
//     {
//         o.x /= w; o.y /= w; o.z /= w;
//     }
// }

 char* ft_get_file(std::string file_name)
{
	std::ifstream file;
	file.open(file_name);
	if (!file.is_open())
	{
		std::cout << "Error opening file : " << file_name << std::endl;
		exit(1);
	}

	std::string line;
	std::stringstream s1;


	s1  << file.rdbuf();
	file.close();
	line = s1.str();

	// std::cout << line.c_str() << std::endl;
	// std::cout << "YES\n";

	char *ret = new char[line.length() + 1];
	strcpy(ret, line.c_str());
	return ret;
}


void DrawTriangle(t_triangle tri)
{
	(void) tri;
	// std::cout << "DrawTriangle" << std::endl;
    // glBegin(GL_LINES);
    // glVertex2f(tri.v[0].x, tri.v[0].y);
    // glVertex2f(tri.v[1].x, tri.v[1].y);
    // glEnd();
    
    // glBegin(GL_LINES);
    // glVertex2f(tri.v[1].x, tri.v[1].y);
    // glVertex2f(tri.v[2].x, tri.v[2].y);
    // glEnd();

    // glBegin(GL_LINES);
    // glVertex2f(tri.v[2].x, tri.v[2].y);
    // glVertex2f(tri.v[0].x, tri.v[0].y);
    // glEnd();
    
}

t_vec3 sub_vec(t_vec3& a, t_vec3& b)
{
	t_vec3 ret;
	ret.v[0] = a.v[0] - b.v[0];
	ret.v[1] = a.v[1] - b.v[1];
	ret.v[2] = a.v[2] - b.v[2];
	return ret;
}