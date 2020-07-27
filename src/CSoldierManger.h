/*
writen by (Younes khafaja) - 2008-2009
You are free to use this code as you see fit
email : lighting-team@hotmail.com
*/
#ifndef SDRM_H
#define SDRM_H
#include <irrlicht.h>
#include"CSoldier.h"
#include"GameGuiInterface.h"
#include <irrKlang.h>
#include"Csounds.h"
#include"Functions.h"
using namespace irr;
class CSoldierManger
{
protected:
scene::IAnimatedMesh*SDRmesh;

IrrlichtDevice *Devic;
int activeNum;
int lvlSlderNum;
Functins func;
int*Pblood;
GGI*Ggi;

CSolderSounds*csnd;

bool isPlyrAttck;//true if solder attack from splder
public:
	CSoldier*Sldrs[30];
core::array<int>ActveSldrs;
void setHitSolder(int sdrNum,core::vector3df post,int i)
{
	if (Sldrs[sdrNum]->getActive())	
	{
		float high=post.Y-Sldrs[sdrNum]->getpostion().Y;
		int ca=Sldrs[sdrNum]->getcurrplayAction();
		if((ca==32)||(ca==35)||(ca==36))//ÇÐÇ ÈØÎ ãä ÎáÝ ÓÇÊÑ 
		{
			if (high>40)
			Sldrs[sdrNum]->subtractBlood(10);
			else if (high>0)
			Sldrs[sdrNum]->subtractBlood(3);
			else if (high<=0)
			Sldrs[sdrNum]->subtractBlood(2);
		}
		else
		{
			if (high>70)
			Sldrs[sdrNum]->subtractBlood(10);
			else if (high>0)
			Sldrs[sdrNum]->subtractBlood(3);
			else if (high<=0)
			Sldrs[sdrNum]->subtractBlood(2);
		}

			if (!Sldrs[sdrNum]->GetisLive())
			{
			Sldrs[sdrNum]->slderDead();
			ActveSldrs.erase(i);
			}
	}
}

//-------------------------------------------------------------------------------------------------------------------------
void selectSeePlayer(core::vector3df camPost,scene::ITriangleSelector*sldrSeeSelector)
{
if (ActveSldrs.size())//if no active stop chick 
{
			static int i=-1;
			core::vector3df intersection=core::vector3df(0,0,0);
			core::triangle3df tri;

		
			if((i+1)<ActveSldrs.size())
			i++;
			else
			i=0;
			int SldNum=ActveSldrs[i];

	
				core::line3df line;
				line.start=camPost;
				line.end=Sldrs[SldNum]->getpostion()+core::vector3df(0,70,0);
				
				if (Devic->getSceneManager()->getSceneCollisionManager()->getCollisionPoint(line,sldrSeeSelector,intersection,tri))
				{
					Sldrs[SldNum]->settriAndIntersection(tri,core::vector2df(intersection.X,intersection.Z));
					Sldrs[SldNum]->setSee(false);
				}
				else{
				Sldrs[SldNum]->setSee(true);
				intersection=core::vector3df(0,0,0);
				}
				
				//alculate the direction of plyer from solder
				core::vector2df Pnorm(line.start.X-line.end.X,line.start.Z-line.end.Z);		//	
				Pnorm=Pnorm.normalize();
				//add the current direct
				Sldrs[SldNum]->setCurrPlyrDirect(Pnorm);
				//calculate  distance between solder and player
				Sldrs[SldNum]->setDistanceFormPlyr(core::line2di(line.start.X,line.start.Z,line.end.X,line.end.Z).getLength());			

				//if solider see player add the direction 
				if(Sldrs[SldNum]->getsee())
				{
					Sldrs[SldNum]->setPlyrDirect(Pnorm);															//
					Sldrs[SldNum]->setPlyrPost(camPost);
				}
				
		
	
}
	
}

void selectSlderState(core::vector3df camPost)
{
if (ActveSldrs.size())//if no active stop chick 
{
			static int id=-1;
			if((id+1)<ActveSldrs.size())
			id++;
			else
			id=0;
			int SldNum=ActveSldrs[id];
			///////////////////////////////
			if(Sldrs[SldNum]->getState()==1)
			{	
				if(Sldrs[SldNum]->getsee())
				{		
					
					core::vector2df Plyrpo=core::vector2df(camPost.X,camPost.Z);
					core::vector2df cntrSeePo=Sldrs[SldNum]->getCnterSeePost();

				
					float disfrmPo=(cntrSeePo-Plyrpo).getLength();//disane from player and point
					if(disfrmPo<0)
					disfrmPo*=-1;				
	
						//chick if from fornt 
						if(disfrmPo<Sldrs[SldNum]->getSeeLen())
						{
						Sldrs[SldNum]->setState(3);
						}
						//chick if from back 
						else if(Sldrs[SldNum]->getDistanceFormPlyr()<Sldrs[SldNum]->getSeeBackLen())
						{
						Sldrs[SldNum]->setState(3);
						}
						//if hear and see 
						else if(Sldrs[SldNum]->getHear())
						{
						Sldrs[SldNum]->setState(3);
						}
					// getCerfulDistaneÇÐÇ Êã ÇØáÇÞ ÇáäÇÑ Úáì ÇáÇÚÈ æåæ ÈÇáÞÑÈ ãä ÌäÏí ãÓÇÝÉ ÇÞá ãä  
						if((isPlyrAttck)&&(Sldrs[SldNum]->getDistanceFormPlyr()<Sldrs[SldNum]->getCerfulDistane()))
						Sldrs[SldNum]->setState(2);



				}		
			}
			else if (Sldrs[SldNum]->getState()==2)
			{
				if(Sldrs[SldNum]->getsee())
				{			
					Sldrs[SldNum]->setState(3);
				}
			}
			else if (Sldrs[SldNum]->getState()==3)
			{
				if(!(Sldrs[SldNum]->getsee()))
				Sldrs[SldNum]->setState(2);
			}

}
}

void selectSldrHear(core::vector3df camPost)
{
int arrSize=ActveSldrs.size();
	for(int i=0;i<arrSize;i++)
	{
	 int sdrNum=ActveSldrs[i];
		if (Sldrs[sdrNum]->getState()==1)
		{
			if (Sldrs[sdrNum]->getsee())
			{
				int hl=Sldrs[sdrNum]->getHearLen();
				int dpl=Sldrs[sdrNum]->getDistanceFormPlyr();
				if(hl>dpl)
				{
				Sldrs[sdrNum]->setHear(true);
				}

			}
			else
			{
			//if hear shoot and dont see him 
				int dpl=Sldrs[sdrNum]->getDistanceFormPlyr();
				int h2=Sldrs[sdrNum]->getHearLen();

				if(h2>dpl)
				{
					if(!(Sldrs[sdrNum]->getPlyerPost().X==1))//if see hem last
					Sldrs[sdrNum]->setState(2);
					else
					Sldrs[sdrNum]->setrunTrackActive(true);
				}
			}
		}


	}

}

void setSldrstopAttack()
{
int arrSize=ActveSldrs.size();
	for(int i=0;i<arrSize;i++)
	{
	 int sdrNum=ActveSldrs[i];

		if (Sldrs[sdrNum]->getState()==3)
		{
			Sldrs[sdrNum]->PlayAction(15,30,true);
			Sldrs[sdrNum]->fireShootVisble(false);
		}


	}

}

void selectIsPlyrAttck()
{
int arrSize=ActveSldrs.size();
	for(int i=0;i<arrSize;i++)
	{
	 int sdrNum=ActveSldrs[i];
		if (Sldrs[sdrNum]->getState()==3)
		{
		isPlyrAttck=true;
		break;
		}
		else
		isPlyrAttck=false;


	}

}

scene::IAnimatedMesh*GetSolderMesh(int x)
{
return Sldrs[x]->getSolderMesh();
}
scene::IAnimatedMeshSceneNode*GetSolderSnode(int x)
{
return Sldrs[x]->getSoldernode();
}
void _Destructor()
{
delete csnd;
csnd=0;
delete Ggi;
Ggi=0;

Sldrs[0]->_Destrctor();
Sldrs[1]->_Destrctor();
Sldrs[2]->_Destrctor();
Sldrs[3]->_Destrctor();
Sldrs[4]->_Destrctor();
Sldrs[5]->_Destrctor();
Sldrs[6]->_Destrctor();
Sldrs[7]->_Destrctor();
Sldrs[8]->_Destrctor();
Sldrs[9]->_Destrctor();
Sldrs[10]->_Destrctor();






}


//-----------------------------------------------------------------------------------------------------------------------
void RenderDrowSolders()
{

}
virtual void RenderSolders(float timeeilp,core::vector3df camP,scene::ITriangleSelector*sldrSeeSelector){}
virtual void selectActives(core::vector3df plyrPos){}
};


class CSoldierManger_1 : public CSoldierManger
{
private:
core::rect<int> rec1,rec2,rec3;
bool enterRect1,enterRect2,enterRect3;
public:
CSoldierManger_1(IrrlichtDevice *Dev,ISoundEngine* SEng,scene::IMetaTriangleSelector*mselector,scene::ITriangleSelector*Seeselector,int&blood,GGI*ggi)
{
enterRect1=enterRect2=enterRect3=true;
Devic=Dev;
Pblood=&blood;
Ggi=ggi;
csnd=new CSolderSounds(SEng);

//-CSoldier_1-->normal soldier
//-CSoldier_2-->sniper soldier
	Dev->getFileSystem()->addZipFileArchive("data/ascr.pk3");
core::vector2df po[6];
//--------------------------- 0 íØáÚ Úáì ÇáÌÈá----------------------------------
	Sldrs[0]=new CSoldier_1();
	Sldrs[0]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("sldrAA0.b3d"),core::vector3df(-1182,100,7666),mselector,Seeselector,0);
	Sldrs[0]->setadvanceData(1000,2000,5000,6000,1000);
	po[0].set(-1182,7666);
	po[1].set(-449,6853);
	po[2].set(-1383,6210);
	po[3].set(-2053,6870);
	Sldrs[0]->setWalkData(po,70,30,true,false,true);
	po[0].set(-507,6563);
	po[1].set(236,5288);
	po[2].set(2870,2260);
	Sldrs[0]->setrunTrackData(3,po,100,35,true,false);
//---------------------------1---------------------------------------------------------------
	Sldrs[1]=new CSoldier_3();
	Sldrs[1]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("sldrC1.b3d"),core::vector3df(-807.7,100,7989.8),mselector,Seeselector,1);
	Sldrs[1]->setadvanceData(1000,1700,1000,1000,3000);
	po[0].set(-982,7870);
	Sldrs[1]->setrunTrackData(1,po,100,35,true,false);
	Sldrs[1]->RotaSldrToDirect(core::vector2df(0,-1));
//---------------------------2----------------------------------------------------------------
	Sldrs[2]=new CSoldier_1();
	Sldrs[2]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("sldrA0.b3d"),core::vector3df(6513,100,6730),mselector,Seeselector,2);
	Sldrs[2]->setadvanceData(1000,2000,1000,3000,1000);
	po[0].set(6513,6730);
	po[1].set(6513,-1142);
	Sldrs[2]->setWalkData(po,70,30,false,false,true);
//---------------------------3----------------------------------------------------------------
	Sldrs[3]=new CSoldier_1();
	Sldrs[3]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("sldrA1.b3d"),core::vector3df(6329.3,100,2259.18),mselector,Seeselector,4);
	Sldrs[3]->setadvanceData(2000,2000,1000,3000);
	Sldrs[3]->RotaSldrToDirect(core::vector2df(-1,0));
//---------------------------4----------------------------------------------------------------
	Sldrs[4]=new CSoldier_3();
	Sldrs[4]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("sldrC2.b3d"),core::vector3df(6235,100,1484),mselector,Seeselector,4);
	Sldrs[4]->setadvanceData(2000,2000,3000,5000);
	Sldrs[4]->RotaSldrToDirect(core::vector2df(-1,0));
	po[0].set(6129.5,1492);
	Sldrs[4]->setrunTrackData(1,po,100,30,true,false);
//----------------------5-sniper---------------------------------------------------------------
	core::vector2df Cntr;
	Sldrs[5]=new CSoldier_2();
	Sldrs[5]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("sldrB1.b3d"),core::vector3df(6782.4,800, -866.08),mselector,Seeselector,5);
	Sldrs[5]->setadvanceData(2000,3000,2000,5000,3000);
	Cntr.set(6782.4,-866.08);
	po[0].set(6732.4,-896.7);
	po[1].set(6813,-926.6);
	po[2].set(6796.6,-853.5);
	po[3].set(6764.6,-822);
	Sldrs[5]->setWalkBorgData(Cntr,40,po,40,30);
//----------------------6-sniper---------------------------------------------------------------
	Sldrs[6]=new CSoldier_2();
	Sldrs[6]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("sldrB2.b3d"),core::vector3df(6798.4,800,6433),mselector,Seeselector,6);
	Sldrs[6]->setadvanceData(2000,3000,2000,5000,3000);
	Cntr.set(6798.4,6433);
	po[0].set(6735.7,6414.8);
	po[1].set(6781.7,6480.6);
	po[2].set(6852.3,6470.8);
	po[3].set(6826.5,6374.7);
	Sldrs[6]->setWalkBorgData(Cntr,20,po,40,30);
	
//----------------------7-sniper---------------------------------------------------------------
	Sldrs[7]=new CSoldier_2();
	Sldrs[7]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("sldrB3.b3d"),core::vector3df(14070.878, 800,6470.916),mselector,Seeselector,7);
	Sldrs[7]->setadvanceData(2000,3000,2000,5000,3000);
	Cntr.set(14070.878,6470.916);
	po[0].set(14051.9,6510.5);
	po[1].set(14029.9,6457.6);
	po[2].set(14067.8,6448.1);
	po[3].set(14143.7,6501.2);
	Sldrs[7]->setWalkBorgData(Cntr,40,po,40,30);
//----------------------8-sniper---------------------------------------------------------------
	Sldrs[8]=new CSoldier_2();
	Sldrs[8]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("sldrB4.b3d"),core::vector3df(14080.983,800,-874.085),mselector,Seeselector,8);
	Sldrs[8]->setadvanceData(2000,3000,2000,5000,3000);
	Cntr.set(14080.983,-874.085);
	po[0].set(14047.5,-812.3);
	po[1].set(14013.4,-904.7);
	po[2].set(14093.3,-919.2);
	po[3].set(14145.5,-851.5);
	Sldrs[8]->setWalkBorgData(Cntr,40,po,40,30);
//----------------------9-sniper---------------------------------------------------------------
	Sldrs[9]=new CSoldier_2();
	Sldrs[9]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("sldrB5.b3d"),core::vector3df(12985.5,500,4421.4),mselector,Seeselector,9);
	Sldrs[9]->setadvanceData(2000,3500,1000,2000,3000);
	Sldrs[9]->RotaSldrToDirect(core::vector2df(0,-1));
//----------------------10---------------------------------------------------------------------
	Sldrs[10]=new CSoldier_1();
	Sldrs[10]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("sldrA2.b3d"),core::vector3df(8110, 70, 2259),mselector,Seeselector,10);
	Sldrs[10]->setadvanceData(1000,2000,1000,4000,2000);
	po[0].set(6794,2214);
	po[1].set(6715,2347);
	Sldrs[10]->setrunTrackData(2,po,140,35,true,false);
	
//----------------------11---------------------------------------------------------------------
	Sldrs[11]=new CSoldier_1();
	Sldrs[11]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("sldrA3.b3d"),core::vector3df(6974.4,70,6334),mselector,Seeselector,11);
	Sldrs[11]->setadvanceData(2000,2000,1000,1000,3000);
	po[0].set(6974.4,6334);
	po[1].set(9290,6380);
	po[2].set(9186,4257);
	po[3].set(9290,6280);
	Sldrs[11]->setWalkData(po,70,30,true,false,true);
	//----------------------12---------------------------------------------------------------------
	Sldrs[12]=new CSoldier_3();
	Sldrs[12]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("sldrC3.b3d"),core::vector3df(7204,70,4177),mselector,Seeselector,12);
	Sldrs[12]->setadvanceData(1000,2000,1000,3000,2000);
	po[0].set(7204,4177);
	po[1].set(9465,4216);
	Sldrs[12]->setWalkData(po,70,30,false,false,true);
	
	int rn=func.RandomRange(0,1);
	if(rn==0){
	po[0].set(8183,4053);
	Sldrs[12]->setrunTrackData(1,po,140,35,true,false);
	}else if(rn==1){
	po[0].set(8303,4108);
	po[1].set(8085,2781);
	Sldrs[12]->setrunTrackData(2,po,140,35,true,false);
	}
	//----------------------13---------------------------------------------------------------------
	rn=func.RandomRange(0,1);
	if(rn==0){
	Sldrs[13]=new CSoldier_3();
	Sldrs[13]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("sldrC4.b3d"),core::vector3df(8267,70,899),mselector,Seeselector,13);
	}
	else if(rn==1){
	Sldrs[13]=new CSoldier_1();
	Sldrs[13]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("sldrA4.b3d"),core::vector3df(8267,70,899),mselector,Seeselector,13);
	}

	Sldrs[13]->setadvanceData(2000,2000,1000,1000,1000);
	po[0].set(7288,1197);
	Sldrs[13]->setrunTrackData(1,po,140,35,true,false);
	//----------------------14---------------------------------------------------------------------
	Sldrs[14]=new CSoldier_1();
	Sldrs[14]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("sldrA5.b3d"),core::vector3df(10495,70,2251),mselector,Seeselector,14);
	Sldrs[14]->setadvanceData(1000,2000,1000,1000,1000);
	po[0].set(10495,2251);
	po[1].set(9169,2245);
	Sldrs[14]->setWalkData(po,70,30,false,false,true);
	//----------------------15---------------------------------------------------------------------
	Sldrs[15]=new CSoldier_1();
	Sldrs[15]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("sldrA6.b3d"),core::vector3df(7660,70,500),mselector,Seeselector,15);
	Sldrs[15]->setadvanceData(3000,3000,1000,3000,1000);
	po[0].set(7660,500);
	po[1].set(7660,-635);
	Sldrs[15]->setWalkData(po,70,30,false,false,true);
	po[0].set(7597,-5);
	po[1].set(7403,10);
	po[2].set(7427,205);
	po[3].set(7246,749);
	po[4].set(7646,1155);
	po[5].set(7651,1374);
	Sldrs[15]->setrunTrackData(6,po,140,30,true,false);
	//----------------------16---------------------------------------------------------------------
	Sldrs[16]=new CSoldier_1();
	Sldrs[16]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("sldrA7.b3d"),core::vector3df(13186,70,4228),mselector,Seeselector,16);
	Sldrs[16]->setadvanceData(2000,2000,1000,5000,3000);
	po[0].set(13186,4228);
	po[1].set(13256,5843);
	Sldrs[16]->setWalkData(po,70,30,false,false,true);
	//----------------------17---------------------------------------------------------------------
	Sldrs[17]=new CSoldier_3();
	Sldrs[17]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("sldrC5.b3d"),core::vector3df(13856,70,1554),mselector,Seeselector,17);
	Sldrs[17]->setadvanceData(1000,2000,1000,2000,1000);
	po[0].set(13856,1554);
	po[1].set(13835,1739);
	Sldrs[17]->setrunTrackData(2,po,140,30,true,false);

	//----------------------18---------------------------------------------------------------------
	Sldrs[18]=new CSoldier_1();
	Sldrs[18]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("sldrA8.b3d"),core::vector3df(11978,70,5411),mselector,Seeselector,18);
	Sldrs[18]->setadvanceData(1000,2000,1000,2000,1000);
	Sldrs[18]->RotaSldrToDirect(core::vector2df(1,0));
	po[0].set(12124,4783);
	Sldrs[18]->setrunTrackData(1,po,120,30,true,false);
	//----------------------19---------------------------------------------------------------------
	Sldrs[19]=new CSoldier_1();
	Sldrs[19]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("sldrA9.b3d"),core::vector3df(11219,500,5604),mselector,Seeselector,19);
	Sldrs[19]->setadvanceData(3000,3000,1000,5000,3000);
	po[0].set(11219,5604);
	po[1].set(13018,5597);
	Sldrs[19]->setWalkData(po,70,30,false,false,true);
	rn=func.RandomRange(0,2);
	if(!(rn==0)){
	po[0].set(11345,5554);
	po[1].set(11321,4488);
	po[2].set(11189,4412);
	po[3].set(11187,4967);
	po[4].set(11519,4971);
	Sldrs[19]->setrunTrackData(5,po,140,30,true,false);
	}
	//----------------------20---------------------------------------------------------------------
	Sldrs[20]=new CSoldier_1();
	Sldrs[20]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("sldrA10.b3d"),core::vector3df(18266,-40,13726),mselector,Seeselector,20);
	Sldrs[20]->setadvanceData(2000,2000,200,5000,1000);
	po[0].set(18266,13726);
	po[1].set(18719,13700);
	Sldrs[20]->setWalkData(po,70,30,false,false,true);

	//----------------------21---------------------------------------------------------------------
	Sldrs[21]=new CSoldier_3();
	Sldrs[21]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("sldrC6.b3d"),core::vector3df(19939,70,17809),mselector,Seeselector,21);
	Sldrs[21]->setadvanceData(3000,3000,1000,5000,1000);
	po[0].set(19939,17809);
	po[1].set(19857,18950);
	Sldrs[21]->setWalkData(po,70,30,false,false,true);
	po[0].set(19613,18305);
	po[1].set(19475,18281);
	Sldrs[21]->setrunTrackData(2,po,120,30,true,false);
	//----------------------22---------------------------------------------------------------------
	Sldrs[22]=new CSoldier_1();
	Sldrs[22]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("sldrA11.b3d"),core::vector3df(23036,70,16925),mselector,Seeselector,22);
	Sldrs[22]->setadvanceData(3000,3000,1000,5000,1000);
	po[0].set(22969,16636);
	po[1].set(20888,16234);
	Sldrs[22]->setrunTrackData(2,po,120,30,true,false);
	//----------------------23---------------------------------------------------------------------
	Sldrs[23]=new CSoldier_1();
	Sldrs[23]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("sldrA12.b3d"),core::vector3df(24361,-40,18404),mselector,Seeselector,23);
	Sldrs[23]->setadvanceData(3000,3000,1000,5000,1000);

		//----------------------24-dead--------------------------------------------------------------------
	Sldrs[24]=new CSoldier_1();
	Sldrs[24]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("sldrA12.b3d"),core::vector3df(27628,70,19032),mselector,Seeselector,24);
	Sldrs[24]->RotaSldrToDirect(core::vector2df(1,0));
	Sldrs[24]->slderDead();			 
		//----------------------25-dead--------------------------------------------------------------------
	Sldrs[25]=new CSoldier_1();
	Sldrs[25]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("sldrA12.b3d"),core::vector3df(28168,70,19146),mselector,Seeselector,25);
	Sldrs[25]->slderDead();
	//*******************************************************************************
//ãÌãæÚÉ ÇáÌäæÏ ÇßÊÝ Ýí Ãæá ãæÞÚ
	Sldrs[0]->setActive(true);
	Sldrs[1]->setActive(true);
	Sldrs[2]->setActive(true);
	Sldrs[3]->setActive(true);
	Sldrs[4]->setActive(true);
	Sldrs[5]->setActive(true);
	Sldrs[6]->setActive(true);
	Sldrs[7]->setActive(true);
	Sldrs[8]->setActive(true);
	Sldrs[9]->setActive(true);
	Sldrs[10]->setActive(true);
	

	ActveSldrs.push_back(0);
	ActveSldrs.push_back(1);
	ActveSldrs.push_back(2);
	ActveSldrs.push_back(3);
	ActveSldrs.push_back(4);
	ActveSldrs.push_back(5);
	ActveSldrs.push_back(6);
	ActveSldrs.push_back(7);
	ActveSldrs.push_back(8);
	ActveSldrs.push_back(9);
	ActveSldrs.push_back(10);
	


	
	rec1=core::rect<int>(10534,6425,5571,-611);
	rec1.repair();
	rec2=core::rect<int>(14920,6458,9332,-600);
	rec2.repair();
	rec3=core::rect<int>(19467,9924,14265,564);
	rec3.repair();

						
}

void RenderSolders(float timeeilp,core::vector3df camP,scene::ITriangleSelector*sldrSeeSelector)
{
static float totalTime=0;
totalTime+=timeeilp;
	if (totalTime>=0.1f)
	{
	selectActives(camP);		
	selectIsPlyrAttck();

	Sldrs[0]->SOILDER_RENDER(Pblood,Ggi,totalTime);
	Sldrs[1]->SOILDER_RENDER(Pblood,Ggi,totalTime);
	Sldrs[2]->SOILDER_RENDER(Pblood,Ggi,totalTime);
	Sldrs[3]->SOILDER_RENDER(Pblood,Ggi,totalTime);
	Sldrs[4]->SOILDER_RENDER(Pblood,Ggi,totalTime);
	Sldrs[5]->SOILDER_RENDER(Pblood,Ggi,totalTime);
	Sldrs[6]->SOILDER_RENDER(Pblood,Ggi,totalTime);
	Sldrs[7]->SOILDER_RENDER(Pblood,Ggi,totalTime);
	Sldrs[8]->SOILDER_RENDER(Pblood,Ggi,totalTime);
	Sldrs[9]->SOILDER_RENDER(Pblood,Ggi,totalTime);
	Sldrs[10]->SOILDER_RENDER(Pblood,Ggi,totalTime);
	Sldrs[11]->SOILDER_RENDER(Pblood,Ggi,totalTime);
	Sldrs[12]->SOILDER_RENDER(Pblood,Ggi,totalTime);
	Sldrs[13]->SOILDER_RENDER(Pblood,Ggi,totalTime);
	Sldrs[14]->SOILDER_RENDER(Pblood,Ggi,totalTime);
	Sldrs[15]->SOILDER_RENDER(Pblood,Ggi,totalTime);
	Sldrs[16]->SOILDER_RENDER(Pblood,Ggi,totalTime);
	Sldrs[17]->SOILDER_RENDER(Pblood,Ggi,totalTime);
	Sldrs[18]->SOILDER_RENDER(Pblood,Ggi,totalTime);
	Sldrs[19]->SOILDER_RENDER(Pblood,Ggi,totalTime);
	Sldrs[20]->SOILDER_RENDER(Pblood,Ggi,totalTime);
	Sldrs[21]->SOILDER_RENDER(Pblood,Ggi,totalTime);
	Sldrs[22]->SOILDER_RENDER(Pblood,Ggi,totalTime);
	Sldrs[23]->SOILDER_RENDER(Pblood,Ggi,totalTime);
	totalTime=0;
	}
	//===============================================================================================================//
	Sldrs[0]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);
	Sldrs[1]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);
	Sldrs[2]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);
	Sldrs[3]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);
	Sldrs[4]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);
	Sldrs[5]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);
	Sldrs[6]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);
	Sldrs[7]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);
	Sldrs[8]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);
	Sldrs[9]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);
	Sldrs[10]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);
	Sldrs[11]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);
	Sldrs[12]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);
	Sldrs[13]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);
	Sldrs[14]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);
	Sldrs[15]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);
	Sldrs[16]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);
	Sldrs[17]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);
	Sldrs[18]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);
	Sldrs[19]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);
	Sldrs[20]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);
	Sldrs[21]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);
	Sldrs[22]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);
	Sldrs[23]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);

	selectSeePlayer(camP,sldrSeeSelector);
	selectSlderState(camP);
}
void selectActives(core::vector3df plyrPos)
{

if (enterRect3)
{
	core::position2di plyrPost;
	plyrPost.X=plyrPos.X;
	plyrPost.Y=plyrPos.Z;


	if (enterRect1)
	{
		if (rec1.isPointInside(plyrPost))
		{
		Sldrs[11]->setActive(true);
		Sldrs[12]->setActive(true);
		Sldrs[13]->setActive(true);
		Sldrs[14]->setActive(true);
		Sldrs[15]->setActive(true);

		ActveSldrs.push_back(11);
		ActveSldrs.push_back(12);
		ActveSldrs.push_back(13);
		ActveSldrs.push_back(14);
		ActveSldrs.push_back(15);
		enterRect1=false;
		}
	}

	if (enterRect2)
	{
		if (rec2.isPointInside(plyrPost))
		{
		Sldrs[16]->setActive(true);
		Sldrs[17]->setActive(true);
		Sldrs[18]->setActive(true);
		Sldrs[19]->setActive(true);

		ActveSldrs.push_back(16);
		ActveSldrs.push_back(17);
		ActveSldrs.push_back(18);
		ActveSldrs.push_back(19);

		enterRect2=false;
		}
	}
	if (enterRect3)
	{
		if (rec3.isPointInside(plyrPost))
		{
		Sldrs[20]->setActive(true);
		Sldrs[21]->setActive(true);
		Sldrs[22]->setActive(true);
		Sldrs[23]->setActive(true);

		ActveSldrs.push_back(20);
		ActveSldrs.push_back(21);
		ActveSldrs.push_back(22);
		ActveSldrs.push_back(23);
		enterRect3=false;
		}
	}
}
}
};
class CSoldierManger_2 : public CSoldierManger
{
private:
core::rect<int> rec1,rec2,rec3;
bool enterRect1,enterRect2,enterRect3;
public:
CSoldierManger_2(IrrlichtDevice *Dev,ISoundEngine* SEng,scene::IMetaTriangleSelector*mselector,scene::ITriangleSelector*Seeselector,int&blood,GGI*ggi)
{
enterRect1=enterRect2=enterRect3=true;
Devic=Dev;
Pblood=&blood;
Ggi=ggi;
csnd=new CSolderSounds(SEng);

//-CSoldier_1-->normal soldier
//-CSoldier_2-->sniper soldier
	
core::vector2df po[6];
Dev->getFileSystem()->addZipFileArchive("data/ascr.pk3");
//--------------------------- 0 íØáÚ Úáì ÇáÌÈá----------------------------------
	Sldrs[0]=new CSoldier_1();
	Sldrs[0]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("sldrAA0.b3d"),core::vector3df(-456,500,1632),mselector,Seeselector,0);
	Sldrs[0]->setadvanceData(1500,1500,200,3000);
	po[0].set(-456,1632);
	po[1].set(-456,2989);
	Sldrs[0]->setWalkData(po,70,30,false,false,true);

//---------------------------1---------------------------------------------------------------
	Sldrs[1]=new CSoldier_1();
	Sldrs[1]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("sldrA0.b3d"),core::vector3df(499,500,3180),mselector,Seeselector,1);
	Sldrs[1]->setadvanceData(1500,1500,200,3000);
	po[0].set(499,3180);
	po[1].set(582,6254);
	Sldrs[1]->setWalkData(po,70,30,false,false,true);
//---------------------------2--sniper--------------------------------------------------------------
	core::vector2df Cntr;
	Sldrs[2]=new CSoldier_2();
	Sldrs[2]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("SDR/sldrB1.b3d"),core::vector3df(115,800,5440),mselector,Seeselector,5);
	Sldrs[2]->setadvanceData(2000,3000,2000,5000,3000);
	Cntr.set(115,5440);
	po[0].set(273,5291);
	po[1].set(-71,5269);
	po[2].set(-87,5630);
	po[3].set(306,5655);
	Sldrs[2]->setWalkBorgData(Cntr,200,po,40,30);
	//------------------------------3 sniper--------------------------------------------------
	Sldrs[3]=new CSoldier_2();
	Sldrs[3]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("SDR/sldrB2.b3d"),core::vector3df(1675,800,7025),mselector,Seeselector,5);
	Sldrs[3]->setadvanceData(2000,3000,2000,5000,3000);
	Cntr.set(1675,7025);
	po[0].set(1680,6842);
	po[1].set(1494,7024);
	po[2].set(1725,7195);
	po[3].set(1875,6957);
	Sldrs[3]->setWalkBorgData(Cntr,200,po,60,30);
//---------------4-----------------------------------------------------------------------------
	Sldrs[4]=new CSoldier_3();
	Sldrs[4]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("SDR/sldrC1.b3d"),core::vector3df(-204,100,6795),mselector,Seeselector,12);
	Sldrs[4]->setadvanceData(1000,2000,1000,3000,2000);

	po[0].set(-156,6665);
	Sldrs[4]->setrunTrackData(1,po,100,30,true,false);
//-----------5---------------------------------------------------------------------------------
	Sldrs[5]=new CSoldier_1();
	Sldrs[5]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("sldrA1.b3d"),core::vector3df(1476,500,7260),mselector,Seeselector,1);
	Sldrs[5]->setadvanceData();
	po[0].set(1476,7260);
	po[1].set(1900,7262);
	Sldrs[5]->setWalkData(po,70,30,false,false,true);
//---------------------------6---------------------------------------------------------------
	Sldrs[6]=new CSoldier_1();
	Sldrs[6]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("sldrA2.b3d"),core::vector3df(3720,500,6595),mselector,Seeselector,1);
	Sldrs[6]->setadvanceData();
//---------------------------7---------------------------------------------------------------
	Sldrs[7]=new CSoldier_1();
	Sldrs[7]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("sldrA3.b3d"),core::vector3df(4079,500,4142),mselector,Seeselector,1);
	Sldrs[7]->setadvanceData();
//---------------------------8---------------------------------------------------------------
	Sldrs[8]=new CSoldier_1();
	Sldrs[8]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("sldrAA1.b3d"),core::vector3df(3849,500,2009),mselector,Seeselector,1);
	Sldrs[8]->setadvanceData();
	//----------------------9-----------------------------------------------------------------------------
	Sldrs[9]=new CSoldier_3();
	Sldrs[9]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("SDR/sldrC2.b3d"),core::vector3df(4177,100,2161),mselector,Seeselector,12);
	Sldrs[9]->setadvanceData(1000,2000,1000,3000,2000);

	po[0].set(4038,2664);
	Sldrs[9]->setrunTrackData(1,po,100,30,true,false);
//---------------------------3----------------------------------------------------------------
	/*Sldrs[3]=new CSoldier_1();
	Sldrs[3]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("SDR/sldrA1.b3d"),core::vector3df(6329.3,100,2259.18),mselector,Seeselector,4);
	Sldrs[3]->setadvanceData(2000,2000,1000,3000);
	Sldrs[3]->RotaSldrToDirect(core::vector2df(-1,0));
//---------------------------4----------------------------------------------------------------
	Sldrs[4]=new CSoldier_3();
	Sldrs[4]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("SDR/sldrC2.b3d"),core::vector3df(6235,100,1484),mselector,Seeselector,4);
	Sldrs[4]->setadvanceData(2000,2000,3000,5000);
	Sldrs[4]->RotaSldrToDirect(core::vector2df(-1,0));
	po[0].set(6129.5,1492);
	Sldrs[4]->setrunTrackData(1,po,100,30,true,false);
//----------------------5-sniper---------------------------------------------------------------
	core::vector2df Cntr;
	Sldrs[5]=new CSoldier_2();
	Sldrs[5]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("SDR/sldrB1.b3d"),core::vector3df(6782.4,800, -866.08),mselector,Seeselector,5);
	Sldrs[5]->setadvanceData(2000,3000,2000,5000,3000);
	Cntr.set(6782.4,-866.08);
	po[0].set(6732.4,-896.7);
	po[1].set(6813,-926.6);
	po[2].set(6796.6,-853.5);
	po[3].set(6764.6,-822);
	Sldrs[5]->setWalkBorgData(Cntr,40,po,40,30);
//----------------------6-sniper---------------------------------------------------------------
	Sldrs[6]=new CSoldier_2();
	Sldrs[6]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("SDR/sldrB2.b3d"),core::vector3df(6798.4,800,6433),mselector,Seeselector,6);
	Sldrs[6]->setadvanceData(2000,3000,2000,5000,3000);
	Cntr.set(6798.4,6433);
	po[0].set(6735.7,6414.8);
	po[1].set(6781.7,6480.6);
	po[2].set(6852.3,6470.8);
	po[3].set(6826.5,6374.7);
	Sldrs[6]->setWalkBorgData(Cntr,20,po,40,30);
	
//----------------------7-sniper---------------------------------------------------------------
	Sldrs[7]=new CSoldier_2();
	Sldrs[7]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("SDR/sldrB3.b3d"),core::vector3df(14070.878, 800,6470.916),mselector,Seeselector,7);
	Sldrs[7]->setadvanceData(2000,3000,2000,5000,3000);
	Cntr.set(14070.878,6470.916);
	po[0].set(14051.9,6510.5);
	po[1].set(14029.9,6457.6);
	po[2].set(14067.8,6448.1);
	po[3].set(14143.7,6501.2);
	Sldrs[7]->setWalkBorgData(Cntr,40,po,40,30);
//----------------------8-sniper---------------------------------------------------------------
	Sldrs[8]=new CSoldier_2();
	Sldrs[8]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("SDR/sldrB4.b3d"),core::vector3df(14080.983,800,-874.085),mselector,Seeselector,8);
	Sldrs[8]->setadvanceData(2000,3000,2000,5000,3000);
	Cntr.set(14080.983,-874.085);
	po[0].set(14047.5,-812.3);
	po[1].set(14013.4,-904.7);
	po[2].set(14093.3,-919.2);
	po[3].set(14145.5,-851.5);
	Sldrs[8]->setWalkBorgData(Cntr,40,po,40,30);
//----------------------9-sniper---------------------------------------------------------------
	Sldrs[9]=new CSoldier_2();
	Sldrs[9]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("SDR/sldrB5.b3d"),core::vector3df(12985.5,500,4421.4),mselector,Seeselector,9);
	Sldrs[9]->setadvanceData(2000,3500,1000,2000,3000);
	Sldrs[9]->RotaSldrToDirect(core::vector2df(0,-1));
//----------------------10---------------------------------------------------------------------
	Sldrs[10]=new CSoldier_1();
	Sldrs[10]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("SDR/sldrA2.b3d"),core::vector3df(8110, 70, 2259),mselector,Seeselector,10);
	Sldrs[10]->setadvanceData(1000,2000,1000,4000,2000);
	po[0].set(6794,2214);
	po[1].set(6715,2347);
	Sldrs[10]->setrunTrackData(2,po,140,35,true,false);
	
//----------------------11---------------------------------------------------------------------
	Sldrs[11]=new CSoldier_1();
	Sldrs[11]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("SDR/sldrA3.b3d"),core::vector3df(6974.4,70,6334),mselector,Seeselector,11);
	Sldrs[11]->setadvanceData(2000,2000,1000,1000,3000);
	po[0].set(6974.4,6334);
	po[1].set(9290,6380);
	po[2].set(9186,4257);
	po[3].set(9290,6280);
	Sldrs[11]->setWalkData(po,70,30,true,false,true);
	//----------------------12---------------------------------------------------------------------
	Sldrs[12]=new CSoldier_3();
	Sldrs[12]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("SDR/sldrC3.b3d"),core::vector3df(7204,70,4177),mselector,Seeselector,12);
	Sldrs[12]->setadvanceData(1000,2000,1000,3000,2000);
	po[0].set(7204,4177);
	po[1].set(9465,4216);
	Sldrs[12]->setWalkData(po,70,30,false,false,true);
	
	int rn=func.RandomRange(0,1);
	if(rn==0){
	po[0].set(8183,4053);
	Sldrs[12]->setrunTrackData(1,po,140,35,true,false);
	}else if(rn==1){
	po[0].set(8303,4108);
	po[1].set(8085,2781);
	Sldrs[12]->setrunTrackData(2,po,140,35,true,false);
	}
	//----------------------13---------------------------------------------------------------------
	rn=func.RandomRange(0,1);
	if(rn==0){
	Sldrs[13]=new CSoldier_3();
	Sldrs[13]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("SDR/sldrC4.b3d"),core::vector3df(8267,70,899),mselector,Seeselector,13);
	}
	else if(rn==1){
	Sldrs[13]=new CSoldier_1();
	Sldrs[13]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("SDR/sldrA4.b3d"),core::vector3df(8267,70,899),mselector,Seeselector,13);
	}

	Sldrs[13]->setadvanceData(2000,2000,1000,1000,1000);
	po[0].set(7288,1197);
	Sldrs[13]->setrunTrackData(1,po,140,35,true,false);
	//----------------------14---------------------------------------------------------------------
	Sldrs[14]=new CSoldier_1();
	Sldrs[14]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("SDR/sldrA5.b3d"),core::vector3df(10495,70,2251),mselector,Seeselector,14);
	Sldrs[14]->setadvanceData(1000,2000,1000,1000,1000);
	po[0].set(10495,2251);
	po[1].set(9169,2245);
	Sldrs[14]->setWalkData(po,70,30,false,false,true);
	//----------------------15---------------------------------------------------------------------
	Sldrs[15]=new CSoldier_1();
	Sldrs[15]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("SDR/sldrA6.b3d"),core::vector3df(7660,70,500),mselector,Seeselector,15);
	Sldrs[15]->setadvanceData(3000,3000,1000,3000,1000);
	po[0].set(7660,500);
	po[1].set(7660,-635);
	Sldrs[15]->setWalkData(po,70,30,false,false,true);
	po[0].set(7597,-5);
	po[1].set(7403,10);
	po[2].set(7427,205);
	po[3].set(7246,749);
	po[4].set(7646,1155);
	po[5].set(7651,1374);
	Sldrs[15]->setrunTrackData(6,po,140,30,true,false);
	//----------------------16---------------------------------------------------------------------
	Sldrs[16]=new CSoldier_1();
	Sldrs[16]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("SDR/sldrA7.b3d"),core::vector3df(13186,70,4228),mselector,Seeselector,16);
	Sldrs[16]->setadvanceData(2000,2000,1000,5000,3000);
	po[0].set(13186,4228);
	po[1].set(13256,5843);
	Sldrs[16]->setWalkData(po,70,30,false,false,true);
	//----------------------17---------------------------------------------------------------------
	Sldrs[17]=new CSoldier_3();
	Sldrs[17]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("SDR/sldrC5.b3d"),core::vector3df(13856,70,1554),mselector,Seeselector,17);
	Sldrs[17]->setadvanceData(1000,2000,1000,2000,1000);
	po[0].set(13856,1554);
	po[1].set(13835,1739);
	Sldrs[17]->setrunTrackData(2,po,140,30,true,false);

	//----------------------18---------------------------------------------------------------------
	Sldrs[18]=new CSoldier_1();
	Sldrs[18]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("SDR/sldrA8.b3d"),core::vector3df(11978,70,5411),mselector,Seeselector,18);
	Sldrs[18]->setadvanceData(1000,2000,1000,2000,1000);
	Sldrs[18]->RotaSldrToDirect(core::vector2df(1,0));
	po[0].set(12124,4783);
	Sldrs[18]->setrunTrackData(1,po,120,30,true,false);
	//----------------------19---------------------------------------------------------------------
	Sldrs[19]=new CSoldier_1();
	Sldrs[19]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("SDR/sldrA9.b3d"),core::vector3df(11219,500,5604),mselector,Seeselector,19);
	Sldrs[19]->setadvanceData(3000,3000,1000,5000,3000);
	po[0].set(11219,5604);
	po[1].set(13018,5597);
	Sldrs[19]->setWalkData(po,70,30,false,false,true);
	rn=func.RandomRange(0,2);
	if(!(rn==0)){
	po[0].set(11345,5554);
	po[1].set(11321,4488);
	po[2].set(11189,4412);
	po[3].set(11187,4967);
	po[4].set(11519,4971);
	Sldrs[19]->setrunTrackData(5,po,140,30,true,false);
	}
	//----------------------20---------------------------------------------------------------------
	Sldrs[20]=new CSoldier_1();
	Sldrs[20]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("SDR/sldrA10.b3d"),core::vector3df(18266,30,13726),mselector,Seeselector,20);
	Sldrs[20]->setadvanceData(2000,2000,200,5000,1000);
	po[0].set(18266,13726);
	po[1].set(18719,13700);
	Sldrs[20]->setWalkData(po,70,30,false,false,true);

	//----------------------21---------------------------------------------------------------------
	Sldrs[21]=new CSoldier_3();
	Sldrs[21]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("SDR/sldrC6.b3d"),core::vector3df(19939,70,17809),mselector,Seeselector,21);
	Sldrs[21]->setadvanceData(3000,3000,1000,5000,1000);
	po[0].set(19939,17809);
	po[1].set(19857,18950);
	Sldrs[21]->setWalkData(po,70,30,false,false,true);
	po[0].set(19613,18305);
	po[1].set(19475,18281);
	Sldrs[21]->setrunTrackData(2,po,120,30,true,false);
	//----------------------22---------------------------------------------------------------------
	Sldrs[22]=new CSoldier_1();
	Sldrs[22]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("SDR/sldrA11.b3d"),core::vector3df(23036,70,16925),mselector,Seeselector,22);
	Sldrs[22]->setadvanceData(3000,3000,1000,5000,1000);
	po[0].set(22969,16636);
	po[1].set(20888,16234);
	Sldrs[22]->setrunTrackData(2,po,120,30,true,false);
	//----------------------23---------------------------------------------------------------------
	Sldrs[23]=new CSoldier_1();
	Sldrs[23]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("SDR/sldrA12.b3d"),core::vector3df(24361,-40,18404),mselector,Seeselector,23);
	Sldrs[23]->setadvanceData(3000,3000,1000,5000,1000);

		//----------------------24-dead--------------------------------------------------------------------
	Sldrs[24]=new CSoldier_1();
	Sldrs[24]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("SDR/sldrA12.b3d"),core::vector3df(27628,70,19032),mselector,Seeselector,24);
	Sldrs[24]->RotaSldrToDirect(core::vector2df(1,0));
	Sldrs[24]->slderDead();			 
		//----------------------25-dead--------------------------------------------------------------------
	Sldrs[25]=new CSoldier_1();
	Sldrs[25]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("SDR/sldrA12.b3d"),core::vector3df(28168,70,19146),mselector,Seeselector,25);
	Sldrs[25]->slderDead();
	//*******************************************************************************
*/
	//ãÌãæÚÉ ÇáÌäæÏ ÇßÊÝ Ýí Ãæá ãæÞÚ
	Sldrs[0]->setActive(true);
	Sldrs[1]->setActive(true);
	Sldrs[2]->setActive(true);
	Sldrs[3]->setActive(true);
	Sldrs[4]->setActive(true);
	Sldrs[5]->setActive(true);
	Sldrs[6]->setActive(true);
	Sldrs[7]->setActive(true);
	Sldrs[8]->setActive(true);
	Sldrs[9]->setActive(true);


	ActveSldrs.push_back(0);
	ActveSldrs.push_back(1);
	ActveSldrs.push_back(2);
	ActveSldrs.push_back(3);
	ActveSldrs.push_back(4);
	ActveSldrs.push_back(5);
	ActveSldrs.push_back(6);
	ActveSldrs.push_back(7);
	ActveSldrs.push_back(8);
	ActveSldrs.push_back(9);



	
	rec1=core::rect<int>(10534,6425,5571,-611);
	rec1.repair();
	rec2=core::rect<int>(14920,6458,9332,-600);
	rec2.repair();
	rec3=core::rect<int>(19467,9924,14265,564);
	rec3.repair();

						
}

void RenderSolders(float timeeilp,core::vector3df camP,scene::ITriangleSelector*sldrSeeSelector)
{
static float totalTime=0;
totalTime+=timeeilp;
	if (totalTime>=0.1f)
	{
	selectActives(camP);		
	selectIsPlyrAttck();

	Sldrs[0]->SOILDER_RENDER(Pblood,Ggi,totalTime);
	Sldrs[1]->SOILDER_RENDER(Pblood,Ggi,totalTime);
	Sldrs[2]->SOILDER_RENDER(Pblood,Ggi,totalTime);
	Sldrs[3]->SOILDER_RENDER(Pblood,Ggi,totalTime);
	Sldrs[4]->SOILDER_RENDER(Pblood,Ggi,totalTime);
	Sldrs[5]->SOILDER_RENDER(Pblood,Ggi,totalTime);
	Sldrs[6]->SOILDER_RENDER(Pblood,Ggi,totalTime);
	Sldrs[7]->SOILDER_RENDER(Pblood,Ggi,totalTime);
	Sldrs[8]->SOILDER_RENDER(Pblood,Ggi,totalTime);
	Sldrs[9]->SOILDER_RENDER(Pblood,Ggi,totalTime);


	totalTime=0;
	}
	//===============================================================================================================//
	Sldrs[0]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);
	Sldrs[1]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);
	Sldrs[2]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);
	Sldrs[3]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);
	Sldrs[4]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);
	Sldrs[5]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);
	Sldrs[6]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);
	Sldrs[7]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);
	Sldrs[8]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);
	Sldrs[9]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);

	selectSeePlayer(camP,sldrSeeSelector);
	selectSlderState(camP);
}
void selectActives(core::vector3df plyrPos)
{
/*
if (enterRect3)
{
	core::position2di plyrPost;
	plyrPost.X=plyrPos.X;
	plyrPost.Y=plyrPos.Z;


	if (enterRect1)
	{
		if (rec1.isPointInside(plyrPost))
		{
		Sldrs[11]->setActive(true);
		Sldrs[12]->setActive(true);
		Sldrs[13]->setActive(true);
		Sldrs[14]->setActive(true);
		Sldrs[15]->setActive(true);

		ActveSldrs.push_back(11);
		ActveSldrs.push_back(12);
		ActveSldrs.push_back(13);
		ActveSldrs.push_back(14);
		ActveSldrs.push_back(15);
		enterRect1=false;
		}
	}

	if (enterRect2)
	{
		if (rec2.isPointInside(plyrPost))
		{
		Sldrs[16]->setActive(true);
		Sldrs[17]->setActive(true);
		Sldrs[18]->setActive(true);
		Sldrs[19]->setActive(true);

		ActveSldrs.push_back(16);
		ActveSldrs.push_back(17);
		ActveSldrs.push_back(18);
		ActveSldrs.push_back(19);

		enterRect2=false;
		}
	}
	if (enterRect3)
	{
		if (rec3.isPointInside(plyrPost))
		{
		Sldrs[20]->setActive(true);
		Sldrs[21]->setActive(true);
		Sldrs[22]->setActive(true);
		Sldrs[23]->setActive(true);

		ActveSldrs.push_back(20);
		ActveSldrs.push_back(21);
		ActveSldrs.push_back(22);
		ActveSldrs.push_back(23);
		enterRect3=false;
		}
	}
}
*/
}
};
class CSoldierManger_3 : public CSoldierManger
{
private:
core::rect<int> rec1,rec2,rec3;
bool enterRect1,enterRect2,enterRect3;
public:
CSoldierManger_3(IrrlichtDevice *Dev,ISoundEngine* SEng,scene::IMetaTriangleSelector*mselector,scene::ITriangleSelector*Seeselector,int&blood,GGI*ggi)
{
enterRect1=enterRect2=enterRect3=true;
Devic=Dev;
Pblood=&blood;
Ggi=ggi;
csnd=new CSolderSounds(SEng);

//-CSoldier_1-->normal soldier
//-CSoldier_2-->sniper soldier
	
core::vector2df po[6];
Dev->getFileSystem()->addZipFileArchive("data/ascr.pk3");
//--------------------------- 0 íØáÚ Úáì ÇáÌÈá----------------------------------
	Sldrs[0]=new CSoldier_1();
	Sldrs[0]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("sldrAA0.b3d"),core::vector3df(448,500,-1714),mselector,Seeselector,0);
	Sldrs[0]->setadvanceData(1000,2000,5000,6000,1000);
	Sldrs[0]->RotaSldrToDirect(core::vector2df(0,-1));
//---------------------------1---------------------------------------------------------------
	Sldrs[1]=new CSoldier_1();
	Sldrs[1]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("sldrA0.b3d"),core::vector3df(-1305,500,-2399),mselector,Seeselector,1);
	Sldrs[1]->setadvanceData(1000,1700,1000,1000,3000);
	
	po[0].set(-1305,-2399);
	po[1].set(-391,-2314);
	Sldrs[1]->setWalkData(po,70,30,false,false,true);

//---------------------------2----------------------------------------------------------------
	Sldrs[2]=new CSoldier_1();
	Sldrs[2]->SetData(Devic,csnd,Devic->getSceneManager()->getMesh("sldrA1.b3d"),core::vector3df(1256,500,-1883),mselector,Seeselector,2);
	Sldrs[2]->setadvanceData(1000,2000,1000,3000,1000);
	po[0].set(1256,-1883);
	po[1].set(1192,-269);
	Sldrs[2]->setWalkData(po,70,30,false,false,true);
//---------------------------3----------------------------------------------------------------
	Sldrs[3]=new CSoldier_1();

	//ãÌãæÚÉ ÇáÌäæÏ ÇßÊÝ Ýí Ãæá ãæÞÚ
	Sldrs[0]->setActive(true);
	Sldrs[1]->setActive(true);
	Sldrs[2]->setActive(true);


	ActveSldrs.push_back(0);
	ActveSldrs.push_back(1);
	ActveSldrs.push_back(2);


	//no rect need
	/*rec1=core::rect<int>(10534,6425,5571,-611);
	rec1.repair();
	rec2=core::rect<int>(14920,6458,9332,-600);
	rec2.repair();
	rec3=core::rect<int>(19467,9924,14265,564);
	rec3.repair();
*/
						
}

void RenderSolders(float timeeilp,core::vector3df camP,scene::ITriangleSelector*sldrSeeSelector)
{
static float totalTime=0;
totalTime+=timeeilp;
	if (totalTime>=0.1f)
	{
	selectActives(camP);		
	selectIsPlyrAttck();

	Sldrs[0]->SOILDER_RENDER(Pblood,Ggi,totalTime);
	Sldrs[1]->SOILDER_RENDER(Pblood,Ggi,totalTime);
	Sldrs[2]->SOILDER_RENDER(Pblood,Ggi,totalTime);

	totalTime=0;
	}
	//===============================================================================================================//
	Sldrs[0]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);
	Sldrs[1]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);
	Sldrs[2]->MovingAndFrmCnsr(timeeilp,Pblood,Ggi);


	selectSeePlayer(camP,sldrSeeSelector);
	selectSlderState(camP);
}
void selectActives(core::vector3df plyrPos)//set solder active depend the rectangle
{
/*
if (enterRect3)
{
	core::position2di plyrPost;
	plyrPost.X=plyrPos.X;
	plyrPost.Y=plyrPos.Z;


	if (enterRect1)
	{
		if (rec1.isPointInside(plyrPost))
		{
		Sldrs[11]->setActive(true);
		Sldrs[12]->setActive(true);
		Sldrs[13]->setActive(true);
		Sldrs[14]->setActive(true);
		Sldrs[15]->setActive(true);

		ActveSldrs.push_back(11);
		ActveSldrs.push_back(12);
		ActveSldrs.push_back(13);
		ActveSldrs.push_back(14);
		ActveSldrs.push_back(15);
		enterRect1=false;
		}
	}

	if (enterRect2)
	{
		if (rec2.isPointInside(plyrPost))
		{
		Sldrs[16]->setActive(true);
		Sldrs[17]->setActive(true);
		Sldrs[18]->setActive(true);
		Sldrs[19]->setActive(true);

		ActveSldrs.push_back(16);
		ActveSldrs.push_back(17);
		ActveSldrs.push_back(18);
		ActveSldrs.push_back(19);

		enterRect2=false;
		}
	}
	if (enterRect3)
	{
		if (rec3.isPointInside(plyrPost))
		{
		Sldrs[20]->setActive(true);
		Sldrs[21]->setActive(true);
		Sldrs[22]->setActive(true);
		Sldrs[23]->setActive(true);

		ActveSldrs.push_back(20);
		ActveSldrs.push_back(21);
		ActveSldrs.push_back(22);
		ActveSldrs.push_back(23);
		enterRect3=false;
		}
	}
}
*/
}
};
#endif