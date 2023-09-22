#include "../includes/header.hpp"

t_mesh ft_parsing(std::string file_name)
{
    
    std::ifstream file(file_name);
    if (!file.is_open())
    {
        std::cout << "Error opening file : " << file_name << std::endl;
        exit(1);
    }

    t_mesh mesh;
    std::vector<t_vec3> vertexs;
    std::string line;
    int num_line = -1;
    int start = num_line;
    while (std::getline(file, line))
    {
        num_line++;
        if (line[0] == 'v' && line[1] == ' ')
        {
            if (start == -1)
                start = num_line + 1;
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
            vert.x = std::stof(x);
            vert.y = std::stof(y);
            vert.z = std::stof(z);
			// std::cout << "vertex : " << num_line << " " << vert.x << " " << vert.y << " " << vert.z << std::endl;
            vertexs.push_back(vert);
        }
        else if (line[0] == 'f' && line[1] == ' ')
        {
			int v_pos[3];
            std::string x, y, z;
            int i = 2;
            while (line[i] != ' ')
            {
                x += line[i];
                i++;
            }
            while (line[i] == ' '){i++;}
            while (line[i] != ' ')
            {
                y += line[i];
                i++;
            }
            while (line[i] == ' '){i++;}
            while (line[i] != ' ')
            {
                z += line[i];
                i++;
            }
            v_pos[0] = std::stoi(x);
            v_pos[1] = std::stoi(y);
            v_pos[2] = std::stoi(z);
			// std::cout << "triangle " << v_pos[0] << " " << v_pos[1] << " " << v_pos[2] << std::endl;
            x = "";
            y = "";
            z = "";
           i++;
		//    std::cout << " x values : " << vertexs[v_pos[0] - start].x << " " << vertexs[v_pos[1] - start].x << " " << vertexs[v_pos[2] - start].x << std::endl;
		//    std::cout << " y values : " << vertexs[v_pos[0] - start].y << " " << vertexs[v_pos[1] - start].y << " " << vertexs[v_pos[2] - start].y << std::endl;
		//    std::cout << " z values : " << vertexs[v_pos[0] - start].z << " " << vertexs[v_pos[1] - start].z << " " << vertexs[v_pos[2] - start].z << std::endl; 
            mesh.triangles.push_back({vertexs[v_pos[0] - start], vertexs[v_pos[1] - start], vertexs[v_pos[2] - start]});
		}
    }
    file.close();
    return mesh;
}

void MultiMatrixVector(t_vec3 &i, t_vec3 &o, t_mat4x4 &m)
{
    o.x = i.x * m.v[0][0] + i.y * m.v[1][0] + i.z * m.v[2][0] + m.v[3][0];
    o.y = i.x * m.v[0][1] + i.y * m.v[1][1] + i.z * m.v[2][1] + m.v[3][1];
    o.z = i.x * m.v[0][2] + i.y * m.v[1][2] + i.z * m.v[2][2] + m.v[3][2];
    float w = i.x * m.v[0][3] + i.y * m.v[1][3] + i.z * m.v[2][3] + m.v[3][3];
    if (w != 0.0f)
    {
        o.x /= w; o.y /= w; o.z /= w;
    }
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