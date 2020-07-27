/*
writen by (Younes khafaja) - 2008-2009
You are free to use this code as you see fit
email : lighting-team@hotmail.com
*/
#ifndef GAMEAPP_H
#define GAMEAPP_H

#include"Cplayer.h"
#include"EvenReciver.h"
#include "StartGInterface.h"
#include"CLevels.h"
#include"GameGuiInterface.h"
#include"Csounds.h"
using namespace irr;

#include <irrKlang.h>
using namespace irrklang;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#ifdef _IRR_WINDOWS_
#pragma comment (lib, "irrKlang.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

struct locationData
{
	core::vector3df post;
	core::vector3df rout;
};

class gameApp
{
private:

	int LevelNumber;
	MyEventReceiver receiver;
	IrrlichtDevice *device ;
	ISoundEngine* Sndengine;
	video::IVideoDriver* driver ;
	scene::ISceneManager* smgr;
	gui::IGUIEnvironment*Guienviro;

	CLevels*LVL;
	Cplayer *player;
	gameInterface*starshow;
	GGI*ggi;
	CGameSounds*Gsnd;
	locationData PLyrLoction;
	bool PlayGame,PassFirstInterface,Startlvlshow,showTeamlogo;
public:
	gameApp()
	{
	showTeamlogo=true;
	PlayGame=true;
	PassFirstInterface=true;
	Startlvlshow=true;

			irr::SIrrlichtCreationParameters param;
			param.AntiAlias=false;
			param.EventReceiver=&receiver;
			param.Fullscreen=1;
			param.WindowSize=core::dimension2d<s32>(800,600);
			param.DriverType = video::EDT_DIRECT3D9;

			 device = createDeviceEx(param);

	//device =createDevice(video::EDT_DIRECT3D9, core::dimension2d<s32>(800,600),32,0, false ,true,&receiver);
	Sndengine = createIrrKlangDevice();
	device->getCursorControl()->setVisible(false);
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	Guienviro=device->getGUIEnvironment();
	driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS,true);
	driver->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT,true);

	//driver->setTextureCreationFlag( video::ETCF_ALWAYS_32_BIT, true );
	}
	//************************
	bool runGame()
		{

			while(1)
			{
				Gsnd=new CGameSounds(Sndengine);
				//ÇÐÇ ÇÚÇÏÉ ÇááÚÈÉ áÇ íÏÎá åÐÇ ÇáßæÏ
				if(PassFirstInterface)
				{
					starshow=new gameInterface(device,&receiver,showTeamlogo,Gsnd);//bulid start interface
					showTeamlogo=false;
					if (starshow->ExitGame())
					return 0;
					LevelNumber=starshow->getLevelNumber();
				}
					device->getCursorControl()->setVisible(false);

					//*****************select level***********************************
					if(LevelNumber==1)
					LVL=new CLevels_1(device);
					if(LevelNumber==2)
					LVL=new CLevels_2(device);
					if(LevelNumber==3)
					LVL=new CLevels_3(device);
					//*******************Select ggi*********************************
					if(LevelNumber==1)

					ggi=new GGI1(device,&receiver,Gsnd,LVL->getWeopon(),LVL->getStartWeopNum(),&PlayGame/*to stop game when winning*/);
					if(LevelNumber==2)
					ggi=new GGI2(device,&receiver,Gsnd,LVL->getWeopon(),LVL->getStartWeopNum(),&PlayGame);
					if(LevelNumber==3)
					ggi=new GGI3(device,&receiver,Gsnd,LVL->getWeopon(),LVL->getStartWeopNum(),&PlayGame);
					//*************************************************************

					player=new Cplayer(device,Sndengine,LVL->getStartWeopNum(),LVL->getWeopon(),LVL->getStartPlyrPoint(),LVL->getStartPlyrRout(),LVL->getcollMselector(),LVL->getshootMselector(),ggi,&receiver,LevelNumber);


					Startlvlshow=true;
				//main game loop
					bool restGame=mainGameLoop();

					if(restGame)
					{
					restCurrentLevel();
					}
					else
					{
					ouitCurrentLevel();
					}

			}

			//Exit Game
			ShutDown();
			return 0;
		}




	//************************
	void ouitCurrentLevel()
	{


		smgr->clear();
		Guienviro->clear();
		Sndengine->removeAllSoundSources();
		driver->removeAllHardwareBuffers();
		driver->removeAllTextures();
		deleteALLGameClass();

			device->drop();
			device=0;
			Sndengine->drop();
			Sndengine=0;

			irr::SIrrlichtCreationParameters param;
			param.AntiAlias=false;
			param.EventReceiver=&receiver;
			param.Fullscreen=1;
			param.WindowSize=core::dimension2d<s32>(800,600);
			param.DriverType = video::EDT_DIRECT3D9;
			device = createDeviceEx(param);

			Sndengine = createIrrKlangDevice();

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	Guienviro=device->getGUIEnvironment();
	driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS,true);


		StopGAme(false);

		PassFirstInterface=true;

	}
	void restCurrentLevel()
	{
		smgr->clear();
		deleteALLGameClass();
		Sndengine->removeAllSoundSources();
		PassFirstInterface=false;
		StopGAme(false);
		device->sleep(150);

	}
	void deleteALLGameClass()
		{

			//starshow->_Destructor();

			LVL->_Destructor();
			ggi->_Destructor();
			player->_Destructor();
					delete starshow;
					starshow=0;
					delete LVL;
					LVL=0;
					delete player;
					delete Gsnd;
					Gsnd=0;
					player=0;
					//delete ggi;
					//ggi=0;
		}


	bool mainGameLoop()
	{
	u32 then = device->getTimer()->getTime();


		while(device->run())
		{
			if(device->isWindowActive())
			{
						const float fps = driver->getFPS();
						const u32 now = device->getTimer()->getTime();
						const f32 frameDeltaTime = (f32)(now - then) / 1000.f;// Time in seconds
						then = now;



					if(Startlvlshow)
					{

						driver->beginScene(false, true, 0);
						Startlvlshow=ggi->START_LEVEL_SHOW(frameDeltaTime);
						driver->endScene();

					}else
					{

							if (PlayGame)
							{

									player->PlayerRnder(frameDeltaTime);
									driver->beginScene(true, true, 0);
									//********************************************************

									smgr->drawAll();
									ggi->GuiInterfaceRender(player->getBlood(),frameDeltaTime);
									player->DrowRendering();//is not use currently

									//********************************************************
									driver->endScene();


							}
							else
							{
								driver->beginScene(false, true, 0);
								int PrseeNum=ggi->DrowStopGameInterFace();
								driver->endScene();

								if(PrseeNum==1)//prses back
								{
									StopGAme(false);
									player->setRotation(PLyrLoction.rout);
									device->sleep(150);
								}
								else if(PrseeNum==2)//prsee rest
								{
									return true;//
									break;
								}
								else if(PrseeNum==3)//prsee exit
								{
									return false;
									break;
								}
							}
					}


				prseeEscape();


				/*wchar_t tmp[1024];
				swprintf(tmp, 1024, L"x:%f Z:%f fps:%f",player->getcamera2Posttion().X,player->getcamera2Posttion().Z,fps);
				device->setWindowCaption(tmp);
				*/
			device->setWindowCaption(L"The Glory Road");
			}
			else
			device->yield();
		}




	}
	void prseeEscape()
	{
		static bool ent=true;
		if(receiver.IsKeyDown(irr::KEY_ESCAPE))
		{
			if (ent)
			{
				if (Startlvlshow)
				Startlvlshow=false;
				else
				{
					if (PlayGame==true)
					{
					StopGAme(true);
					//PLyrLoction.post=player->getPosttion();
					PLyrLoction.rout=player->getRoution();
					}
					else
					{
					StopGAme(false);


					//player->setPostion(PLyrLoction.post);
					player->setRotation(PLyrLoction.rout);
					}
				}

			ent=false;
			}
		}
		else
		ent=true;


		//change camera
		/*if(receiver.IsKeyDown(irr::KEY_F3))
		player->useFreeCamera(true);
		else if(receiver.IsKeyDown(irr::KEY_F4))
		player->useFreeCamera(false);
		*/

	}
	void StopGAme(bool stop)
	{
		if(stop)
		{
			PlayGame=false;
			device->getCursorControl()->setVisible(true);
		}
		else
		{
			//if(ggi->getChick()==0)
		//	{
				PlayGame=true;
				device->getCursorControl()->setVisible(false);
				//ggi->backTomain();
			//}
			//else
			//
		}


	}

	void ShutDown()
	{
	device->closeDevice();
	device->drop();
	device=0;

	}
};


#endif
