#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in float isColorIn;

out vec3 ourColor;
out vec2 TexCoord;
out float isColorOut;



uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform bool isColor;
uniform float zoom;

void main()
{

	if (isColor)
	{
		isColorOut = 1.0;
	}
	else
	{
		isColorOut = 0.0;
	}
    gl_Position = projection * view * model * vec4(aPos / zoom, 1.0);
	ourColor = aColor;
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	//calculate normal
	

	// vec3 normal;
	// vec3 vector1 = aPos[1] - aPos[0];
	// vec3 vector2 = aPos[2] - aPos[0];
	// normal.x = vector1.y * vector2.z - vector1.z * vector2.y;
	// normal.y = vector1.z * vector2.x - vector1.x * vector2.z;
	// normal.z = vector1.x * vector2.y - vector1.y * vector2.x;
	// normal = normalize(normal);
	// isColorOut = 1.0;
	// ourColor = aColor * normal;
}





