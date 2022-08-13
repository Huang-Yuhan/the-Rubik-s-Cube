#pragma once
#include"vec3.h"
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
		f[0][1] = a.y;
		f[0][2] = a.z;
		f[1][0] = b.x;
		f[1][1] = b.y;
		f[1][2] = b.z;
		f[2][0] = c.x;
		f[2][1] = c.y;
		f[2][2] = c.z;
		f[3][0] = d.x;
		f[3][1] = d.y;
		f[3][2] = d.z;
	}
	Matrix operator*(const Matrix& a)
	{
		Matrix tmp;
		for (int k = 0; k <= 3; k++)
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					tmp.f[i][j] = f[i][k] * a.f[k][j];
		return tmp;
	}
	vec3 operator*(const vec3& a)
	{
		vec3 tmp;
		tmp.x = a.x * f[0][0] + a.y * f[1][0] + a.z * f[2][0] + f[3][0];
		tmp.y = a.x * f[0][1] + a.y * f[1][1] + a.z * f[2][1] + f[3][1];
		tmp.z = a.x * f[0][2] + a.y * f[1][2] + a.z * f[2][2] + f[3][2];
		return tmp;
	}
};

Matrix LookAt(const vec3& u, const vec3& r, const vec3& d,const vec3&pos)
{
	Matrix m1, m2(vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1), -pos);
	m1.f[0][0] = r.x;
	m1.f[0][1] = r.y;
	m1.f[0][2] = r.z;
	m1.f[1][0] = u.x;
	m1.f[1][1] = u.y;
	m1.f[1][1] = u.z;
	m1.f[2][0] = d.x;
	m1.f[2][1] = d.y;
	m1.f[2][2] = d.z;
	m1.f[3][3] = 1;
	m2.f[3][3] = 1;
	return m1 * m2;
}