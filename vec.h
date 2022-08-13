#pragma once

#include<cmath>
#include<graphics.h>
const double pi = atan(1) * 4;

class vec3
{
public:
	double x, y, z;
	vec3() = default;
	vec3(double xx, double yy, double zz) :x(xx), y(yy), z(zz)
	{

	}
	vec3 operator *=(double n)
	{
		this->x *= n;
		this->y *= n;
		this->z *= n;
		return *this;
	}
	vec3 operator-()const
	{
		return vec3(-x, -y, -z);
	}
};

vec3 operator+(const vec3& a, const vec3& b);
vec3 operator-(const vec3& a, const vec3& b);
vec3 operator*(const vec3& a, double n);
vec3 operator/(const vec3& a, double n);
double distance(const vec3& a, const vec3& b);
double Cos(const vec3& a, const vec3& b);//计算两个向量之间的夹角余弦值
vec3 cross(const vec3& u, const vec3& v);//向量叉乘
int cross(const POINT& a, const POINT& b);
void rotateX(vec3& vertex, double degree);//物体坐标系沿x轴正方向顺时针旋转degree度
void rotateY(vec3& vertex, double degree);//物体坐标系沿y轴正方向顺时针旋转degree度
void rotateZ(vec3& vertex, double degree);//物体坐标系沿y轴正方向顺时针旋转degree度
double length(const vec3& a);

class vec4
{
public:
	double x, y, z, w;
	vec4() = default;
	vec4(double xx, double yy, double zz,double ww) :x(xx), y(yy), z(zz),w(ww)
	{

	}
	vec4 operator *=(double n)
	{
		this->x *= n;
		this->y *= n;
		this->z *= n;
		this->w *= n;
		return *this;
	}
	vec4 operator-()const
	{
		return vec4(-x, -y, -z,-w);
	}
};


vec4 operator+(const vec4& a, const vec4& b);
vec4 operator-(const vec4& a, const vec4& b);
vec4 operator*(const vec4& a, double n);
vec4 operator/(const vec4& a, double n);
double distance(const vec4& a, const vec4& b);
double Cos(const vec4& a, const vec4& b);//计算两个向量之间的夹角余弦值
vec4 cross(const vec4& u, const vec4& v);//向量叉乘
void rotateX(vec4& vertex, double degree);//物体坐标系沿x轴正方向顺时针旋转degree度
void rotateY(vec4& vertex, double degree);//物体坐标系沿y轴正方向顺时针旋转degree度
void rotateZ(vec4& vertex, double degree);//物体坐标系沿y轴正方向顺时针旋转degree度
double length(const vec3& a);