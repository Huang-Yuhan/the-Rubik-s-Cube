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

	plcter[0] = &cube[CubeIndex(0,0,1)].plane[0];
	plcter[1] = &cube[CubeIndex(1, 0, 0)].plane[1];
	plcter[2] = &cube[CubeIndex(0, 0, -1)].plane[2];
	plcter[3] = &cube[CubeIndex(-1, 0, 0)].plane[3];
	plcter[4] = &cube[CubeIndex(0, 1, 0 )].plane[4];
	plcter[5] = &cube[CubeIndex(0, -1, 0)].plane[5];


}

void TheRubiksCube::GameStart()
{
	initgraph(width, height, EW_SHOWCONSOLE);
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

void TheRubiksCube::processinput()
{
	const int W = 0x57;
	const int S = 0x53;
	const int A = 0x40;
	const int D = 0x44;
	const double step = pi * 1 / 180;//10度的步长
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
		//找到面
		//旋转
		break;
	case WM_RBUTTONDOWN://按下鼠标左键，逆时针旋转
		//找到面
		//旋转
		break;
	default:break;
	}
	draw();
}
