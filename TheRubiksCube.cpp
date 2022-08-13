#include "TheRubiksCube.h"

const int offsete = 2 * e;

const int width = 1440;
const int height = 900;
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

}