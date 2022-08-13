#pragma once

#include"vec.h"
#include<cmath>
#include<iostream>
inline vec3 tran(double rho, double phi, double theta)
{
	return vec3(rho * sin(theta) * sin(phi), rho * cos(theta), rho * sin(theta) * cos(phi));
}

class Watcher
{
public:
	double rho, phi, theta;
	vec3 w, u, v;//uvw坐标——摄像机坐标系
	/*
	* z=rho*sin(theta)*cos(phi)
	* x=rho*sin(theta)*sin(phi)
	* y=rho*cos(theta)
	*/
	vec3 pos, updir, frontdir, rightdir;

	Watcher()
	{
		rho =800; phi = 0; theta = pi / 2;
		update();
	}
	void update()
	{
		pos = tran(rho, phi, theta);
		frontdir = -pos / length(pos);
		updir = vec3(0, 1, 0);
		rightdir = cross(frontdir, updir);
		w = -frontdir;
		u = cross(updir, w);
		u = u / length(u);
		v = cross(w, u);
		std::cout << "(" << pos.x << "," << pos.y << "," << pos.z << ")" << std::endl;
	}
	void rotate_right(double degree)
	{
		phi = phi + degree;
		if (phi > 2 * pi)phi -= 2 * pi;
		if (phi < -2 * pi)phi += 2 * pi;
		update();
	}
	void rotate_left(double degree)
	{
		phi = phi - degree;
		if (phi > 2 * pi)phi -= 2 * pi;
		if (phi < -2 * pi)phi += 2 * pi;
		update();
	}
	void rotate_up(double degree)
	{
		theta = theta - degree;
		if (theta < 1e-6)theta = 1e-6;
		if (theta > pi)theta = pi;
		update();
	}
	void rotate_down(double degree)
	{
		theta = theta + degree;
		if (theta < 1e-6)theta = 1e-6;
		if (theta > pi)theta = pi;
		update();
	}
};