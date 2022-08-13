#include"matrix.h"
#include<iostream>
Matrix LookAt(const vec3& r, const vec3& u, const vec3& d, const vec3& pos)
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
	Matrix m3 = m1 * m2;
	/*for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			std::cout << m3.f[i][j] << " ";
		std::cout << "\n";
	}*/
	return m3;
}