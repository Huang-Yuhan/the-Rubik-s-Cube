#include"vec.h"

vec3 operator+(const vec3& a, const vec3& b)
{
	return vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

vec3 operator-(const vec3& a, const vec3& b)
{
	return vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

vec3 operator*(const vec3& a, double n)
{
	return vec3(a.x * n, a.y * n, a.z * n);
}

vec3 operator/(const vec3& a, double n)
{
	return vec3(a.x / n, a.y / n, a.z / n);
}

double distance(const vec3& a, const vec3& b)
{
	double dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z;
	return sqrt(dx * dx + dy * dy + dz * dz);
}

double Cos(const vec3& a, const vec3& b)//计算两个向量之间的夹角余弦值
{
	double dotmult = a.x * b.x + a.y * b.y + a.z * b.z;
	double lena = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	double lenb = sqrt(b.x * b.x + b.y * b.y + b.z * b.z);
	double costheta = dotmult / (lena * lenb);
	return costheta;
}

vec3 cross(const vec3& u, const vec3& v)//向量叉乘
{
	return vec3(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);
}

int cross(const POINT& a, const POINT& b)
{
	return a.x * b.y - a.y * b.x;
}


void rotateX(vec3& vertex, double degree)//物体坐标系沿x轴正方向顺时针旋转degree度
{
	//本来图形学中的旋转默认是逆时针旋转，这里为了与我们预设的统一，在公式中将角度换成了相反数，根据三角函数诱导公式进行变形
	degree = degree / 180 * pi;
	double dx, dy, dz;
	dx = vertex.x;
	dy = vertex.y * cos(degree) + vertex.z * sin(degree);
	dz = vertex.z * cos(degree) - vertex.y * sin(degree);
	vertex.x = dx; vertex.y = dy; vertex.z = dz;
}
void rotateY(vec3& vertex, double degree)//物体坐标系沿y轴正方向顺时针旋转degree度
{
	//本来图形学中的旋转默认是逆时针旋转，这里为了与我们预设的统一，在公式中将角度换成了相反数，根据三角函数诱导公式进行变形
	degree = degree / 180 * pi;
	double dx, dy, dz;
	dx = vertex.x * cos(degree) - vertex.z * sin(degree);
	dy = vertex.y;
	dz = vertex.x * sin(degree) + vertex.z * cos(degree);
	vertex.x = dx; vertex.y = dy; vertex.z = dz;
}
void rotateZ(vec3& vertex, double degree)//物体坐标系沿y轴正方向顺时针旋转degree度
{
	//本来图形学中的旋转默认是逆时针旋转，这里为了与我们预设的统一，在公式中将角度换成了相反数，根据三角函数诱导公式进行变形
	degree = degree / 180 * pi;
	double dx, dy, dz;

	dx = vertex.x * cos(degree) + vertex.y * sin(degree);
	dy = vertex.y * cos(degree) - vertex.x * sin(degree);
	dz = vertex.z;
	vertex.x = dx; vertex.y = dy; vertex.z = dz;
}

double length(const vec3& a)
{
	return distance(a, vec3(0, 0, 0));
}


vec4 operator+(const vec4& a, const vec4& b)
{
	return vec4(a.x + b.x, a.y + b.y, a.z + b.z,a.w+b.w);
}

vec4 operator-(const vec4& a, const vec4& b)
{
	return vec4(a.x - b.x, a.y - b.y, a.z - b.z,a.w-b.w);
}

vec4 operator*(const vec4& a, double n)
{
	return vec4(a.x * n, a.y * n, a.z * n,a.w*n);
}

vec4 operator/(const vec4& a, double n)
{
	return vec4(a.x / n, a.y / n, a.z / n,a.w/n);
}