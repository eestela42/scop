#ifndef GAME_HPP
# define GAME_HPP

# include "header.hpp"


class game
{
private:
	int width;
	int height;
	bool isRunning;
	t_mesh mesh;

	t_mat4x4 matProj;
	float fTheta;
	float fNear;
	float fFar;
	float fFov;
	float fAspectRatio;
	float fFovRad;
public:
	~game();
	game(/* args */);
	game(int width, int height);

	int init(int ac, char **av);
	void gameLoop();

	void upDateMesh(t_mesh tmp);
	void updateIsRunning(bool tmp);
};




#endif