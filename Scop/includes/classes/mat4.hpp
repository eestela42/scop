#ifndef MAT4_HPP
# define MAT4_HPP

# include "../base_header.hpp"


// # include "vec3.hpp"


namespace ee
{
class mat4
{
	public:
		mat4();
		~mat4();
		mat4(const mat4 &src);
		mat4(float diag);

		mat4&	operator=(const mat4 &rhs);
		float*	operator[](int index);
		mat4	operator*(const mat4 &rhs);
		
		mat4&	translate(float x, float y, float z);
		mat4&	rotate(float angle, float x, float y, float z);
		mat4&	perspective(float fov, float aspect, float near, float far);

		void	print_mat();
		float&	getValue();
	private:
		float	value[4][4];

};
}


#endif
