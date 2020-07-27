/*
writen by (Younes khafaja) - 2008-2009
You are free to use this code as you see fit
email : lighting-team@hotmail.com
*/
#include <irrlicht.h>
using namespace irr;
#ifndef REC_H
#define REC_H
class MyEventReceiver : public IEventReceiver
{
public:
	
	// This is the one method that we have to implement
	virtual bool OnEvent(const SEvent& event)
	{
		if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
		{

			if(event.MouseInput.Event==irr::EMIE_LMOUSE_PRESSED_DOWN)
			IsClickLButten=true;
			else if (event.MouseInput.Event==irr::EMIE_LMOUSE_LEFT_UP)
			IsClickLButten=false;
			else if (event.MouseInput.Event==irr::EMIE_MOUSE_WHEEL)
			IsWheel=true;
			if(event.MouseInput.Event==irr::EMIE_RMOUSE_PRESSED_DOWN)		
			IsClickRButten=true;
			else if (event.MouseInput.Event==irr::EMIE_RMOUSE_LEFT_UP)
			IsClickRButten=false;
		}
		// Remember whether each key is down or up
		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

		return false;
	}

	// This is used to check whether a key is being held down
	virtual bool IsKeyDown(EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}
	MyEventReceiver()
	{
		enter=true;
		IsWheel=false;
		coninuseClick=false;
		IsClickLButten=false;
		IsClickRButten=false;	
		for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
		KeyIsDown[i] = false;

	}
void setLeftClickContinuse(bool enable)
{
coninuseClick=enable;
}

bool isLMouseClick()
{
return IsClickLButten;	
}
bool isRMouseClick()
{
return IsClickRButten;	
}

bool isWheel()
{
return IsWheel;
}
void setWheelFALSE()
{
IsWheel=false;
}
private:
	// We use this array to store the current state of each key
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
	bool IsClickLButten;
	bool IsClickRButten;	
	bool IsWheel;	
	bool coninuseClick;//åÐÇ ÇáãÊÛíÑ áÌá ÇáÑÓíÝÑ íÑÓá æÍíÏÉ ÚäÏ ÖÛØ ÒÑ ÇáãÇæÓ ÇáÈÓÇÑ æáíÓ ÑÓÇÆ
	bool enter;
};

#endif
