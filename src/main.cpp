/*
writen by (Younes khafaja) - 2008-2009
You are free to use this code as you see fit
email : lighting-team@hotmail.com
*/

#include"gameApp.h"



//----------------------------------------------------------------------------

	int main()

//int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,															int nCmdShow)
	{
	
	gameApp*GAME=new gameApp();

	
	GAME->runGame();

	
	GAME->ShutDown();
	
	}

