#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
  
out vec4 vertexColor; // specify a color output to the fragment shader

// uniform mat4 matRotZ;
// uniform mat4 matRotX;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


// typedef struct s_triangle
// {
// 	int v[3];
// }				t_triangle;

// void MultiMatrixVector(vec3 &i, vec3 &o, mat4 &m)
// {
//     o.x = i.x * m[0][0] + i.y * m[1][0] + i.z * m[2][0] + m[3][0];
//     o.y = i.x * m[0][1] + i.y * m[1][1] + i.z * m[2][1] + m[3][1];
//     o.z = i.x * m[0][2] + i.y * m[1][2] + i.z * m[2][2] + m[3][2];
//     float w = i.x * m[0][3] + i.y * m[1][3] + i.z * m[2][3] + m[3][3];
//     if (w != 0.0f)
//     {
//         o.x /= w; o.y /= w; o.z /= w;
//     }
// }

void main()
{
	// vec3 triRotatedZ[3], triRotatedZX[3];

	// MultiMatrixVector(aPos[0], triRotatedZ[0], matRotZ);
	// MultiMatrixVector(aPos[1], triRotatedZ[1], matRotZ);
	// MultiMatrixVector(aPos[2], triRotatedZ[2], matRotZ);

	// MultiMatrixVector(triRotatedZ[0], triRotatedZX[0], matRotX);
	// MultiMatrixVector(triRotatedZ[1], triRotatedZX[1], matRotX);
	// MultiMatrixVector(triRotatedZ[2], triRotatedZX[2], matRotX);



	// gl_Position = vec4(triRotatedZX, 1.0); // see how we directly give a vec3 to vec4's constructor

	gl_Position = /* projection * view * */ model * vec4(aPos, 1.0f);
    vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // set the output variable to a dark-red color
}
