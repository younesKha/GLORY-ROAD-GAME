/*
writen by (Younes khafaja) - 2008-2009
You are free to use this code as you see fit
email : lighting-team@hotmail.com
*/
#ifndef GGI_H
#define GGI_H
#include <irrlicht.h>
#include"CWeapon.h"
#include"Game_Butten.h"
#include"EvenReciver.h"
#include "ArabicFont.h"
#include "Csounds.h"
//#include<string>
using namespace irr;

class GGI
{
protected:
	IrrlichtDevice*Device;
	gui::IGUIEnvironment*guienvir;
	gui::IGUIImage*GunFocus,*ZoomImage,*hitImage,*prgress;
	scene::ISceneManager*smanger;
	video::IVideoDriver* driv;
	video::ITexture*TxureNambers;
	core::rect<int>numRect[10];
	MyEventReceiver*recover;
	CGameSounds*Gsnd;
	
	bool*playESCP;
	CWeapon*W;
	int Wnumber;
	core::rect<s32>num[10];
	bool ShowZoomImage,gover,ShowWin,showStopInterface;
	int Redindex,overindex,winindx;
	bool StartgameFade;
	int QRchick;  //quit exit chick
	int winShowIndx ;
	gui::IGUIFont* Enfont,* Enfont2;
	ArabicFont *arabF;
	//---Butten-----
	Game_Butten*back_B,*rest_B,*control_B,*Abrout_B;
	Game_Butten*Byes,*Bno;
	//--------------
	void DrowBledProgress(int blood)
	{

		int Blead=blood;	
		Blead=100-Blead;
		driv->draw2DRectangle(video::SColor(100,0,255,0),core::rect<s32>(0, 400, 10, 600));
		driv->draw2DRectangle(video::SColor(150,255,0,0),core::rect<s32>(0, 400, 10, 400+Blead*2));

	}
	void DrowGunFocus()
	{
		static int oldnum=0;
		if (!(oldnum==Wnumber))
		{
		GunFocus->setVisible(false);
		Device->getFileSystem()->addZipFileArchive("data/weap.pk3");
		GunFocus=guienvir->addImage(smanger->getVideoDriver()->getTexture(W->weap[Wnumber].GfocusGunpath),W->weap[Wnumber].GfocusGunpost,true);
		GunFocus->setScaleImage(true);
		GunFocus->setVisible(true);
		oldnum=Wnumber;
		}
		GunFocus->draw();
	}

	void DrowGunName()
	{
		driv->draw2DRectangle(video::SColor(50,255,0,0),core::rect<s32>(120,580,170,600));
		Enfont->draw( W->weap[Wnumber].Gname,core::rect<s32>(130,580,250,590),video::SColor(255,0,0,0));
	}
	void DrowShotCount()
	{
		DrowNumbers(W->weap[Wnumber].GP_TotalShotCount,20,550);		
	}
	void DrowStorgeShotCount()
	{
		DrowNumbers(W->weap[Wnumber].GP_ShotInStorgeCount,20,510);
	}
	void DrowRedHide()
	{
		if(Redindex>0)
		{
		driv->draw2DRectangle(video::SColor(Redindex,255,0,0),core::rect<s32>(0,0,800,600));
		Redindex-=5;
		}
	}
	void DrowNumbers(int num,int x,int y)
	{
		
	int numlen;
	int *nmbr;
		if (num>=100)
		{
		numlen=3;
		nmbr=new int[3];
		nmbr[0]=num/100;
		nmbr[1]=(num/10)-10;
		nmbr[2]=num%10;
		}
		else if (num>=10)
		{
		numlen=2;
		nmbr=new int[2];
		nmbr[0]=num/10;
		nmbr[1]=num%10;
		}
		else
		{
		numlen=1;
		nmbr=new int();
		nmbr[0]=num%10;
		}

		for(int i=0;i<numlen;i++)
		{	
		driv->draw2DImage(TxureNambers,core::position2d<s32>(x,y),numRect[nmbr[i]],0,video::SColor(200,255,255,255), true);
		x+=20;
		}
	}


	void drowGameOver(float Frmtimeell)
	{

			static float time_Total=0;

			time_Total+=Frmtimeell;

		if(time_Total>7.0f)
		{
			Device->getCursorControl()->setVisible(true);			
			//ÚäÏ äåÇíÉ ÚÑÖ ÇáÝæÒ ÇÙåÑ ÝÇÝÐÉ ÇáÇÓßÈ ÝæáÓÊ åäÇ íÚäí ÊÑæÇ
			*playESCP=false;
			//Gsnd->SEngine->stopAllSounds();
			time_Total=0;
		}
				
		if(overindex<255)
		{
			overindex++;
		}
		driv->draw2DRectangle(video::SColor(overindex,255,255,255),core::rect<s32>(0,0,800,600));
		driv->draw2DRectangle(video::SColor(overindex,180,170,170),core::rect<s32>(0,170,800,270));
		int txt[23]={112,113,112,113,112,113,70,43,83,12,113,0,82,87,95,87,114,112,113,112,113,112,113};//ÝÔáÊ ÇáãåãÉ
		arabF->DrowText(23,txt,core::position2d<s32>(490,530),video::SColor(overindex,20,20,20));
		
		int txt1[25]={97,74,98,0,70,84,113,0,82,43,95,30,0,104,113,108,113,10,87,51,102,113,38,30,0};//æÞæÇÝá ÇáÔåÏÇÁ áÇ ÊãÖí ÓÏÇ
		arabF->DrowText(25,txt1,core::position2d<s32>(520,200),video::SColor(overindex,255,255,255));
		int txt2[23]={117,89,113,0,82,32,99,113,100,87,51,102,113,94,98,113,0,82,55,67,101,3,89};//Çä Çáí íãÖí åæ ÇáØÛíÇä
		arabF->DrowText(23,txt2,core::position2d<s32>(512,230),video::SColor(overindex,255,255,255));

	}


	void DrowZoomImage()
	{
	if (ShowZoomImage)
	ZoomImage->draw();
	}

	void DrowStartGameFade(float Frmtimeell)
	{

		static float timeTot=0;
		static int cont=255;
			if(StartgameFade)
			{
				
				driv->draw2DRectangle(video::SColor(cont,0,0,0),core::rect<s32>(0,0,800,600));

				timeTot+=Frmtimeell;
				
				if(timeTot>=0.01f)
				{
					cont-=3;
						
						if(cont<=0)
						{
						StartgameFade=false;
						timeTot=0;
						cont=255;
						}
						
						
				timeTot=0;
				}
			
			}
			
	}

public:
	void GuiInterfaceRender(int blood,float Frmtimeell)
	{
	if(!gover)
	{
	DrowBledProgress(blood);
	DrowGunFocus();
	DrowStorgeShotCount();
	DrowShotCount();
	DrowZoomImage();
	DrowRedHide();
	DrowGunName();
	DrowStartGameFade(Frmtimeell);
	DrowWinning(Frmtimeell);
	}
	else
	drowGameOver(Frmtimeell);

	}
	void DrowWinImage()
	{
	driv->draw2DRectangle(video::SColor(255,100,100,200),core::rect<s32>(0,0,800,600));
	}
	int DrowStopGameInterFace()
	{
		driv->draw2DRectangle(video::SColor(100,100,100,100),core::rect<s32>(0,0,800,600));

		if(QRchick==1)
		return DrowwOuitYN();
		else if(QRchick==2)
		return DrowwRestYN();
		else if(QRchick==3)
		return DrowControl();
		else
		{
		back_B->DrowButten();
		rest_B->DrowButten();
		control_B->DrowButten();
		Abrout_B->DrowButten();
		}

		//===========================
		if(back_B->isClickDown(recover))
		{
			return 1;
			Gsnd->PlayClickSound();
		}
		else if(rest_B->isClickDown(recover))
		{
			QRchick=2;
			Gsnd->PlayClickSound();
		}
		else if(control_B->isClickDown(recover))
		{
			QRchick=3;
			Gsnd->PlayClickSound();
		}
		else if(Abrout_B->isClickDown(recover))
		{
		QRchick=1;
		Gsnd->PlayClickSound();
		}

		


		return 0;
	}
	int DrowwOuitYN()
	{

			driv->draw2DRectangle(video::SColor(255,50,50,50),core::rect<s32>(200,0,220,600));
			driv->draw2DRectangle(video::SColor(255,50,50,50),core::rect<s32>(600,0,620,600));
			driv->draw2DRectangle(video::SColor(200,20,20,40),core::rect<s32>(0,200,800,450));

		int txt2[25]={94,112,84,113,10,34,100,30,113,0,82,26,34,97,17,113,86,89,113,0,82,87,95,87,114};//åá ÊÑíÏ ÇÛáÇÞ ÇááÚÈÉ
		arabF->DrowText(25,txt2,core::position2d<s32>(530,250),video::SColor(255,255,255,255));
		Byes->DrowButten();
		Bno->DrowButten();
		//=====================================
		if(Bno->isClickDown(recover))
		{
		Gsnd->PlayClickSound();
		QRchick=0;
		return 0;
		}
		if(Byes->isClickDown(recover))
		{
		Gsnd->PlayClickSound();
		return 3;
		}

		if(recover->IsKeyDown(irr::KEY_ESCAPE))
		{
		Gsnd->PlayClick2Sound();
		QRchick=0;
		}
		return 0;

	}
	int DrowwRestYN()
	{
			driv->draw2DRectangle(video::SColor(255,50,50,100),core::rect<s32>(200,0,220,600));
			driv->draw2DRectangle(video::SColor(255,50,50,100),core::rect<s32>(600,0,620,600));
			driv->draw2DRectangle(video::SColor(200,20,20,40),core::rect<s32>(0,200,800,450));
		int txt2[21]={94,112,84,113,10,34,100,30,113,0,62,3,29,93,113,0,82,87,95,87,114};//åá ÊÑíÏ ÇÛáÇÞ ÇááÚÈÉ
		arabF->DrowText(21,txt2,core::position2d<s32>(500,250),video::SColor(255,255,255,255));
		Byes->DrowButten();
		Bno->DrowButten();
		//=====================================
		if(Bno->isClickDown(recover))
		{
		Gsnd->PlayClickSound();
		QRchick=0;
		return 0;
		}
		if(Byes->isClickDown(recover))
		{
		Gsnd->PlayClickSound();
		return 2;
		}

		if(recover->IsKeyDown(irr::KEY_ESCAPE))
		{
			Gsnd->PlayClickSound();
			QRchick=0;
		}
		return 0;
	}

	int DrowControl()
	{
	driv->draw2DRectangle(video::SColor(255,50,10,10),core::rect<s32>(0,0,800,600));
	driv->draw2DRectangle(video::SColor(255,0,0,0),core::rect<s32>(300,0,650,800));
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
	int txt8[26]={1,10,98,86,3,10,101,80,113,113,113,112,113,112,113,112,113,112,113,112,113,112,113,113,113,49};//ÃæÊæãÇÊíßí
	arabF->DrowText(26,txt8,core::position2d<s32>(600,310),video::SColor(255,255,255,255));
	
	if(recover->IsKeyDown(irr::KEY_ESCAPE))
	QRchick=0;
	return 0;
	}
	void setGunNumber(int num)
	{
	Wnumber=num;
	}
	void setZoomvisible(bool b)
	{
	ShowZoomImage=b;
	}
	void PlayRed()
	{
	Redindex=100;
	}
	void setGameOver(bool isOver)
{
gover=isOver;
}

	void _Destructor()
	{
		//delete recover;
		//recover=0;

		//delete W;
		//W=0;
	}
	void setWinning(bool win)
	{
		ShowWin=win;
		
	}
	int getChick()
	{
	return QRchick;
	}
	void backTomain()
	{
	QRchick=0;
	}
	//------------------------
	virtual bool START_LEVEL_SHOW(float frmeTime){return false;}
	virtual void DrowWinning(float Frmtimeell){}
};
class GGI1: public GGI
{
public:
GGI1(IrrlichtDevice*Dev,MyEventReceiver*EvenRec,CGameSounds*GSnd,CWeapon*Weop,int Gnum,bool*playEscp)
	{
	winShowIndx=0;
		QRchick=0;
	Gsnd=GSnd;
	playESCP=playEscp;
	ShowWin=false;
	StartgameFade=true;
	winindx=overindex=Redindex=0;
	Device=Dev;
	recover=EvenRec;
	smanger=Dev->getSceneManager();
	W=Weop;
	Wnumber=Gnum;
	driv =smanger->getVideoDriver();
	showStopInterface=gover=ShowZoomImage=false;
	guienvir=smanger->getGUIEnvironment();
	GunFocus=guienvir->addImage(smanger->getVideoDriver()->getTexture(W->weap[Wnumber].GfocusGunpath),W->weap[Wnumber].GfocusGunpost,true);
	GunFocus->setScaleImage(true);
//--------------------------------------------------------------------------------------
	Dev->getFileSystem()->addZipFileArchive("data/weap.pk3");
	ZoomImage=guienvir->addImage(smanger->getVideoDriver()->getTexture("zoomImage.png"),core::position2d<s32>(0,0),true);
	ZoomImage->setScaleImage(true);
	ZoomImage->setRelativePosition(core::rect<s32>(0,0,800,600));
	ZoomImage->setVisible(true);
//------------------------------------------------------------------------	
	Dev->getFileSystem()->addZipFileArchive("data/ggui.pk3");
	//----------------------------------------------------------------------
	TxureNambers=driv->getTexture("number.bmp");
	driv->makeColorKeyTexture(TxureNambers, core::position2d<s32>(0,0));
//----------------------------------Butten data---------------------------------------------------
	back_B=new Game_Butten(Device,"Bback.png",core::position2d<s32>(300,200));
	rest_B=new Game_Butten(Device,"BrestGame.PNG",core::position2d<s32>(300,240));
	control_B=new Game_Butten(Device,"Bcontrol.png",core::position2d<s32>(300,280));
	Abrout_B=new Game_Butten(Device,"Bext.png",core::position2d<s32>(300,320));

	Byes=new Game_Butten(Device,"yes.png",core::position2d<s32>(300,350));
	Bno=new Game_Butten(Device,"no.png",core::position2d<s32>(500,350));
//-----------------------font-------------------------------------------------------
Enfont=Dev->getGUIEnvironment()->getFont("Fonts/EngFont1.bmp");

arabF= new ArabicFont(Dev,"Fonts/Arabfont.bmp");
//--------------------------------------------------------------------------------
	numRect[0]=core::rect<s32>(324,0,346,49);
	numRect[1]=core::rect<s32>(290,0,311,49);
	numRect[2]=core::rect<s32>(255,0,276,49);
	numRect[3]=core::rect<s32>(221,0,242,49);
	numRect[4]=core::rect<s32>(186,0,207,49);
	numRect[5]=core::rect<s32>(151,0,172,49);
	numRect[6]=core::rect<s32>(117,0,138,49);
	numRect[7]=core::rect<s32>(82,0,103,49);
	numRect[8]=core::rect<s32>(48,0,69,49);
	numRect[9]=core::rect<s32>(13,0,34,49);
	
	}
bool START_LEVEL_SHOW(float frmeTime)
	{
		static bool plySnd=true;
		if(plySnd)
		{
		Gsnd->SEngine->stopAllSounds();
			Gsnd->PlayMusic3Sound();
		plySnd=false;
		}

					
		driv->draw2DRectangle(video::SColor(255,0,0,0),core::rect<s32>(0,0,800,600));
		driv->draw2DRectangle(video::SColor(255,40,30,30),core::rect<s32>(0,180,800,450));
		driv->draw2DRectangle(video::SColor(255,40,90,30),core::rect<s32>(700,0,730,600));

		 int txt0[14]={10,75,30,85,113,70,30,33,6,77,113,86,19,30};//ÊÞÏã ÝÏÑÈß ãÌÏ
		 arabF->DrowText(14,txt0,core::position2d<s32>(695,50),video::SColor(255,0,255,0));
		
		 int txt[47]={74,3,86,12,113,86,19,87,98,62,114,113,86,92,113,0,82,87,19,3,94,30,100,92,6,23,71,34,113,90,71,76,26,83,72,113,86,98,0,74,64,113,0,82,63,30,97};
		arabF->DrowText(47,txt,core::position2d<s32>(600,200),video::SColor(255,255,255,255));
		
		int txt2[35]={42,34,76,113,74,55,3,61,113,66,36,116,113,97,0,33,38,3,82,80,113,70,102,113,86,95,87,114,113,18,95,3,30,100,114};
		arabF->DrowText(35,txt2,core::position2d<s32>(600,230),video::SColor(255,255,255,255));
		
		int txt3[10]={94,30,69,113,0,82,87,95,87,114};
		arabF->DrowText(10,txt3,core::position2d<s32>(600,280),video::SColor(255,0,255,255));

		int txt4[37]={74,11,84,113,1,78,7,34,113,62,30,29,113,86,92,113,18,91,98,29,113,0,108,22,11,111,81,113,0,108,38,34,0,115,101,83,102};
		arabF->DrowText(37,txt4,core::position2d<s32>(600,310),video::SColor(255,255,255,255));
		
		int txt5[11]={86,98,62,30,113,0,83,86,95,87,114};
		arabF->DrowText(11,txt5,core::position2d<s32>(600,360),video::SColor(255,0,255,255));
				
		int txt6[22]={0,82,39,3,62,114,113,0,82,39,3,6,62,114,113,46,7,3,22,112,112,3};
		arabF->DrowText(22,txt6,core::position2d<s32>(600,390),video::SColor(255,255,255,255));
		
		int txt7[13]={94,84,113,1,90,12,113,18,3,94,112,112,36};
		arabF->DrowText(13,txt7,core::position2d<s32>(450,490),video::SColor(255,255,255,255));
		
		int txt8[10]={0,50,67,55,113,86,39,55,34,116};
		arabF->DrowText(10,txt8,core::position2d<s32>(450,530),video::SColor(30,255,255,255));
		


		if(recover->IsKeyDown(irr::KEY_SPACE))
		{
			StartgameFade=true;
			plySnd=true;
			return false;
			
		}

	
		
		return true;
	}




void DrowWinning(float Frmtimeell)
	{
		if(ShowWin)
		{
		static float timeTotal=0;
		float frameDeltaTime=Frmtimeell;
		if(winindx<254)
		winindx+=2;

		driv->draw2DRectangle(video::SColor(winindx,0,0,0),core::rect<s32>(0,0,800,600));

			if(winindx>250)
			{
				driv->draw2DRectangle(video::SColor(255,20,20,50),core::rect<s32>(0,200,800,400));
				driv->draw2DRectangle(video::SColor(150,0,20,0),core::rect<s32>(700,0,710,600));
				driv->draw2DRectangle(video::SColor(150,0,20,0),core::rect<s32>(100,0,110,600));
				if(	winShowIndx==0)
				{
					 int txt[29]={112,113,112,113,112,113,10,87,12,113,0,82,87,95,87,114,113,6,91,19,3,21,113,112,113,112,113,112,113};
					 arabF->DrowText(29,txt,core::position2d<s32>(500,300),video::SColor(255,255,255,255));
					timeTotal+=frameDeltaTime;
					if (timeTotal>12.0f)
					{
						winShowIndx=1;
						timeTotal=0;
					}
				}
				else if (winShowIndx==1)
				{
				 int txt[31]={97,62,3,29,113,0,83,86,19,3,94,30,100,92,113,117,82,2,113,74,98,0,62,30,94,88,113,6,39,111,88};
				 arabF->DrowText(31,txt,core::position2d<s32>(520,300),video::SColor(255,255,255,255));
			
					timeTotal+=frameDeltaTime;
					if (timeTotal>5.0f)
					{
						winShowIndx=2;
						timeTotal=0;
					}
				}
				else if (winShowIndx==2)
				{
				 int txt[60]={0,82,19,101,44,113,0,108,38,34,0,115,101,83,102,113,100,63,11,34,69,113,6,87,75,11,84,113,0,82,63,43,34,0,9,113,86,92,113,18,91,98,29,93,113,97,100,11,98,62,30,113,6,34,29,113,62,91,101,72};
				 arabF->DrowText(60,txt,core::position2d<s32>(670,300),video::SColor(255,255,255,255));
					
					timeTotal+=frameDeltaTime;
					if (timeTotal>5.0f)
					{
						winShowIndx=3;
						timeTotal=0;
					}
				}
				else if (winShowIndx==3)
				{
				 int txt[17]={0,66,111,73,113,18,87,101,64,113,0,82,87,63,3,6,34};
				 arabF->DrowText(17,txt,core::position2d<s32>(500,300),video::SColor(255,255,255,255));
					
					timeTotal+=frameDeltaTime;
					if (timeTotal>5.0f)
					{
						winShowIndx=4;
						timeTotal=0;
					}
				}
				else if (winShowIndx==4)
				{
				 int txt[30]={54,3,115,34,0,9,113,0,108,38,11,55,111,61,113,10,87,110,113,38,87,3,104,113,0,82,75,55,3,61};
				 arabF->DrowText(30,txt,core::position2d<s32>(550,300),video::SColor(255,255,255,255));
					
					timeTotal+=frameDeltaTime;
					if (timeTotal>5.0f)
					{
						winShowIndx=5;
						timeTotal=0;
					}
				}
				else if (winShowIndx==5)
				{
				 int txt[24]={0,82,87,91,55,75,114,113,86,75,7,83,114,113,62,83,2,113,0,18,11,101,3,21};
				 arabF->DrowText(24,txt,core::position2d<s32>(510,300),video::SColor(255,255,255,255));
					
					timeTotal+=frameDeltaTime;
					if (timeTotal>5.0f)
					{
						winShowIndx=6;
						timeTotal=0;
					}
				}
				else if (winShowIndx==6)
				{
				 int txt[12]={94,84,113,1,90,12,113,86,39,11,63,30};
				 arabF->DrowText(12,txt,core::position2d<s32>(510,300),video::SColor(255,255,255,255));
					
					timeTotal+=frameDeltaTime;
					if (timeTotal>5.0f)
					{
						winShowIndx=7;
						timeTotal=0;
					}
				}
				else if (winShowIndx==7)
				{	
					Device->getCursorControl()->setVisible(true);			
					//ÚäÏ äåÇíÉ ÚÑÖ ÇáÝæÒ ÇÙåÑ ÝÇÝÐÉ ÇáÇÓßÈ ÝæáÓÊ åäÇ íÚäí ÊÑæÇ
					*playESCP=false;
					//Gsnd->SEngine->stopAllSounds();
					timeTotal=0;
				}


			}
		}
	}

};
class GGI2: public GGI
{
public:
GGI2(IrrlichtDevice*Dev,MyEventReceiver*EvenRec,CGameSounds*GSnd,CWeapon*Weop,int Gnum,bool*playEscp)
	{
	winShowIndx=0;
	QRchick=0;
	ShowWin=false;
	playESCP=playEscp;
	StartgameFade=true;
	Gsnd=GSnd;
	winindx=overindex=Redindex=0;
	Device=Dev;
	recover=EvenRec;
	smanger=Dev->getSceneManager();
	W=Weop;
	Wnumber=Gnum;
	driv =smanger->getVideoDriver();
	showStopInterface=gover=ShowZoomImage=false;
	guienvir=smanger->getGUIEnvironment();
	GunFocus=guienvir->addImage(smanger->getVideoDriver()->getTexture(W->weap[Wnumber].GfocusGunpath),W->weap[Wnumber].GfocusGunpost,true);
	GunFocus->setScaleImage(true);
//--------------------------------------------------------------------------------------
	Dev->getFileSystem()->addZipFileArchive("data/weap.pk3");
	ZoomImage=guienvir->addImage(smanger->getVideoDriver()->getTexture("zoomImage.png"),core::position2d<s32>(0,0),true);
	ZoomImage->setScaleImage(true);
	ZoomImage->setRelativePosition(core::rect<s32>(0,0,800,600));
	ZoomImage->setVisible(true);
	//-----------------------------------Add ggui.pk3------------------------------	
	Dev->getFileSystem()->addZipFileArchive("data/ggui.pk3");
	//---------------------------------------------------------------------
	TxureNambers=driv->getTexture("number.bmp");
	driv->makeColorKeyTexture(TxureNambers, core::position2d<s32>(0,0));
//----------------------------------Butten data---------------------------------------------------
	back_B=new Game_Butten(Device,"Bback.png",core::position2d<s32>(300,200));
	rest_B=new Game_Butten(Device,"BrestGame.PNG",core::position2d<s32>(300,240));
	control_B=new Game_Butten(Device,"Bcontrol.png",core::position2d<s32>(300,280));
	Abrout_B=new Game_Butten(Device,"Bext.png",core::position2d<s32>(300,320));

	Byes=new Game_Butten(Device,"yes.png",core::position2d<s32>(300,350));
	Bno=new Game_Butten(Device,"no.png",core::position2d<s32>(500,350));
//-----------------------font-------------------------------------------------------
Enfont=Dev->getGUIEnvironment()->getFont("Fonts/EngFont1.bmp");

arabF= new ArabicFont(Dev,"Fonts/Arabfont.bmp");
//--------------------------------------------------------------------------------
	numRect[0]=core::rect<s32>(324,0,346,49);
	numRect[1]=core::rect<s32>(290,0,311,49);
	numRect[2]=core::rect<s32>(255,0,276,49);
	numRect[3]=core::rect<s32>(221,0,242,49);
	numRect[4]=core::rect<s32>(186,0,207,49);
	numRect[5]=core::rect<s32>(151,0,172,49);
	numRect[6]=core::rect<s32>(117,0,138,49);
	numRect[7]=core::rect<s32>(82,0,103,49);
	numRect[8]=core::rect<s32>(48,0,69,49);
	numRect[9]=core::rect<s32>(13,0,34,49);
	
	}
bool START_LEVEL_SHOW(float frmeTime)
	{
		static bool plySnd=true;
		if(plySnd)
		{
		Gsnd->SEngine->stopAllSounds();
		plySnd=false;
		}
	
		driv->draw2DRectangle(video::SColor(255,0,0,0),core::rect<s32>(0,0,800,600));
		driv->draw2DRectangle(video::SColor(255,20,20,20),core::rect<s32>(0,200,800,400));
		driv->draw2DRectangle(video::SColor(100,40,90,30),core::rect<s32>(700,0,730,600));
		
		 int txt0[14]={10,75,30,85,113,70,30,33,6,77,113,86,19,30};//ÊÞÏã ÝÏÑÈß ãÌÏ
		 arabF->DrowText(14,txt0,core::position2d<s32>(695,50),video::SColor(255,0,255,0));

		int txt6[12]={86,95,87,114,113,10,30,33,100,6,101,114};
		arabF->DrowText(12,txt6,core::position2d<s32>(450,290),video::SColor(255,255,255,255));

		int txt7[13]={94,84,113,1,90,12,113,18,3,94,112,112,36};
		arabF->DrowText(13,txt7,core::position2d<s32>(450,490),video::SColor(255,255,255,255));
		
		int txt8[10]={0,50,67,55,113,86,39,55,34,116};
		arabF->DrowText(10,txt8,core::position2d<s32>(450,530),video::SColor(30,255,255,255));
		
		if(recover->IsKeyDown(irr::KEY_SPACE))
		{
			StartgameFade=true;
			plySnd=true;
			return false;
		}

		/*if(timetot>5.0f)
		{
			timetot=0;
			StartgameFade=true;
			return false;
		}
		*/
		
		return true;
	}



void DrowWinning(float Frmtimeell)
	{
		if(ShowWin)
		{
		static float timeTotal=0;
		float frameDeltaTime=Frmtimeell;
		
		if(winindx<254)
		winindx++;
		driv->draw2DRectangle(video::SColor(winindx,0,0,0),core::rect<s32>(0,0,800,600));
	

			if(winindx>250)
			{

				if(winShowIndx==0)
				{
					
					driv->draw2DRectangle(video::SColor(130,30,20,40),core::rect<s32>(0,100,800,500));					
					
					int txt[29]={112,113,112,113,112,113,10,87,12,113,0,82,87,95,87,114,113,6,91,19,3,21,113,112,113,112,113,112,113};
					 arabF->DrowText(29,txt,core::position2d<s32>(500,300),video::SColor(255,255,255,255));
					
					 int txt1[14]={10,75,30,85,113,70,30,33,6,77,113,86,19,30};
					 arabF->DrowText(14,txt1,core::position2d<s32>(470,340),video::SColor(255,0,255,0));

					 timeTotal+=frameDeltaTime;
					if (timeTotal>10.0f)
					{
						winShowIndx=1;
						 
					}

				
				}
				else
				{
				//ÚäÏ äåÇíÉ ÚÑÖ ÇáÝæÒ ÇÙåÑ ÝÇÝÐÉ ÇáÇÓßÈ ÝæáÓÊ åäÇ íÚäí ÊÑæÇ
					Device->getCursorControl()->setVisible(true);
					*playESCP=false;
					//Gsnd->SEngine->stopAllSounds();
					timeTotal=0;
				}




			}
		}
	}

};
class GGI3: public GGI
{
public:
GGI3(IrrlichtDevice*Dev,MyEventReceiver*EvenRec,CGameSounds*GSnd,CWeapon*Weop,int Gnum,bool*playEscp)
	{
	winShowIndx=0;
	QRchick=0;
	ShowWin=false;
	StartgameFade=true;
	playESCP=playEscp;
	Gsnd=GSnd;
	winindx=overindex=Redindex=0;
	Device=Dev;
	recover=EvenRec;
	smanger=Dev->getSceneManager();
	W=Weop;
	Wnumber=Gnum;
	driv =smanger->getVideoDriver();
	showStopInterface=gover=ShowZoomImage=false;
	guienvir=smanger->getGUIEnvironment();
	GunFocus=guienvir->addImage(smanger->getVideoDriver()->getTexture(W->weap[Wnumber].GfocusGunpath),W->weap[Wnumber].GfocusGunpost,true);
	GunFocus->setScaleImage(true);
//--------------------------------------------------------------------------------------
	Dev->getFileSystem()->addZipFileArchive("data/weap.pk3");
	ZoomImage=guienvir->addImage(smanger->getVideoDriver()->getTexture("zoomImage.png"),core::position2d<s32>(0,0),true);
	ZoomImage->setScaleImage(true);
	ZoomImage->setRelativePosition(core::rect<s32>(0,0,800,600));
	ZoomImage->setVisible(true);
	//-----------------------------------Add ggui.pk3------------------------------	
	Dev->getFileSystem()->addZipFileArchive("data/ggui.pk3");
	//---------------------------------------------------------------------
	TxureNambers=driv->getTexture("number.bmp");
	driv->makeColorKeyTexture(TxureNambers, core::position2d<s32>(0,0));
//----------------------------------Butten data---------------------------------------------------
	back_B=new Game_Butten(Device,"Bback.png",core::position2d<s32>(300,200));
	rest_B=new Game_Butten(Device,"BrestGame.PNG",core::position2d<s32>(300,240));
	control_B=new Game_Butten(Device,"Bcontrol.png",core::position2d<s32>(300,280));
	Abrout_B=new Game_Butten(Device,"Bext.png",core::position2d<s32>(300,320));

	Byes=new Game_Butten(Device,"yes.png",core::position2d<s32>(300,350));
	Bno=new Game_Butten(Device,"no.png",core::position2d<s32>(500,350));
//-----------------------font-------------------------------------------------------
Enfont=Dev->getGUIEnvironment()->getFont("Fonts/EngFont1.bmp");

arabF= new ArabicFont(Dev,"Fonts/Arabfont.bmp");
//--------------------------------------------------------------------------------
	numRect[0]=core::rect<s32>(324,0,346,49);
	numRect[1]=core::rect<s32>(290,0,311,49);
	numRect[2]=core::rect<s32>(255,0,276,49);
	numRect[3]=core::rect<s32>(221,0,242,49);
	numRect[4]=core::rect<s32>(186,0,207,49);
	numRect[5]=core::rect<s32>(151,0,172,49);
	numRect[6]=core::rect<s32>(117,0,138,49);
	numRect[7]=core::rect<s32>(82,0,103,49);
	numRect[8]=core::rect<s32>(48,0,69,49);
	numRect[9]=core::rect<s32>(13,0,34,49);
	
	}
bool START_LEVEL_SHOW(float frmeTime)
	{
		static bool plySnd=true;
		if(plySnd)
		{
		Gsnd->SEngine->stopAllSounds();
		plySnd=false;
		}
	
		driv->draw2DRectangle(video::SColor(255,0,0,0),core::rect<s32>(0,0,800,600));
		driv->draw2DRectangle(video::SColor(255,10,10,10),core::rect<s32>(0,200,800,400));
		driv->draw2DRectangle(video::SColor(100,40,90,30),core::rect<s32>(700,0,730,600));

		 int txt0[14]={10,75,30,85,113,70,30,33,6,77,113,86,19,30};//ÊÞÏã ÝÏÑÈß ãÌÏ
		 arabF->DrowText(14,txt0,core::position2d<s32>(695,50),video::SColor(255,0,255,0));

		int txt6[12]={86,95,87,114,113,10,19,34,100,7,101,114};
		arabF->DrowText(12,txt6,core::position2d<s32>(450,290),video::SColor(255,255,255,255));

		int txt7[13]={94,84,113,1,90,12,113,18,3,94,112,112,36};
		arabF->DrowText(13,txt7,core::position2d<s32>(450,490),video::SColor(255,255,255,255));
		
		int txt8[10]={0,50,67,55,113,86,39,55,34,116};
		arabF->DrowText(10,txt8,core::position2d<s32>(450,530),video::SColor(30,255,255,255));
		
		if(recover->IsKeyDown(irr::KEY_SPACE))
		{
			StartgameFade=true;
			plySnd=true;
			return false;
		}

		/*if(timetot>5.0f)
		{
			timetot=0;
			StartgameFade=true;
			return false;
		}
		*/
		
		return true;
	}



void DrowWinning(float Frmtimeell)
	{
		if(ShowWin)
		{
		static float timeTotal=0;
		float frameDeltaTime=Frmtimeell;
			
		if(winindx<254)
		winindx++;

		driv->draw2DRectangle(video::SColor(winindx,0,0,0),core::rect<s32>(0,0,800,600));
	
			if(winindx>250)
			{

				if(	winShowIndx==0)
				{
					 int txt[29]={112,113,112,113,112,113,10,87,12,113,0,82,87,95,87,114,113,6,91,19,3,21,113,112,113,112,113,112,113};
					 arabF->DrowText(29,txt,core::position2d<s32>(500,300),video::SColor(255,255,255,255));
					timeTotal+=frameDeltaTime;
					if (timeTotal>12.0f)
					{
						winShowIndx=1;
						timeTotal=0;
					}
				
				}
				else if (winShowIndx==1)
				{
				 int txt[31]={97,62,3,29,113,0,83,86,19,3,94,30,104,92,113,117,82,2,113,74,98,0,62,30,94,88,113,6,39,111,88};
				 arabF->DrowText(31,txt,core::position2d<s32>(520,300),video::SColor(255,255,255,255));
					
					timeTotal+=frameDeltaTime;
					if (timeTotal>5.0f)
					{
						winShowIndx=2;
						timeTotal=0;
					}
				}
				else if (winShowIndx==2)
				{
				 int txt[60]={0,82,19,101,44,113,0,108,38,34,0,115,101,83,102,113,100,63,11,34,69,113,6,87,75,11,84,113,0,82,63,43,34,0,9,113,86,92,113,18,91,98,29,93,113,97,100,11,98,62,30,113,6,34,29,113,62,91,101,72};
				 arabF->DrowText(60,txt,core::position2d<s32>(700,300),video::SColor(255,255,255,255));
					
					timeTotal+=frameDeltaTime;
					if (timeTotal>5.0f)
					{
						winShowIndx=3;
						timeTotal=0;
					}
				}
				else if (winShowIndx==3)
				{
				 int txt[17]={0,66,111,73,113,18,87,101,64,113,0,82,87,63,3,6,34};
				 arabF->DrowText(17,txt,core::position2d<s32>(500,300),video::SColor(255,255,255,255));
					
					timeTotal+=frameDeltaTime;
					if (timeTotal>5.0f)
					{
						winShowIndx=4;
						timeTotal=0;
					}
				}
				else if (winShowIndx==4)
				{
				 int txt[30]={54,3,115,34,0,9,113,1,108,38,11,55,111,61,113,10,87,110,113,38,87,3,104,113,0,82,75,55,3,61};
				 arabF->DrowText(30,txt,core::position2d<s32>(550,300),video::SColor(255,255,255,255));
					
					timeTotal+=frameDeltaTime;
					if (timeTotal>5.0f)
					{
						winShowIndx=5;
						timeTotal=0;
					}
				}
				else if (winShowIndx==5)
				{
				 int txt[24]={0,82,87,91,55,75,114,113,86,75,7,83,114,113,62,83,2,113,0,18,11,101,3,21};
				 arabF->DrowText(24,txt,core::position2d<s32>(510,300),video::SColor(255,255,255,255));
					
					timeTotal+=frameDeltaTime;
					if (timeTotal>5.0f)
					{
						winShowIndx=6;
						timeTotal=0;
					}
				}
				else if (winShowIndx==6)
				{
				 int txt[12]={94,84,113,1,90,12,113,86,39,11,63,30};
				 arabF->DrowText(12,txt,core::position2d<s32>(510,300),video::SColor(255,255,255,255));
					
					timeTotal+=frameDeltaTime;
					if (timeTotal>7.0f)
					{
						winShowIndx=7;
						timeTotal=0;
					}
				}
				else if (winShowIndx==7)
				{	
					Device->getCursorControl()->setVisible(true);			
					//ÚäÏ äåÇíÉ ÚÑÖ ÇáÝæÒ ÇÙåÑ ÝÇÝÐÉ ÇáÇÓßÈ ÝæáÓÊ åäÇ íÚäí ÊÑæÇ
					*playESCP=false;
					//Gsnd->SEngine->stopAllSounds();
					timeTotal=0;
				}

			}
		}
	}

};
#endif