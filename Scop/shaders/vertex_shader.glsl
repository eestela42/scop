#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in float isColorIn;


out vec3 ourColor;
out vec2 TexCoord;
out float isColorOut;



uniform mat4 modelView;
uniform bool isColor;
uniform float zoom;



void main()
{
	
	if (isColor)
		isColorOut = 1.0;
	else
		isColorOut = 0.0;
    gl_Position = modelView * vec4(aPos / zoom, 1.0);
	
	ourColor = aColor;
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}





