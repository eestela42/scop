#include "../../includes/classes/mat4.hpp"

mat4::mat4()
{
	for (int i = 0; i < 4; i++)
		for (int y = 0; y < 4; y++)
			this->value[i][y] = 0;
}

mat4::~mat4()
{
}

mat4::mat4(const mat4 &src)
{
	*this = src;
}

mat4::mat4(float diag) : mat4()
{
	for (int i = 0; i < 4; i++)
		this->value[i][i] = diag;
}


mat4& mat4::operator=(const mat4 &rhs)
{
	for (int i = 0; i < 4; i++)
		for (int y = 0; y < 4; y++)
			this->value[i][y] = rhs.value[i][y];
	return (*this);
}

mat4&	mat4::translate(float x, float y, float z)
{
	this->value[3][0] = x;
	this->value[3][1] = y;
	this->value[3][2] = z;
	return (*this);
}

mat4&	mat4::rotate(float angle, float x, float y, float z)
{
	float rad = angle * M_PI / 180;
	float c = std::cos(rad);
	float s = std::sin(rad);
	float omc = 1.0f - c;

	this->value[0][0] = x * x * omc + c;
	this->value[0][1] = x * y * omc - z * s;
	this->value[0][2] = x * z * omc + y * s;

	this->value[1][0] = y * x * omc + z * s;
	this->value[1][1] = y * y * omc + c;
	this->value[1][2] = y * z * omc - x * s;

	this->value[2][0] = x * z * omc - y * s;
	this->value[2][1] = y * z * omc + x * s;
	this->value[2][2] = z * z * omc + c;
	return (*this);
}

mat4&	mat4::perspective(float fov, float aspect, float near, float far)
{
	float rad = fov * M_PI / 180;
	float tanHalfFovy = std::tan(rad / 2.0f);
	
	this->value[0][0] = 1.0f / (aspect * tanHalfFovy);
	this->value[1][1] = 1.0f / (tanHalfFovy);
	this->value[2][2] = -(far + near) / (far - near);
	this->value[2][3] = -1.0f;
	this->value[3][2] = -(2.0f * far * near) / (far - near);
	return (*this);
}

void	mat4::print_mat()
{
	for (int i = 0; i < 4; i++)
	{
		std::cout << "| ";
		for (int y = 0; y < 4; y++)
		{
			std::cout << this->value[y][i] << " ";
		}
		std::cout << "|" << std::endl;
	}
	std::cout << std::endl;
}

float&	mat4::getValue()
{
	return (this->value[0][0]);
}