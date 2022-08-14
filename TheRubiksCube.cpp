#include "TheRubiksCube.h"
#include<vector>
#include<algorithm>
#include<iostream>
const int offsete = 2 * e;

const double eps = 1e-6;

inline bool isequal(double a, double b)
{
	if (abs(a - b) < eps)return true;
	else return false;
}

int CubeIndex(int x, int y, int z)
{
	return (x + 1) * 9 + (y + 1) * 3 + (z + 1) * 1;
}

TheRubiksCube::TheRubiksCube()
{
	//初始化offset
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				cube[i * 9 + j * 3 + k].bindoffset(vec3((i - 1.0) * offsete, (j - 1.0) * offsete, (k - 1.0) * offsete));
	/*魔方各面配色
	F BLUE
	R RED
	B GREEN
	L ORANGE
	U YELLOW
	D WHITE
	*/
	for (int i = 0; i < 27; i++)cube[i].plane[0].setcolor(BLUE);
	for (int i = 0; i < 27; i++)cube[i].plane[1].setcolor(RED);
	for (int i = 0; i < 27; i++)cube[i].plane[2].setcolor(GREEN);
	for (int i = 0; i < 27; i++)cube[i].plane[3].setcolor(RGB(231,101,26));//自行百度或自行尝试
	for (int i = 0; i < 27; i++)cube[i].plane[4].setcolor(YELLOW);
	for (int i = 0; i < 27; i++)cube[i].plane[5].setcolor(WHITE);
	pre.message = WM_MOUSEMOVE;

	for(int i=0;i<27;i++)
		for (int j = 0; j < 6; j++)
		{
			vec3 tmp= cube[i].plane[j].center();
			if ((isequal(abs(tmp.x), 3 * e) || isequal(abs(tmp.y), 3 * e) || isequal(abs(tmp.z), 3 * e)) == false)
				cube[i].plane[j].setcolor(RGB(25, 25, 25));
		}
}

void TheRubiksCube::GameStart()
{
	initgraph(width, height);
	setorigin(width / 2, height / 2);//将原点设置在中心
	setbkcolor(RGB(25, 25, 25));//设置背景颜色
	BeginBatchDraw();//批量绘制，类似于OpenGL中缓冲区，最后会一起绘制出来，否则绘制出来的图形会偶尔有闪烁现象
	// 获得窗口句柄
	HWND hWnd = GetHWnd();
	// 使用 Windows API 修改窗口名称
	SetWindowText(hWnd, L"魔方模拟器");
	draw();
}

void TheRubiksCube::rotateF(double degree,DIR dir)
{
	if (dir == DIR::anti_clockwise)degree = -degree;
	for(int i=0;i<27;i++)
		if (isequal(offsete, cube[i].offset.z))
		{
			cube[i].local_rotate_z(degree);
			rotateZ(cube[i].offset,degree);
			cube[i].bindoffset(cube[i].offset);
		}
}

void TheRubiksCube::rotateR(double degree, DIR dir)
{
	if (dir == DIR::anti_clockwise)degree = -degree;
	for (int i = 0; i < 27; i++)
		if (isequal(offsete, cube[i].offset.x))
		{
			cube[i].local_rotate_x(degree);
			rotateX(cube[i].offset, degree);
			cube[i].bindoffset(cube[i].offset);
		}
}
void TheRubiksCube::rotateB(double degree, DIR dir)
{
	if (dir == DIR::anti_clockwise)degree = -degree;
	for (int i = 0; i < 27; i++)
		if (isequal(-offsete, cube[i].offset.z))
		{
			cube[i].local_rotate_z(-degree);
			rotateZ(cube[i].offset, -degree);
			cube[i].bindoffset(cube[i].offset);
		}
}
void TheRubiksCube::rotateL(double degree, DIR dir)
{
	if (dir == DIR::anti_clockwise)degree = -degree;
	for (int i = 0; i < 27; i++)
		if (isequal(-offsete, cube[i].offset.x))
		{
			cube[i].local_rotate_x(-degree);
			rotateX(cube[i].offset, -degree);
			cube[i].bindoffset(cube[i].offset);
		}
}
void TheRubiksCube::rotateU(double degree, DIR dir)
{
	if (dir == DIR::anti_clockwise)degree = -degree;
	for (int i = 0; i < 27; i++)
		if (isequal(offsete, cube[i].offset.y))
		{
			cube[i].local_rotate_y(degree);
			rotateY(cube[i].offset, degree);
			cube[i].bindoffset(cube[i].offset);
		}
}

void TheRubiksCube::rotateD(double degree, DIR dir)
{
	if (dir == DIR::anti_clockwise)degree = -degree;
	for (int i = 0; i < 27; i++)
		if (isequal(-offsete, cube[i].offset.y))
		{
			cube[i].local_rotate_y(-degree);
			rotateY(cube[i].offset, -degree);
		}
}

void TheRubiksCube::draw()
{
	cleardevice();
	std::vector<Plane> v;
	for (int i = 0; i < 27; i++)
		for (int j = 0; j < 6;j++)v.push_back(cube[i].plane[j]);
	std::sort(v.begin(), v.end());
	auto it = v.begin();
	for (it; it != v.end(); it++)it->draw();
	FlushBatchDraw();
}

void TheRubiksCube::solve(int x, int y,DIR dir)
{
	std::vector<Plane> v;
	for (int i = 0; i < 27; i++)
		for (int j = 0; j < 6; j++)v.push_back(cube[i].plane[j]);
	std::sort(v.begin(), v.end());
	auto it = v.begin();
	auto index = v.end();
	for (it; it != v.end(); it++)
	{
		if (it->isinside({ x,y }))index = it;
	}
	if(index==v.end())return;
	vec3 cen = index->center();
	int step = 2;
	int cnt = 45;
	if (isequal(cen.x, 3 * e))
	{
		for (int i = 1; i <= cnt; i++)
		{
			rotateR(step, dir);
			draw();
		}
	}
	if (isequal(cen.x, -3 * e))
	{
		for (int i = 1; i <= cnt; i++)
		{
			rotateL(step, dir);
			draw();
		}
	}
	if (isequal(cen.y, 3 * e))
	{
		for (int i = 1; i <= cnt; i++)
		{
			rotateU(step, dir);
			draw();
		}
	}
	if (isequal(cen.y, -3 * e))
	{
		for (int i = 1; i <= cnt; i++)
		{
			rotateD(step, dir);
			draw();
		}
	}
	if (isequal(cen.z, 3 * e))
	{
		for (int i = 1; i <= cnt; i++)
		{
			rotateF(step, dir);
			draw();
		}
	}
	if (isequal(cen.z, -3 * e))
	{
		for (int i = 1; i <= cnt; i++)
		{
			rotateB(step, dir);
			draw();
		}
	}

}

void TheRubiksCube::processinput()
{
	const int W = 0x57;
	const int S = 0x53;
	const int A = 0x40;
	const int D = 0x44;
	const double step = pi * 2 / 180;//10度的步长
	flushmessage(EM_MOUSE);
	ExMessage m = getmessage();
	switch (m.message)
	{
	case WM_KEYDOWN://按下wsad
		std::cout << (char)tolower(m.vkcode) << std::endl;
		switch ((char)tolower(m.vkcode))
		{
		case 'w':watcher.rotate_up(step); break;
		case 's':watcher.rotate_down(step);  break;
		case 'a':watcher.rotate_left(step);  break;
		case 'd':watcher.rotate_right(step);  break;
		default:break;
		}
		break;
	case WM_LBUTTONDOWN://按下鼠标左键，顺时针旋转
		if (pre.message == WM_LBUTTONDOWN)break;
		//找到面
		//旋转
		solve(m.x-width/2,m.y-height/2,DIR::anti_clockwise);
		break;
	case WM_RBUTTONDOWN://按下鼠标右键，逆时针旋转
		if (pre.message == WM_RBUTTONDOWN)break;
		//找到面
		//旋转
		solve(m.x-width/2, m.y-height/2, DIR::clockwise);
		break;
	default:break;
	}
	draw();
	pre = m;
}
