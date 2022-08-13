#pragma once
#include"vec.h"
#include"graphics.h"
#include"Watcher.h"
#include"matrix.h"
const int width = 1440;
const int height = 900;
extern Watcher watcher;

class Plane
{
public:
	const vec3* point[4];
	COLORREF plane_color;
	vec3 offset;
	Plane(const vec3* a, const vec3* b, const vec3* c, const vec3* d) :offset(0, 0, 0)
	{
		bindpoint(a, b, c, d);
		plane_color = BLACK;
	}
	Plane()
	{
		plane_color = BLACK;
	}
	vec3 world_coordinate(const vec3& a)
	{
		return a + offset;
	}
	POINT screen_coordinate(const vec3& a)
	{
		Matrix look_at = LookAt(watcher.u,watcher.v,watcher.w, watcher.pos);
		Matrix Mvp = Matrix(vec4(width / 2.0, 0, 0, 0), vec4(0, height / 2.0, 0, 0), vec4(0, 0, 1, 0), vec4((width - 1.0) / 2, (height - 1.0) / 2, 0, 1));
		double n = -300;
		double f = -700;
		double l = -300;
		double r = 300;
		double b = -300;
		double t = 300;
		Matrix Mper = Matrix(vec4(2*n/(r-l),0,0,0), vec4(0,2*n/(t-b),0,0), vec4((l+r)/(l-r),(b+t)/(b-t),(f+n)/(n-f),-1), vec4(0,0,2*f*n/(f-n),0));
		vec3 tmp = world_coordinate(a);
		vec4 ans = Mvp * Mper * look_at * vec4(tmp.x,tmp.y,tmp.z,1);
		POINT anspoint;
		anspoint.x = ans.x / ans.w;
		anspoint.y = ans.y / ans.w;
		return anspoint;
	}
	void bindoffset(const vec3& a)
	{
		offset = a;
	}
	void bindpoint(const vec3* a, const vec3* b, const vec3* c, const vec3* d)
	{
		point[0] = a;
		point[1] = b;
		point[2] = c;
		point[3] = d;
	}
	void setcolor(COLORREF color)
	{
		plane_color = color;
	}
	void draw()
	{
		setfillcolor(plane_color);
		setlinecolor(BLACK);
		POINT p[4] = { screen_coordinate(*point[0]),screen_coordinate(*point[1]) ,screen_coordinate(*point[2]) ,screen_coordinate(*point[3]) };//最后在屏幕中显示的坐标
		fillpolygon(p, 4);//在图中画出来
	}
	vec3 center()const//面的中心
	{
		return ((*point[0]) + (*point[2])) / 2+offset;
	}
	bool isinside(const POINT& a)//判断a（屏幕里的坐标）是否在这个面在屏幕当中的显示区域
	{
		POINT p[4] = {screen_coordinate(*point[0]),screen_coordinate(*point[1]) ,screen_coordinate(*point[2]) ,screen_coordinate(*point[3])};//最后在屏幕中显示的坐标
		int result=cross({ a.x - p[0].x,a.y - p[0].y }, { p[1].x - p[0].x,p[1].y - p[0].y });
		for (int i = 0; i < 3; i++)
		{
			int tmp=cross({ a.x - p[i].x,a.y - p[i].y }, { p[i + 1].x - p[i].x,p[i + 1].y - p[i].y });
			if ((tmp>0&&result<0)||(tmp<0&&result>0))return false;
		}
		return true;
	}
	bool operator<(const Plane& a)const
	{
		return distance(center(), watcher.pos) > distance(a.center(), watcher.pos);
	}
};
