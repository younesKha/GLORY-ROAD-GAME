/*
writen by (Younes khafaja) - 2008-2009
You are free to use this code as you see fit
email : lighting-team@hotmail.com
*/
#ifndef SDR_H
#define SDR_H
#include <irrlicht.h>
#include"Functions.h"
#include"GameGuiInterface.h"
#include <irrKlang.h>
#include"Csounds.h"
#include"myShotNode.h"


using namespace irrklang;
using namespace irr;
//„⁄·Ê„«   ⁄ÿÏ ··Ã‰œÌ ··„‘Ì Ê«·œÊ—«‰ ÕÊ· «·„Ê«ﬁ⁄ ›Ì »œ«Ì… «··⁄»…
struct WalkData
{
	core::vector2df point[4];
	core::vector2df walkNormal[4];
	float Len[4];
	int walkSpeed;
	float animSPeed;
	bool Is4point;//Â· Ì„‘Ì √—»⁄ ‰ﬁ«ÿ √Ê ‰ﬁÿ Ì‰
	bool active;// ⁄„·Ì… «·„‘Ì ›⁄«·… √Ê  Êﬁ›  
	int actionNum;

};
struct WalkBorgData
{
	core::vector2df cnterP;
	float radLen;
	core::vector2df walkNormal[4];
	core::vector2df currWalkNorm;
	int walkSpeed;
	int animSPeed;
	int standTime;
};


struct runTrackData
{
int Pointcount;
core::vector2df*pontes;
core::vector2df*DirNorm;
float *Len;
bool active;
bool running;
int actionNum;
int animSpped;
int runSpeed;
};

class CSoldier
{
private:

protected:
	scene::IAnimatedMeshSceneNode*Sldr;
	scene::ISceneNode*fire_shoot;
	scene::ISceneNode*CnterSeeNode;

	scene::ISceneNode*rm[3],*lm[3],*bm[3];
	//MyShotNode*fireline1,*fireline2;
	scene::ISceneNode*fireline[3];
	IrrlichtDevice *Devic;
	
	Functins func;
	
	int responseSpeed;//  1-5 ”—⁄… «·≈” Ã«»… ··√ÕœÀ
	
	int attcNum;
	int sdrNum;
	int Sdrblood;
	bool active,live,see,hear;
	int state;//1-safe/2-dengare/3-attack
	
	int hearLen;
	int	seelen;//the len of see (change if state change)
	int	seeBacklen;
	float farCnterSeePo;
	
	int cerfulDis;//„”«›… «·≈‰ »«… «–« ﬂ«‰ «··⁄» „ﬂ‘Ê› 
	///sound require///////////////////
	ISoundEngine* SEngine; 
	irrklang::ISoundSource*soldrshoot;
	CSolderSounds *csnd;
	///////////////////////////////////
	int Rnumbers[20];//random number dicided hit player or not
	int arrayIndx;

	core::dimension2di SldrActions[40];//sidrs animations
	int currActinNum;//the current animation frame
	int currActionSpeed;
	//float AngleRotation;
	core::vector2df DefultSldrNormal; //defult soldier direct(0,1) 
	core::vector2df PlyrDirect;       //the direct of player from soldier if he see him
	core::vector2df oldPlyrDirect;
	core::vector2df currPlyrDirect;  //the direct of player from soldier if he see him or not
	core::vector3df PlyrPost;		//the post if sldr see player
	core::vector2df MoveDirect;		//the move direct of soidier
	core::vector2df slderDirect;	// the rotation of soldier
	int MoveSpeed;				 //the sppeed of moving
	int DistToPlyr;//distance form plyr to dolder
	int RplayFirstHit;//random number dicided if play hit or not
	bool stopWaking;
	bool stoprunTrack;
	core::vector2df intersection;
	core::triangle3df tri;
	
	scene::ITriangleSelector*SEESelector;

	int attackActLen;//the time between  change attack type;  
	int readyActLen;//the time between  change sharch type; 
	//as static
	bool ff;
	int enterIndx;
	int ft; //for walk
	float tot;//counter to walking function
	//Õ«’ »ŸÂÊ— Œÿ «ÿ·«ﬁ «·Ã‰œÌ
	bool enter11;
	core::vector3df startPoint;
	core::vector3df endPoint;

public:

	void SetData(IrrlichtDevice*Dev,CSolderSounds*csd,scene::IAnimatedMesh*mesh,core::vector3df sldPost,scene::IMetaTriangleSelector*mselector,scene::ITriangleSelector*SeeSelector,int id)
	{
	stoprunTrack=stopWaking=false;
	Devic=Dev;
	SEESelector=SeeSelector;
	state=1;//inatinal state(safe) 
	sdrNum=id;
	Sdrblood=10;
	see=active=false;
	live=true;
	hear=false;
	ff=true;

	enter11=true;
	enterIndx=1;
	attcNum=0;
	
	//---------------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------------
	PlyrPost.set(1,1,1);

	RplayFirstHit=func.RandomRange(0,2);

	for(int e=0;e<20;e++)
	Rnumbers[e]=func.RandomRange(1,10);
	arrayIndx=-1;

	DefultSldrNormal=core::vector2df(0,1);
	MoveDirect=core::vector2df(0,0);
	MoveSpeed=0;

	
	Sldr=Devic->getSceneManager()->addAnimatedMeshSceneNode(mesh,0,id,sldPost);
	
	//Sldr->setAutomaticCulling(scene::E_CULLING_TYPE::EAC_FRUSTUM_SPHERE);
	Sldr->setScale(core::vector3df(0.95,1.3f,0.95));
	Sldr->setMaterialFlag(video::EMF_LIGHTING,false);
	Sldr->setMaterialFlag(video::EMF_FOG_ENABLE,true); 
	//Sldr->setMaterialFlag(video::EMF_ANISOTROPIC_FILTER,true);
	//-------------------------------------------------------------------------
	//add solder shadow
	//Sldr->addShadowVolumeSceneNode();
    // Devic->getSceneManager()->setShadowColor(video::SColor(30,0,0,0));
//-------------------------------------------------------------------------------
	

	scene::ISceneNodeAnimator* anim = 0;
	anim = Devic->getSceneManager()->createCollisionResponseAnimator(mselector,Sldr, core::vector3df(20,66,20),core::vector3df(0,-20,0),
																		core::vector3df(0,1,0));
	Sldr->addAnimator(anim);
	anim->drop();
	anim=0;

	//=================sound data======================= 
	//soldrshoot=SEngine->addSoundSourceFromFile("sounds/sldrshoot.wav");
	csnd=csd;
	//=================================================
	rm[0]= Devic->getSceneManager()->addEmptySceneNode(Sldr,-1);
	rm[1]= Devic->getSceneManager()->addEmptySceneNode(Sldr,-1);
	rm[2]= Devic->getSceneManager()->addEmptySceneNode(Sldr,-1);
	lm[0]= Devic->getSceneManager()->addEmptySceneNode(Sldr,-1);
	lm[1]= Devic->getSceneManager()->addEmptySceneNode(Sldr,-1);
	lm[2]= Devic->getSceneManager()->addEmptySceneNode(Sldr,-1);
	bm[0]= Devic->getSceneManager()->addEmptySceneNode(Sldr,-1);
	bm[1]= Devic->getSceneManager()->addEmptySceneNode(Sldr,-1);
	bm[2]= Devic->getSceneManager()->addEmptySceneNode(Sldr,-1);

	rm[0]->setPosition(core::vector3df(1,0,0));
	rm[1]->setPosition(core::vector3df(1,0,.5).normalize());
	rm[2]->setPosition(core::vector3df(1,0,1).normalize());
	lm[0]->setPosition(core::vector3df(-1,0,0));
	lm[1]->setPosition(core::vector3df(-1,0,.5).normalize());
	lm[2]->setPosition(core::vector3df(-1,0,1).normalize());
	bm[0]->setPosition(core::vector3df(0,0,-1));
	bm[1]->setPosition(core::vector3df(0.5,0,-1).normalize());
	bm[2]->setPosition(core::vector3df(-0.5,0,-1).normalize());
	//====================shoot fire bool=============================
	/*MyShotNode *SldrShadow =new MyShotNode(Devic->getSceneManager()->getRootSceneNode(), Devic->getSceneManager(),-1);
	SldrShadow->setParent(Sldr);
	SldrShadow->setPosition(core::vector3df(0,0,0));
	SldrShadow->setScale(core::vector3df(10,0,10));
	SldrShadow->setMaterialTexture(0,Devic->getVideoDriver()->getTexture("SDR/sldrShadow.png"));
	SldrShadow->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);	
	SldrShadow->setMaterialFlag(video::EMF_LIGHTING,false);	
*/
	//Devic->getSceneManager()->addCubeSceneNode(10,Sldr,-1,core::vector3df(0,50,0));

	fire_shoot = Devic->getSceneManager()->addBillboardSceneNode(Sldr,core::dimension2d<f32>(30,30),core::vector3df(0,-2000,0),-1);
	fire_shoot->setMaterialTexture(0,Devic->getVideoDriver()->getTexture("fireGun.bmp"));
	fire_shoot->setMaterialFlag(video::EMF_LIGHTING, false);
	fire_shoot->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	fire_shoot->setVisible(false);

	//-------------------------------------------------



 PlayAction(15,30,false);

}

	void setadvanceData(float PcnterSeeFar=3000.0f,int Pseelen=3500,int Pseebacklen=1000,int PhearLen=3000,int PcerfulDistance=2000)
	{
		

			farCnterSeePo=PcnterSeeFar;
			seelen=Pseelen;
			seeBacklen=Pseebacklen;
			hearLen=PhearLen;
			cerfulDis=PcerfulDistance;

			//‰ﬁÿ… «·—ƒÌ… «·√„«„Ì…
		CnterSeeNode= Devic->getSceneManager()->addEmptySceneNode(Sldr,-1);
		CnterSeeNode->setPosition(core::vector3df(0,0,farCnterSeePo));// the far of point from the soilder	


			
	}

	void RotaSldrToDirect(core::vector2df dirc)
	{
		dirc=dirc.normalize();
		slderDirect=dirc;
		int x=1;
	
		if (dirc.X<0)
		x=-1;

		float angl = acos(DefultSldrNormal.dotProduct(dirc));
		angl=core::radToDeg(angl);
		Sldr->setRotation(core::vector3df(0,x*angl,0));	
	}
	void sldrShooting(int*blood,GGI*ggi)
	{
		if (see)
		{	
		int rn=getRandomN1To10();
			if (getDistanceFormPlyr()<500)
			{
				if(rn<=8)
				{
					*blood-=(5+rn);
					ggi->PlayRed();
					//csnd->playhitSound(true);
				}
			}
			else if (getDistanceFormPlyr()<5000)
			{
				if(rn<=5)
				{
					*blood-=(2+rn);
					ggi->PlayRed();
					//csnd->playhitSound(false);
				}
			}
			else if (getDistanceFormPlyr()>5000)
			{
				if(rn<=2)
				{
					*blood-=(1+rn);
					ggi->PlayRed();
				//	csnd->playhitSound(false);
				}
			}

			//*****************************************

		}
	}
	void PlaySldrShootFireline()
	{
	//fireline[0]->setPosition(fire_shoot->getAbsolutePosition());

		core::vector3df lineNorml=(fire_shoot->getAbsolutePosition()-PlyrPost).normalize();
		
		core::vector3df startPoint=fire_shoot->getAbsolutePosition()+lineNorml*-200;
		core::vector3df endPoint=fire_shoot->getAbsolutePosition()+lineNorml*-10000;
	
		int radmNum =func.RandomRange(-30,30);
		
		endPoint.X+=radmNum;
		endPoint.Z+=radmNum*-1;	
		endPoint.Y+=radmNum;

		
	if(enterIndx==1)
	{

			scene::ISceneNodeAnimator* anim =Devic->getSceneManager()->createFlyStraightAnimator(startPoint,endPoint,700,0);
			if (anim)
			{	
				fireline[0]->addAnimator(anim);
				anim->drop();
				anim=0;
			}

	enterIndx=2;	
	}
	
	else if (enterIndx==2)
	{
			scene::ISceneNodeAnimator* anim =Devic->getSceneManager()->createFlyStraightAnimator(startPoint,endPoint,700,0);
			if (anim)
			{
				fireline[1]->addAnimator(anim);
				anim->drop();
				anim=0;
			}
			
	enterIndx=3;
	}
	
	else if (enterIndx==3)
	{
			scene::ISceneNodeAnimator* anim =Devic->getSceneManager()->createFlyStraightAnimator(startPoint,endPoint,700,0);
			if (anim)
			{
				fireline[2]->addAnimator(anim);
				anim->drop();
				anim=0;
			}

	enterIndx=1;
	}

	

	}

	void DrowFireLine()
	{



			if(fire_shoot->isVisible())
			{

				if(enter11)
				{
					core::vector3df lineNorml=(fire_shoot->getAbsolutePosition()-PlyrPost).normalize();
					
					startPoint=fire_shoot->getAbsolutePosition()+lineNorml*-20;
					endPoint=fire_shoot->getAbsolutePosition()+lineNorml*-5000;
				
					int radmNum =func.RandomRange(-5,5);
					
					endPoint.X+=radmNum;
					endPoint.Z+=radmNum*-1;	
					endPoint.Y+=radmNum;
				enter11=false;
				}
				Devic->getVideoDriver()->draw3DLine(startPoint,endPoint,video::SColor(150,200,200,20));
			}
			else
			enter11=true;
	}
	void _Destrctor()
	{
//	delete csnd;
//	csnd=0;

	}
	//------------------------------------------------------------------------------------------------------------------------------	
	scene::IAnimatedMesh*getSolderMesh()
{
return Sldr->getMesh();
}
	scene::IAnimatedMeshSceneNode*getSoldernode()
{
return Sldr;
}
	void StopWalking(bool stop)
	{
	stopWaking=stop;
	}
	void StoprunTrack(bool stop)
	{
		stoprunTrack=stop;
	}
	int getRandomN1To10()
	{
	arrayIndx++;
	if (arrayIndx==20)
	arrayIndx=0;
	return Rnumbers[arrayIndx];
	}
	int getBlood()
	{
	return Sdrblood;
	}
	bool GetisLive()
	{
	return live;
	}
	void setActive(bool b)
	{
		active=b;
	}
	void setSee(bool b)
	{
		see=b;
	}
	bool getActive()
	{
	return active;
	}
	void setDirectandSpeed(core::vector2df dir,int sp)
	{
	MoveDirect=dir;
    MoveDirect=MoveDirect.normalize();
	MoveSpeed=sp;
	}
	void setCerfulDistane(int dis)
	{
	cerfulDis=dis;
	}
	int getCerfulDistane()
	{
		return cerfulDis;
	}
	void setPlyrDirect(core::vector2df dir)
	{
		PlyrDirect=dir;
	}
	void setCurrPlyrDirect(core::vector2df dir)
	{
		currPlyrDirect=dir;
	}

	void setPlyrPost(core::vector3df PlrPost)
	{
	PlyrPost=PlrPost;
	}
	bool getsee()
	{
	return see;
	}
	int getSdrNum()
	{
	return sdrNum;
	}
	void releaseMesh()
	{
	Sldr->getMesh()->grab();
	Sldr->getMesh()->drop();

	Sldr->grab();
	Sldr->drop();
	}

	void PlayAction(int AcionNumber,float AnimSpeed,bool b)
	{
	currActinNum=AcionNumber;
	currActionSpeed=AnimSpeed;
	Sldr->setFrameLoop(SldrActions[AcionNumber].Width,SldrActions[AcionNumber].Height);
	Sldr->setLoopMode(b);
	Sldr->setAnimationSpeed(AnimSpeed);
	}
	void setDistanceFormPlyr(int dis)
	{
	if (dis<0)
	dis*=-1;
		DistToPlyr=dis;
	}
	void setSdrVisable(bool b)
	{
	Sldr->setVisible(b);
	}
	core::vector3df getpostion()
	{
		//core::vector3df po=Sldr->getAbsolutePosition();
		//po.Y+70;
		return Sldr->getAbsolutePosition();
	}
	core::vector2df getCnterSeePost()
	{
	return core::vector2df(CnterSeeNode->getAbsolutePosition().X,CnterSeeNode->getAbsolutePosition().Z);
	}
	core::vector3df getPlyerPost()
	{
		return PlyrPost;
	}
	void fireShootVisble(bool visble)
	{
	fire_shoot->setVisible(visble);
	}
	
	int getState()
	{
	return state;
	}
	void setState(int State)
	{
	state=State;
	}
	int getSeeLen()
	{
	return seelen;
	}
	int getHearLen()
	{
	return hearLen;
	}
	void setHear(bool b)
	{
	hear=b;
	}
	int getHear()
	{
	return hear;
	}
	int getSeeBackLen()
	{
	return seeBacklen;
	}
	int getDistanceFormPlyr()
	{
	return DistToPlyr;
	}
	core::vector2df getRotatDir()
	{
	return slderDirect;

	}

	void settriAndIntersection(core::triangle3df trigl,core::vector2df sectionPoint)
	{
	tri=trigl;
	intersection=sectionPoint;
	}
	int getcurrplayAction()
	{
	return currActinNum;
	}
	
	virtual void SOILDER_RENDER(int*blood,GGI*ggi,float timeelip){}
	virtual void setWalkData(core::vector2df p[],int speed,float animSPeed,bool is4type,bool running,bool Active){}
	virtual void setrunTrackData(int pointCount,core::vector2df p[],int runspeed,int animSpeed,bool running,bool active){}
	virtual void RUNTRUCK(){}
	virtual void setWalkActive(bool active){}
	virtual void setrunTrackActive(bool active){}
	virtual	void setWalkBorgData(core::vector2df cnter,float ridus,core::vector2df p[],int speed,int animSPeed){}	
	virtual void WAKING(float timeelip){}
	virtual void attack(int*blood,GGI*ggi){}
	virtual void MovingAndFrmCnsr(float timeelip,int*blood,GGI*ggi){}	
	virtual void setSolderType(bool isM16){}
	virtual void subtractBlood(int x){}
	virtual void slderDead(){}
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CSoldier_1 : public CSoldier
{
private:

WalkData*wd;
runTrackData*rtd;
bool bv,fs,fst,fst2,fst3,fst_stat2e,enter5;
int nt1,nt2,nt3,nt4,nt5,nt6,n2,n3;
int Rmovdir; // random direct 
core::vector2df runDir;// the direct of solider when run follow the player
int Rtbd;//random to getattacktype function
int Rmtd;//random max attck distance

int ft2,indx;
public:
	CSoldier_1()
	{
	wd=0;
	rtd=0;
	attackActLen=15;
	readyActLen=20;
	indx=ft2=attcNum=0;
	fst=fst2=fst3=bv=fs=fst_stat2e=enter5=true;
	tot=0;
	//ltr=true;
	nt1=nt2=nt3=nt4=nt5=nt6=n2=n3=Rmovdir=0;
	Rtbd=func.RandomRange(200,500);
	Rmtd=func.RandomRange(4000,7000);


	SldrActions[0].set(221,245);	//dead1
	SldrActions[1].set(401,420);	//dead2
	SldrActions[2].set(421,455);	//dead3

	SldrActions[6].set(201,211);	//hit1
	SldrActions[7].set(301,310);  //hit2
	
	SldrActions[10].set(1,32);		//walking
	SldrActions[11].set(380,400);   //runing

	SldrActions[15].set(33,80);		//stands
	SldrActions[16].set(81,200);    // ·› 
	SldrActions[17].set(33,34);     //stand short
	
	SldrActions[20].set(246,280); //Ì—›Õ «·”·«Õ ÊÌÿ·ﬁ «·‰«—
	SldrActions[21].set(261,280);//Ì” „— ›Ì «ÿ·«ﬁ «·‰«—
	SldrActions[22].set(311,333);// walk right Shoot
	SldrActions[23].set(334,356);//walk left shoot
	SldrActions[24].set(357,379);//walk back
	SldrActions[25].set(246,260); //Ì—›Õ «·”·«Õ ÊÌÿ·ﬁ «·‰«—
	
	SldrActions[26].set(279,280); //ready to shoot
	
	SldrActions[27].set(311,333);// Ready right 
	SldrActions[28].set(334,356);// ready left
	}
	void setWalkData(core::vector2df p[],int speed,float animSPeed,bool is4type,bool running,bool Active)
	{

		wd=new WalkData();
		
		wd->point[0].set(p[0]);
		wd->point[1].set(p[1]);
		wd->point[2].set(p[2]);
		wd->point[3].set(p[3]);
	

		wd->Len[0]=(p[1]-p[0]).getLength();
		wd->Len[1]=(p[2]-p[1]).getLength();
		wd->Len[2]=(p[3]-p[2]).getLength();
		wd->Len[3]=(p[3]-p[0]).getLength();
	
		// ŒÊÌ· «·ÿÊ· ·⁄œœ „ÊÃ»
		if(wd->Len[0]<0)
		wd->Len[0]*=-1;
		if(wd->Len[1]<0)
		wd->Len[1]*=-1;
		if(wd->Len[2]<0)
		wd->Len[2]*=-1;
		if(wd->Len[3]<0)
		wd->Len[3]*=-1;
		///////////////////////////////////
		wd->walkNormal[0].set((p[1]-p[0]).normalize());
		wd->walkNormal[1].set((p[2]-p[1]).normalize());
		wd->walkNormal[2].set((p[3]-p[2]).normalize());
		wd->walkNormal[3].set((p[0]-p[3]).normalize());


		wd->animSPeed=animSPeed;
		wd->walkSpeed=speed;
		wd->Is4point=is4type;
		wd->active=Active;
		
			if(running)
			wd->actionNum=11;
			else
			wd->actionNum=10;

		ft=0;
		if(!is4type)
		{
		wd->walkNormal[1].set((p[0]-p[1]).normalize());
		wd->Len[1]=wd->Len[0];
		}

	}	
	void setrunTrackData(int pointCount,core::vector2df p[],int runspeed,int animSpeed,bool running,bool active)
	{
	rtd=new runTrackData();
	rtd->Pointcount=pointCount;
	rtd->pontes=new core::vector2df[pointCount+1];
	rtd->DirNorm=new core::vector2df[pointCount];
	rtd->Len=new float[pointCount];

		for(int i=0;i<pointCount;i++)
		rtd->pontes[i+1].set(p[i]);
		for(int i=0;i<pointCount-1;i++)
		{

			rtd->Len[i+1]=(p[i+1]-p[i]).getLength();
			rtd->DirNorm[i+1].set((p[i+1]-p[i]).normalize());	
			
			if(rtd->Len[i+1]<0)
			rtd->Len[i+1]*=-1;
		}

	rtd->active=active;
	rtd->running=running;
	rtd->runSpeed=runspeed;
	rtd->animSpped=animSpeed;
	
	if(running)
	rtd->actionNum=11;
	else
	rtd->actionNum=10;

	if(active)
	stopWaking=true;
	else
	stopWaking=false;


	}
	void setWalkActive(bool active)
	{
		if(!wd)
		wd->active=active;
	}
	void setrunTrackActive(bool active)
		{
			if(rtd)
			{
			rtd->active=active;
			stopWaking=true;
			}

		}

	void MovingAndFrmCnsr(float timeelip,int*blood,GGI*ggi)
	{
		if(active)
		{
			if (MoveSpeed)
			{
			core::vector2df sidrPost;
			sidrPost.X=Sldr->getAbsolutePosition().X;
			sidrPost.Y=Sldr->getAbsolutePosition().Z;

			sidrPost+=MoveDirect*MoveSpeed*timeelip;
			Sldr->setPosition(core::vector3df(sidrPost.X,Sldr->getAbsolutePosition().Y,sidrPost.Y));
			}
			//show fire bool 
			if((currActinNum==20)||(currActinNum==21))//if action number is shoot 
			{
				if(((263<=Sldr->getFrameNr())&&(Sldr->getFrameNr()<=265))||((267<=Sldr->getFrameNr())&&(Sldr->getFrameNr()<=269))||((271<=Sldr->getFrameNr())&&(Sldr->getFrameNr()<=273)))
				{
					fire_shoot->setPosition(core::vector3df(3,50,55));
					fire_shoot->setVisible(true);
					if (ff)
					{
					csnd->playSldrShootSound(400.0f/DistToPlyr);
					sldrShooting(blood,ggi);
					//PlaySldrShootFireline();
					ff=false;
					}
					}
					else{
					fire_shoot->setVisible(false);
					ff=true;
					}
			}
			else if (currActinNum==22)//attack right
			{
				if((320<=Sldr->getFrameNr())&&(Sldr->getFrameNr()<=323)||(325<=Sldr->getFrameNr())&&(Sldr->getFrameNr()<=328))
				{
					fire_shoot->setPosition(core::vector3df(20,35,55));
					fire_shoot->setVisible(true);
					if (ff)
					{
					csnd->playSldrShootSound(400.0f/DistToPlyr);
					sldrShooting(blood,ggi);
					//PlaySldrShootFireline();
					ff=false;
					}
				}
				else{
				fire_shoot->setVisible(false);
				ff=true;
				}
			}
			else if (currActinNum==23)//atack left
			{
				if((340<=Sldr->getFrameNr())&&(Sldr->getFrameNr()<=343)||(346<=Sldr->getFrameNr())&&(Sldr->getFrameNr()<=348))
				{
					fire_shoot->setPosition(core::vector3df(20,35,55));
					fire_shoot->setVisible(true);
					if (ff)
					{
					csnd->playSldrShootSound(400.0f/DistToPlyr);
					sldrShooting(blood,ggi);
					//PlaySldrShootFireline();
					ff=false;
					}
				}
				else{
				fire_shoot->setVisible(false);
				ff=true;
				}
			}
			else if (currActinNum==24)//atack back
			{
				if((358<=Sldr->getFrameNr())&&(Sldr->getFrameNr()<=360)||(362<=Sldr->getFrameNr())&&(Sldr->getFrameNr()<=364)||(366<=Sldr->getFrameNr())&&(Sldr->getFrameNr()<=368)||(370<=Sldr->getFrameNr())&&(Sldr->getFrameNr()<=372))
				{
					fire_shoot->setPosition(core::vector3df(3,40,55));
					fire_shoot->setVisible(true);
					if (ff)
					{

					csnd->playSldrShootSound(400.0f/DistToPlyr);
					sldrShooting(blood,ggi);
					//PlaySldrShootFireline();
					ff=false;
					}
				}
				else{
				fire_shoot->setVisible(false);
				ff=true;
				}
			}
			else{
			fire_shoot->setVisible(false);
			ff=true;
			}
		}
	}	

	
	void SOILDER_RENDER(int*blood,GGI*ggi,float timeelip)
	{
		if(active)
		{
		attack(blood,ggi);
		WAKING(timeelip);
		RUNTRUCK();
		}
	}	
	void attack(int*blood,GGI*ggi)
	 {
		 if (state==3)
		 {
			 if (n2==0)
			 { 
			n3=0;
			StopWalking(true);
			StoprunTrack(true);
			fst=fst_stat2e=enter5=true;		
			
			oldPlyrDirect=PlyrDirect;
			int oldAttcNum=attcNum;
			
			if (oldAttcNum==8)
			attcNum= 2;
			else if(oldAttcNum==9)
			attcNum= 3;
			else
			attcNum=getAttackType();

			if (oldAttcNum==attcNum)
			bv=false;
			else
			bv=true;
			
			attackActLen=func.RandomRange(15,30);
				
				if (attcNum==1)
				setDirectandSpeed(core::vector2df(0,0),0);
				else if (attcNum==2||attcNum==3||attcNum==4||attcNum==5)
				{
					Rmovdir=func.RandomRange(0,2);
					fs=false;
				}
			 }
		 n2++;
		 if (n2>=attackActLen)//every 1.5 secand 
		 n2=0;
		 }
		 else if(state==2)
		 {
			//-------------------------------------------------
			 if(fst_stat2e)// «Ê· „« Ì’»Õ Õ«·… «·Ã‰œÌ 2 ›ﬁÿ ÌœŒ· „—… Ê«Õœ…
			{
				n2=0;
				if(attcNum==2)
				attcNum=9;
				else if(attcNum==3)
				attcNum=8;
				else
				attcNum=7;
				
				fst_stat2e=false;
				enter5=true;
				fst=true;

				//if(getBlood()<10)
				readyActLen=func.RandomRange(10,15);//«–« «·Ã‰œÌ „’«» ÌÃ—Ì ‰ÕÊ «··⁄» ÊÌ‰ Ÿ— „‰ ‰’› «·Ï Ê«Õœ À«‰»…
				//else
				//readyActLen=func.RandomRange(10,30);//«–« «·Ã‰œÌ €Ì— „’«» ÌÃ—Ì ‰ÕÊ «··⁄» ÊÌ‰ Ÿ— „‰ À«‰Ì… «·Ï 5 ÀÊ«‰Ì”
			}
			//------------------------------------------------------
			n3++;
			if (n3>=readyActLen)//random time between tow action
			{
				if(enter5)
				{
					//----------------------Õ”«» »⁄œÂ ⁄‰ „ﬂ«‰ «Œ »«¡ «·√⁄»-----------------------
					core::vector2df PlyrPo=core::vector2df(PlyrPost.X,PlyrPost.Z);
					core::vector2df sldrrPo=core::vector2df(Sldr->getAbsolutePosition().X,Sldr->getAbsolutePosition().Z);	
					float di=(PlyrPo-sldrrPo).getLength();
					//-------------------------------------------------------
					if(di<0)
					di*=-1;

						if (di<100)//«–« Ê’· ·„Êﬁ⁄ «Œ »«¡ «··⁄» Ì Êﬁ›
						{
							PlayAction(15,30,true);
							setDirectandSpeed(core::vector2df(0,0),0);
							attcNum=0;
							enter5=false;
						}
						else
						{
							attcNum=getReadyshootType(di);
							fst=true;
							n3=0;
						}
				}
			}
		 }
		//======================================================================
		 if (attcNum)
		 {
			if (attcNum==1)
			attack_stand(blood,ggi);
			else if (attcNum==2)
			attack_right(blood,ggi);//right
			else if (attcNum==3)
			attack_left(blood,ggi);//left
			else if (attcNum==4)
			attack_back(blood,ggi);
			else if (attcNum==5)
			attack_Run(blood,ggi);
			else if (attcNum==6)
			followingHimRun(false,core::vector2df(0,0));
			else if (attcNum==7)
			followingHimStand();
			else if (attcNum==8)
			followingHimRight();//right
			else if (attcNum==9)
			followingHimLeft();//left
		 }
	}
	void attack_stand(int*blood,GGI*ggi)
	 {
		if (live&&active)
		{	
			nt1++;
			if(nt1==2)
			{
				if(bv)
				{
					if (state==3)
					{
						if (fs)
						{
						PlayAction(20,30,false);
						bv=false;
						fs=false;
						}
						else{
						PlayAction(21,30,false);
						bv=false;
						}
					}
					else if (state==2)
					{
						PlayAction(17,30,false);
						fire_shoot->setVisible(false);
						fs=true;
					}
				}
			 nt1=0;
			}
			if(Sldr->getFrameNr()==SldrActions[currActinNum].Height)//if solder action is finsh
			bv=true;
			if (currActinNum==20||currActinNum==21)
			RotaSldrToDirect(PlyrDirect);
		}
	}
	void attack_right(int*blood,GGI*ggi)
	 {
		if (live&&active)
		{	
			nt2++;
			if(nt2==2)
			{
				if(bv)
				{
					if (state==3)
					{
						if (fs)
						{
						PlayAction(20,30,false);
						bv=false;
						fs=false;
						}
						else{
						PlayAction(22,25,true);
						core::vector2df rd=core::vector2df(rm[Rmovdir]->getAbsolutePosition().X-Sldr->getAbsolutePosition().X,rm[Rmovdir]->getAbsolutePosition().Z-Sldr->getAbsolutePosition().Z);
						setDirectandSpeed(rd,70);
						bv=false;
						}
					}
					else if (state==2)
					{
						PlayAction(17,30,false);
						fire_shoot->setVisible(false);
						setDirectandSpeed(core::vector2df(0,0),0);
						fs=true;
						bv=true;
					}
				}
			  nt2=0;
			}
			if(Sldr->getFrameNr()==SldrActions[currActinNum].Height||state==2)//if solder action is finsh
			bv=true;

			if (currActinNum==22)
			{
			RotaSldrToDirect(PlyrDirect);
			core::vector2df rd=core::vector2df(rm[Rmovdir]->getAbsolutePosition().X-Sldr->getAbsolutePosition().X,rm[Rmovdir]->getAbsolutePosition().Z-Sldr->getAbsolutePosition().Z);
			setDirectandSpeed(rd,70);

			}
		}
	}



	void attack_left(int*blood,GGI*ggi)
	 {
		if (live&&active)
		{	
			nt3++;
			if(nt3==2)
			{
				if(bv)
				{
					if (state==3)
					{
						if (fs)
						{
						PlayAction(20,30,false);
						bv=false;
						fs=false;
						}
						else{
						PlayAction(23,25,true);
						core::vector2df rd=core::vector2df(lm[Rmovdir]->getAbsolutePosition().X-Sldr->getAbsolutePosition().X,lm[Rmovdir]->getAbsolutePosition().Z-Sldr->getAbsolutePosition().Z);
						setDirectandSpeed(rd,70);
						bv=false;
						}
					}
					else if (state==2)
					{
						PlayAction(17,30,false);
						fire_shoot->setVisible(false);
						setDirectandSpeed(core::vector2df(0,0),0);
						fs=true;
						bv=true;
					}
				}
			  nt3=0;
			}
			if(Sldr->getFrameNr()==SldrActions[currActinNum].Height||state==2)//if solder action is finsh
			bv=true;

			if (currActinNum==23)
			{
			RotaSldrToDirect(PlyrDirect);
			core::vector2df rd=core::vector2df(lm[Rmovdir]->getAbsolutePosition().X-Sldr->getAbsolutePosition().X,lm[Rmovdir]->getAbsolutePosition().Z-Sldr->getAbsolutePosition().Z);
			setDirectandSpeed(rd,70);
			}
		}
	}

	void attack_back(int*blood,GGI*ggi)
	 {
		if (live&&active)
		{	
			nt4++;
			if(nt4==2)
			{
				if(bv)
				{
					if (state==3)
					{
						if (fs)
						{
						PlayAction(20,30,false);
						bv=false;
						fs=false;
						}
						else{
						PlayAction(24,30,true);
						core::vector2df rd=core::vector2df(bm[Rmovdir]->getAbsolutePosition().X-Sldr->getAbsolutePosition().X,bm[Rmovdir]->getAbsolutePosition().Z-Sldr->getAbsolutePosition().Z);
						setDirectandSpeed(rd,70);
						bv=false;
						}
					}
					else if (state==2)
					{
						PlayAction(17,30,false);
						fire_shoot->setVisible(false);
						setDirectandSpeed(core::vector2df(0,0),0);
						fs=true;
						bv=true;
					}
				}
			  nt4=0;
			}
			if(Sldr->getFrameNr()==SldrActions[currActinNum].Height||state==2)//if solder action is finsh
			bv=true;

			if (currActinNum==24)
			{
			RotaSldrToDirect(PlyrDirect);
			core::vector2df rd=core::vector2df(bm[Rmovdir]->getAbsolutePosition().X-Sldr->getAbsolutePosition().X,bm[Rmovdir]->getAbsolutePosition().Z-Sldr->getAbsolutePosition().Z);
			setDirectandSpeed(rd,70);
			}

		}
	}




	void attack_Run(int*blood,GGI*ggi)
	 {
		if (live&&active)
		{	
			nt5++;
			if(nt5==5)
			{
				if(bv)
				{
					if (state==3)
					{
	
						PlayAction(11,30,true);
						RotaSldrToDirect(currPlyrDirect);
						setDirectandSpeed(currPlyrDirect,150);
						bv=false;
					}
				}
			  nt5=0;
			}


			if (currActinNum==11)
			{
				RotaSldrToDirect(currPlyrDirect);
				setDirectandSpeed(currPlyrDirect,150);
			}

		}
	}

	
	void followingHimRun(bool toPoint,core::vector2df point)
	  {
		nt6++;
		if (nt6==5)//every .5secand correct the path
		{
			if (fst)
			{
			//normal to the plyer place point
			//*************************************************************
			core::vector2df PlyrPo=core::vector2df(PlyrPost.X,PlyrPost.Z);
			core::vector2df sldrrPo=core::vector2df(Sldr->getAbsolutePosition().X,Sldr->getAbsolutePosition().Z);	
			core::vector2df plyrplacenNor=(PlyrPo-sldrrPo).normalize();//« Ã«Â „Œ»«¡ «··«⁄»
			//**************************************************************
			PlayAction(11,30,true);
     		setDirectandSpeed(plyrplacenNor,200);
			RotaSldrToDirect(plyrplacenNor);
			fst=false;
			fst3=true;
			}

			nt6=0;
		}
	  }
	void followingHimStand()
		{
			if(fst)
			{
			//*************************************************************
			core::vector2df PlyrPo=core::vector2df(PlyrPost.X,PlyrPost.Z);
			core::vector2df sldrrPo=core::vector2df(Sldr->getAbsolutePosition().X,Sldr->getAbsolutePosition().Z);	
			core::vector2df plyrplacenNor=(PlyrPo-sldrrPo).normalize();//« Ã«Â „Œ»«¡ «··«⁄»
			//**************************************************************		PlayAction(26,30,false);
			PlayAction(26,20,false);	
			setDirectandSpeed(core::vector2df(0,0),0);
			RotaSldrToDirect(plyrplacenNor);
			fst=false;
			fs=false;
			}
		}
	void followingHimRight()
		{
			if(fst)
			{
			PlayAction(27,20,true);				
			//fst=false;
			fs=false;
			}
			//*************************************************************
			core::vector2df PlyrPo=core::vector2df(PlyrPost.X,PlyrPost.Z);
			core::vector2df sldrrPo=core::vector2df(Sldr->getAbsolutePosition().X,Sldr->getAbsolutePosition().Z);	
			core::vector2df plyrplacenNor=(PlyrPo-sldrrPo).normalize();//« Ã«Â „Œ»«¡ «··«⁄»
			//**************************************************************
			RotaSldrToDirect(plyrplacenNor);
			core::vector2df rd=core::vector2df(rm[1]->getAbsolutePosition().X-Sldr->getAbsolutePosition().X,rm[1]->getAbsolutePosition().Z-Sldr->getAbsolutePosition().Z);
			setDirectandSpeed(rd,50);
		
	
	}
	void followingHimLeft()
		{
			if(fst)
			{
			PlayAction(28,20,true);				
			//fst=false;
			fs=false;
			}
			//*************************************************************
			core::vector2df PlyrPo=core::vector2df(PlyrPost.X,PlyrPost.Z);
			core::vector2df sldrrPo=core::vector2df(Sldr->getAbsolutePosition().X,Sldr->getAbsolutePosition().Z);	
			core::vector2df plyrplacenNor=(PlyrPo-sldrrPo).normalize();//« Ã«Â „Œ»«¡ «··«⁄»
			//**************************************************************		PlayAction(26,30,false);

			RotaSldrToDirect(plyrplacenNor);
			core::vector2df rd=core::vector2df(lm[1]->getAbsolutePosition().X-Sldr->getAbsolutePosition().X,lm[1]->getAbsolutePosition().Z-Sldr->getAbsolutePosition().Z);
			setDirectandSpeed(rd,50);
		}

    
	int getAttackType()
		 {
			if(getDistanceFormPlyr()>4000)
			return 5;//run to him
			else if(getDistanceFormPlyr()<Rtbd&&getBlood()<4)
			return func.RandomRange(2,4);
			else if(getDistanceFormPlyr()<Rtbd)
			return 4;
			else if (getDistanceFormPlyr()<1000||getBlood()<10)
			return func.RandomRange(2,3);
			else if (getDistanceFormPlyr()>Rmtd)
			return 5;
			else
			return 1;
		 }
	int getReadyshootType(float disfrmPlace)
		 {		
			 if ((disfrmPlace<=2000)&&(getBlood()==10)&&(attcNum==6))
			{
				readyActLen=func.RandomRange(20,30);
				return 7;
			 }
			 else if ((disfrmPlace<=2000)&&(getBlood()==10)&&(attcNum==7))
			{
			  readyActLen=func.RandomRange(20,50);
			  return 6;
			 }
			 else if ((disfrmPlace<=5000)&&(getBlood()==10))
			{
			  readyActLen=func.RandomRange(20,50);
			  return 6;
			 }

}
	
	void subtractBlood(int x)
	{
	Sdrblood-=x;
	int Rhit=func.RandomRange(1,5);//’Ê  √·„ ⁄‘Ê«∆Ì
	if(see)
	state=3;
	else
	state=2;
	
	StopWalking(true);

	if (Sdrblood<=0)
	{
	live=false;
	csnd->playSldrHitSound(600.0f/DistToPlyr,Rhit);
	}
	else
	{
		if (RplayFirstHit)
		{
			if (x==3)
			{
			PlayAction(7,30,false);//«’«»… ›Ì «·»ÿ‰
			csnd->playSldrHitSound(600.0f/DistToPlyr,Rhit);
			}
			else if (x==2)
			PlayAction(6,30,false);//«’«»… ›Ì «·—Ã·
			RplayFirstHit=0;
			MoveSpeed=0;
			csnd->playSldrHitSound(600.0f/DistToPlyr,Rhit);
		}
	}
	}
	void WAKING(float timeelip)
	 {
	if((!stopWaking)&&(wd))
			
	{
		if (wd->active&&live)
		{
			//=================================================================================//
			//==============================IF FOUR POINT=======================================//
			if (wd->Is4point)
			{
				if (ft==0)//move1
				{
					Sldr->setPosition(core::vector3df(wd->point[0].X,Sldr->getAbsolutePosition().Y,wd->point[0].Y));
					setDirectandSpeed(wd->walkNormal[0],wd->walkSpeed);
					RotaSldrToDirect(wd->walkNormal[0]);
					PlayAction(wd->actionNum,wd->animSPeed,true);	
					ft=1;
				}	
				else if (ft==1)//stop1
				{

					float currlen=(core::vector2df(Sldr->getAbsolutePosition().X,Sldr->getAbsolutePosition().Z)-wd->point[0]).getLength();
					if (currlen<0)
					currlen*=-1;

					if(wd->Len[0]<=currlen)
					{
						MoveSpeed=0;
						PlayAction(15,wd->animSPeed,true);
						ft=2;
						tot=0;
					}

				}
				else if (ft==2)//stand
				{
				tot+=timeelip;
					if (tot>3)
					ft=3;	
				}
				else if (ft==3)//move2
				{
					Sldr->setPosition(core::vector3df(wd->point[1].X,Sldr->getAbsolutePosition().Y,wd->point[1].Y));
					setDirectandSpeed(wd->walkNormal[1],wd->walkSpeed);
					RotaSldrToDirect(wd->walkNormal[1]);
					PlayAction(wd->actionNum,wd->animSPeed,true);	
					ft=4;
				}
				else if (ft==4)//stop2
				{
					float currlen=(core::vector2df(Sldr->getAbsolutePosition().X,Sldr->getAbsolutePosition().Z)-wd->point[1]).getLength();
					if (currlen<0)
					currlen*=-1;

					if(wd->Len[1]<currlen)
					{
						MoveSpeed=0;
						PlayAction(16,wd->animSPeed,true);
						ft=5;
						tot=0;
					}
				}
				else if (ft==5)//stand2
				{
				tot+=timeelip;
					if (tot>5)
					ft=6;
				}
				else if (ft==6)//move3
				{
					Sldr->setPosition(core::vector3df(wd->point[2].X,Sldr->getAbsolutePosition().Y,wd->point[2].Y));
					setDirectandSpeed(wd->walkNormal[2],wd->walkSpeed);
					RotaSldrToDirect(wd->walkNormal[2]);
					PlayAction(wd->actionNum,wd->animSPeed,true);	
					ft=7;
				}
				else if (ft==7)//stop3
				{
					float currlen=(core::vector2df(Sldr->getAbsolutePosition().X,Sldr->getAbsolutePosition().Z)-wd->point[2]).getLength();
					if (currlen<0)
					currlen*=-1;

					if(wd->Len[2]<currlen)
					{
						MoveSpeed=0;
						PlayAction(15,wd->animSPeed,true);
						ft=8;
						tot=0;
					}
				}
				else if (ft==8)//stand
				{
				tot+=timeelip;
					if (tot>5)
					ft=9;
				}
				else if (ft==9)//move4
				{
					Sldr->setPosition(core::vector3df(wd->point[3].X,Sldr->getAbsolutePosition().Y,wd->point[3].Y));
					setDirectandSpeed(wd->walkNormal[3],wd->walkSpeed);
					RotaSldrToDirect(wd->walkNormal[3]);
					PlayAction(wd->actionNum,wd->animSPeed,true);	
					ft=10;
				}
				else if (ft==10)//stop4
				{

					float currlen=(core::vector2df(Sldr->getAbsolutePosition().X,Sldr->getAbsolutePosition().Z)-wd->point[3]).getLength();
					if (currlen<0)
					currlen*=-1;

					if(wd->Len[3]<currlen)
					{
						MoveSpeed=0;
						PlayAction(16,wd->animSPeed,true);
						ft=11;
						tot=0;
					}
				}
				else if (ft==11)//stand4
				{
				tot+=timeelip;
					if (tot>5)
					ft=0;
				}
			}
			//=================================================================================//
			//==============================IF TWO POINT=======================================//
			else
			{
				if (ft==0)//move1
				{
					Sldr->setPosition(core::vector3df(wd->point[0].X,Sldr->getAbsolutePosition().Y,wd->point[0].Y));
					setDirectandSpeed(wd->walkNormal[0],wd->walkSpeed);
					RotaSldrToDirect(wd->walkNormal[0]);
					PlayAction(wd->actionNum,wd->animSPeed,true);	
					ft=1;
				}	
				else if (ft==1)//stop1
				{

					float currlen=(core::vector2df(Sldr->getAbsolutePosition().X,Sldr->getAbsolutePosition().Z)-wd->point[0]).getLength();
					if (currlen<0)
					currlen*=-1;

					if(wd->Len[0]<currlen)
					{
						MoveSpeed=0;
						PlayAction(15,wd->animSPeed,true);
						ft=2;
						tot=0;
					}

				}
				else if (ft==2)//stand
				{
				tot+=timeelip;
					if (tot>3)
					ft=3;	
				}
				else if (ft==3)//move2
				{
					Sldr->setPosition(core::vector3df(wd->point[1].X,Sldr->getAbsolutePosition().Y,wd->point[1].Y));
					setDirectandSpeed(wd->walkNormal[1],wd->walkSpeed);
					RotaSldrToDirect(wd->walkNormal[1]);
					PlayAction(wd->actionNum,wd->animSPeed,true);	
					ft=4;
				}
				else if (ft==4)//stop2
				{
					float currlen=(core::vector2df(Sldr->getAbsolutePosition().X,Sldr->getAbsolutePosition().Z)-wd->point[1]).getLength();
					if (currlen<0)
					currlen*=-1;

					if(wd->Len[1]<currlen)
					{
						MoveSpeed=0;
						PlayAction(16,wd->animSPeed,true);
						ft=5;
						tot=0;
					}
				}
				else if (ft==5)//stand2
				{
				tot+=timeelip;
					if (tot>5)
					ft=0;
				}
		
		}
	 }
 }
}
	void RUNTRUCK()
	{
	if((!stoprunTrack)&&(rtd))
	{
		if(rtd->active&&active)
		{
			if(ft2==0)
			{
				rtd->pontes[0]=core::vector2df(Sldr->getAbsolutePosition().X,Sldr->getAbsolutePosition().Z);
				rtd->Len[0]=(rtd->pontes[1]-rtd->pontes[0]).getLength();
				if(rtd->Len[0]<0)
				rtd->Len[0]*=-1;
				rtd->DirNorm[0]=(rtd->pontes[1]-rtd->pontes[0]).normalize();			
				ft2=1;

			}
			else if(ft2==1)
			{
				setDirectandSpeed(rtd->DirNorm[indx],rtd->runSpeed);
				RotaSldrToDirect(rtd->DirNorm[indx]);
				PlayAction(rtd->actionNum,rtd->animSpped,true);	

				ft2=2;
			}
			else if (ft2==2)
			{
			core::vector2df currPo=core::vector2df(Sldr->getAbsolutePosition().X,Sldr->getAbsolutePosition().Z);
			float currlen=(rtd->pontes[indx]-currPo).getLength();
			if (currlen<0)
			currlen*=-1;

					if(currlen>=rtd->Len[indx])
					{
					ft2=1;
					indx++;
					}

					if(indx==rtd->Pointcount)
					{
					stoprunTrack=true;
					MoveSpeed=0;
					PlayAction(15,30,true);
					}
			}
		}
	}
	}
	void slderDead()
	{
	//ÿÌÕ… «·Ã‰œÌ »‘ﬂ· ⁄‘Ê«∆Ì
		int x=func.RandomRange(0,2);

	PlayAction(x,30,false);
	stoprunTrack=active=live=see=false;
	state=0;
	fire_shoot->setVisible(false);
		//add Solder Weopen NOde

		if((x==0)||(x==1))
		{
			DeadSoldrWeop node;
			node.ShootCount=func.RandomRange(20,50);
			node.weopType=2;
		
			core::vector2df backNorm=core::vector2df(bm[0]->getAbsolutePosition().X-Sldr->getAbsolutePosition().X,bm[0]->getAbsolutePosition().Z-Sldr->getAbsolutePosition().Z);
			core::vector2df PlyrPost=core::vector2df(Sldr->getAbsolutePosition().X,Sldr->getAbsolutePosition().Z);
			core::vector2df WeopPost=PlyrPost+backNorm*50;

			core::rect<float> wP(WeopPost.X+30,WeopPost.Y-30,WeopPost.X-30,WeopPost.Y+30);
			node.WeopPlace=wP;
			node.WeopPlace.repair();

			DSWArry.push_back(node);		
		}
		else if(x==2)
		{
			DeadSoldrWeop node;
			node.ShootCount=func.RandomRange(20,50);
			node.weopType=2;
		
			core::vector2df backNorm=core::vector2df(bm[0]->getAbsolutePosition().X-Sldr->getAbsolutePosition().X,bm[0]->getAbsolutePosition().Z-Sldr->getAbsolutePosition().Z);
			core::vector2df PlyrPost=core::vector2df(Sldr->getAbsolutePosition().X,Sldr->getAbsolutePosition().Z);
			core::vector2df WeopPost=PlyrPost-backNorm*50;

			core::rect<float> wP(WeopPost.X+30,WeopPost.Y-30,WeopPost.X-30,WeopPost.Y+30);
			node.WeopPlace=wP;
			node.WeopPlace.repair();

			DSWArry.push_back(node);	

		}
	}
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CSoldier_2 : public CSoldier
{
private:
bool m16Sldr;
	 bool bv;
	bool fs,fs2,fst;
	int n,nt6;
	//core::dimension2di SldrActions[30];//sidrs animations
WalkBorgData*wd;
public:
	CSoldier_2()
	{
	wd=0;
	m16Sldr=false;
 	bv=true;
	fs2=fs=fst=true;
	n=0;
	ft=0;
	nt6=0;

	SldrActions[0].set(221,245);	//dead
	
	SldrActions[6].set(201,211);	//hit1
	SldrActions[7].set(301,310);  //hit2
	SldrActions[10].set(1,32);		//walking
	SldrActions[11].set(380,400);   //runing
	SldrActions[15].set(33,80);		//stands
	SldrActions[16].set(81,200);    // ·› 
	SldrActions[17].set(33,34);     //stand short
	SldrActions[20].set(246,260);//Ì—›Õ «·”·«Õ
	SldrActions[21].set(261,281);//Ìÿ·ﬁ “«ÊÌ… „‰Œ›÷…
	SldrActions[22].set(301,321);//Ìÿ·ﬁ “«ÊÌ… „— ›⁄…

	}

	void setWalkBorgData(core::vector2df cnter,float ridus,core::vector2df p[],int speed,int animSPeed)
	{
		wd=new WalkBorgData();
		
		wd->cnterP.set(cnter);
		wd->radLen=ridus;
		wd->walkNormal[0].set((p[0]-cnter).normalize());
		wd->walkNormal[1].set((p[1]-cnter).normalize());
		wd->walkNormal[2].set((p[2]-cnter).normalize());
		wd->walkNormal[3].set((p[3]-cnter).normalize());


		wd->animSPeed=animSPeed;
		wd->walkSpeed=speed;


	}	
	
	void SOILDER_RENDER(int*blood,GGI*ggi,float timeelip)
	{
		if(active)
		{
			attack(blood,ggi);
			WAKING(timeelip);
		}
	}
	void WAKING(float timeelip)
	 {
		if((!stopWaking)&&(wd))//walk
		{
			if (ft==0)
			{
				int dirmove=func.RandomRange(0,3);
				wd->currWalkNorm=wd->walkNormal[dirmove];
				setDirectandSpeed(wd->walkNormal[dirmove],wd->walkSpeed);
				RotaSldrToDirect(wd->walkNormal[dirmove]);
				PlayAction(10,wd->animSPeed,true);	
			ft=1;
			}
			else if (ft==1)//stop
			{
					float currlen=(core::vector2df(Sldr->getAbsolutePosition().X,Sldr->getAbsolutePosition().Z)-wd->cnterP).getLength();
					if (currlen<0)
					currlen*=-1;

					if(wd->radLen<currlen)
					{
						MoveSpeed=0;
						PlayAction(15,wd->animSPeed,true);
						ft=2;
						tot=0;
						wd->standTime=func.RandomRange(30,100);
					}
			}
			else if (ft==2)//stand
			{
				tot++;
				if(wd->standTime>80)
				{
					if(tot==5)
					PlayAction(16,wd->animSPeed,false);

					if(tot==75)
					PlayAction(16,wd->animSPeed,false);
				}
				else if(wd->standTime>40)
				{
					if(tot==30)
					PlayAction(16,wd->animSPeed,false);

				}
				if(tot>wd->standTime)
				{
				ft=3;
				}

			}
			else if(ft==3)
			{
				wd->currWalkNorm*=-1;
				setDirectandSpeed(wd->currWalkNorm,wd->walkSpeed);
				RotaSldrToDirect(wd->currWalkNorm);
				PlayAction(10,wd->animSPeed,true);	
				ft=4;
			}
			else if(ft==4)
			{
				float currlen=(core::vector2df(Sldr->getAbsolutePosition().X,Sldr->getAbsolutePosition().Z)-wd->cnterP).getLength();
				if (currlen<0)
				currlen*=-1;

				if(currlen<5)
				{
					MoveSpeed=0;
					PlayAction(15,wd->animSPeed,true);
					ft=5;
					wd->standTime=func.RandomRange(0,5);
					tot=0;

				}

			}
			else if(ft==5)
			{
				tot++;
				if(tot>wd->standTime)
				{
				ft=0;
				}
			}
			
		}
	}
	void MovingAndFrmCnsr(float timeelip,int*blood,GGI*ggi)
	{
	if(active)
	{
			if (MoveSpeed)
			{
			core::vector2df sidrPost;
			sidrPost.X=Sldr->getAbsolutePosition().X;
			sidrPost.Y=Sldr->getAbsolutePosition().Z;

			sidrPost+=MoveDirect*MoveSpeed*timeelip;
			Sldr->setPosition(core::vector3df(sidrPost.X,Sldr->getAbsolutePosition().Y,sidrPost.Y));
			}

			if((currActinNum==21)||(currActinNum==22))//if action number is shoot 
			{

					if((263<=Sldr->getFrameNr())&&(Sldr->getFrameNr()<=265)||(303<=Sldr->getFrameNr())&&(Sldr->getFrameNr()<=305))
					{
						fire_shoot->setPosition(core::vector3df(13.225,19.64,61.747));
						if(currActinNum==22)
						fire_shoot->setPosition(core::vector3df(9.49,43.65,65.4));

						fire_shoot->setVisible(true);
						if (ff)
						{
						
						csnd->playSldrShootBrgnvSound(1000.0f/DistToPlyr);
						sldrShooting(blood,ggi);
						ff=false;
						}
						}
						else{
						fire_shoot->setVisible(false);
						ff=true;
						}
			}
			else
			{
			fire_shoot->setVisible(false);
			ff=true;
			}
	}
		
}

	void attack(int*blood,GGI*ggi)
	 {
		if (live&&active)
		{	
			n++;
			if(n==3)
			{
				if (state==3)
				RotaSldrToDirect(PlyrDirect);

				if(bv)
				{
					if (state==3)
					{
						if (fs)
						{
						StopWalking(true);
						MoveSpeed=0;
						PlayAction(20,30,false);
						bv=false;
						fs=false;
						fs2=true;
						fst=true;
						}
						else{
						if(DistToPlyr>1500)
						PlayAction(22,30,false);
						else
						PlayAction(21,30,false);

						bv=false;
						}
					}
					else if (state==2)
					{
						if(fs2)
						{
							PlayAction(15,30,false);
							fire_shoot->setVisible(false);
							fs=true;
							fs2=false;
						}
						else if (getBlood()<10)
						{
						followingHimRun();
						}
					}
				
				}
				else
				{
					if(Sldr->getFrameNr()==SldrActions[currActinNum].Height)
					bv=true;
				}
			 n=0;
			}
			
		}
	}


	void followingHimRun()
	  {
		nt6++;
		if (nt6==5)//every .5secand correct the path
		{
			if (fst)
			{
			PlayAction(10,30,true);
     		setDirectandSpeed(currPlyrDirect,70);
			RotaSldrToDirect(currPlyrDirect);
			fst=false;
			}
			else
			{
     		setDirectandSpeed(currPlyrDirect,100);
			RotaSldrToDirect(currPlyrDirect);
			}

			nt6=0;
		}
	  }
	void subtractBlood(int x)
	{
	Sdrblood-=x;
	
	if(see)
	state=3;
	else
	state=2;
	int Rhit=func.RandomRange(1,5);//’Ê  √·„ ⁄‘Ê«∆Ì

	StopWalking(true);

	if (Sdrblood<=0)
	{
	live=false;
	csnd->playSldrHitSound(700.0f/DistToPlyr,Rhit);
	}
	else
	{
		if (RplayFirstHit)
		{
			if (x==3)
			{
			PlayAction(7,30,false);//«’«»… ›Ì «·»ÿ‰
			csnd->playSldrHitSound(700.0f/DistToPlyr,Rhit);
			}
			else if (x==2)
			PlayAction(6,30,false);//«’«»… ›Ì «·—Ã·
			RplayFirstHit=0;
			MoveSpeed=0;
			csnd->playSldrHitSound(700.0f/DistToPlyr,Rhit);
		}
	}
	}
	 void slderDead()
	{

	PlayAction(0,30,false);
	stoprunTrack=active=live=see=false;
	state=0;
	fire_shoot->setVisible(false);
		if(currActinNum==0)
		{
			DeadSoldrWeop node;
			node.ShootCount=func.RandomRange(10,20);
			node.weopType=4;
		
			core::vector2df backNorm=core::vector2df(bm[0]->getAbsolutePosition().X-Sldr->getAbsolutePosition().X,bm[0]->getAbsolutePosition().Z-Sldr->getAbsolutePosition().Z);
			core::vector2df PlyrPost=core::vector2df(Sldr->getAbsolutePosition().X,Sldr->getAbsolutePosition().Z);
			core::vector2df WeopPost=PlyrPost+backNorm*50;


			core::rect<float> wP(WeopPost.X+30,WeopPost.Y-30,WeopPost.X-30,WeopPost.Y+30);
			node.WeopPlace=wP;
			node.WeopPlace.repair();

			DSWArry.push_back(node);

			
		}
	}
	//--------------------------------------------------------------------
	void setSolderType(bool isM16)
	{
		m16Sldr=isM16;
	}
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CSoldier_3 : public CSoldier
{
private:

WalkData*wd;
runTrackData*rtd;
bool bv,bv1,fs,fst,fst2,fst3,fst4,fst5,fst6,fst_stat2e,enter5;
int nt1,nt2,n2,n3,cont;
int Rmovdir; // random direct 
core::vector2df runDir;// the direct of solider when run follow the player
int Rtbd;//random to getattacktype function
int Rmtd;//random max attck distance
int timeBetnAtt;//time between stater attack
int ft2,indx;
int attnum;

public:
	CSoldier_3()
	{
	wd=0;
	rtd=0;
	attackActLen=2;
	readyActLen=20;
	nt1=n2=nt2=n3=indx=ft2=cont=0;
	fst6=fst5=fst4=fst=fst2=fst3=bv=bv1=fs=fst_stat2e=enter5=true;
	attnum=tot=0;

	//ltr=true;
	nt1=Rmovdir=0;
	Rtbd=func.RandomRange(200,500);
	Rmtd=func.RandomRange(3000,4000);


	SldrActions[0].set(221,245);	//dead
	SldrActions[1].set(401,422);
	SldrActions[2].set(507,541);

	SldrActions[6].set(201,211);	//hit1
	SldrActions[7].set(301,310);  //hit2
	
	SldrActions[10].set(1,32);		//walking
	SldrActions[11].set(380,400);   //runing

	SldrActions[15].set(33,80);		//stands
	SldrActions[16].set(81,200);    // ·› 
	SldrActions[17].set(33,34);     //stand short
	
	SldrActions[20].set(246,280); //Ì—›Õ «·”·«Õ ÊÌÿ·ﬁ «·‰«—
	SldrActions[21].set(261,280);//Ì” „— ›Ì «ÿ·«ﬁ «·‰«—
	SldrActions[22].set(311,333);// walk right Shoot
	SldrActions[23].set(334,356);//walk left shoot
	SldrActions[24].set(357,379);//walk back
	SldrActions[25].set(246,260); //Ì—›Õ «·”·«Õ ÊÌÿ·ﬁ «·‰«—
	
	SldrActions[26].set(279,280); //ready to shoot
	
	SldrActions[27].set(311,333);// Ready right 
	SldrActions[28].set(334,356);// ready left


SldrActions[30].set(459,476);//Ì‰“· Œ·› «·”« —
SldrActions[31].set(476,506);//«‰ ÷«— Œ·› «·”« —
SldrActions[32].set(423,442);//  Ìÿ·⁄ „‰ Œ·› «·”« — ÊÌÿŒ ÿ·ﬁ Ì‰

SldrActions[35].set(435,442);//»ÿ·ﬁ ÿ·ﬁ Ì‰
SldrActions[36].set(435,438);//»ÿ·ﬁ ÿ·ﬁ…
SldrActions[37].set(441,459);//„”«›… ›«÷Ì…





	}
	void setWalkData(core::vector2df p[],int speed,float animSPeed,bool is4type,bool running,bool Active)
	{

		wd=new WalkData();
		
		wd->point[0].set(p[0]);
		wd->point[1].set(p[1]);
		wd->point[2].set(p[2]);
		wd->point[3].set(p[3]);
	

		wd->Len[0]=(p[1]-p[0]).getLength();
		wd->Len[1]=(p[2]-p[1]).getLength();
		wd->Len[2]=(p[3]-p[2]).getLength();
		wd->Len[3]=(p[3]-p[0]).getLength();
	
		// ŒÊÌ· «·ÿÊ· ·⁄œœ „ÊÃ»
		if(wd->Len[0]<0)
		wd->Len[0]*=-1;
		if(wd->Len[1]<0)
		wd->Len[1]*=-1;
		if(wd->Len[2]<0)
		wd->Len[2]*=-1;
		if(wd->Len[3]<0)
		wd->Len[3]*=-1;
		///////////////////////////////////
		wd->walkNormal[0].set((p[1]-p[0]).normalize());
		wd->walkNormal[1].set((p[2]-p[1]).normalize());
		wd->walkNormal[2].set((p[3]-p[2]).normalize());
		wd->walkNormal[3].set((p[0]-p[3]).normalize());


		wd->animSPeed=animSPeed;
		wd->walkSpeed=speed;
		wd->Is4point=is4type;
		wd->active=Active;
		
			if(running)
			wd->actionNum=11;
			else
			wd->actionNum=10;

		ft=0;
		if(!is4type)
		{
		wd->walkNormal[1].set((p[0]-p[1]).normalize());
		wd->Len[1]=wd->Len[0];
		}

	}	
	void setrunTrackData(int pointCount,core::vector2df p[],int runspeed,int animSpeed,bool running,bool active)
	{
	rtd=new runTrackData();
	rtd->Pointcount=pointCount;
	rtd->pontes=new core::vector2df[pointCount+1];
	rtd->DirNorm=new core::vector2df[pointCount];
	rtd->Len=new float[pointCount];

		for(int i=0;i<pointCount;i++)
		rtd->pontes[i+1].set(p[i]);
		for(int i=0;i<pointCount-1;i++)
		{

			rtd->Len[i+1]=(p[i+1]-p[i]).getLength();
			rtd->DirNorm[i+1].set((p[i+1]-p[i]).normalize());	
			
			if(rtd->Len[i+1]<0)
			rtd->Len[i+1]*=-1;


		
		}

	rtd->active=active;
	rtd->running=running;
	rtd->runSpeed=runspeed;
	rtd->animSpped=animSpeed;
	
	if(running)
	rtd->actionNum=11;
	else
	rtd->actionNum=10;

	if(active)
	stopWaking=true;
	else
	stopWaking=false;


	}
	void setWalkActive(bool active)
	{
		if(!wd)
		wd->active=active;
	}
	void setrunTrackActive(bool active)
		{
			if(rtd)
			{
			rtd->active=active;
			stopWaking=true;
			}

		}

	void MovingAndFrmCnsr(float timeelip,int*blood,GGI*ggi)
	{
		if(active)
		{
			if (MoveSpeed)
			{
			core::vector2df sidrPost;
			sidrPost.X=Sldr->getAbsolutePosition().X;
			sidrPost.Y=Sldr->getAbsolutePosition().Z;

			sidrPost+=MoveDirect*MoveSpeed*timeelip;
			Sldr->setPosition(core::vector3df(sidrPost.X,Sldr->getAbsolutePosition().Y,sidrPost.Y));
			}
			//show fire bool 
			if((currActinNum==20)||(currActinNum==21))//if action number is shoot 
			{
				if(((263<=Sldr->getFrameNr())&&(Sldr->getFrameNr()<=265))||((267<=Sldr->getFrameNr())&&(Sldr->getFrameNr()<=269))||((271<=Sldr->getFrameNr())&&(Sldr->getFrameNr()<=273)))
				{
					fire_shoot->setPosition(core::vector3df(3,50,55));
					fire_shoot->setVisible(true);
					if (ff)
					{
					csnd->playSldrShootSound(400.0f/DistToPlyr);
					sldrShooting(blood,ggi);
					//PlaySldrShootFireline();
					ff=false;
					}
					}
					else{
					fire_shoot->setVisible(false);
					ff=true;
					}
			}
			else if ((currActinNum==35)||(currActinNum==36)||(currActinNum==32))//attack right
			{
				if((435<=Sldr->getFrameNr())&&(Sldr->getFrameNr()<=437)||(439<=Sldr->getFrameNr())&&(Sldr->getFrameNr()<=440))
				{
					fire_shoot->setPosition(core::vector3df(10,35,55));
					fire_shoot->setVisible(true);
					if (ff)
					{
					csnd->playSldrShootSound(400.0f/DistToPlyr);
					sldrShooting(blood,ggi);
					//PlaySldrShootFireline();
					ff=false;
					}
				}
				else{
				fire_shoot->setVisible(false);
				ff=true;
				}
			}
			else{
			fire_shoot->setVisible(false);
			ff=true;
			}
		}

	
	}	

	void SOILDER_RENDER(int*blood,GGI*ggi,float timeelip)
	{
		if(active)
		{
			attack(blood,ggi);
			WAKING(timeelip);
			RUNTRUCK();
		}
	}

	void attack(int*blood,GGI*ggi)
	 {
		
		 if (state==3)
		 {

				if(fst6)//ÌœŒ· „—… Ê«Õœ… ›ﬁÿ
				{
				setrunTrackActive(true);
				fst6=false;
				}

		 fst_stat2e=true;
		
			 if (n2==0)
			 { 

					if(cont==0)
					{
						 
						if(rtd)
						{
						int disToPlyr=getDistanceFormPlyr();
						float disToSater=(core::vector2df(Sldr->getAbsolutePosition().X,Sldr->getAbsolutePosition().Z)-rtd->pontes[rtd->Pointcount]).getLength();
						if (disToSater<0)
						disToSater*=-1;
							
							if(disToPlyr>disToSater+300)
							{
								if(fst4&&!(stoprunTrack))
								{
								rtd->runSpeed+=50;
								rtd->animSpped+=20;
								rtd->actionNum=11;

								Sldr->setAnimationSpeed(currActionSpeed+20);
								MoveSpeed+=50;
								fst4=false;
								}
								
								if(stoprunTrack)//«–« Ê’· «·Ã‰œÌ ·„ﬂ«‰ «·”« —
								{
								cont=2;
								attackActLen=1;
								}
							}
							else
							{
							rtd->active=false;
							cont=1;	
							attackActLen=2;
							}
						}
					}
					else if(cont==1)
					{
					attack_stand();
					}
					else if(cont==2)
					{
					attack_sater();
					}
			 }
		 }
		else if (state==2)
		{
		fst5=true;
			if(fst_stat2e)
			{
				if(cont==1){
					PlayAction(17,30,false);
					fire_shoot->setVisible(false);
					fs=true;
				}
				else if(cont==2)
				{
					if(Sldr->getFrameNr()==SldrActions[currActinNum].Height)//if solder action is finsh
					{
						if(currActinNum==31)
						{
						}
						else if((currActinNum==35)||(currActinNum==36)||(currActinNum==37))
						{
							int x=func.RandomRange(0,1);
							if(x)
							PlayAction(36,30,false);
							else
							PlayAction(31,30,false);
						}
						else if((currActinNum==20)||(currActinNum==21))
						{
						PlayAction(15,30,false);

						}
					fire_shoot->setVisible(false);
					fs=true;
					bv1=bv=true;
					}
					


				}

			fst_stat2e=false;
			}
		 }
		 
		 n2++;
			 if (n2>=attackActLen)
			 n2=0;

	}

	void attack_sater()
	{
	
	if(nt2==0)
	{
		if(chichSaterSee())
		{
		
		 attnum=getAttackType();
		

		}
		else//attack stand
		{
			attnum=3;
		}
		nt2=0;

	}
	nt2++;
	if(nt2>=timeBetnAtt)//1 loop=0.2 sec
	nt2=0;
		
			if(attnum==1)
			{
			Attack_underSater();
			fst5=true;
			}
			else if(attnum==2)
			{
			takeSater();
			
			}
			else if(attnum==3)
			{
			attack_stand();
			
			}
	}
	void takeSater()
	{
		if (fst5)
		{
			if((currActinNum==35)||(currActinNum==36)||(currActinNum==32)||(currActinNum==20)||(currActinNum==21)||(currActinNum==15)||(currActinNum==16))
			{
			PlayAction(30,33,false);
			RotaSldrToDirect(PlyrDirect);
			fst5=false;
			}
		}
		else
		{
			n3++;
			if(n3>=10)
			{
			PlayAction(31,25,false);
			n3=0;
			}
			
		}


	}
	void Attack_underSater()
	{

				if(bv)
				{
					if((currActinNum==31)||(currActinNum==30))
					{
					PlayAction(32,35,false);
					}
					else
					{
						int num=func.RandomRange(0,1);	
						if(num==0)
						PlayAction(36,35,false);
						else if(num==1)
						PlayAction(35,35,false);
					}
				bv=false;
				}

			if(Sldr->getFrameNr()==SldrActions[currActinNum].Height)//if solder action is finsh
			bv=true;




	RotaSldrToDirect(PlyrDirect);
	}

	bool chichSaterSee()
	{
			core::vector3df intersection;
			core::triangle3df tri;
			core::line3df line;
			line.start=PlyrPost;
			line.end=getpostion()+core::vector3df(0,-20,0);

			if(!(PlyrPost.X==0))
			{
				if (Devic->getSceneManager()->getSceneCollisionManager()->getCollisionPoint(line,SEESelector,intersection,tri))
				{
				return true;	
				}
				else{
				return false;
				}
			}
			else
			return false;


	}
	int getAttackType()
	{
	 int at=func.RandomRange(1,2);
	
	 if(at==1)
	timeBetnAtt= func.RandomRange(15,25);
	else if(at==2)
	timeBetnAtt= func.RandomRange(10,15);
	
	 return at;
	}
	void attack_stand()
	 {
		if (live&&active)
		{	

				if(bv)
				{
					if (state==3)
					{
						if (fs)
						{
						MoveSpeed=0;
						PlayAction(20,40,false);
						bv=false;
						fs=false;
						}
						else{
						PlayAction(21,30,false);
						bv=false;
						}
					}
				}

			if(Sldr->getFrameNr()==SldrActions[currActinNum].Height)//if solder action is finsh
			bv=true;
			if (currActinNum==20||currActinNum==21)
			RotaSldrToDirect(PlyrDirect);
		}
	}
	void subtractBlood(int x)
	{
	Sdrblood-=x;
	
	if(see)
	state=3;
	else
	state=2;
	
	StopWalking(true);
	int Rhit=func.RandomRange(1,5);//’Ê  √·„ ⁄‘Ê«∆Ì
	if (Sdrblood<=0)
	{
	live=false;
	csnd->playSldrHitSound(600.0f/DistToPlyr,Rhit);
	}
	else
	{
		if (RplayFirstHit)
		{
			if (x==3)
			{
			//PlayAction(7,30,false);//«’«»… ›Ì «·»ÿ‰
			csnd->playSldrHitSound(600.0f/DistToPlyr,Rhit);
			RplayFirstHit=0;
			}
			else if (x==2)
			//PlayAction(6,30,false);//«’«»… ›Ì «·—Ã·
			RplayFirstHit=0;
			//MoveSpeed=0;
			csnd->playSldrHitSound(600.0f/DistToPlyr,Rhit);
		}
	}
	}




	void WAKING(float timeelip)
	 {
	if((!stopWaking)&&(wd))
	{
		if (wd->active&&live)
		{
			//=================================================================================//
			//==============================IF FOUR POINT=======================================//
			if (wd->Is4point)
			{
				if (ft==0)//move1
				{
					Sldr->setPosition(core::vector3df(wd->point[0].X,Sldr->getAbsolutePosition().Y,wd->point[0].Y));
					setDirectandSpeed(wd->walkNormal[0],wd->walkSpeed);
					RotaSldrToDirect(wd->walkNormal[0]);
					PlayAction(wd->actionNum,wd->animSPeed,true);	
					ft=1;
				}	
				else if (ft==1)//stop1
				{

					float currlen=(core::vector2df(Sldr->getAbsolutePosition().X,Sldr->getAbsolutePosition().Z)-wd->point[0]).getLength();
					if (currlen<0)
					currlen*=-1;

					if(wd->Len[0]<=currlen)
					{
						MoveSpeed=0;
						PlayAction(15,wd->animSPeed,true);
						ft=2;
						tot=0;
					}

				}
				else if (ft==2)//stand
				{
				tot+=timeelip;
					if (tot>3)
					ft=3;	
				}
				else if (ft==3)//move2
				{
					Sldr->setPosition(core::vector3df(wd->point[1].X,Sldr->getAbsolutePosition().Y,wd->point[1].Y));
					setDirectandSpeed(wd->walkNormal[1],wd->walkSpeed);
					RotaSldrToDirect(wd->walkNormal[1]);
					PlayAction(wd->actionNum,wd->animSPeed,true);	
					ft=4;
				}
				else if (ft==4)//stop2
				{
					float currlen=(core::vector2df(Sldr->getAbsolutePosition().X,Sldr->getAbsolutePosition().Z)-wd->point[1]).getLength();
					if (currlen<0)
					currlen*=-1;

					if(wd->Len[1]<currlen)
					{
						MoveSpeed=0;
						PlayAction(16,wd->animSPeed,true);
						ft=5;
						tot=0;
					}
				}
				else if (ft==5)//stand2
				{
				tot+=timeelip;
					if (tot>5)
					ft=6;
				}
				else if (ft==6)//move3
				{
					Sldr->setPosition(core::vector3df(wd->point[2].X,Sldr->getAbsolutePosition().Y,wd->point[2].Y));
					setDirectandSpeed(wd->walkNormal[2],wd->walkSpeed);
					RotaSldrToDirect(wd->walkNormal[2]);
					PlayAction(wd->actionNum,wd->animSPeed,true);	
					ft=7;
				}
				else if (ft==7)//stop3
				{
					float currlen=(core::vector2df(Sldr->getAbsolutePosition().X,Sldr->getAbsolutePosition().Z)-wd->point[2]).getLength();
					if (currlen<0)
					currlen*=-1;

					if(wd->Len[2]<currlen)
					{
						MoveSpeed=0;
						PlayAction(15,wd->animSPeed,true);
						ft=8;
						tot=0;
					}
				}
				else if (ft==8)//stand
				{
				tot+=timeelip;
					if (tot>5)
					ft=9;
				}
				else if (ft==9)//move4
				{
					Sldr->setPosition(core::vector3df(wd->point[3].X,Sldr->getAbsolutePosition().Y,wd->point[3].Y));
					setDirectandSpeed(wd->walkNormal[3],wd->walkSpeed);
					RotaSldrToDirect(wd->walkNormal[3]);
					PlayAction(wd->actionNum,wd->animSPeed,true);	
					ft=10;
				}
				else if (ft==10)//stop4
				{

					float currlen=(core::vector2df(Sldr->getAbsolutePosition().X,Sldr->getAbsolutePosition().Z)-wd->point[3]).getLength();
					if (currlen<0)
					currlen*=-1;

					if(wd->Len[3]<currlen)
					{
						MoveSpeed=0;
						PlayAction(16,wd->animSPeed,true);
						ft=11;
						tot=0;
					}
				}
				else if (ft==11)//stand4
				{
				tot+=timeelip;
					if (tot>5)
					ft=0;
				}
			}
			//=================================================================================//
			//==============================IF TWO POINT=======================================//
			else
			{
				if (ft==0)//move1
				{
					Sldr->setPosition(core::vector3df(wd->point[0].X,Sldr->getAbsolutePosition().Y,wd->point[0].Y));
					setDirectandSpeed(wd->walkNormal[0],wd->walkSpeed);
					RotaSldrToDirect(wd->walkNormal[0]);
					PlayAction(wd->actionNum,wd->animSPeed,true);	
					ft=1;
				}	
				else if (ft==1)//stop1
				{

					float currlen=(core::vector2df(Sldr->getAbsolutePosition().X,Sldr->getAbsolutePosition().Z)-wd->point[0]).getLength();
					if (currlen<0)
					currlen*=-1;

					if(wd->Len[0]<currlen)
					{
						MoveSpeed=0;
						PlayAction(15,wd->animSPeed,true);
						ft=2;
						tot=0;
					}

				}
				else if (ft==2)//stand
				{
				tot+=timeelip;
					if (tot>3)
					ft=3;	
				}
				else if (ft==3)//move2
				{
					Sldr->setPosition(core::vector3df(wd->point[1].X,Sldr->getAbsolutePosition().Y,wd->point[1].Y));
					setDirectandSpeed(wd->walkNormal[1],wd->walkSpeed);
					RotaSldrToDirect(wd->walkNormal[1]);
					PlayAction(wd->actionNum,wd->animSPeed,true);	
					ft=4;
				}
				else if (ft==4)//stop2
				{
					float currlen=(core::vector2df(Sldr->getAbsolutePosition().X,Sldr->getAbsolutePosition().Z)-wd->point[1]).getLength();
					if (currlen<0)
					currlen*=-1;

					if(wd->Len[1]<currlen)
					{
						MoveSpeed=0;
						PlayAction(16,wd->animSPeed,true);
						ft=5;
						tot=0;
					}
				}
				else if (ft==5)//stand2
				{
				tot+=timeelip;
					if (tot>5)
					ft=0;
				}
		
		}
	 }
 }
}
	void RUNTRUCK()
	{
	if((!stoprunTrack)&&(rtd))
	{
		if(rtd->active&&active)
		{
			if(ft2==0)
			{
				rtd->pontes[0]=core::vector2df(Sldr->getAbsolutePosition().X,Sldr->getAbsolutePosition().Z);
				rtd->Len[0]=(rtd->pontes[1]-rtd->pontes[0]).getLength();
				if(rtd->Len[0]<0)
				rtd->Len[0]*=-1;
				rtd->DirNorm[0]=(rtd->pontes[1]-rtd->pontes[0]).normalize();			
				ft2=1;

			}
			else if(ft2==1)
			{
				setDirectandSpeed(rtd->DirNorm[indx],rtd->runSpeed);
				RotaSldrToDirect(rtd->DirNorm[indx]);
				PlayAction(rtd->actionNum,rtd->animSpped,true);	

				ft2=2;
			}
			else if (ft2==2)
			{
			core::vector2df currPo=core::vector2df(Sldr->getAbsolutePosition().X,Sldr->getAbsolutePosition().Z);
			float currlen=(rtd->pontes[indx]-currPo).getLength();
			if (currlen<0)
			currlen*=-1;

					if(currlen>=rtd->Len[indx])
					{
					ft2=1;
					indx++;
					}

					if(indx==rtd->Pointcount)
					{
					stoprunTrack=true;
					MoveSpeed=0;
					PlayAction(15,30,true);
					}
			}
		}
	}
	}
	void slderDead()
	{

	//ÿÌÕ… «·Ã‰œÌ »‘ﬂ· ⁄‘Ê«∆Ì
		int x=func.RandomRange(0,2);
x=1;
	PlayAction(x,30,false);
	stoprunTrack=active=live=see=false;
	state=0;
	fire_shoot->setVisible(false);
		//add Solder Weopen NOde

		if((x==0)||(x==1))
		{
			DeadSoldrWeop node;
			node.ShootCount=func.RandomRange(20,50);
			node.weopType=2;
		
			core::vector2df backNorm=core::vector2df(bm[0]->getAbsolutePosition().X-Sldr->getAbsolutePosition().X,bm[0]->getAbsolutePosition().Z-Sldr->getAbsolutePosition().Z);
			core::vector2df PlyrPost=core::vector2df(Sldr->getAbsolutePosition().X,Sldr->getAbsolutePosition().Z);
			core::vector2df WeopPost=PlyrPost+backNorm*50;

			core::rect<float> wP(WeopPost.X+30,WeopPost.Y-30,WeopPost.X-30,WeopPost.Y+30);
			node.WeopPlace=wP;
			node.WeopPlace.repair();

			DSWArry.push_back(node);		
		}
		else if(x==2)
		{
			DeadSoldrWeop node;
			node.ShootCount=func.RandomRange(20,50);
			node.weopType=2;
		
			core::vector2df backNorm=core::vector2df(bm[0]->getAbsolutePosition().X-Sldr->getAbsolutePosition().X,bm[0]->getAbsolutePosition().Z-Sldr->getAbsolutePosition().Z);
			core::vector2df PlyrPost=core::vector2df(Sldr->getAbsolutePosition().X,Sldr->getAbsolutePosition().Z);
			core::vector2df WeopPost=PlyrPost-backNorm*50;

			core::rect<float> wP(WeopPost.X+30,WeopPost.Y-30,WeopPost.X-30,WeopPost.Y+30);
			node.WeopPlace=wP;
			node.WeopPlace.repair();

			DSWArry.push_back(node);	

		}
	}
};
#endif