#pragma once

#include"vec3.h"
#include<cmath>
inline vec3 tran(double rho, double phi, double theta)
{
	return vec3(rho * sin(theta) * sin(phi), rho * cos(theta), rho * sin(theta) * cos(phi));
}

class Watcher
{
public:
	double rho, phi, theta;
	vec3 w, u, v;
	/*
	* z=rho*sin(theta)*cos(phi)
	* x=rho*sin(theta)*sin(phi)
	* y=rho*cos(theta)
	*/
	vec3 pos, updir, frontdir, rightdir;

	Watcher()
	{
		rho = 600; phi = theta = 0;
		pos = tran(rho,phi,theta);
		pos = pos / length(pos);
		frontdir = -pos;
		updir = vec3(0,1,0);
		rightdir = cross(frontdir, updir);
	}
	//旋转变换
	/*void rotate_right(double degree)
	{
		
	}*/
};