#pragma once
#include"vec.h"
class Matrix
{
public:
	double f[4][4];
	Matrix()
	{
		memset(f, 0, sizeof(f));
	}
	Matrix(const vec3& a, const vec3& b, const vec3& c, const vec3& d)
	{
		memset(f, 0, sizeof(f));
		f[0][0] = a.x;
		f[1][0] = a.y;
		f[2][0] = a.z;
		f[0][1] = b.x;
		f[1][1] = b.y;
		f[2][1] = b.z;
		f[0][2] = c.x;
		f[1][2] = c.y;
		f[2][2] = c.z;
		f[0][3] = d.x;
		f[1][3] = d.y;
		f[2][3] = d.z;
	}
	Matrix(const vec4& a, const vec4& b, const vec4& c, const vec4& d)
	{
		memset(f, 0, sizeof(f));
		f[0][0] = a.x;
		f[1][0] = a.y;
		f[2][0] = a.z;
		f[3][0] = a.w;
		f[0][1] = b.x;
		f[1][1] = b.y;
		f[2][1] = b.z;
		f[3][1] = b.w;
		f[0][2] = c.x;
		f[1][2] = c.y;
		f[2][2] = c.z;
		f[3][2] = c.w;
		f[0][3] = d.x;
		f[1][3] = d.y;
		f[2][3] = d.z;
		f[3][3] = d.w;
	}
	Matrix operator*(const Matrix& a)
	{
		Matrix tmp;
		for (int k = 0; k < 4; k++)
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					tmp.f[i][j] += f[i][k] * a.f[k][j];
		return tmp;
	}
	vec3 operator*(const vec3& a)
	{
		vec3 tmp;
		tmp.x = a.x * f[0][0] + a.y * f[0][1] + a.z * f[0][2] + f[0][3];
		tmp.y = a.x * f[1][0] + a.y * f[1][1] + a.z * f[1][2] + f[1][3];
		tmp.z = a.x * f[2][0] + a.y * f[2][1] + a.z * f[2][2] + f[2][3];
		return tmp;
	}
	vec4 operator*(const vec4& a)
	{
		vec4 tmp;
		tmp.x = a.x * f[0][0] + a.y * f[0][1] + a.z * f[0][2] + a.w * f[0][3];
		tmp.y = a.x * f[1][0] + a.y * f[1][1] + a.z * f[1][2] + a.w * f[1][3];
		tmp.z = a.x * f[2][0] + a.y * f[2][1] + a.z * f[2][2] + a.w * f[2][3];
		tmp.w = a.x * f[3][0] + a.y * f[3][1] + a.z * f[3][2] + a.w * f[3][3];
		return tmp;
	}
};

Matrix LookAt(const vec3& u, const vec3& r, const vec3& d, const vec3& pos);