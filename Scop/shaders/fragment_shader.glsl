#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;
in float isColorOut;


uniform sampler2D ourTexture;

void main()
{
	//only one Color
	// FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);

	if (isColorOut == 1.0f)
		FragColor = vec4(ourColor, 1.0);
    else
		FragColor = texture(ourTexture, TexCoord);
}
