#pragma once

#include"Cube.h"
#include"Watcher.h"


enum class DIR
{
	clockwise, anti_clockwise
};

class TheRubiksCube
{
public:
	Cube cube[27];//27个立方体
	TheRubiksCube();
	void GameStart();
	void draw();//绘图
	Plane* plcter[6];//Plane center
	void rotateF(double degree,DIR dir);
	void rotateR(double degree,DIR dir);
	void rotateB(double degree,DIR dir);
	void rotateL(double degree,DIR dir);
	void rotateU(double degree,DIR dir);
	void rotateD(double degree,DIR dir);
	~TheRubiksCube()
	{
		closegraph();
	}
	void processinput();
};

