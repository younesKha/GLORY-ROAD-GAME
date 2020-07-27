/*
writen by (Younes khafaja) - 2008-2009
You are free to use this code as you see fit
email : lighting-team@hotmail.com
*/
#ifndef GME_H
#define GME_H

#include"Game_Butten.h"
#include"EvenReciver.h"
#include "ArabicFont.h"
#include "Csounds.h"


class gameInterface
{
private:
IrrlichtDevice *Device;
Game_Butten*selectMissionB,*settingB,*aboutB,*exitB;
Game_Butten*Bmiss1,*Bmiss2,*Bmiss3,*BstartMission;
Game_Butten*Byes,*Bno;
MyEventReceiver*evenRec;
CGameSounds*Gsnd;
int LEVELNumber;
bool exitGame;
bool SHowComBanner,showLevelChoose,ShowstartChoose,loadGame,showCtraters,EndLoop;
bool DwexitYN;
bool DContol;
video::IVideoDriver*driver;

ArabicFont *arabF;
gui::IGUIFont* Enfont;
gui::IGUIImage*teamlogo,*irrlogo,*GloryWay,*mainwindow;
//----------------as static --------------------------------
 int show;
 float totTime;
 int xx;
 int CRTRMOV;
public:

//--------------------------------------------------------------------------------------------//
gameInterface(IrrlichtDevice*device,MyEventReceiver*EvenRec,bool ShowComBanner,CGameSounds*GSnd)
{

Device=device;
Gsnd=GSnd;
ShowstartChoose=true;
showLevelChoose=false;
DContol=false;
SHowComBanner=ShowComBanner;
showCtraters=false;
EndLoop=false;
exitGame=false;
DwexitYN=loadGame=false;
xx=show=totTime=0;
LEVELNumber=0;
CRTRMOV=0;

driver=Device->getVideoDriver();

Device->getFileSystem()->addZipFileArchive("data/ggui.pk3");


	selectMissionB=new Game_Butten(Device,"Bselectmission.png",core::position2d<s32>(20,120));
	settingB=new Game_Butten(Device,"Bcontrol.png",core::position2d<s32>(20,160));
	aboutB=new Game_Butten(Device,"Bcreaters.png",core::position2d<s32>(20,200));
	exitB=new Game_Butten(Device,"Bclose.png",core::position2d<s32>(20,500));

	Bmiss1=new Game_Butten(Device,"mission1.png",core::position2d<s32>(480,150));
	Bmiss2=new Game_Butten(Device,"mission2.png",core::position2d<s32>(480,190));
	Bmiss3=new Game_Butten(Device,"mission3.png",core::position2d<s32>(480,230));

	BstartMission=new Game_Butten(Device,"sartgame.png",core::position2d<s32>(20,520));

	Byes=new Game_Butten(Device,"yes.png",core::position2d<s32>(300,350));
	Bno=new Game_Butten(Device,"no.png",core::position2d<s32>(500,350));
	evenRec=EvenRec;
	Device->getCursorControl()->setVisible(false);
//-------------------------------------image----------------------------------------------------------------
gui::IGUIEnvironment*guiE=Device->getGUIEnvironment();
teamlogo=guiE->addImage(Device->getVideoDriver()->getTexture("teamlogo.tga"),core::position2d<s32>(240,100));
teamlogo->setScaleImage(true);
irrlogo=guiE->addImage(Device->getVideoDriver()->getTexture("irrlichtlogo.tga"),core::position2d<s32>(0,0));
GloryWay=guiE->addImage(Device->getVideoDriver()->getTexture("theGolyWay.TGA"),core::position2d<s32>(0,0));
GloryWay->setScaleImage(true);

mainwindow	=guiE->addImage(Device->getVideoDriver()->getTexture("mainground.tga"),core::position2d<s32>(0,0));
mainwindow->setScaleImage(true);


//----------------------------------------------------------------------------------------------------------

	Enfont=device->getGUIEnvironment()->getFont("Fonts/EngFont1.bmp");
	arabF= new ArabicFont(device,"Fonts/Arabfont.bmp");




//*****************************LOOOOOOOOOOOP**************************************
//********************************************************************************

u32 then = Device->getTimer()->getTime();
	const f32 MOVEMENT_SPEED = 5.f;

	while(Device->run() && driver)
	{
		if (Device->isWindowActive())
		{
		// Work out a frame delta time.
		const u32 now = Device->getTimer()->getTime();
		const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
		then = now;

			driver->beginScene(true, true, video::SColor(255,0,0,0));
			//****************************************************************
			if (ShowstartChoose)
			{
				if (SHowComBanner)
				DrowCompanyBanner(frameDeltaTime);
				else
				DrowStartChoice();
			}
			DrowLevelChoice();
			DrowLoadGame();
			DrowCreaters(frameDeltaTime);
			DrowControl();
			pressEscape();
			DrowExit_Y_N();

			if(EndLoop)
			break;
			//*****************************************************************
			driver->endScene();

		}
	}

//********************************************************************************
//********************************************************************************
}
void pressEscape()
{
	if(evenRec->IsKeyDown(irr::KEY_ESCAPE))
	{
		if (!ShowstartChoose)
		{
			Gsnd->PlayClick2Sound();
			ShowstartChoose=true;
			showLevelChoose=false;
			showCtraters=false;
			DwexitYN=false;
			DContol=false;
			CRTRMOV=0;
		}
	}
}
//--------------------------------------------------------------------------------------------//
void DrowCompanyBanner(float timeSec)
{
	static u32 xx=255;
	static bool pySnd=true;
	if (xx>0)//drow team logo
	{
		static float timeellips=0;

		teamlogo->setColor(video::SColor(xx,255,255,255));
		teamlogo->draw();
		irrlogo->setColor(video::SColor(xx,255,255,255));
		irrlogo->draw();

		timeellips+=timeSec;
		if (timeellips>=10)
		{
		xx-=1;
		}
	}

	else if(xx==0)//Drow darb al magd logo
	{
	if(pySnd)
	{
		Gsnd->PlayMusic2Sound();
		pySnd=false;
	}
	GloryWay->draw();
	int txt2[19]={0,50,67,56,113,112,113,99,113,112,113,82,111,38,11,87,34,0,33};
	arabF->DrowText(19,txt2,core::position2d<s32>(750,500),video::SColor(100,255,255,255));

	if(evenRec->IsKeyDown(irr::EKEY_CODE::KEY_KEY_D))
	{
	Gsnd->SEngine->stopAllSounds();
		SHowComBanner=false;
		Gsnd->PlayClick3Sound();
		Gsnd->PlayMusic1Sound();
		pySnd=true;
	}
	}

}
//-------------------------------------------------------------------------------------------//
void DrowStartChoice()
{
	Device->getCursorControl()->setVisible(true);

	mainwindow->draw();

	selectMissionB->DrowButten();
	settingB->DrowButten();
	aboutB->DrowButten();
	exitB->DrowButten();


//===============CHick click=======================
	if(selectMissionB->isClickDown(evenRec))
	{
	Gsnd->PlayClickSound();
		ShowstartChoose=false;
	showLevelChoose=true;
	}

	if(aboutB->isClickDown(evenRec))
	{
	ShowstartChoose=false;
	showCtraters=true;
	Gsnd->PlayClickSound();
	}
	if(exitB->isClickDown(evenRec))
	{
		Gsnd->PlayClickSound();
		ShowstartChoose=false;
		DwexitYN=true;

	}
	if(settingB->isClickDown(evenRec))
	{
	Gsnd->PlayClickSound();
	ShowstartChoose=false;
	DContol=true;
	}

}
void DrowExit_Y_N()
{
	if(DwexitYN)
	{
	driver->draw2DRectangle(video::SColor(255,50,50,50),core::rect<s32>(200,0,220,600));
	driver->draw2DRectangle(video::SColor(255,50,50,50),core::rect<s32>(600,0,620,600));
	driver->draw2DRectangle(video::SColor(200,20,20,40),core::rect<s32>(0,200,800,450));
	int txt2[20]={94,112,84,113,10,34,100,30,113,0,66,111,73,113,0,82,83,63,7,114};//åá ÊÑíÏ ÇÛáÇÞ ÇááÚÈÉ
	arabF->DrowText(20,txt2,core::position2d<s32>(500,245),video::SColor(255,255,255,255));
	Byes->DrowButten();
	Bno->DrowButten();

	if(Bno->isClickDown(evenRec))
	{
	Gsnd->PlayClickSound();
	ShowstartChoose=true;
	DwexitYN=false;
	}
	if(Byes->isClickDown(evenRec))
	{
	Gsnd->PlayClickSound();
	exitGame=true;
	EndLoop=true;
	}
	}
}
//---------------------------------------------------------------------------------------------//
void DrowLevelChoice()
{

	if(showLevelChoose)
	{
		mainwindow->draw();
		driver->draw2DRectangle(video::SColor(220,0,0,0),core::rect<s32>(0,0,800,600));
		driver->draw2DRectangle(video::SColor(250,5,0,0),core::rect<s32>(0,0,800,100));
		driver->draw2DRectangle(video::SColor(250,5,0,0),core::rect<s32>(0,500,800,600));

		int txt[11]={0,26,11,34,113,0,82,87,95,87,114};//ÇáÍÑßÉ ÃãÇã
		arabF->DrowText(11,txt,core::position2d<s32>(730,30),video::SColor(255,255,255,255));

		Bmiss1->DrowButten();
		Bmiss2->DrowButten();
		Bmiss3->DrowButten();
		BstartMission->DrowButten();
		//==========================================
		if(Bmiss1->isClickDown(evenRec))
		{
			if(LEVELNumber!=1)
			Gsnd->PlayClickSound();

		LEVELNumber=1;
		Bmiss1->setisChick(true);
		Bmiss2->setisChick(false);
		Bmiss3->setisChick(false);
		}
		if(Bmiss2->isClickDown(evenRec))
		{
			if(LEVELNumber!=2)
			Gsnd->PlayClickSound();

		LEVELNumber=2;
		Bmiss2->setisChick(true);
		Bmiss1->setisChick(false);
		Bmiss3->setisChick(false);
		}
		if(Bmiss3->isClickDown(evenRec))
		{
			if(LEVELNumber!=3)
			Gsnd->PlayClickSound();

		LEVELNumber=3;
		Bmiss3->setisChick(true);
		Bmiss1->setisChick(false);
		Bmiss2->setisChick(false);
		}
		if(BstartMission->isClickDown(evenRec))
		{
			if(LEVELNumber!=0)
			{
				Gsnd->PlayStartGameSound();
				showLevelChoose=false;
				loadGame=true;
			}
		}
	}
}

void DrowControl()
{
	if(DContol)
	{
		mainwindow->draw();
		driver->draw2DRectangle(video::SColor(130,0,0,0),core::rect<s32>(0,0,800,600));
		driver->draw2DRectangle(video::SColor(200,50,10,10),core::rect<s32>(0,0,800,600));
		driver->draw2DRectangle(video::SColor(255,0,0,0),core::rect<s32>(300,0,650,800));
			int txt9[6]={0,82,11,23,79,88};//ÇáÊÍßã
			arabF->DrowText(6,txt9,core::position2d<s32>(760,50),video::SColor(255,255,0,0));

			int txt[25]={0,82,23,34,78,114,113,1,86,3,85,113,113,113,112,113,112,113,112,113,112,113,113,113,45};//ÇáÍÑßÉ ÃãÇã
			arabF->DrowText(25,txt,core::position2d<s32>(600,100),video::SColor(255,255,255,255));
			int txt2[24]={0,82,23,34,78,114,113,26,83,72,113,113,113,112,113,112,113,112,113,112,113,113,113,37};//ÇáÍÑßÉ ÎáÝ
			arabF->DrowText(24,txt2,core::position2d<s32>(600,130),video::SColor(255,255,255,255));
			int txt3[25]={0,82,23,34,78,114,113,100,87,101,92,113,113,113,112,113,112,113,112,113,112,113,113,113,99};//ÇáÍÑßÉ íãíä
			arabF->DrowText(25,txt3,core::position2d<s32>(600,160),video::SColor(255,255,255,255));
			int txt4[25]={0,82,23,34,78,114,113,100,38,3,33,113,113,113,112,113,112,113,112,113,112,113,113,113,41};//ÇáÍÑßÉ íÓÇÑ
			arabF->DrowText(25,txt4,core::position2d<s32>(600,190),video::SColor(255,255,255,255));
			int txt5[32]={18,83,98,37,113,113,113,112,113,112,113,112,113,112,113,112,113,112,113,112,113,112,113,112,113,113,78,91,11,34,97,81};//ÌáæÓ
			arabF->DrowText(32,txt5,core::position2d<s32>(591,220),video::SColor(255,255,255,255));
			int txt6[37]={74,71,36,113,113,113,112,113,112,113,112,113,112,113,112,113,112,113,112,113,112,113,112,113,112,113,112,113,112,113,113,113,86,39,55,34,93};//ÞÝÒ
			arabF->DrowText(37,txt6,core::position2d<s32>(591,250),video::SColor(255,255,255,255));
			int txt7[26]={10,67,101,101,34,113,0,82,87,27,36,89,113,113,113,112,113,112,113,112,113,112,113,113,113,13};//ÊÛííÑ ÇáãÎÒä
			arabF->DrowText(26,txt7,core::position2d<s32>(600,280),video::SColor(255,255,255,255));
			int txt8[26]={1,10,98,86,3,10,101,80,113,113,113,112,113,112,113,112,113,112,113,112,113,112,113,113,113,49};//
			arabF->DrowText(26,txt8,core::position2d<s32>(600,310),video::SColor(255,255,255,255));

            int txt99[29]={10,67,101,101,33,113,0,82,39,111,21,113,113,112,113,112,113,112,113,62,19,84,113,0,82,87,3,97,37};//ÊÛííÑ ÇáÓáÇÍ
			arabF->DrowText(29,txt99,core::position2d<s32>(600,340),video::SColor(255,255,255,255));
            int txt10[29]={0,82,10,75,34,100,5,113,112,113,112,113,112,113,35,33,113,0,82,87,3,97,37,113,0,108,100,87,92};//ÇáÊÞÑíÈ
			arabF->DrowText(29,txt10,core::position2d<s32>(600,370),video::SColor(255,255,255,255));

	}
}
void DrowCreaters(float frmTime)
{

	if(showCtraters)
	{

		mainwindow->draw();
		driver->draw2DRectangle(video::SColor(230,0,0,0),core::rect<s32>(0,0,800,600));

				Enfont->draw(L"project lead ",core::rect<s32>(360,525+CRTRMOV,500,100),video::SColor(255,100,255,20));
				int txt[15]={100,97,90,40,113,100,23,101,2,113,26,71,3,18,114};
				arabF->DrowText(15,txt,core::position2d<s32>(480,545+CRTRMOV),video::SColor(255,255,255,255));

				Enfont->draw(L"software engineering",core::rect<s32>(330,625+CRTRMOV,500,100),video::SColor(255,100,255,50));
				int txt2[15]={100,97,90,40,113,100,23,101,2,113,26,71,3,18,114};
				arabF->DrowText(15,txt2,core::position2d<s32>(480,645+CRTRMOV),video::SColor(255,255,255,255));

				Enfont->draw(L"programming",core::rect<s32>(370,725+CRTRMOV,500,100),video::SColor(255,100,255,50));
				int txt3[15]={100,97,90,40,113,100,23,101,2,113,26,71,3,18,114};
				arabF->DrowText(15,txt3,core::position2d<s32>(480,745+CRTRMOV),video::SColor(255,255,255,255));

				Enfont->draw(L"models",core::rect<s32>(390,825+CRTRMOV,500,100),video::SColor(255,100,255,50));
				int txt4[15]={1,100,98,5,113,100,23,101,2,113,26,71,3,18,114};
				arabF->DrowText(15,txt4,core::position2d<s32>(480,845+CRTRMOV),video::SColor(255,255,255,255));
				int txt5[14]={1,29,85,113,100,23,101,2,113,26,71,3,18,114};
				arabF->DrowText(14,txt5,core::position2d<s32>(480,875+CRTRMOV),video::SColor(255,255,255,255));

				Enfont->draw(L"3D animation",core::rect<s32>(370,935+CRTRMOV,500,100),video::SColor(255,100,255,50));
				int txt6[15]={1,100,98,5,113,100,23,101,2,113,26,71,3,18,114};
				arabF->DrowText(15,txt6,core::position2d<s32>(480,950+CRTRMOV),video::SColor(255,255,255,255));

				Enfont->draw(L"levels design",core::rect<s32>(370,1035+CRTRMOV,500,100),video::SColor(255,100,255,50));
				int txt7[15]={100,97,90,40,113,100,23,101,2,113,26,71,3,18,114};
				arabF->DrowText(15,txt7,core::position2d<s32>(480,1055+CRTRMOV),video::SColor(255,255,255,255));

				Enfont->draw(L"ART",core::rect<s32>(397,1135+CRTRMOV,500,100),video::SColor(255,100,255,50));
				int txt8[15]={100,97,90,40,113,100,23,101,2,113,26,71,3,18,114};
				arabF->DrowText(15,txt8,core::position2d<s32>(480,1155+CRTRMOV),video::SColor(255,255,255,255));


				totTime+=frmTime;

			//	driver->draw2DRectangle(video::SColor(255,20,20,40),core::rect<s32>(0,0,800,600));
				driver->draw2DRectangle(video::SColor(200,0,0,0),core::rect<s32>(0,0,200,600));
				driver->draw2DRectangle(video::SColor(200,0,0,0),core::rect<s32>(600,0,800,600));
				driver->draw2DRectangle(video::SColor(255,40,0,0),core::rect<s32>(0,500,800,600));
				Enfont->draw(L"website : http://t0g0r.wordpress.com",core::rect<s32>(10,520,500,100),video::SColor(255,255,255,255));
				Enfont->draw(L"Emails : lighting.team2010@gmail.com",core::rect<s32>(10,540,500,100),video::SColor(255,255,255,255));
				Enfont->draw(L"lighting-team@hotmail.com",core::rect<s32>(80,555,525,100),video::SColor(255,255,255,255));

				if(totTime>=0.05f)
				{
				CRTRMOV-=1;
				totTime=0;
				}

				if(CRTRMOV< -1197)//loop creaters show
				CRTRMOV=0;


	}
	else
	{
		show=0;
		totTime=0;
	}
}
void DrowLoadGame()
{
	if(loadGame)
	{

	mainwindow->draw();
	driver->draw2DRectangle(video::SColor(130,0,0,0),core::rect<s32>(0,0,800,600));
	driver->draw2DRectangle(video::SColor(200,20,20,20),core::rect<s32>(0,500,800,600));
	//driver->draw2DRectangle(video::SColor(255,0,0,0),core::rect<s32>(0,100,800,500));

	//ÇäÊÙÑ áÍÙÇÊ
	int txt2[20]={10,23,87,101,84,113,0,82,87,95,87,114,113,113,133,112,113,112,113,112};
	arabF->DrowText(20,txt2,core::position2d<s32>(750,500),video::SColor(255,255,255,255));

	Device->getCursorControl()->setVisible(false);

	xx++;
	if(xx>30)
	{
	Gsnd->SEngine->stopAllSounds();
	Gsnd->PlayMusic4Sound();
	EndLoop=true;
	xx=0;
	}
	}
}
//------------------------------------------------------------------------------------------//
int getLevelNumber()
{
return LEVELNumber;
}
bool ExitGame()
{
return exitGame;
}

void _Destructor()
{
delete selectMissionB;
selectMissionB=0;
delete settingB;
settingB=0;
delete aboutB;
aboutB=0;
delete exitB;
exitB=0;
//delete evenRec;
//evenRec=0;
}
};
#endif GME_H
