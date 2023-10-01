#include "../../includes/classes/mesh.hpp"



my_mesh::~my_mesh()
{}

my_mesh::my_mesh()
{}

my_mesh::my_mesh(const my_mesh &copy)
{
	*this = copy;
}

my_mesh::my_mesh(std::string file_name)
{
	parseFromFile(file_name);
	
	// this->vertexes = this->base_vertexes;
	// this->triangles = facesToTriangles();

	facesToTrianglesDupVertexes();
	addInfoToVertexes();
}

void	my_mesh::parseFromFile(std::string file_name)
{
	std::ifstream file(file_name);
    if (!file.is_open())
    {
        std::cout << "Error opening file : " << file_name << std::endl;
        exit(1);
    }

    std::string line;
    while (std::getline(file, line))
	{
		if (line.size() > 2)
		{
        if (line[0] == 'v' && line[1] == ' ')
        {
			//std::cout << "line : " << line << std::endl;
            t_vec3 vert;
            std::string x, y, z;
            int i = 2;
            while (line[i] != ' ')
            {
                x += line[i];
                i++;
            }
            while (line[i] == ' ')
				{i++;}
            while (line[i] != ' ')
            {
                y += line[i];
                i++;
            }
            while (line[i] == ' ')
				{i++;}
            while (line[i] && line[i] != ' ')
            {
                z += line[i];
                i++;
            }
            vert.v[0] = std::stof(x);
            vert.v[1] = std::stof(y);
            vert.v[2] = std::stof(z);
            this->base_vertexes.push_back(vert);
        }
        else if (line[0] == 'f' && line[1] == ' ')
        {
			std::vector<unsigned int>value;
			int i = 2;
			while(line[i] == ' '){i++;}
			while(line[i])
			{
				std::string tmp;
				while(line[i] && line[i] != ' ')
				{
					tmp += line[i];
					i++;
				}
				value.push_back(std::stoi(tmp));

				while(line[i] == ' '){i++;}
			}
			this->base_faces.push_back(value);
		}
		}
    }
    file.close();
}


std::vector<t_triangle> my_mesh::facesToTriangles()
{
	std::vector<t_triangle> new_triangles;
	for (std::vector<std::vector<unsigned int>>::iterator it = this->base_faces.begin(); it != this->base_faces.end(); ++it)
	{
		if (it->size() < 3)
		{
			std::cout << "Error : face with less than 3 vertexes" << std::endl;
			exit(1);
		}

		int i = 2;
		while (i < it->size())
		{
			t_triangle triangle;
			triangle.v[0] = it->at(0) - 1;
			triangle.v[1] = it->at(i - 1) - 1;
			triangle.v[2] = it->at(i) - 1;
			new_triangles.push_back(triangle);
			i++;
		}
	}
	return (new_triangles);
}

void my_mesh::facesToTrianglesDupVertexes()
{
	std::vector<t_vec3> new_vertexes;
	std::vector<t_triangle> new_triangles;
	for (std::vector<std::vector<unsigned int>>::iterator it = this->base_faces.begin(); it != this->base_faces.end(); ++it)
	{
		if (it->size() < 3)
		{
			std::cout << "Error : face with less than 3 vertexes" << std::endl;
			exit(1);
		}

		int i = 2;
		while (i < it->size())
		{
			t_vec3 vert[3];
			vert[0] = base_vertexes[it->at(0) - 1];
			vert[1] = base_vertexes[it->at(i - 1) - 1];
			vert[2] = base_vertexes[it->at(i) - 1];
			new_vertexes.push_back(vert[0]);
			new_vertexes.push_back(vert[1]);
			new_vertexes.push_back(vert[2]);
			i++;
		}
	}
	this->vertexes = new_vertexes;
	
	int i = 0;
	int max = this->vertexes.size();
	while (i < max)
	{
		t_triangle triangle;
		triangle.v[0] = i;
		triangle.v[1] = i + 1;
		triangle.v[2] = i + 2;
		new_triangles.push_back(triangle);
		i += 3;
	}
	
	this->triangles = new_triangles;
}

void my_mesh::addInfoToVertexes()
{
	std::vector<t_vec3> new_vbo;
	t_vec3 colors[] = {
		{1.0f, 0.0f, 0.0f}, // red
		{0.0f, 1.0f, 0.0f}, // green
		{0.0f, 0.0f, 1.0f}  // blue
	};
	t_vec3 textureCoo[] = {
		{1.0f, 1.0f, 1.0f},
		{1.0f, 0.0f, 1.0f},
		{0.0f, 0.0f},
		{0.0f, 1.0f}
	};
	int colorIndex = 0;
	int face = 0;
	int last_face = -1;
	for (int i = 0; i < this->vertexes.size(); i++)
	{
		
		new_vbo.push_back(this->vertexes[i]);
		new_vbo.push_back(colors[colorIndex]);
		new_vbo.push_back(textureCoo[i % 2]);
		if (face < base_faces.size() && (i - last_face) == (base_faces[face].size() - 2) * 3)
		{
			std::cout << "face : " << face << std::endl;
			std::cout << "size face : " << base_faces[face].size() << std::endl;
			std::cout << "i : " << i << std::endl;
			std::cout << "last_face : " << last_face << std::endl << std::endl;
			face++;
			last_face = i;
			colorIndex = (colorIndex + 1) % 3;
		}
	}
	this->vertexes = new_vbo;
}


my_mesh &my_mesh::operator=(const my_mesh &copy)
{
	this->base_vertexes = copy.base_vertexes;
	this->base_faces = copy.base_faces;
	this->vertexes = copy.vertexes;
	this->triangles = copy.triangles;
	return (*this);
}

