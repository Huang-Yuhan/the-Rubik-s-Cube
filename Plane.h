#pragma once
#include"vec3.h"
#include"graphics.h"
#include"Watcher.h"


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
	POINT screen_coordinate(const vec3& a)
	{
		vec3 tmp = a + offset;
		return { int(tmp.x),int(tmp.y) };
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
		return ((*point[0]) + (*point[2])) / 2;
	}
	bool isinside(const POINT& a)//判断a（屏幕里的坐标）是否在这个面在屏幕当中的显示区域
	{
		POINT p[4] = { screen_coordinate(*point[0]),screen_coordinate(*point[1]) ,screen_coordinate(*point[2]) ,screen_coordinate(*point[3]) };//最后在屏幕中显示的坐标
		int result=cross({ a.x - p[0].x,a.y - p[0].y }, { p[1].x - p[0].x,p[1].y - p[0].y });
		for (int i = 0; i < 3; i++)
		{
			int tmp=cross({ a.x - p[i].x,a.y - p[i].y }, { p[i + 1].x - p[i].x,p[i + 1].y - p[i].y });
			if ((tmp>0&&result<0)||(tmp<0&&result>0))return false;
		}
		return true;
	}
};
/*
bool operator>(const Plane& a, const Plane& b)//判断这两个面谁离摄像机最近
{
	return distance(a.center(), watcher) > distance(b.center(), watcher);
}*/