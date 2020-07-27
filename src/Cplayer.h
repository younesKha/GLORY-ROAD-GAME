/*
writen by (Younes khafaja) - 2008-2009
You are free to use this code as you see fit
email : lighting-team@hotmail.com
*/
#include <irrlicht.h>
#include"EvenReciver.h"
#include"myShotNode.h"
#include"CWeapon.h"
#include"Functions.h"
#include"GameGuiInterface.h"
#include"CSoldierManger.h"
#include <irrKlang.h>

#include"Csounds.h"

using namespace irrklang;
using namespace irr;
#ifndef PLY_H
#define PLY_H

class Cplayer
{
private:
		IrrlichtDevice *Devic;
		ISoundEngine* SEngine;

		CPlayerSounds *snd;
		scene::ICameraSceneNode*camera;
		scene::ICameraSceneNode*camera2;
		scene::ISceneNodeAnimator* cameraAnimator ;

		scene::ISceneManager* smanger;
		scene::ISceneNode* fire_shoot;

		scene::ISceneNodeAnimatorCollisionResponse*camColl;//camera colliton setting
		scene::ITriangleSelector*shootMSeletor;
		scene::IMetaTriangleSelector*Mselector;
		scene::IParticleSystemSceneNode*ps;
		scene::ISceneNode* CamTrgNd;//ãÞØÉ ÇãÇã ÇáßÇãíÑÇ ÍÊì ÊÌÚáì ÇáÓáÇÍ íÏæÑ áÃÚáì ÈÇäÊÙÇã ÚäÏ ÇáÅØáÇÞ

		irrklang::ISoundSource*shootSound;
		irrklang::ISoundSource*ChangeStorgeSound;
		irrklang::ISoundSource*FullStorgeSound;

		video::ITexture*PatclBlood,*PatclStoon,*PatclSmok,*Patclwall,*Patcliron;
		video::ITexture*shootCollWall,*shootCollIron;
		scene::IParticleEmitter*em;
		scene::IParticleEmitter*em2;


		CWeapon*Pweop;
		MyEventReceiver*EvenReciver;
		GGI*ggi;
		int CWN;//current weopon number
		scene::IAnimatedMeshSceneNode*gun;
		scene::IAnimatedMesh *MeshGuns[5];


		int Plyrblood;
		bool isGun,isBomb,isRBJ;
		bool PlayGame,braekLoop,stopPlaying;
		bool G1,G2,G3,G4;
		bool RoutCamUp;//ÏæÑÇä ÇáßÇãíÑÇ áÃÚáì ÚäÏ ÇáÅØáÇÞ

		Functins func;
		CSoldierManger*sdrsMgr;

		SKeyMap keyMap[9];

		scene::ISceneCollisionManager*scollmgr;


public:
Cplayer(IrrlichtDevice *device,ISoundEngine* Sndengine,int StartGun,CWeapon*Pw,core::vector3df startPostion,core::vector3df StartPlyrRout
		,scene::IMetaTriangleSelector*mselector
		,scene::IMetaTriangleSelector*lvlSelector,GGI*Ggi,MyEventReceiver *receiver,int lvlNumber)
	{
		Plyrblood=100;
		CWN=StartGun;
		PlayGame=true;
		isGun=true;
		isBomb=false;
		isRBJ=false;
		braekLoop=false;
		RoutCamUp=false;
		stopPlaying=false;

		Pweop=Pw;
		ggi=Ggi;
		G1=G2=G3=G4=true;
		EvenReciver=receiver;
		Devic=device;
		SEngine=Sndengine;
		smanger=device->getSceneManager();
		Mselector=mselector;
		shootMSeletor=lvlSelector;

		video::IVideoDriver* driver =device->getVideoDriver();
		ps =smanger->addParticleSystemSceneNode(false);
		//--------------------Play sound object-----------------
		snd=new CPlayerSounds(Sndengine);
		//--------------------------------------------------------
		keyMap[1].Action = EKA_MOVE_FORWARD;
		keyMap[1].KeyCode = KEY_KEY_W;
		keyMap[3].Action = EKA_MOVE_BACKWARD;
		keyMap[3].KeyCode = KEY_KEY_S;
		keyMap[5].Action = EKA_STRAFE_LEFT;
		keyMap[5].KeyCode = KEY_KEY_A;
		keyMap[7].Action = EKA_STRAFE_RIGHT;
		keyMap[7].KeyCode = KEY_KEY_D;
		keyMap[8].Action = EKA_JUMP_UP;
		keyMap[8].KeyCode = KEY_SPACE;

	//----------------------------------------------------------------
	camera2 = smanger->addCameraSceneNodeFPS(0,200.0,1.3f);
	camera2->setPosition(startPostion); //1st=pos in x-2nd value= spawn height-3rd=pos in y
	camera2->setFarValue (50000.0f); //sets the distance for the clipping plane, the bigger the farther
	camera2->setFOV(core::degToRad(60.0f)); // a value of 0.5 makes it look alienish
	//camera->setTarget( core::vector3df(0,0,-1)); //target camera position-3rd value negative =90, positive=0 -1st value (-) rotates camera
	camera2->setRotation(core::vector3df(0,180,0)); //rotate the camera x,y,z degrees
	camera2->setAspectRatio(4/3);

	camera = smanger->addCameraSceneNodeFPS(0,80.0,0.4f,-1, keyMap,9,true,10); //1st value= obligatory 0-2nd value= mouse sensitivity-3rd value handles cam speed
	camera->setPosition(startPostion); //1st=pos in x-2nd value= spawn height-3rd=pos in y
	camera->setNearValue(5);
	camera->setFarValue (10000.0f); //sets the distance for the clipping plane, the bigger the farther
	camera->setFOV(core::degToRad(60.0f)); // a value of 0.5 makes it look alienish
	camera->setRotation(StartPlyrRout);
	camera->setAspectRatio(4/3);

	//--------------------------------------------------------------
	CamTrgNd=smanger->addEmptySceneNode(camera,-1);
	CamTrgNd->setPosition(core::vector3df(0,0,100));
	//-----------------------------------------------------------------
	//camera collisin

	cameraAnimator =camColl= smanger->createCollisionResponseAnimator(Mselector, camera,core::vector3df(30,60,30),core::vector3df(0,-50,0),
														core::vector3df(0,70,0));
	camera->addAnimator(cameraAnimator);
	//cameraAnimator->drop();
	//cameraAnimator=0;
	//----------------------------GUN DATA------------------------------------------------------------------
	UploadPlyerGuns();
	//--------------------------CollisionManager-----------------------------------
	scollmgr=smanger->getSceneCollisionManager();
	//-----------------------SOUND----------------------------------------
	shootSound=SEngine->addSoundSourceFromFile(Pweop->weap[CWN].GshotSoundp);
	ChangeStorgeSound=SEngine->addSoundSourceFromFile(Pweop->weap[CWN].GchangeStorgeSound);
	FullStorgeSound=SEngine->addSoundSourceFromFile("sounds/NoShoot.wav");

//-----------------------------------------------------------------------
	fire_shoot = smanger->addBillboardSceneNode(gun,core::dimension2d<f32>(20,20),Pweop->weap[CWN].GfirePost,-1);
	fire_shoot->setMaterialFlag(video::EMF_LIGHTING, false);
	fire_shoot->setMaterialTexture(0,driver->getTexture(Pweop->weap[CWN].GfireTexturePath));
	fire_shoot->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	fire_shoot->setVisible(false);
	//------------------------------------------------------------------------------------------
	Devic->getFileSystem()->addZipFileArchive("data/weap.pk3");
	//-------------------------------ShootCollision----------------------------------------------------------------
	shootCollWall=driver->getTexture("wallshot.png");
	shootCollIron=driver->getTexture("ironshot.png");
	//===========================================================================================================
	if(lvlNumber==1)
	sdrsMgr=new CSoldierManger_1(device,SEngine,Mselector,shootMSeletor,Plyrblood,ggi);

	if(lvlNumber==2)
	sdrsMgr=new CSoldierManger_2(device,SEngine,Mselector,shootMSeletor,Plyrblood,ggi);
	if(lvlNumber==3)
	sdrsMgr=new CSoldierManger_3(device,SEngine,Mselector,shootMSeletor,Plyrblood,ggi);
	//===========================================================================================================

	shotPartical();

	}
	~Cplayer()
	{
	//	delete camera;
	//	delete gun;
	//	camera->remove();
	//	gun->remove();

	}

//---------------------------------------------------------------------------
void UploadPlyerGuns()
{
	for(int s=0;s<5;s++)
	{
		if(Pweop->weap[s].GP_isHold)
		MeshGuns[s]=smanger->getMesh(Pweop->weap[s].Gpath);
	}
	gun =smanger->addAnimatedMeshSceneNode(MeshGuns[CWN],camera);
	gun->setPosition(Pweop->weap[CWN].Gpostion);
	gun->setFrameLoop(0,0);

	//video::SMaterial material;
   // material.setTexture(0, driver->getTexture(Pweop->weap[CWN].GTexturePath));
   // material.Lighting = true;
	//material.ZBuffer=true;
	//gun->getMaterial(0)=material;

	gun->setMaterialFlag(video::EMF_LIGHTING, false);
	gun->setRotation(Pweop->weap[CWN].Groution);
	gun->setScale(core::vector3df(0.85,1.0f,0.85));


}
void PlayerRnder(float timeeilpse)//loop with out Drow
{
	if(!stopPlaying)
	{
		if (G1)
		ClickShot(timeeilpse);
		if (G2)
		ChangeSpare(timeeilpse);
		if (G3)
		ZoomGun(timeeilpse);
		if (G4)
		SwapGun(timeeilpse);
		//---------------------------------------------------
			static float tt=0;
			tt+=timeeilpse;
			if (tt>=0.05)
			{
			startShot();
			tt=0;
			if (gun->getFrameNr()==29)
			G1=G2=G3=G4=true;
			}
		//--------------------solderRender-------------------------
		sdrsMgr->RenderSolders(timeeilpse,camera->getAbsolutePosition(),shootMSeletor);
		//----------------------------------------------
		//chick if player take Dead solder weopon
		chickDSW();
		//chick if player take Health
		chickHEALTH();
		//chick win location
		chickWinLocation();
		//route gun up if shoot
		routGunUp(timeeilpse);
		//setdawn
		PlyrDown(timeeilpse);
		//change aytomatic-OFF/ON
		changeGunAutomatic();
		//player Dead
		playerDead();
	}
}
void changeGunAutomatic()
{
	static bool enter=false;
	if(EvenReciver->IsKeyDown(irr::KEY_KEY_Q))
	{

		if (CWN==2&&!enter)
		{
			if (Pweop->weap[CWN].GIsAutomatic==true)
			Pweop->weap[CWN].GIsAutomatic=false;
			else
			Pweop->weap[CWN].GIsAutomatic=true;
		}
	enter=true;
	}
	else
	enter=false;
}
void PlyrDown(float timeeilpse)
{
	static bool enter1=true;
	static bool enter2=false;
	static bool plyrUp=false;
	static int idx=0;
	if(EvenReciver->IsKeyDown(irr::KEY_CONTROL))
	{

		if(enter1)
		{
		//camColl->setEllipsoidRadius(core::vector3df(30,20,30));
		camColl->setEllipsoidTranslation(core::vector3df(0,10,0));
		enter1=false;
		enter2=true;
		}

	}
	else
	{
		if(enter2)
		{
			enter1=true;
			camColl->setGravity(core::vector3df(0,0,0));
			float ybost=camera->getAbsolutePosition().Y+5;
			camera->setPosition(core::vector3df(camera->getAbsolutePosition().X,ybost,camera->getAbsolutePosition().Z));
			idx++;
			if(idx==12)
			{
			plyrUp=true;
			enter2=false;
			idx=0;
			}
		}
	}

	if (plyrUp)
	{
	camColl->setEllipsoidTranslation(core::vector3df(0,70,0));
	camColl->setGravity(core::vector3df(0,-50,0));
	plyrUp=false;
	}

}
void SwapGun(float timeeilpse)
{
if(EvenReciver->isWheel())
{
	if(CWN==2)
	{
		if (Pweop->weap[3].GP_isHold)
		{
			SetGunData(3);
			ggi->setGunNumber(3);
			snd->PlaySwapWeopSound();
		}
		else if (Pweop->weap[4].GP_isHold)
		{
			SetGunData(4);
			ggi->setGunNumber(4);
			snd->PlaySwapWeopSound();
		}
	}
	else if(CWN==3)
	{
		if (Pweop->weap[4].GP_isHold)
		{
			SetGunData(4);
			ggi->setGunNumber(4);
			snd->PlaySwapWeopSound();
		}
		else if (Pweop->weap[2].GP_isHold)
		{
			SetGunData(2);
			ggi->setGunNumber(2);
			snd->PlaySwapWeopSound();
		}
	}
	else if(CWN==4)
	{
		if (Pweop->weap[2].GP_isHold)
		{
			SetGunData(2);
			ggi->setGunNumber(2);
			snd->PlaySwapWeopSound();
		}
		else if (Pweop->weap[3].GP_isHold)
		{
			SetGunData(3);
			ggi->setGunNumber(3);
			snd->PlaySwapWeopSound();
		}
	}
		EvenReciver->setWheelFALSE();
}


	if(EvenReciver->IsKeyDown(irr::KEY_KEY_3))
	{
		if (!(CWN==2))//áãäÚ ÊßÑÇÑ ÇÓÊÏÚÇÁ ÇáÓáÇÍ äÝÓå
		{
			if (Pweop->weap[2].GP_isHold)
			{
			SetGunData(2);
			ggi->setGunNumber(2);
			snd->PlaySwapWeopSound();
			}
		}
	}
	else if(EvenReciver->IsKeyDown(irr::KEY_KEY_4))
	{
		if (!(CWN==3))
		{
			if (Pweop->weap[3].GP_isHold)
			{
			SetGunData(3);
			ggi->setGunNumber(3);
			snd->PlaySwapWeopSound();
			}
		}
	}
	else if(EvenReciver->IsKeyDown(irr::KEY_KEY_5))
	{
		if (!(CWN==4))
		{
			if (Pweop->weap[4].GP_isHold)
			{
			SetGunData(4);
			ggi->setGunNumber(4);
			snd->PlaySwapWeopSound();
			}
		}
	}
}
void SetGunData(int GunNumber)
{
		CWN=GunNumber;
		video::IVideoDriver* driver =smanger->getVideoDriver();
		//scene::IAnimatedMesh*gunMesh=smanger->getMesh(Pweop->weap[CWN].Gpath);
		gun->setVisible(0);
		//gun->grab();
		//gun->drop();
		//gun=0;
		gun =smanger->addAnimatedMeshSceneNode(MeshGuns[CWN],camera);
		gun->setPosition(Pweop->weap[CWN].Gpostion);
		gun->setRotation(Pweop->weap[CWN].Groution);
		gun->setFrameLoop(0,0);
		gun->setAnimationSpeed(0);
		//gun->setMaterialTexture(0,driver->getTexture(Pweop->weap[CWN].GTexturePath));
		gun->setMaterialFlag(video::EMF_LIGHTING, false);

		//fire_shoot->grab();
		//fire_shoot->drop();
		//fire_shoot=0;
		fire_shoot = smanger->addBillboardSceneNode(gun,core::dimension2d<f32>(20,20),Pweop->weap[CWN].GfirePost);
		fire_shoot->setMaterialFlag(video::EMF_LIGHTING, false);
		fire_shoot->setMaterialTexture(0,driver->getTexture(Pweop->weap[CWN].GfireTexturePath));
		fire_shoot->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
		fire_shoot->setVisible(false);

		scene::ISceneNodeAnimator* anim =smanger->createFlyStraightAnimator(core::vector3df(0,-20,0),Pweop->weap[CWN].Gpostion,200,0);
		gun->addAnimator(anim);
		//gun->setScale(core::vector3df(0.85,1.0f,0.85));
		gun->setAnimationSpeed(30);
		anim->drop();
		anim=0;

}
void ZoomGun(float timeeilpse)
{
	static bool ft=true;
	if (Pweop->weap[CWN].GIsMakeZoom)
	{
		if(EvenReciver->isRMouseClick())
		{
		camera->setFOV(core::degToRad(Pweop->weap[CWN].GFOV));

			if(Pweop->weap[CWN].GNumber==2)
			{
			Pweop->weap[2].GshotRandom=core::position2di(-400,400);
			Pweop->weap[2].GIsAutomatic=false;
			}
			else if(Pweop->weap[CWN].GNumber==4)
			{
			ggi->setZoomvisible(true);
			}

		G2=G4=false;
		if(ft)
		{
		snd->PlayUseZoomSound();
		ft=false;
		}
		}
		else
		{
		G2=G4=true;
		ft=true;
		Pweop->weap[2].GshotRandom=core::position2di(-800,800);
		Pweop->weap[2].GIsAutomatic=true;
		camera->setFOV(core::degToRad(60.0f));
		ggi->setZoomvisible(false);
		}
	}

}
void ChangeSpare(float timeeilpse)
{
	if(EvenReciver->IsKeyDown(irr::KEY_KEY_R))
	{
		if (Pweop->weap[CWN].GP_TotalShotCount)
		{
			if((Pweop->weap[CWN].GP_ShotInStorgeCount<Pweop->weap[CWN].GstShotStorageCount)&&(Pweop->weap[CWN].GP_TotalShotCount))
			{
			G1=G2=G3=G4=false;
			gun->setFrameLoop(10,30);
			SEngine->play2D(Pweop->weap[CWN].GchangeStorgeSound);
			gun->setAnimationSpeed(Pweop->weap[CWN].GanimaitonSpeed);
			gun->setLoopMode(false);

			int sneed=Pweop->weap[CWN].GstShotStorageCount-Pweop->weap[CWN].GP_ShotInStorgeCount;
				if (sneed<=Pweop->weap[CWN].GP_TotalShotCount)
				{
				Pweop->weap[CWN].GP_TotalShotCount-=sneed;
				Pweop->weap[CWN].GP_ShotInStorgeCount+=sneed;
				}
				else
				{
				Pweop->weap[CWN].GP_ShotInStorgeCount+=Pweop->weap[CWN].GP_TotalShotCount;
				Pweop->weap[CWN].GP_TotalShotCount=0;
			}


			}
		}
	}

}
void ClickShot(float timeeilpse)
{
ShotFire(timeeilpse);
}

void routGunUp(float timeillp)
{
static bool enter2=false;
static int counter=0;
static int counter1=0;
static int upMoveSpeed=0;

	if (RoutCamUp)
	{
	upMoveSpeed=Pweop->weap[CWN].GRoutCamUpSpeed;
	RoutCamUp=false;
	enter2=true;
	}

	if(enter2==true)
	{
	int RCUS=upMoveSpeed;
	camera->setTarget(CamTrgNd->getAbsolutePosition()+core::vector3df(0,1,0)*timeillp*RCUS);

	if(upMoveSpeed>0)
	upMoveSpeed-=350*timeillp;
	else
	{
	upMoveSpeed=(Pweop->weap[CWN].GRoutCamUpSpeed*(-1))+counter1*timeillp;
	counter1+=350;
		if(upMoveSpeed>0)
		{
			enter2=false;
			counter1=0;
		}

	}

	//if(upMoveSpeed<(Pweop->weap[CWN].GRoutCamUpSpeed*(-1)))
	//enter2=false;
	}

}
void ShotFire(float timeeilpse)
{
static bool autmaic= true;
static float FrameTime=0;
static bool ss=true;

if(EvenReciver->isLMouseClick() && autmaic)
{
	if (Pweop->weap[CWN].GP_ShotInStorgeCount)
	{
			if(FrameTime==0)
			{
			scene::ISceneNodeAnimator* anim =smanger->createFlyStraightAnimator(Pweop->weap[CWN].GbackPostion,Pweop->weap[CWN].Gpostion,350,false);
			gun->addAnimator(anim);
			anim->drop();
			anim=0;

			fire_shoot->setVisible(true);
			Pweop->weap[CWN].GP_ShotInStorgeCount-=1;
			SEngine->play2D(Pweop->weap[CWN].GshotSoundp);
			ShotCollion();
			sdrsMgr->selectSldrHear(camera->getAbsolutePosition());//select the soldier hear player
			RoutCamUp=true;
			}

		FrameTime+=timeeilpse;
		if(FrameTime>=Pweop->weap[CWN].GTimeBetShot)
		FrameTime=0;
		autmaic=Pweop->weap[CWN].GIsAutomatic; //autmatic or not

	}
	else

		if (ss){
		SEngine->play2D(FullStorgeSound);
		ss=false;
		}
}


	if(!EvenReciver->isLMouseClick())
	{

	FrameTime=0;
	autmaic=true;
	ss=true;
	}

}
void ShotCollion()
{
	core::line3d<f32> line;
	core::vector3df CamNormlDir=(camera->getTarget()-camera->getAbsolutePosition()).normalize();

	line.start=camera->getAbsolutePosition() + CamNormlDir * 40.0f;
	line.end = camera->getAbsolutePosition() + CamNormlDir * 90000.0f;

	int xp=func.RandomRange(Pweop->weap[CWN].GshotRandom.X,Pweop->weap[CWN].GshotRandom.Y);
	line.end.X+=xp;
	line.end.Z+=xp;
	xp=func.RandomRange(Pweop->weap[CWN].GshotRandom.X,Pweop->weap[CWN].GshotRandom.Y);
	line.end.Y+=xp;

	core::vector3df intersection,intersection1;
	 core::triangle3df tri;
//-----------------------------------------------------------------------------------------------------//

			bool isSldrhit=false;
			 for(int i=0;i<sdrsMgr->ActveSldrs.size();i++)
			{
					int sdrNum=sdrsMgr->ActveSldrs[i];

					scene::IAnimatedMeshSceneNode*sn2=sdrsMgr->Sldrs[sdrNum]->getSoldernode();
					scene::IAnimatedMesh*msh=sdrsMgr->Sldrs[sdrNum]->getSolderMesh();
					//make solder slector
					scene::ITriangleSelector*ts=smanger->createTriangleSelector(msh,sn2);
					sn2->setTriangleSelector(ts);
					ts->drop();
					ts=0;
					//ÇÐÇ ÊÕÇÏã ãÚ ÇáÌäÏí æäÊÍÞÞ ÇÏÇ ßÇä ÇáÌäÏí ÎáÝ ÓÇÊÑ
					bool iscoll=scollmgr->getCollisionPoint(line,sn2->getTriangleSelector(),intersection1, tri);
					if (iscoll)
					  {
						// saTer ÇÐÇ ßÇä ÇáÌäÏí ãÎÊÈÃ ÎáÝ
						  if (scollmgr->getCollisionPoint(core::line3df(line.start,intersection1),shootMSeletor,intersection, tri))
						  {
										//*****set emiter
										ps->setEmitter(em);
										ps->setMaterialTexture(0, PatclStoon);
										//**************************//

									core::vector3df triNroml=tri.getNormal().normalize();
									video::IVideoDriver* driver =smanger->getVideoDriver();

									MyShotNode *shoteff =new MyShotNode(smanger->getRootSceneNode(), smanger,-1);

									shoteff->setMaterialTexture(0,shootCollWall);
									//shoteff->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);

									shoteff->setPosition(intersection+triNroml);

									if(triNroml.normalize()==core::vector3df(-1,0,0))
									shoteff->setRotation(core::vector3df(0,0,90));
									else if(triNroml.normalize()==core::vector3df(1,0,0))
									shoteff->setRotation(core::vector3df(0,0,-90));
									else if(triNroml.normalize()==core::vector3df(0,0,-1))
									shoteff->setRotation(core::vector3df(-90,0,0));
									else if(triNroml.normalize()==core::vector3df(0,0,1))
									shoteff->setRotation(core::vector3df(90,0,0));
									ps->setPosition(intersection);
								}
							    else//splder is hit
							    {
									//set Eimter
									ps->setEmitter(em2);
									ps->setMaterialTexture(0, PatclBlood );
									ps->setPosition(intersection1);
									sdrsMgr->setHitSolder(sdrNum,intersection1,i);
							    }
								isSldrhit=true;
							     break;
					}

				}

			 if(!isSldrhit)
			 {
				if (scollmgr->getCollisionPoint(line,shootMSeletor,intersection, tri))
				{
					core::line3d<f32> line2;
					line2.start=intersection+CamNormlDir*-1*20;
					line2.end=intersection+CamNormlDir*20;

					scene::ISceneNode*snhit=scollmgr->getSceneNodeFromRayBB(line2,0,false);
					//snhit->setVisible(false);
					if(snhit->getID()==500)//earth
					{
                        em->setDirection(core::vector3df(0.0f,0.2f,0.0f));
						ps->setEmitter(em);
						ps->setMaterialTexture(0, PatclSmok);
						ps->setPosition(intersection);

					}
					else if(snhit->getID()==501)//wall
					{
						core::vector3df triNroml=tri.getNormal().normalize();
						//*****set emiter
						ps->setEmitter(em);
						ps->setMaterialTexture(0, Patclwall);
						ps->setPosition(intersection);
						em->setDirection(triNroml*0.1);
						//**************************
						if(!(triNroml.Y>0.2))
						{
						MyShotNode *shoteff =new MyShotNode(smanger->getRootSceneNode(), smanger,-1);
						shoteff->setMaterialTexture(0,shootCollWall);
						shoteff->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
						shoteff->setPosition(intersection+triNroml);
						shoteff->setMaterialFlag(video::EMF_BACK_FACE_CULLING,false);

						core::vector3df shootDirect=getshootCollDirct(triNroml);
						shoteff->setRotation(shootDirect);
						}
					}
					else if(snhit->getID()==502)//iron
					{
						core::vector3df triNroml=tri.getNormal().normalize();
						//*****set emiter
						ps->setEmitter(em2);
						ps->setMaterialTexture(0, Patcliron);
						ps->setPosition(intersection);
						em->setDirection(triNroml*0.1);
						//****************************************************************************

						if(!(triNroml.Y>0.2))
						{
						MyShotNode *shoteff =new MyShotNode(smanger->getRootSceneNode(), smanger,-1);
						shoteff->setMaterialTexture(0,shootCollIron);
						shoteff->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
						shoteff->setPosition(intersection+triNroml);
						shoteff->setMaterialFlag(video::EMF_BACK_FACE_CULLING,false);

						core::vector3df shootDirect=getshootCollDirct(triNroml);
						shoteff->setRotation(shootDirect);
						}

					}

				}
			 }

 // }

}
core::vector3df getshootCollDirct(core::vector3df triNormal)
{

	//core::vector3df defultDir=core::vector3df(0,1,0);
	//core::vector3df dir;

float Xv=0,Yv=0,Zv=0;
core::vector2df newDirct;
core::vector2df DefuDir;
int x;
float angl;


	//-----------------------routation at X------------------------
/*
	newDirct=core::vector2df(triNormal.Z,triNormal.Y);
	 DefuDir=core::vector2df(1,0);
		x=1;

		if (newDirct.X<0)
		x=-1;

		 angl = acos(DefuDir.dotProduct(newDirct));
		angl=core::radToDeg(angl);
		Xv=x*angl;



	//-----------------------routation at Z------------------------
	 newDirct=core::vector2df(triNormal.X,triNormal.Y);
	 DefuDir=core::vector2df(0,1);

		angl = acos(DefuDir.dotProduct(newDirct));
		angl=core::radToDeg(angl);
		Zv=angl;
*/
	//-----------------------routation at Y------------------------
	 newDirct=core::vector2df(triNormal.X,triNormal.Z).normalize();
	 DefuDir=core::vector2df(0,1);

		x=1;
		if (newDirct.X<0)
		x=-1;

		 angl = acos(DefuDir.dotProduct(newDirct));
		angl=core::radToDeg(angl);
		Yv=x*angl;

		//--------------------------------------------------------


	return core::vector3df(Xv,Yv,Zv);
}
void startShot()//áÙåæÑ äÇÑ ÇáÅØáÇÞ ÈÔßá æÇÖÍ ÊÚãá åÐå Úáì Úãá ÊÃÎíÑ ÞÈá ÇÎÝÇÁ ÇáäÇÑ æßÐáß ÇáÔÙÇíÇ
{
static int enter=0;
	if (fire_shoot->isVisible()==true)
	{
	enter++;
		if (enter>=3){
		fire_shoot->setVisible(false);
//RoutGUp=false;
		ps->setPosition(core::vector3df(0,-200,0));
		}
	}
	else
	enter=0;
}
void shotPartical()//partical shot setting
{
video::IVideoDriver* driver =smanger->getVideoDriver();

PatclBlood=driver->getTexture("blood.png");
PatclStoon=driver->getTexture("stonCollion.png");
PatclSmok=driver->getTexture("arethShadaya.png");
Patclwall=driver->getTexture("wallShadaya.png");
Patcliron=driver->getTexture("ironShadaya.png");

	ps->setPosition(core::vector3df(0,0,0));
		//bsp collisn
		em = ps->createBoxEmitter(
		core::aabbox3d<f32>(-5,0,-5,5,1,5), // emitter size
		core::vector3df(0.0f,0.0f,0.2f),   // initial direction
		50,100,                             // emit rate
		video::SColor(255,255,255,255),       // darkest color
		video::SColor(255,255,255,255),       // brightest color
		1000,1500,5,                          // min and max age, angle
		core::dimension2df(1.0f,1.2f),        // min size
		core::dimension2df(3.0f,3.0f));       // max size

		//soldier colisn
		em2 = ps->createBoxEmitter(
		core::aabbox3d<f32>(-5,5,5,1,-1,1), // emitter size
		core::vector3df(0.0f,-0.1f,0.0f),   // initial direction
		50,80,                             // emit rate
		video::SColor(0,200,200,200),       // darkest color
		video::SColor(0,255,255,255),       // brightest color
		100,300,90,                         // min and max age, angle
		core::dimension2df(1.f,1.f),         // min size
		core::dimension2df(4.f,4.f));


	ps->setEmitter(em2); // this grabs the emitter
	ps->setID(104);
	//em->drop(); // so we can drop it here without deleting it

	scene::IParticleAffector* paf2 = ps->createGravityAffector(core::vector3df(0,-0.5f,0));
	ps->addAffector(paf2);
	paf2->drop();

	//scene::IParticleAffector* paf = ps->createFadeOutParticleAffector();
	//ps->addAffector(paf);
	//paf->drop();

	ps->setVisible(true);
	ps->setPosition(core::vector3df(0,-1000,0));
	ps->setScale(core::vector3df(1,1,1));
	ps->setMaterialFlag(video::EMF_LIGHTING, false);
	//ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
	ps->setMaterialTexture(0, PatclStoon);
	ps->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);

}

core::vector3df RoteToDir(core::vector3df p1,core::vector3df p2)
{
core::vector2df vec1,vec2;
float anglX,anglY,anglZ;
vec1.set(p1.Y,p1.Z);
vec2.set(p2.Y,p2.Z);
anglX=acos(vec1.X*vec2.X+vec1.Y*vec2.Y);
vec1.set(p1.X,p1.Z);
vec2.set(p2.X,p2.Z);
anglY=acos(vec1.X*vec2.X+vec1.Y*vec2.Y);
vec1.set(p1.X,p1.Y);
vec2.set(p2.X,p2.Y);
int x=-1;
if ((p2.X/sqrt(pow(p2.X,2)))==-1)
x=1;
anglZ=acos(vec1.X*vec2.X+vec1.Y*vec2.Y);

return core::vector3df(core::radToDeg(anglX),0,core::radToDeg(anglZ)*x);
  }

void chickDSW()//dead solder weoben
{
if (DSWArry.size())
{
	for(int i=0;i<DSWArry.size();i++)
	{
		core::position2df plyrPo;
		plyrPo.X=camera->getAbsolutePosition().X;
		plyrPo.Y=camera->getAbsolutePosition().Z;

		if(DSWArry[i].WeopPlace.isPointInside(plyrPo))
		{
			//if hold his weop
			if(Pweop->weap[DSWArry[i].weopType].GP_isHold)
			{


				if(Pweop->weap[DSWArry[i].weopType].GmaxShotCount>Pweop->weap[DSWArry[i].weopType].GP_TotalShotCount)
				{
					if(Pweop->weap[DSWArry[i].weopType].GP_TotalShotCount+DSWArry[i].ShootCount>Pweop->weap[DSWArry[i].weopType].GmaxShotCount)
					{
						Pweop->weap[DSWArry[i].weopType].GP_TotalShotCount=Pweop->weap[DSWArry[i].weopType].GmaxShotCount;
						DSWArry.erase(i);
						snd->PlaytakeWeopSound();
					}
					else
					{
						Pweop->weap[DSWArry[i].weopType].GP_TotalShotCount+=DSWArry[i].ShootCount;
						DSWArry.erase(i);
						snd->PlaytakeWeopSound();
					}
				}
			}
			else//if not hold add it
			{
				Pweop->weap[DSWArry[i].weopType].GP_isHold=true;
				Pweop->weap[DSWArry[i].weopType].GP_TotalShotCount+=DSWArry[i].ShootCount;
				//add gun mesh
				MeshGuns[DSWArry[i].weopType]=smanger->getMesh(Pweop->weap[DSWArry[i].weopType].Gpath);

				DSWArry.erase(i);
				snd->PlaytakeWeopSound();

			}
		}
	}
}
}
void chickWinLocation()
{
		core::position2df plyrPo;
		plyrPo.X=camera->getAbsolutePosition().X;
		plyrPo.Y=camera->getAbsolutePosition().Z;

		if(Winlocation.isPointInside(plyrPo))
		{
			snd->SEngine->stopAllSounds();
			snd->PlayWinMusicSound();
			stopPlaying=true;
			ggi->setWinning(true);
		}

}
void chickHEALTH()//dead solder weoben
{
if (HealthArry.size())
{
	for(int i=0;i<HealthArry.size();i++)
	{
		core::position2df plyrPo;
		plyrPo.X=camera->getAbsolutePosition().X;
		plyrPo.Y=camera->getAbsolutePosition().Z;

		if(HealthArry[i].HealthPlace.isPointInside(plyrPo))
		{

			scene::ISceneNode*sn=Devic->getSceneManager()->getSceneNodeFromId(HealthArry[i].snId);
			snd->PlayTakeKealthSound();
			sn->setVisible(false);
			Plyrblood+=HealthArry[i].healtCount;
			HealthArry.erase(i);
		}
	}
}
}




void DrowRendering()//loop drow render
{
//ggi->GuiInterfaceRender(Plyrblood);
sdrsMgr->RenderDrowSolders();

}
void playerDead()
{

	if (Plyrblood<=0)
	{
		if(!stopPlaying)
		{


			snd->SEngine->stopAllSounds();
			snd->PlayYouKilledSound();
			snd->PlayendMusicSound();

			camera2->setPosition(camera->getAbsolutePosition());
			camera2->setTarget(camera->getTarget());

			camera->setInputReceiverEnabled(false);
			camera->removeAnimators();


			camera2->setInputReceiverEnabled(false);

			smanger->setActiveCamera(camera2);


				core::vector3df downPost=core::vector3df(camera->getAbsolutePosition().X,camera->getAbsolutePosition().Y-60,camera->getAbsolutePosition().Z);
				scene::ISceneNodeAnimator* anim =smanger->createFlyStraightAnimator(camera->getAbsolutePosition(),downPost,300,false);
				camera2->addAnimator(anim);
				anim->drop();
				anim=0;

				stopPlaying=true;
				ggi->setGameOver(true);
				sdrsMgr->setSldrstopAttack();



		}
	}
}
void _Destructor()
{
sdrsMgr->_Destructor();
delete snd;
snd=0;
em2->drop();
em2=0;
em->drop();
em=0;
//delete Pweop;
//Pweop=0;
delete sdrsMgr;
sdrsMgr=0;
}
//----------------------
void setInputReceiverEnable(bool stop)
{
camera->setInputReceiverEnabled(stop);
}
void useFreeCamera(bool use)
{
	if(use)
	{
	smanger->setActiveCamera(camera2);
	camera2->setPosition(camera->getAbsolutePosition());
	}
	else
	smanger->setActiveCamera(camera);
}


core::vector3df getPosttion()
{
return camera->getAbsolutePosition();

}
core::vector3df getcamera2Posttion()
{
return camera2->getAbsolutePosition();

}
core::vector3df getRoution()
{
return camera->getRotation();
}

void setPostion(core::vector3df po)
{
camera->setPosition(po);

}
void setRotation(core::vector3df ro)
{
	camera->setRotation(ro);
}
int getBlood()
{
return Plyrblood;
}

};
#endif
