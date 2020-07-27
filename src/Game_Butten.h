/*
writen by (Younes khafaja) - 2008-2009
You are free to use this code as you see fit
email : lighting-team@hotmail.com
*/
#ifndef BTN_H
#define BTN_H
#include <irrlicht.h>
#include"EvenReciver.h"
using namespace irr;

class Game_Butten
{
private:
core::rect<s32>rec1,rec2,loc;
core::position2d<s32>post;
video::IVideoDriver*Driver; 
IrrlichtDevice *Dev;
video::ITexture*texture;
bool isOver,isChick;
public:
Game_Butten(IrrlichtDevice *device,c8*textureName,core::position2d<s32>Buttenpostion)
{
Dev=device;
isChick=false;
Driver=device->getVideoDriver();
texture=Driver->getTexture(textureName);
core::dimension2d<s32> Tsize=texture->getOriginalSize();
rec1=core::rect<int>(0,0,Tsize.Width/2,Tsize.Height);
rec2=core::rect<int>(Tsize.Width/2,0,Tsize.Width,Tsize.Height);
post=Buttenpostion;


loc=core::rect<s32>(post.X,post.Y,post.X+rec1.getWidth(),post.Y+rec1.getHeight());
}
void DrowButten()
{
	if ((loc.isPointInside(Dev->getCursorControl()->getPosition())))
	{
	Driver->draw2DImage(texture,post,rec2,0,video::SColor(255,255,255,255), true);
	isOver=true;
	}
	else
	{
	Driver->draw2DImage(texture,post,rec1,0,video::SColor(255,255,255,255), true);
	isOver=false;
	}

	if(isChick)
	Driver->draw2DImage(texture,post,rec2,0,video::SColor(255,255,255,255), true);
}
bool isClickDown(MyEventReceiver*evenRec)
{
	if ((isOver)&&(evenRec->isLMouseClick()))
	return true;
	else
	return false;
}
void setisChick(bool cli)
{
isChick=cli;
}

};
#endif BTN_H