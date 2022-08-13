#include "TheRubiksCube.h"
#include "vec3.h"
#include<iostream>

Watcher watcher;

int main()
{
	/*TheRubiksCube game;
	game.GameStart();*/
	vec3 tmp = vec3(0, 0, 1) + vec3(1, 1, 1);
	std::cout<<tmp.z;
	getchar();
	return 0;
}