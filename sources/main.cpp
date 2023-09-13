#include "header.hpp"
//g++ openGL.cpp -lglut -lGLU -lGL; ./a.out




void displayMe(void)
{
    
    // glClear(GL_COLOR_BUFFER_BIT);
    // glBegin(GL_POLYGON);
    //     glVertex3f(0.5, 0.0, 0.5);
    //     glVertex3f(0.5, 0.0, 0.0);
    //     glVertex3f(0.0, 0.5, 0.0);
    //     glVertex3f(0.0, 0.0, 0.5);
    // glEnd();
    // glFlush();
}
 
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
            vert.x = std::stof(x);
            vert.y = std::stof(y);
            vert.z = std::stof(z);
			std::cout << "vertex : " << num_line << " " << vert.x << " " << vert.y << " " << vert.z << std::endl;
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
			std::cout << "triangle " << v_pos[0] << " " << v_pos[1] << " " << v_pos[2] << std::endl;
            x = "";
            y = "";
            z = "";
           i++;
		   std::cout << " x values : " << vertexs[v_pos[0] - start].x << " " << vertexs[v_pos[1] - start].x << " " << vertexs[v_pos[2] - start].x << std::endl;
		   std::cout << " y values : " << vertexs[v_pos[0] - start].y << " " << vertexs[v_pos[1] - start].y << " " << vertexs[v_pos[2] - start].y << std::endl;
		   std::cout << " z values : " << vertexs[v_pos[0] - start].z << " " << vertexs[v_pos[1] - start].z << " " << vertexs[v_pos[2] - start].z << std::endl; 
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
    glBegin(GL_LINES);
    glVertex2f(tri.v[0].x, tri.v[0].y);
    glVertex2f(tri.v[1].x, tri.v[1].y);
    glEnd();
    
    glBegin(GL_LINES);
    glVertex2f(tri.v[1].x, tri.v[1].y);
    glVertex2f(tri.v[2].x, tri.v[2].y);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(tri.v[2].x, tri.v[2].y);
    glVertex2f(tri.v[0].x, tri.v[0].y);
    glEnd();
    
}

int main(int argc, char** argv)
{
    


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    float screenWidth = 500;
    float screenHeight = 750;
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(10, 200);
    glutCreateWindow("Hello world!");
   

    t_mesh mesh;
    t_mat4x4 matProj;
    t_mat4x4 matRotZ, matRotX;

    float fTheta = 1.0f;
    // Rotation Z
		
    mesh = ft_parsing(argv[1]);
        // mesh.triangles = {

		// // SOUTH
		// { 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f },
		// { 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f },

		// // EAST                                                      
		// { 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f },
		// { 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f },

		// // NORTH                                                     
		// { 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f },
		// { 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f },

		// // WEST                                                      
		// { 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
		// { 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f },

		// // TOP                                                       
		// { 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f },
		// { 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f },

		// // BOTTOM                                                    
		// { 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f },
		// { 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f },

		// };

    float fNear = 0.1f;
    float fFar = 10000.0f;
    float fFov = 90.0f;
    float fAspectRatio = screenHeight / screenWidth;
    float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);
    matProj.v[0][0] = fAspectRatio * fFovRad;
    matProj.v[1][1] = fFovRad;
    matProj.v[2][2] = fFar / (fFar - fNear);
    matProj.v[3][2] = (-fFar * fNear) / (fFar - fNear);
    matProj.v[2][3] = 1.0f;
    matProj.v[3][3] = 0.0f;
    while (1)
    {
        matRotZ.v[0][0] = cosf(fTheta);
		matRotZ.v[0][1] = sinf(fTheta);
		matRotZ.v[1][0] = -sinf(fTheta);
		matRotZ.v[1][1] = cosf(fTheta);
		matRotZ.v[2][2] = 1;
		matRotZ.v[3][3] = 1;

		// Rotation X
		matRotX.v[0][0] = 1;
		matRotX.v[1][1] = cosf(fTheta * 0.5f);
		matRotX.v[1][2] = sinf(fTheta * 0.5f);
		matRotX.v[2][1] = -sinf(fTheta * 0.5f);
		matRotX.v[2][2] = cosf(fTheta * 0.5f);
		matRotX.v[3][3] = 1;

    glClear(GL_COLOR_BUFFER_BIT);

				// Test line

    // glBegin(GL_LINES);
    // glVertex2f(1.0f, 1.0f);
    // glVertex2f(0.0f, 0.0f);
    // glEnd();

				// ---END Test line

    for (auto triangle : mesh.triangles)
    {
        t_triangle triProjected;
	// std::cout << triangle.v[0].x << " " << triangle.v[0].y << " " << triangle.v[0].z
	// << " " << triangle.v[1].x << " " << triangle.v[1].y << " " << triangle.v[1].z
	// << " " << triangle.v[2].x << " " << triangle.v[2].y << " " << triangle.v[2].z << std::endl;

					// Rotate in Z-Axis

		t_triangle triRotatedZ, triRotatedZX;
        MultiMatrixVector(triangle.v[0], triRotatedZ.v[0], matRotZ);
        MultiMatrixVector(triangle.v[1], triRotatedZ.v[1], matRotZ);
        MultiMatrixVector(triangle.v[2], triRotatedZ.v[2], matRotZ);

        MultiMatrixVector(triRotatedZ.v[0], triRotatedZX.v[0], matRotX);
        MultiMatrixVector(triRotatedZ.v[1], triRotatedZX.v[1], matRotX);
        MultiMatrixVector(triRotatedZ.v[2], triRotatedZX.v[2], matRotX);

        // MultiMatrixVector(triRotatedZX.v[0], triProjected.v[0], matProj);
        // MultiMatrixVector(triRotatedZX.v[1], triProjected.v[1], matProj);
        // MultiMatrixVector(triRotatedZX.v[2], triProjected.v[2], matProj);

		triProjected = triRotatedZX;
		
		// triProjected.v[0].x -=1.0f; triProjected.v[0].y -=1.0f;
        // triProjected.v[1].x -=1.0f; triProjected.v[1].y -=1.0f;
        // triProjected.v[2].x -=1.0f; triProjected.v[2].y -=1.0f;

        DrawTriangle(triProjected);

					// ---END Rotate in Z-Axis


					// Affiche normalelement

        // MultiMatrixVector(triangle.v[0], triProjected.v[0], matProj);
        // MultiMatrixVector(triangle.v[1], triProjected.v[1], matProj);
        // MultiMatrixVector(triangle.v[2], triProjected.v[2], matProj);
		// std::cout << "triangleProjected" << triProjected.v[0].x << " " << triProjected.v[0].y << " " << triProjected.v[0].z << std::endl;
		// DrawTriangle(triProjected);

					// ---END Affiche normalelement


        


        
        fTheta += 0.00004f;
    }
    glFlush();
    

    // glutDisplayFunc(displayMe);
    // glutMainLoop();
    }
    return 0;
}