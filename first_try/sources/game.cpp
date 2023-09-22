#include "../includes/game.hpp"

game::~game()
{
}

game::game()
{
	this->width = 600;
	this->height = 450;
	this->isRunning = false;
}

game::game(int width, int height): game()
{
	this->width = width;
	this->height = height;
}

int game::init(int ac, char **av)
{
	glutInit(&ac, av);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(this->width, this->height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OpenGL - First window demo");
	//glutDisplayFunc(displayMe);
	

	
    

    this->fTheta = 1.0f;
    this->fNear = 0.1f;
    this->fFar = 10000.0f;
    this->fFov = 90.0f;
    this->fAspectRatio = this->height / this->width;
    this->fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);
    this->matProj.v[0][0] = fAspectRatio * fFovRad;
    this->matProj.v[1][1] = fFovRad;
    this->matProj.v[2][2] = fFar / (fFar - fNear);
    this->matProj.v[3][2] = (-fFar * fNear) / (fFar - fNear);
    this->matProj.v[2][3] = 1.0f;
    this->matProj.v[3][3] = 0.0f;

	this->upDateMesh(ft_parsing(av[1]));
	this->updateIsRunning(true);
	this->gameLoop();
	return (0);
}

void game::gameLoop()
{	
    while (this->isRunning)
    {
	
	}	
}

void game::updateIsRunning(bool tmp)
{
	this->isRunning = tmp;
}

void game::upDateMesh(t_mesh tmp)
{
	this->mesh = tmp;
}
