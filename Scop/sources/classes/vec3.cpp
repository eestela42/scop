#include "../../includes/classes/vec3.hpp"

using namespace ee;

vec3::~vec3()
{}

vec3::vec3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

vec3::vec3(const float &src)
{
	this->x = src;
	this->y = src;
	this->z = src;
}

vec3::vec3(const float &x, const float &y, const float &z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

vec3::vec3(const float* src)
{
	if (!src)
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
		return ;
	}
	this->x = src[0];
	this->y = src[1];
	this->z = src[2];
}

float*	vec3::getFloatTab() const
{
	float* tab = new float[3];
	tab[0] = this->x;
	tab[1] = this->y;
	tab[2] = this->z;
	return (tab);
}


float	vec3::getx() const
{
	return (this->x);
}

float	vec3::gety() const
{
	return (this->y);
}

float	vec3::getz() const
{
	return (this->z);
}

vec3&	vec3::operator=(const vec3 &rhs) 
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
	return (*this);
}

vec3&	vec3::operator=(const float &rhs) 
{
	this->x = rhs;
	this->y = rhs;
	this->z = rhs;
	return (*this);
}

vec3&	vec3::operator=(const float* rhs) 
{
	if (!rhs)
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
		return (*this);
	}
	this->x = rhs[0];
	this->y = rhs[1];
	this->z = rhs[2];
	return (*this);
}

vec3	vec3::operator+(const vec3 &rhs) const
{
	return (vec3(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z));
}

vec3	vec3::operator+(const float rhs) const
{
	return (vec3(this->x + rhs, this->y + rhs, this->z + rhs));
}

vec3	vec3::operator-(const vec3 &rhs) const
{
	return (vec3(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z));
}

vec3	vec3::operator-(const float rhs) const
{
	return (vec3(this->x - rhs, this->y - rhs, this->z - rhs));
}

vec3	vec3::operator*(const vec3 &rhs) const
{
	return (vec3(this->x * rhs.x, this->y * rhs.y, this->z * rhs.z));
}

vec3	vec3::operator*(const float rhs) const
{
	return (vec3(this->x * rhs, this->y * rhs, this->z * rhs));
}

vec3	vec3::operator/(const vec3 &rhs) const
{
	return (vec3(this->x / rhs.x, this->y / rhs.y, this->z / rhs.z));
}

vec3	vec3::operator/(const float rhs) const
{
	return (vec3(this->x / rhs, this->y / rhs, this->z / rhs));
}



vec3&	vec3::operator+=(const vec3 &rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
	this->z += rhs.z;
	return (*this);
}

vec3&	vec3::operator+=(const float rhs)
{
	this->x += rhs;
	this->y += rhs;
	this->z += rhs;
	return (*this);
}
		
vec3&	vec3::operator-=(const vec3 &rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	this->z -= rhs.z;
	return (*this);
}

vec3&	vec3::operator-=(const float rhs)
{
	this->x -= rhs;
	this->y -= rhs;
	this->z -= rhs;
	return (*this);
}

vec3&	vec3::operator*=(const vec3 &rhs)
{
	this->x *= rhs.x;
	this->y *= rhs.y;
	this->z *= rhs.z;
	return (*this);
}

vec3&	vec3::operator*=(const float rhs)
{
	this->x *= rhs;
	this->y *= rhs;
	this->z *= rhs;
	return (*this);
}

vec3&	vec3::vec3::operator/=(const vec3 &rhs)
{
	this->x /= rhs.x;
	this->y /= rhs.y;
	this->z /= rhs.z;
	return (*this);
}

vec3&	vec3::operator/=(const float rhs)
{
	this->x /= rhs;
	this->y /= rhs;
	this->z /= rhs;
	return (*this);
}

bool	vec3::operator==(const vec3 &rhs) const
{
	return (this->x == rhs.x && this->y == rhs.y && this->z == rhs.z);
}
bool	vec3::operator!=(const vec3 &rhs) const
{
	return (this->x != rhs.x || this->y != rhs.y || this->z != rhs.z);
}

float&	vec3::operator[](const int index)
{
	if (index == 0)
		return (this->x);
	else if (index == 1)
		return (this->y);
	else if (index == 2)
		return (this->z);
	else
		throw std::out_of_range("vec3 index out of range");
}

namespace ee
{
	std::ostream&	operator<<(std::ostream &out, const vec3 &rhs)
	{
		float* tab = rhs.getFloatTab();
		out << tab[0]<< " " << tab[1] << " " << tab[2];
		delete[] tab;
		return (out);
	}

	vec3			operator*(const float lhs, const vec3 &rhs)
	{
		return (vec3(rhs.getx() * lhs, rhs.gety() * lhs, rhs.getz() * lhs));
	}
	
	vec3			operator/(const float lhs, const vec3 &rhs)
	{
		return (vec3(rhs.getx() / lhs, rhs.gety() / lhs, rhs.getz() / lhs));
	}

	vec3			operator+(const float lhs, const vec3 &rhs)
	{
		return (vec3(rhs.getx() + lhs, rhs.gety() + lhs, rhs.getz() + lhs));
	}

	vec3			operator-(const float lhs, const vec3 &rhs)
	{
		return (vec3(rhs.getx() - lhs, rhs.gety() - lhs, rhs.getz() - lhs));
	}
}