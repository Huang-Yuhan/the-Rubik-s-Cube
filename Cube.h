#pragma once
#include"Plane.h"
//立方体

const double e = 50;//立方体边长一半


class Cube
{
public:
	Plane plane[6];
	vec3 vertex[8] = { vec3(e,e,e),vec3(e,e,-e) ,vec3(e,-e,e),vec3(e,-e,-e),vec3(-e,e,e),vec3(-e,e,-e),vec3(-e,-e,e),vec3(-e,-e,-e) };
	vec3 offset;//该立方体相对于世界坐标系原点的位移
	Cube():offset(0,0,0)
	{
		//按照FRBLUD的顺序
		/*
		规定世界坐标系采用与OpenGL相同的右手系，
		每个立方体的坐标系（物体坐标系）都是由世界坐标系平移原点而来。
		*/
		plane[0].bindpoint(&vertex[0], &vertex[4], &vertex[6], &vertex[2]);
		plane[1].bindpoint(&vertex[0], &vertex[2], &vertex[3], &vertex[1]);
		plane[2].bindpoint(&vertex[3], &vertex[1], &vertex[5], &vertex[7]);
		plane[3].bindpoint(&vertex[4], &vertex[6], &vertex[7], &vertex[5]);
		plane[4].bindpoint(&vertex[5], &vertex[4], &vertex[0], &vertex[1]);
		plane[5].bindpoint(&vertex[6], &vertex[7], &vertex[3], &vertex[2]);
	}
	void bindoffset(const vec3& a)
	{
		offset = a;
		for (int i = 0; i < 6; i++)plane[i].bindoffset(offset);
	}
	void local_rotate_x(double degree)
	{
		for (int i = 0; i < 8; i++)rotateX(vertex[i], degree);
	}
	void local_rotate_y(double degree)
	{
		for (int i = 0; i < 8; i++)rotateY(vertex[i], degree);
	}
	void local_rotate_z(double degree)
	{
		for (int i = 0; i < 8; i++)rotateZ(vertex[i], degree);
	}
};