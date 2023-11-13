#include "../includes/header.hpp"
//g++ openGL.cpp -lglut -lGLU -lGL; ./a.out
#include "../includes/stb_image.h"

bool rotate = true;
bool color = true;

int zoom = 0;
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		rotate = !rotate;

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		zoom = -1;
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		zoom = 1;
	else
		zoom = 0;
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		color = !color;
}




int main(int ac, char** av)
{
    

	if (ac != 2)
	{
		std::cout << "Usage : ./scop file.obj" << std::endl;
		return 1;
	}

	game game(1200, 800);
	game.init(ac, av);

	game.initShadder();
	
	game.initBuffers();

	game.initTexture();

	// only lines
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// rotation

	float fTheta = 1.0f;
	t_mat4x4 matRotZ, matRotX;


	// std::cout << "size : " << game.getMesh().to_ebo.size() * 3 << std::endl; 
	glBindVertexArray(game.getVAO()); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glUseProgram(game.getShaderProgram());




	//textures

	glUniform1i(glGetUniformLocation(game.getShaderProgram(), "ourTexture"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, game.getTexture());

	glEnable(GL_DEPTH_TEST);

	game.setBool("isColor", true);
	


	int i = 1;
	// std::vector<t_vec3> new_vbo = game.getMesh().to_vbo;
	// new_vbo[ 2 + i * 3] = 1.0f;
	game.upDateVBO(game.getMesh().vertexes);

	// game.displayEBO();
	// game.displayVBO();


	mat4 model(1.0f);

	float time = 0.0f;
	float zoom_value = 1.0f;
	

	unsigned int modelLoc = glGetUniformLocation(game.getShaderProgram(), "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model.getValue());


	mat4 view(1.0f);

	view.translate(0.0f, 0.0f, -3.0f);
	
	
	unsigned int viewLoc = glGetUniformLocation(game.getShaderProgram(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view.getValue());


	mat4 projection;

	projection.perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
	
	
	unsigned int projectionLoc = glGetUniformLocation(game.getShaderProgram(), "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection.getValue());


 	while(!glfwWindowShouldClose(game.getWindow()))
	{
			glfwPollEvents();
		game.setFloat("zoom", zoom_value);
		/****matrixes****/
			
			if (rotate)
			{
				model = mat4(1.0f) ;
				model.rotate( time * 50.0f, 0.5f, 1.0f, 0.0f);
				time += 0.01f;
				unsigned int modelLoc = glGetUniformLocation(game.getShaderProgram(), "model");
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model.getValue());
			}

			if (zoom)
			{
				zoom_value += zoom * 0.1f;
			}
			if (color)
				game.setBool("isColor", true);
			else
				game.setBool("isColor", false);


		/****matrixes END****/

		processInput(game.getWindow());

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw our first triangle
		
		
		glDrawElements(GL_TRIANGLES, game.getMesh().triangles.size() * 3, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(game.getWindow());
		
    } 

  
    glfwTerminate();
	return 0;
}