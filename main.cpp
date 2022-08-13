#include "TheRubiksCube.h"
#include<iostream>

Watcher watcher;

int main()
{
	//std::cout << watcher.pos.x << " " << watcher.pos.y << " " << watcher.pos.z << std::endl;
	TheRubiksCube game;
	game.GameStart();
	while (1)
	{
		game.processinput();
	}
	return 0;
}