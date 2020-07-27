/*
writen by (Younes khafaja) - 2008-2009
You are free to use this code as you see fit
email : lighting-team@hotmail.com
*/
#ifndef LVL_H
#define LVL_H
#include <irrlicht.h>
#include "CWeapon.h"
#include "Functions.h"
using namespace irr;
struct levelWeopon
{
int Wnum;
int totalShotCount;
int storgeShotCount;
};



class CLevels
{
protected:

	//----level data-----
	int LVLnumber;
	c8* LVLname;
	core::vector3df LVLpostion;
	core::vector3df LVLP_strPoint;
	core::vector3df LVLP_strRout;
	int LVLP_strWeopon;
	int LVLP_Weopcount;
	levelWeopon*LW;//level weopon
	//----------------
	IrrlichtDevice *Dev;
	scene::ISceneManager* smgr;
	video::IVideoDriver*driver;	

	scene::IAnimatedMesh* bspmesh ;
	scene::IAnimatedMesh*noCollMesh;
	scene::ISceneNode* bspnode;
	
	scene::IMetaTriangleSelector*collMselector;
	scene::IMetaTriangleSelector*shootMselector;
	CWeapon*LVLWeop;
	
	//win location
	
public:

scene::IMetaTriangleSelector*getcollMselector()
{
return collMselector;
}
scene::IMetaTriangleSelector*getshootMselector()
{
return shootMselector;
}

int getStartWeopNum()
{
return LVLP_strWeopon;
}

core::vector3df getStartPlyrPoint()
{
return LVLP_strPoint;
}
core::vector3df getStartPlyrRout()
{
return LVLP_strRout;
}

CWeapon*getWeopon()
{
return LVLWeop;
}


void _Destructor()
{
delete LW;
LW=0;
delete LVLWeop;
LVLWeop=0;
}
//----------------------------------
virtual void BuildLevel(){};
virtual void BuildWeoponCLass(){};

};
//*******************************************************************************************************
class CLevels_1 : public CLevels
{
private:
Functins fun;
public:
CLevels_1(IrrlichtDevice *device)
{
	Dev=device;
	smgr=Dev->getSceneManager();
	driver=Dev->getVideoDriver();
	LVLWeop=new CWeapon();
	BuildLevel();
	BuildWeoponCLass();
}
void BuildLevel()
{
LVLnumber=1;
LVLname="attack";
LVLpostion=core::vector3df(0,0,0);
LVLP_strPoint=core::vector3df(25100,80,19180);
LVLP_strPoint=core::vector3df(-4423.3,80,1000.94);
//LVLP_strRout=core::vector3df(50,90,90);
LVLP_strWeopon=3;
LVLP_Weopcount=1;
//-----------------------------------
LW=new levelWeopon[1];//two weopon to this level

//first weopen;
LW[0].Wnum=3;//klshn
LW[0].totalShotCount=90;
LW[0].storgeShotCount=30;

//------------------------------


 //create mselector
	collMselector=smgr->createMetaTriangleSelector();
	shootMselector=smgr->createMetaTriangleSelector();
	video::ITexture*textures;
	scene::ITriangleSelector*LevelSelector;
	//-------------------------------------------------------------------------------
		core::vector3df *postion=new core::vector3df[200];
		core::vector3df	*rotation=new core::vector3df[200];
//----------------------------add frog-------------------------------------------------------
Dev->getVideoDriver()->setFog(video::SColor(255,100,100,100),true,2000,9000,0.01f,false,false);
//---------------------------------------------------------------------------------------
 //1-add main trrant level
Dev->getFileSystem()->addZipFileArchive("data/lv.pk3");
#ifndef ADD_PLANE
    bspmesh = smgr->getMesh("plane_1.b3d");


	bspnode=smgr->addOctTreeSceneNode(bspmesh->getMesh(0),0,500);

	bspnode->setPosition(core::vector3df(0,0,0));
	bspnode->setMaterialFlag(video::EMF_LIGHTING, false);
	bspnode->setScale( irr::core::vector3df(1,1.2f,1));
	bspnode->setMaterialFlag(video::EMF_FOG_ENABLE,true); 
	LevelSelector = smgr->createOctTreeTriangleSelector(bspmesh->getMesh(0), bspnode, 20);
	bspnode->setTriangleSelector(LevelSelector);
	
	collMselector->addTriangleSelector(LevelSelector);
	shootMselector->addTriangleSelector(LevelSelector);
	LevelSelector->drop();
	LevelSelector=0;
	
	//-----------------------------------------------------------------------------------------------------
		bspmesh = smgr->getMesh("plane_2.b3d");

	bspnode=smgr->addOctTreeSceneNode(bspmesh->getMesh(0),0,500);
	bspnode->setID(500);
	bspnode->setPosition(core::vector3df(0,0,0));
	bspnode->setMaterialFlag(video::EMF_LIGHTING, false);
	bspnode->setScale( irr::core::vector3df(1,1.2f,1));
	bspnode->setMaterialFlag(video::EMF_FOG_ENABLE,true); 
	LevelSelector = smgr->createOctTreeTriangleSelector(bspmesh->getMesh(0), bspnode, 20);
	bspnode->setTriangleSelector(LevelSelector);
	
	collMselector->addTriangleSelector(LevelSelector);
	shootMselector->addTriangleSelector(LevelSelector);
	LevelSelector->drop();
	LevelSelector=0;

	//------------------------------------------------------------------------------------------------------
		    bspmesh = smgr->getMesh("plane_3.b3d");

	bspnode=smgr->addOctTreeSceneNode(bspmesh->getMesh(0),0,500);

	bspnode->setPosition(core::vector3df(0,0,0));
	bspnode->setMaterialFlag(video::EMF_LIGHTING, false);
	bspnode->setScale( irr::core::vector3df(1,1.2f,1));
	bspnode->setIsDebugObject(true);
	LevelSelector = smgr->createOctTreeTriangleSelector(bspmesh->getMesh(0), bspnode, 20);
	bspnode->setTriangleSelector(LevelSelector);
	bspnode->setMaterialFlag(video::EMF_FOG_ENABLE,true); 

	collMselector->addTriangleSelector(LevelSelector);
	shootMselector->addTriangleSelector(LevelSelector);
	LevelSelector->drop();
	LevelSelector=0;
	//-------------------------------------------------------------------------------------------------------
		    bspmesh = smgr->getMesh("plane_4.b3d");

	bspnode=smgr->addOctTreeSceneNode(bspmesh->getMesh(0),0,500);

	bspnode->setPosition(core::vector3df(0,0,0));
	bspnode->setMaterialFlag(video::EMF_LIGHTING, false);
	bspnode->setScale( irr::core::vector3df(1,1.2f,1));
	bspnode->setMaterialFlag(video::EMF_FOG_ENABLE,true); 

	LevelSelector = smgr->createOctTreeTriangleSelector(bspmesh->getMesh(0), bspnode, 20);
	bspnode->setTriangleSelector(LevelSelector);
	
	collMselector->addTriangleSelector(LevelSelector);
	shootMselector->addTriangleSelector(LevelSelector);
	LevelSelector->drop();
	LevelSelector=0;
	//-------------------------------------------------------------------------------------------------------
		    bspmesh = smgr->getMesh("plane_5.b3d");

	bspnode=smgr->addOctTreeSceneNode(bspmesh->getMesh(0),0,500);

	bspnode->setPosition(core::vector3df(0,0,0));
	bspnode->setMaterialFlag(video::EMF_LIGHTING, false);
	bspnode->setScale( irr::core::vector3df(1,1.2f,1));
	bspnode->setMaterialFlag(video::EMF_FOG_ENABLE,true); 

	LevelSelector = smgr->createOctTreeTriangleSelector(bspmesh->getMesh(0), bspnode, 20);
	bspnode->setTriangleSelector(LevelSelector);
	
	collMselector->addTriangleSelector(LevelSelector);
	shootMselector->addTriangleSelector(LevelSelector);
	LevelSelector->drop();
	LevelSelector=0;
	//-------------------------------------------------------------------------------------------------------
		    bspmesh = smgr->getMesh("plane_6.b3d");

	bspnode=smgr->addOctTreeSceneNode(bspmesh->getMesh(0),0,500);

	bspnode->setPosition(core::vector3df(0,0,0));
	bspnode->setMaterialFlag(video::EMF_LIGHTING, false);
	bspnode->setScale( irr::core::vector3df(1,1.2f,1));
	bspnode->setMaterialFlag(video::EMF_FOG_ENABLE,true); 

	LevelSelector = smgr->createOctTreeTriangleSelector(bspmesh->getMesh(0), bspnode, 20);
	bspnode->setTriangleSelector(LevelSelector);
	
	collMselector->addTriangleSelector(LevelSelector);
	shootMselector->addTriangleSelector(LevelSelector);
	LevelSelector->drop();
	LevelSelector=0;
#endif
	//-----------------------------------------------------------------------------------------------//

#ifndef ADD_SKYBOX 
	//create sky box
	/*	scene::ISceneNode* skybox = smgr->addSkyBoxSceneNode(
		Dev->getVideoDriver()->getTexture("./env/irrlicht2_up.jpg"),
		Dev->getVideoDriver()->getTexture("./env/irrlicht2_dn.jpg"),
		Dev->getVideoDriver()->getTexture("./env/irrlicht2_lf.jpg"),
		Dev->getVideoDriver()->getTexture("./env/irrlicht2_rt.jpg"),
		Dev->getVideoDriver()->getTexture("./env/irrlicht2_ft.jpg"),
		Dev->getVideoDriver()->getTexture("./env/irrlicht2_bk.jpg"));
	*/


	scene::ISceneNode* skydome=smgr->addSkyDomeSceneNode(Dev->getVideoDriver()->getTexture("./env/skydome.jpg"),16,8,0.95f,2.0f);
	
	skydome->setMaterialFlag(video::EMF_FOG_ENABLE,true);
	// skybox->setVisible(false);
   skydome->setVisible(true);
#endif

 //ÇáÔÈß 
#ifndef ADD_Shabc

	 noCollMesh= smgr->getMesh("shabak.b3d");
	// textures=   driver->getTexture("seag3.PNG");
		
    scene::ISceneNode*noCollnode = smgr->addOctTreeSceneNode(noCollMesh->getMesh(0),0,-1);
	//noCollnode->setMaterialTexture(0,textures);
	noCollnode->setPosition(core::vector3df(0,0,0));
	noCollnode->setMaterialFlag(video::EMF_LIGHTING, false);
	noCollnode->getMaterial(0).MaterialTypeParam=10;
	noCollnode->setMaterialFlag(video::EMF_FOG_ENABLE,true); 
	noCollnode->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);
	noCollnode->setScale( irr::core::vector3df(1,1.2f,1));
	noCollnode->setMaterialFlag(video::EMF_BACK_FACE_CULLING,false);
#endif
//3-ÇáÔÈß ááÊÕÇÏã
#ifndef ADD_COLLFILE

	
	 scene::IAnimatedMesh*shabcMesh=0 ;
	 shabcMesh= smgr->getMesh("shabak_colejene.b3d");
//"shabak.b3d"
	
     scene::ISceneNode*shabcnode = smgr->addOctTreeSceneNode(shabcMesh->getMesh(0),0,-1);
	 shabcnode->setPosition(core::vector3df(0,0,0));
	//shabcnode->setMaterialTexture(0,textures);
	scene::ITriangleSelector*hideShabcSelector;
	hideShabcSelector = smgr->createOctTreeTriangleSelector(shabcMesh->getMesh(0), shabcnode, 20);
	shabcnode->setTriangleSelector(hideShabcSelector);
	hideShabcSelector->drop();
	shabcnode->setMaterialFlag(video::EMF_LIGHTING, false);
	shabcnode->setMaterialType(video::EMT_NORMAL_MAP_TRANSPARENT_VERTEX_ALPHA);
	shabcnode->setScale( irr::core::vector3df(1,1.2f,1));
#endif
//4-add street
#ifndef ADD_STREET
		
	scene::IAnimatedMesh*StreetMesh=0 ;
	 StreetMesh= smgr->getMesh("streets.b3d");
    
	 scene::ISceneNode*streetnode = smgr->addOctTreeSceneNode(StreetMesh->getMesh(0),0,-1);
	 streetnode->setPosition(core::vector3df(0,0,0));
	 streetnode->getMaterial(0).MaterialTypeParam=10;
	 streetnode->setMaterialFlag(video::EMF_FOG_ENABLE,true); 
	 streetnode->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);
	 streetnode->setMaterialFlag(video::EMF_LIGHTING, false);
	 streetnode->setScale( irr::core::vector3df(1,1.2f,1));
#endif

/////////////////////////////////////ADD level unit//////////////////////////////////////////////
//ÇáÏÇÑ  ÌäÈ ÇáÈÇÈ
#ifndef ADD_MABNA
		postion[0].set(7177.363, 0,581.737);	
		postion[1].set(18571.354,-197.957,13177.723);

		rotation[0].set( 0, 0, 0);
		scene::IAnimatedMesh*Mesh1=0 ;
		Mesh1= smgr->getMesh("mabna.b3d");
  		//textures= driver->getTexture("mabna.jpg");
    

for(int i=0;i<2;i++)
{
	 scene::ISceneNode*node = smgr->addOctTreeSceneNode(Mesh1->getMesh(0),0,501);
	//node->setMaterialTexture(0,textures);
	 node->setPosition(postion[i]);
	node->setRotation(rotation[i]);
	
	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setScale( irr::core::vector3df(1,1.2f,1));
	node->setMaterialFlag(video::EMF_FOG_ENABLE,true); 

	scene::ITriangleSelector*Selectors;
	Selectors = smgr->createOctTreeTriangleSelector(Mesh1->getMesh(0),node, 20);
	node->setTriangleSelector(Selectors);
	collMselector->addTriangleSelector(Selectors);
	shootMselector->addTriangleSelector(Selectors);
	Selectors->drop();
	Selectors=0;
//node->setMaterialFlag(video::EMF_FOG_ENABLE,true);
}
#endif
 //ÇáÏÇÑ  ÇáÑÆíÓíÉ
#ifndef ADD_MABNA2

		postion[0].set(0, 0,0 );
		rotation[0].set( 0, 0, 0);
	
		Mesh1= smgr->getMesh("mabna_2.b3d");
	//textures= driver->getTexture("mabna_2.jpg");


for(int i=0;i<1;i++)
{
	 scene::ISceneNode*node = smgr->addOctTreeSceneNode(Mesh1->getMesh(0),0,501);
	//node->setMaterialTexture(0,textures);
	 node->setPosition(postion[i]);
	node->setRotation(rotation[i]);
	node->setMaterialFlag(video::EMF_FOG_ENABLE,true); 

	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setScale( irr::core::vector3df(1,1.1f,1));
	
	scene::ITriangleSelector*Selectors;
	Selectors = smgr->createOctTreeTriangleSelector(Mesh1->getMesh(0),node, 20);
	node->setTriangleSelector(Selectors);
	collMselector->addTriangleSelector(Selectors);
	shootMselector->addTriangleSelector(Selectors);
	Selectors->drop();
	Selectors=0;
//node->setMaterialFlag(video::EMF_FOG_ENABLE,true);
}
#endif
 //ÇáãßÊÈ æÇáßÑÓí
#ifndef ADD_OFFICE

		postion[0].set(12276.504, 340,5242.588 );
		postion[1].set(12258.16,340,5102.13);
		postion[2].set(12258.16,340,4939.812);
		postion[3].set(12258.16,340,4777.494);
		postion[4].set(12072.633,340,4485.285);
		rotation[4].set( 0, 180, 0);
		postion[5].set(11878.82,340,4939.812);
		postion[6].set(11878.82,340,5102.13);
		postion[7].set(11878.82,340,5264.449);
		postion[8].set(11878.82,340,4777.494);

		postion[9].set(12326.652,0,5412.298);
		rotation[9].set( 0, -90, 0);

		postion[10].set(13020.742,0,4522.359);
		rotation[10].set( 0,90, 0);

		Mesh1= smgr->getMesh("desk.b3d");
	//textures= driver->getTexture("mabna_2.jpg");


for(int i=0;i<11;i++)
{
	 scene::ISceneNode*node = smgr->addOctTreeSceneNode(Mesh1->getMesh(0),0,-1);
	//node->setMaterialTexture(0,textures);
	 node->setPosition(postion[i]);
	node->setRotation(rotation[i]);
	
	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setScale( irr::core::vector3df(1,1.1f,1));
	node->setMaterialFlag(video::EMF_FOG_ENABLE,true); 

	scene::ITriangleSelector*Selectors;
	Selectors = smgr->createOctTreeTriangleSelector(Mesh1->getMesh(0),node, 20);
	node->setTriangleSelector(Selectors);
	collMselector->addTriangleSelector(Selectors);
	shootMselector->addTriangleSelector(Selectors);
	Selectors->drop();
	Selectors=0;
//node->setMaterialFlag(video::EMF_FOG_ENABLE,true);
}
rotation[9].set( 0, 0, 0);
rotation[4].set( 0, 0, 0);
#endif
	 //ÇáØÇæáÉ
#ifndef ADD_TABLE

		postion[0].set(11697.622, 0,5414.562 );
		rotation[0].set( 0, 0, 0);
	
		Mesh1= smgr->getMesh("table.b3d");
	//textures= driver->getTexture("mabna_2.jpg");


for(int i=0;i<1;i++)
{
	 scene::ISceneNode*node = smgr->addOctTreeSceneNode(Mesh1->getMesh(0),0,-1);
	//node->setMaterialTexture(0,textures);
	 node->setPosition(postion[i]);
	node->setRotation(rotation[i]);
	
	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setScale( irr::core::vector3df(1,1.1f,1));
	node->setMaterialFlag(video::EMF_FOG_ENABLE,true); 

	scene::ITriangleSelector*Selectors;
	Selectors = smgr->createOctTreeTriangleSelector(Mesh1->getMesh(0),node, 20);
	node->setTriangleSelector(Selectors);
	collMselector->addTriangleSelector(Selectors);
	shootMselector->addTriangleSelector(Selectors);
	Selectors->drop();
	Selectors=0;
//node->setMaterialFlag(video::EMF_FOG_ENABLE,true);
}
#endif
	 //ÇáßÑÓí
#ifndef ADD_CHAR

		postion[0].set(11900.293, 0,5540.58 );
		postion[1].set(11812.77,0,5540.58);
		postion[2].set(11726.828,0,5540.58);
		postion[3].set(11639.305,0,5540.58);
		postion[4].set(11553.367,0,5540.58);
		postion[5].set(11465.844,0,5540.58);

		postion[6].set(12432.309,0,5334.902);
		rotation[6].set( 0, 180, 0);
		postion[7].set(12513.551,0,5334.902);
		rotation[7].set( 0, 180, 0);
		postion[8].set(12496.238,0,5483.912);
		postion[9].set(12583.762,0,5483.912);

		Mesh1= smgr->getMesh("char.b3d");
	//textures= driver->getTexture("mabna_2.jpg");


for(int i=0;i<10;i++)
{
	 scene::ISceneNode*node = smgr->addOctTreeSceneNode(Mesh1->getMesh(0),0,-1);
	//node->setMaterialTexture(0,textures);
	 node->setPosition(postion[i]);
	node->setRotation(rotation[i]);
	
	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setScale( irr::core::vector3df(1,1.1f,1));
	node->setMaterialFlag(video::EMF_FOG_ENABLE,true); 

	scene::ITriangleSelector*Selectors;
	Selectors = smgr->createOctTreeTriangleSelector(Mesh1->getMesh(0),node, 20);
	node->setTriangleSelector(Selectors);
	collMselector->addTriangleSelector(Selectors);
	shootMselector->addTriangleSelector(Selectors);
	Selectors->drop();
	Selectors=0;
//node->setMaterialFlag(video::EMF_FOG_ENABLE,true);
}
#endif
	 //ÇáÕæÑ
#ifndef ADD_PICTURE

		postion[0].set(0, 0,0 );
		rotation[0].set( 0, 0, 0);
	
		Mesh1= smgr->getMesh("pictures.b3d");
	//textures= driver->getTexture("mabna_2.jpg");


for(int i=0;i<1;i++)
{
	 scene::ISceneNode*node = smgr->addOctTreeSceneNode(Mesh1->getMesh(0),0,-1);
	//node->setMaterialTexture(0,textures);
	 node->setPosition(postion[i]);
	node->setRotation(rotation[i]);
	
	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setScale( irr::core::vector3df(1,1.1f,1));
	
	scene::ITriangleSelector*Selectors;
	Selectors = smgr->createOctTreeTriangleSelector(Mesh1->getMesh(0),node, 20);
	node->setTriangleSelector(Selectors);
	collMselector->addTriangleSelector(Selectors);
	shootMselector->addTriangleSelector(Selectors);
	Selectors->drop();
	Selectors=0;
//node->setMaterialFlag(video::EMF_FOG_ENABLE,true);
}
#endif
	//ÈÇÈ ÇáãæÞÚ
#ifndef ADD_DOOR

		postion[0].set(6752.671, 0,2066.896 );
		rotation[0].set( 0, 0, 0);
	
		Mesh1= smgr->getMesh("door.b3d");
  //textures= driver->getTexture("mabna.jpg");



for(int i=0;i<1;i++)
{
	 scene::ISceneNode*node = smgr->addOctTreeSceneNode(Mesh1->getMesh(0),0,502);
	//node->setMaterialTexture(0,textures);
	 node->setPosition(postion[i]);
	node->setRotation(rotation[i]);
	
	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setScale( irr::core::vector3df(1,1.2f,1));
	node->setMaterialFlag(video::EMF_FOG_ENABLE,true); 

	scene::ITriangleSelector*Selectors;
	Selectors = smgr->createOctTreeTriangleSelector(Mesh1->getMesh(0),node, 20);
	node->setTriangleSelector(Selectors);

	collMselector->addTriangleSelector(Selectors);
	shootMselector->addTriangleSelector(Selectors);
	Selectors->drop();
	Selectors=0;
//node->setMaterialFlag(video::EMF_FOG_ENABLE,true);
}
#endif
//out wall
#ifndef ADD_OUTWALL

		postion[0].set(0, 0,0 );
		rotation[0].set( 0, 0, 0);

	
		Mesh1= smgr->getMesh("out_jedar.b3d");
//  textures= driver->getTexture("mabna.jpg");
//node->setMaterialTexture(0,textures);


for(int i=0;i<1;i++)
{
	 scene::ISceneNode*node = smgr->addOctTreeSceneNode(Mesh1->getMesh(0),0,501);
	
	 node->setPosition(postion[i]);
	node->setRotation(rotation[i]);
	
	node->setMaterialFlag(video::EMF_BACK_FACE_CULLING,false);
	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setScale( irr::core::vector3df(1,1.2f,1));
	node->setMaterialFlag(video::EMF_FOG_ENABLE,true); 

	scene::ITriangleSelector*Selectors;
	Selectors = smgr->createOctTreeTriangleSelector(Mesh1->getMesh(0),node, 20);
	node->setTriangleSelector(Selectors);
	collMselector->addTriangleSelector(Selectors);
	shootMselector->addTriangleSelector(Selectors);
	Selectors->drop();
	Selectors=0;
//node->setMaterialFlag(video::EMF_FOG_ENABLE,true);
}
#endif
//ÏÇÑ ÇáãÈÇÊ	
#ifndef ADD_MABNA3

		postion[0].set(8578.358,0,5941.48);
		postion[1].set(7518.61,0,5936.81);
		postion[2].set(7518.61,0,5070.32);
		postion[3].set(8493.764,0,5068.876);
		postion[4].set(22352.367,-217.88,17460.539);
		postion[5].set(22352.367,-217.88,16834.846);
		rotation[3].set( 0, 0, 0);


		Mesh1= smgr->getMesh("mabna_3.b3d");


for(int i=0;i<6;i++)
{
	 scene::ISceneNode*node = smgr->addOctTreeSceneNode(Mesh1->getMesh(0),0,501);
	
	 node->setPosition(postion[i]);
	node->setRotation(rotation[i]);
	
	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setScale( irr::core::vector3df(1,1.2f,1));
	node->setMaterialFlag(video::EMF_FOG_ENABLE,true); 

	scene::ITriangleSelector*Selectors;
	Selectors = smgr->createOctTreeTriangleSelector(Mesh1->getMesh(0),node, 20);
	node->setTriangleSelector(Selectors);
	collMselector->addTriangleSelector(Selectors);
	shootMselector->addTriangleSelector(Selectors);
	Selectors->drop();
	Selectors=0;
//node->setMaterialFlag(video::EMF_FOG_ENABLE,true);
}
#endif
//ÇáÛÑÝÉ ÇáÕÛíÑÉ
#ifndef ADD_MABNA4

		postion[0].set(8514.527,0,842.103 );
		postion[1].set(8935.232,0,1126.213 );
		postion[2].set(17676.301,-197.77,11410.964);
		postion[3].set(17316.898,-197.77,11410.964);
		postion[4].set(24387.201,-190.508,18434.879);
		
		Mesh1= smgr->getMesh("mabna_4.b3d");


for(int i=0;i<5;i++)
{
	 scene::ISceneNode*node = smgr->addOctTreeSceneNode(Mesh1->getMesh(0),0,501);
	
	 node->setPosition(postion[i]);
	node->setRotation(rotation[i]);
	
	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setScale( irr::core::vector3df(1,1.2f,1));
	node->setMaterialFlag(video::EMF_FOG_ENABLE,true); 

	scene::ITriangleSelector*Selectors;
	Selectors = smgr->createOctTreeTriangleSelector(Mesh1->getMesh(0),node, 20);
	node->setTriangleSelector(Selectors);
	collMselector->addTriangleSelector(Selectors);
	shootMselector->addTriangleSelector(Selectors);
	Selectors->drop();
	Selectors=0;
//node->setMaterialFlag(video::EMF_FOG_ENABLE,true);
}
#endif
//ÇáÓÑíÑ
#ifndef ADD_BED

postion[0].set(8527.723,0,5200.533 );
		rotation[0].set( 0, 0, 0);
		
		Mesh1= smgr->getMesh("bed.b3d");

for(int i=0;i<1;i++)
{
	 scene::ISceneNode*node = smgr->addOctTreeSceneNode(Mesh1->getMesh(0),0,502);
	
	 node->setPosition(postion[i]);
	node->setRotation(rotation[i]);
	
	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setScale( irr::core::vector3df(1,1.2f,1));
	node->setMaterialFlag(video::EMF_FOG_ENABLE,true); 

	scene::ITriangleSelector*Selectors;
	Selectors = smgr->createOctTreeTriangleSelector(Mesh1->getMesh(0),node, 20);
	node->setTriangleSelector(Selectors);
	collMselector->addTriangleSelector(Selectors);
	shootMselector->addTriangleSelector(Selectors);
	Selectors->drop();
	Selectors=0;
//node->setMaterialFlag(video::EMF_FOG_ENABLE,true);
}
#endif
//ÇáÈáæß
#ifndef ADD_BLOCK

	//--------ÇáãæÞÚ ÇáÊÇäí --------------------------
	postion[35].set(17793.885,-15.778,9473.722);
	postion[36].set(17790.209,-20.242,9577.386);
	postion[37].set(17792.146,-35.196,9681.054);
	postion[38].set(17793.885,-47.34,9784.718);
	postion[39].set(17793.885,-61.464,9888.386);
	postion[40].set(17793.885,-76.173,9990.038);
	postion[41].set(17793.885,-87.542,10093.706);
	postion[42].set(17796.635,-101.553,10197.37);
	postion[43].set(17801.018,-103.754,10301.038);
	postion[44].set(17793.885,-105.694,10404.702);
	postion[45].set(17793.885,-111.206,10508.37);
	postion[46].set(17793.885,-111.206,10609.46);
	postion[47].set(17784.045,75.348,9589.987);
	postion[48].set(17793.885,60.393,9693.653);
	postion[49].set(17779.295,48.25,9797.319);
	postion[50].set(17779.131,34.126,9900.985);
	postion[51].set(17773.576,19.417,10002.64);
	postion[52].set(17793.885,8.048,10106.304);
	postion[53].set(17790.467,5.963,10209.972);
	postion[54].set(17802.756,8.164,10313.636);
	postion[55].set(17779.295,10.105,10417.304);
	postion[56].set(17735.631,143.869,9804.312);
	postion[57].set(17735.631,129.745,9907.976);
	postion[58].set(17739.881,115.037,10009.632);
	postion[59].set(17741.787,103.668,10118.456);
	postion[60].set(17742.053,89.656,10216.964);
	postion[61].set(17755.654,87.455,10325.788);

	postion[62].set(18009.588,-15.617,9383.45);
	postion[63].set(18009.588,-15.617,9484.54);
	postion[64].set(18009.424,-10.105,9588.204);
	postion[65].set(17985.963,-8.164,9691.872);
	postion[66].set(17992.084,-101.553,9808.138);
	postion[67].set(17994.834,-87.542,9911.802);
	postion[68].set(17994.834,-76.173,10015.47);
	postion[69].set(17994.834,-61.464,10117.122);
	postion[70].set(17994.834,-47.34,10220.79);
	postion[71].set(17996.572,-35.196,10324.454);
	postion[72].set(17998.51,-20.242,10428.122);
	postion[73].set(17994.834,-15.778,10531.786);
	postion[74].set(17994.834,-38,10635.454);
	postion[75].set(17998.252,-5.963,9795.536);
	postion[76].set(17994.834,8.048,9899.204);
	postion[77].set(18015.143,19.417,10002.868);
	postion[78].set(18009.588,34.126,10104.522);
	postion[79].set(18009.424,48.25,10208.188);
	postion[80].set(17994.834,60.393,10311.854);
	postion[81].set(18004.674,75.348,10415.521);
	postion[82].set(18053.088,80.003,9477.548);
	postion[83].set(18053.088,85.515,9581.212);
	postion[84].set(18033.064,87.455,9679.72);
	postion[85].set(18046.666,89.656,9788.544);
	postion[86].set(18046.932,103.668,9887.052);
	postion[87].set(18048.838,115.037,9995.876);
	postion[88].set(18053.088,129.745,10097.532);
	postion[89].set(18053.088,143.869,10201.196);

	postion[90].set(26201.705,11.65,19457.652);
	postion[91].set(26201.705,11.65,19359.785);
	postion[92].set(26201.705,11.65,19261.918);
	postion[93].set(26201.705,11.65,19164.047);
	postion[94].set(26201.705,11.65,19066.176);
	postion[95].set(26201.705,11.65,18968.309);
	postion[96].set(26201.705,-91.69,19499.586);
	postion[97].set(26201.705,-91.69,19401.715);
	postion[98].set(26201.705,-91.69,19303.848);
	postion[99].set(26201.705,-91.69,19108.109);
	postion[100].set(26201.705,-91.69,19010.238);
	postion[101].set(26201.705,-91.69,18911.941);
	postion[102].set(26201.705,-196.812,19499.586);
	postion[103].set(26201.705,-196.812,19401.715);
	postion[104].set(26201.705,-196.812,19303.848);
	postion[105].set(26201.705,-196.812,19108.109);
	postion[106].set(26201.705,-196.812,19010.238);
	postion[107].set(26201.705,-196.812,18911.941);
	postion[108].set(19161.346,-174.606,11251.656);
	postion[109].set(19023.68,-174.606,11251.656);
	postion[110].set(27912.43,0,20471.209);
	postion[111].set(28164.4,0,20264.23);
	postion[112].set(28243,0,20450.2);
	postion[113].set(28430.5,0,20271.3);
	postion[114].set(28483.4,0,20512.4);
	postion[115].set(28700.1,0,20596.1);
	postion[116].set(28916.982,0,20566.2);

rotation[0].set( 0, 0, 0);
		
		Mesh1= smgr->getMesh("block.b3d");

for(int i=35;i<117;i++)
{
	 scene::ISceneNode*node = smgr->addOctTreeSceneNode(Mesh1->getMesh(0),0,501);
	
	 node->setPosition(postion[i]);
	node->setRotation(rotation[0]);
	
	node->setMaterialFlag(video::EMF_LIGHTING, false);
	
	node->setScale( irr::core::vector3df(1,1.2f,1));
	node->setMaterialFlag(video::EMF_FOG_ENABLE,true); 

	scene::ITriangleSelector*Selectors;
	Selectors = smgr->createOctTreeTriangleSelector(Mesh1->getMesh(0),node, 20);
	node->setTriangleSelector(Selectors);
	collMselector->addTriangleSelector(Selectors);
	shootMselector->addTriangleSelector(Selectors);
	Selectors->drop();
	Selectors=0;
//node->setMaterialFlag(video::EMF_FOG_ENABLE,true);
}
#endif
//ÇáÈáæß ÓÇÊÑ
#ifndef ADD_BLOCK
	postion[0].set(8482.019,-500,-62.035 );
	postion[1].set(5357.242,0,3103.787);
	postion[2].set(5579.657,0,5579.657);
	postion[3].set(5303.01,0,1863.451);
	postion[4].set(5579.657,0,1860.165);
	postion[5].set(6352.893,0,1263.349);
	postion[6].set(6252.721,0,1266.635);
	postion[7].set(6150.139,0,1259.134);
	postion[8].set(6047.557,0,1259.134);
	postion[9].set(6047.557,0,1360.647);
	postion[10].set(6047.557,0,1459.87);
	postion[11].set(6047.557,0,1562.218);
	postion[12].set(6047.557,0,1662.478);
	postion[13].set(6047.557,0,1763.316);
	postion[14].set(6150.139,0,1781.161);
	postion[15].set(6252.721,0,1781.161);
	postion[16].set(6352.893,0,1781.161);
	postion[17].set(7279.947,0,1726.78);
	postion[18].set(7281.017,0,1601.155);
	postion[19].set(8596.924,0,2745.796);
	postion[20].set(9034.517,0,2786.534);
	postion[21].set(8745.527,0,4595.099);
	postion[22].set(10027.902,0,2699.181);
	postion[23].set(10389.609,0,2699.181);
	postion[24].set(10027.902,0,1733.834);
	postion[25].set(10389.609,0,1647.208);
	postion[26].set(13013.206,0,4182.702);
	postion[27].set(13552.084,0,2828.258);
	postion[28].set(13350.591,0,2699.181);
	postion[29].set(13775.56,0,2690.726);
	postion[30].set(12653.829,0,1416.885);
	postion[31].set(12834.068,0,1348.214);
	postion[32].set(13035.562,0,1366.65);
	postion[33].set(13260.356,0,1300.299);
	postion[34].set(13405.704,0,1408.585);

	postion[35].set(19447.004,-219.059,19377.566);
	postion[36].set(19471.504,-219.059,19038.045);
	postion[37].set(19467.619,-219.059,18837.055);
	postion[38].set(19420.33,-219.059,18597.873);
	postion[39].set(19447.004,-219.059,18409.924);
	postion[40].set(19470.814,-219.059,18193.193);
	postion[41].set(19447.004,-219.059,18043.727);
	postion[42].set(19457.857,-219.059,17884.055);
	postion[43].set(19447.004,-219.059,17738.674);
	postion[44].set(19470.379,-219.059,17562.531);
	postion[45].set(19477.822,-219.059,17434.047);
	postion[46].set(19185.621,-219.059,17412.008);
	postion[47].set(18924.238,-219.059,17384.766);
	postion[48].set(18793.547,-219.059,17412.008);
	postion[49].set(18532.164,-219.059,17412.008);
	postion[50].set(18270.781,-219.059,17374.773);
	postion[51].set(18009.398,-219.059,17412.008);
	postion[52].set(17878.707,-219.059,17351.266);
	postion[53].set(17617.324,-219.059,17374.326);
	postion[54].set(17486.633,-219.059,17412.008);
	postion[55].set(17225.25,-219.059,17412.008);
	postion[56].set(17094.559,-219.059,17366.789);
	postion[57].set(16833.176,-219.059,17364.191);

	postion[58].set(-273.046,0,6989.508);
	postion[59].set(-2295.899,0,6754.439);
	postion[60].set(-992.679,0,7750.022);

		
		Mesh1= smgr->getMesh("block_2.b3d");

for(int i=0;i<61;i++)
{
	 scene::ISceneNode*node = smgr->addOctTreeSceneNode(Mesh1->getMesh(0),0,501);
	
	 node->setPosition(postion[i]);
	node->setRotation(rotation[0]);
	
	node->setMaterialFlag(video::EMF_LIGHTING, false);
	
	node->setScale( irr::core::vector3df(1,1.2f,1));
	node->setMaterialFlag(video::EMF_FOG_ENABLE,true); 

	scene::ITriangleSelector*Selectors;
	Selectors = smgr->createOctTreeTriangleSelector(Mesh1->getMesh(0),node, 20);
	node->setTriangleSelector(Selectors);
	collMselector->addTriangleSelector(Selectors);
	shootMselector->addTriangleSelector(Selectors);
	Selectors->drop();
	Selectors=0;
//node->setMaterialFlag(video::EMF_FOG_ENABLE,true);
}
#endif
//ÇáÈÇãíá
#ifndef ADD_BARAMEL

	postion[0].set(7167.527,0,2746.174);
	postion[1].set(6805.67,0,1589.61);
	postion[2].set(7085.8,0,3396.737);
	postion[3].set(8140.516,0,3983.911);
	postion[4].set(8827.125,0,3980.794);
	postion[5].set(8178.919,0,4922.838);
	postion[6].set(8273.021,0,5829.999);
	postion[7].set(9571.58,0,1752.813);
	postion[8].set(7796.808,0,326.601);
	postion[9].set(7404.751,0,495.165);
	postion[10].set(18816.563,-167.087,10984.746);
	postion[11].set(17766.52,-167.087,11162.334);
	postion[12].set(17766.52,-167.087,11071.39);


	postion[13].set(-1593.288,0,5970.634);
	postion[14].set(-1571.577,0,7497.849);
	postion[15].set(27720.695,0,19762.053);
	postion[16].set(27720.695,0,19762.053);
		rotation[0].set( 0, 0, 0);
		
		Mesh1= smgr->getMesh("barmel.b3d");

for(int i=0;i<15;i++)
{
	 scene::ISceneNode*node = smgr->addOctTreeSceneNode(Mesh1->getMesh(0),0,502);
	
	 node->setPosition(postion[i]);
	node->setRotation(rotation[i]);
	
	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setScale( irr::core::vector3df(1,1.2f,1));
	node->setMaterialFlag(video::EMF_FOG_ENABLE,true); 

	scene::ITriangleSelector*Selectors;
	Selectors = smgr->createOctTreeTriangleSelector(Mesh1->getMesh(0),node, 20);
	node->setTriangleSelector(Selectors);
	collMselector->addTriangleSelector(Selectors);
	shootMselector->addTriangleSelector(Selectors);
	Selectors->drop();
	Selectors=0;
//node->setMaterialFlag(video::EMF_FOG_ENABLE,true);
}
#endif
//ãÍØÉ ÇÑÓÇá
#ifndef ADD_WIRELESS

postion[0].set(12841.863,0,-87.839 );
postion[1].set(20018.512,253.381,14393.094);
		rotation[0].set( 0, 0, 0);
		
		Mesh1= smgr->getMesh("wireless.b3d");

for(int i=0;i<2;i++)
{
	 scene::ISceneNode*node = smgr->addOctTreeSceneNode(Mesh1->getMesh(0),0,502);
	
	 node->setPosition(postion[i]);
	node->setRotation(rotation[i]);
	
	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setScale( irr::core::vector3df(1,1.2f,1));
	node->setMaterialFlag(video::EMF_FOG_ENABLE,true); 

	scene::ITriangleSelector*Selectors;
	Selectors = smgr->createOctTreeTriangleSelector(Mesh1->getMesh(0),node, 20);
	node->setTriangleSelector(Selectors);
	collMselector->addTriangleSelector(Selectors);
	shootMselector->addTriangleSelector(Selectors);
	Selectors->drop();
	Selectors=0;
//node->setMaterialFlag(video::EMF_FOG_ENABLE,true);
}
#endif
//ÇáÓíÇÑÉ
#ifndef ADD_CAR

	postion[0].set(9547.475,0,3867.357 );
		rotation[0].set( 0, 0, 0);
		
		Mesh1= smgr->getMesh("car.b3d");

for(int i=0;i<1;i++)
{
	 scene::ISceneNode*node = smgr->addOctTreeSceneNode(Mesh1->getMesh(0),0,502);
	
	 node->setPosition(postion[i]);
	node->setRotation(rotation[i]);
	
	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setScale( irr::core::vector3df(1,1.2f,1));
	node->setMaterialFlag(video::EMF_FOG_ENABLE,true); 

	node->getMaterial(0).MaterialTypeParam=10;
	node->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);
	
	scene::ITriangleSelector*Selectors;
	Selectors = smgr->createOctTreeTriangleSelector(Mesh1->getMesh(0),node, 20);
	node->setTriangleSelector(Selectors);
	collMselector->addTriangleSelector(Selectors);
	shootMselector->addTriangleSelector(Selectors);
	Selectors->drop();
	Selectors=0;
//node->setMaterialFlag(video::EMF_FOG_ENABLE,true);
}
#endif
//ãßÇä ÇÞáÇÚ ÇáØíÇÑÉ
#ifndef ADD_H

postion[0].set(8482.019,0,-62.035 );
postion[1].set(20718.521,-208.576,18693.748);
		rotation[0].set( 0, 0, 0);
		
		Mesh1= smgr->getMesh("h_plane.b3d");

for(int i=0;i<2;i++)
{
	 scene::ISceneNode*node = smgr->addOctTreeSceneNode(Mesh1->getMesh(0),0,501);
	
	 node->setPosition(postion[i]);
	node->setRotation(rotation[i]);
	
	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setScale( irr::core::vector3df(1,1.2f,1));
	node->setMaterialFlag(video::EMF_FOG_ENABLE,true); 

	scene::ITriangleSelector*Selectors;
	Selectors = smgr->createOctTreeTriangleSelector(Mesh1->getMesh(0),node, 20);
	node->setTriangleSelector(Selectors);
	collMselector->addTriangleSelector(Selectors);
	shootMselector->addTriangleSelector(Selectors);
	Selectors->drop();
	Selectors=0;
//node->setMaterialFlag(video::EMF_FOG_ENABLE,true);
}
#endif
//ÇáÓÇÊÑ ÇáØæíá ÇÝÞí
#ifndef ADD_WALLH
		postion[0].set(9822.62,0,5112.984);
		postion[1].set(9825.198,0,3943.526);
		postion[2].set(9826.927,0,2588.672);
		postion[3].set(9825.198,0,472.781);
		postion[4].set(9829.792,0,-882.716);
		postion[5].set(27629.572,0,21063.4);
		postion[6].set(27664.348,0,20986.852);

		rotation[0].set( 0, 0, 0);

		Mesh1= smgr->getMesh("wall_sater_horezntal.b3d");

for(int i=0;i<7;i++)
{
	 scene::ISceneNode*node = smgr->addOctTreeSceneNode(Mesh1->getMesh(0),0,501);
	
	 node->setPosition(postion[i]);
	node->setRotation(rotation[i]);
	
	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setScale( irr::core::vector3df(1,1.2f,1));
	node->setMaterialFlag(video::EMF_FOG_ENABLE,true); 

	scene::ITriangleSelector*Selectors;
	Selectors = smgr->createOctTreeTriangleSelector(Mesh1->getMesh(0),node, 20);
	node->setTriangleSelector(Selectors);
	collMselector->addTriangleSelector(Selectors);
	shootMselector->addTriangleSelector(Selectors);
	Selectors->drop();
	Selectors=0;
//node->setMaterialFlag(video::EMF_FOG_ENABLE,true);
}
#endif
//ÇáÓÇÊÑ ÇáØæíá ÑÇÓí
#ifndef ADD_WALLV

		postion[0].set(6775.019,0,4016.376);
		postion[1].set(8464.196,0,4016.376);
		postion[2].set(7561.88,0,635.021);
		postion[3].set(8475.198,0,630.999);
		postion[4].set(26276.244,0,19709.496);
		postion[5].set(26276.244,0,18578.998);
		postion[6].set(26864.969,0,21456.936);

				rotation[0].set( 0, 0, 0);
		Mesh1= smgr->getMesh("wall_sater_vertecal.b3d");

for(int i=0;i<7;i++)
{
	 scene::ISceneNode*node = smgr->addOctTreeSceneNode(Mesh1->getMesh(0),0,501);
	
	 node->setPosition(postion[i]);
	node->setRotation(rotation[i]);
	
	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setScale( irr::core::vector3df(1,1.2f,1));
	node->setMaterialFlag(video::EMF_FOG_ENABLE,true); 

	scene::ITriangleSelector*Selectors;
	Selectors = smgr->createOctTreeTriangleSelector(Mesh1->getMesh(0),node, 20);
	node->setTriangleSelector(Selectors);
	collMselector->addTriangleSelector(Selectors);
	shootMselector->addTriangleSelector(Selectors);
	Selectors->drop();
	Selectors=0;
//node->setMaterialFlag(video::EMF_FOG_ENABLE,true);
}
#endif
//ÇáÓÇÊÑ ÇáÃÍãÑ ááÓíÇÑÇÊ
#ifndef ADD_SATER2

		postion[0].set(8884.774,0,1566.555);
		rotation[0].set( 0, 0, 0);
		postion[1].set(6109.322,0,2000.455);
		rotation[1].set( 0, 0, 0);
		postion[2].set(6237.52,0,251.297);
		rotation[2].set( 0, 0, 0);
		postion[3].set(13067.485,0,2090.372);
		rotation[3].set( 0, 0, 0);
		postion[4].set(13589.707,0,2474.356);
		rotation[4].set( 0, 0, 0);
		
		Mesh1= smgr->getMesh("sater_02.b3d");

for(int i=0;i<5;i++)
{
	 scene::ISceneNode*node = smgr->addOctTreeSceneNode(Mesh1->getMesh(0),0,501);
	
	 node->setPosition(postion[i]);
	node->setRotation(rotation[i]);
	
	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setScale( irr::core::vector3df(1,1.5f,1));
	node->setMaterialFlag(video::EMF_FOG_ENABLE,true); 

	scene::ITriangleSelector*Selectors;
	Selectors = smgr->createOctTreeTriangleSelector(Mesh1->getMesh(0),node, 20);
	node->setTriangleSelector(Selectors);
	Selectors->drop();
	collMselector->addTriangleSelector(Selectors);
	shootMselector->addTriangleSelector(Selectors);
Selectors->drop();
Selectors=0;
//node->setMaterialFlag(video::EMF_FOG_ENABLE,true);
}
#endif
//tree
#ifndef ADD_TREE

		postion[0].set(10913.125,0,3659.346 );
		postion[1].set(13489.84,0,-525.937 );
		postion[2].set(13489.84,0,5845.705 );
		postion[3].set(-4749.717,2.992,-3451.343);
		postion[4].set(-1709.49,0.306,-2054.971);
		postion[5].set(2342.996,3.026,-3507.696);
		postion[6].set(-4036.867,-339.15,1513.342);
		postion[7].set(-4036.867,-26.742,2897.353);
		postion[8].set(-2905.274,6.742,3911.414);
		postion[9].set(-2138.127,18.942,4465.088);
		postion[10].set(823.706,399.486,3702.271);

		postion[11].set(2634.328,329.747,669.66);
		postion[12].set(4668.804,6.333,-1056.1);
		postion[13].set(6009.532,10.443,-647.419);
		postion[14].set(-4381.253,22.864,8528.272);
		postion[15].set(-483.87,22.864,9890.686);
		postion[16].set(4625.026,2.864,8756.164);
		postion[17].set(8581.578,22.864,8756.164);

		postion[18].set(1718.499,22.864,12709.408);
		postion[19].set(2473.502,22.864,14466.63);
		postion[20].set(1893.747,22.864,16384.082);
		postion[21].set(5000.743,22.864,12871.553);
		postion[22].set(7092.454,22.864,14385.358);
		postion[23].set(6088.612,22.864,18196.621);
		postion[24].set(9236.809,22.864,15379.01);
		postion[25].set(10575.021,10.443,-4217.142);

		Mesh1= smgr->getMesh("tree_01.b3d");

for(int i=0;i<26;i++)
{
	 scene::ISceneNode*node = smgr->addOctTreeSceneNode(Mesh1->getMesh(0),0,-1);
	
	 node->setPosition(postion[i]);
	node->setRotation(rotation[i]);
	
	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setMaterialFlag(video::EMF_FOG_ENABLE,true); 
	
	node->getMaterial(0).MaterialTypeParam=10;
	node->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);
	
	node->setScale( irr::core::vector3df(1,1.2f,1));
	
	//scene::ITriangleSelector*Selectors;
	//Selectors = smgr->createOctTreeTriangleSelector(Mesh1->getMesh(0),node, 20);
	//node->setTriangleSelector(Selectors);
	//Selectors->drop();
//Selectors=0;
//node->setMaterialFlag(video::EMF_FOG_ENABLE,true);
}
#endif
//ÇáÕäÏæÞ ÇáÇÈíÖ
#ifndef ADD_BOX1

		postion[0].set(6209.514,0,2676.302);
		postion[1].set(9259.313,0,1173.156 );
		postion[2].set(13603.827,0,1557.869);
		postion[3].set(24281.912,-188.338,19459.846);
		postion[4].set(-1785.662,0,7519.021);

		rotation[0].set( 0, 0, 0);
		
		Mesh1= smgr->getMesh("box_01.b3d");
 // textures= driver->getTexture("mabna.jpg");
//node->setMaterialTexture(0,textures);
for(int i=0;i<5;i++)
{
	 scene::ISceneNode*node = smgr->addOctTreeSceneNode(Mesh1->getMesh(0),0,502);
	
	 node->setPosition(postion[i]);
	node->setRotation(rotation[i]);
	
	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setScale( irr::core::vector3df(1,1.2f,1));
	node->setMaterialFlag(video::EMF_FOG_ENABLE,true); 

	scene::ITriangleSelector*Selectors;
	Selectors = smgr->createOctTreeTriangleSelector(Mesh1->getMesh(0),node, 20);
	node->setTriangleSelector(Selectors);
	collMselector->addTriangleSelector(Selectors);
	shootMselector->addTriangleSelector(Selectors);
	Selectors->drop();
	Selectors=0;
//node->setMaterialFlag(video::EMF_FOG_ENABLE,true);
}
#endif
//ÇáÕäÏæÞ ÇáÃÒÞ
#ifndef ADD_BOX2

		postion[0].set(7882.885,0,1242.426);
		postion[1].set(8630.629,0,1122.84);
		postion[2].set(9253.151,0,1136.171);



		rotation[2].set( 0, 180, 0);
		Mesh1= smgr->getMesh("box_02.b3d");
  //textures= driver->getTexture("mabna.jpg");
//node->setMaterialTexture(0,textures);
for(int i=0;i<3;i++)
{
	 scene::ISceneNode*node = smgr->addOctTreeSceneNode(Mesh1->getMesh(0),0,502);
	
	 node->setPosition(postion[i]);
	node->setRotation(rotation[i]);
	
	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setScale( irr::core::vector3df(1,1.2f,1));
	node->setMaterialFlag(video::EMF_FOG_ENABLE,true); 

	scene::ITriangleSelector*Selectors;
	Selectors = smgr->createOctTreeTriangleSelector(Mesh1->getMesh(0),node, 20);
	node->setTriangleSelector(Selectors);
	collMselector->addTriangleSelector(Selectors);
	shootMselector->addTriangleSelector(Selectors);
	Selectors->drop();
	Selectors=0;
//node->setMaterialFlag(video::EMF_FOG_ENABLE,true);
}
#endif
//ÇáãÖáÉ ÇáÃÈíÖ æÇáÃÒÑÞ
#ifndef ADD_SKYBOX

		postion[0].set(5856.48,0,2692.991 );
		rotation[0].set( 0, 0, 0);
		postion[1].set(7976.063,0,2742.377 );
		rotation[1].set( 0, 0, 0);
		postion[2].set(13746.593,0,1781.305 );
		rotation[2].set( 0, 180, 0);
		postion[3].set(-817.221,0,8013.19);
		
		Mesh1= smgr->getMesh("mathala.b3d");
  //textures= driver->getTexture("mabna.jpg");
//node->setMaterialTexture(0,textures);
for(int i=0;i<4;i++)
{
	 scene::ISceneNode*node = smgr->addOctTreeSceneNode(Mesh1->getMesh(0),0,502);
	
	 node->setPosition(postion[i]);
	node->setRotation(rotation[i]);
	
	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setScale( irr::core::vector3df(1,1.2f,1));
	node->setMaterialFlag(video::EMF_FOG_ENABLE,true); 

	scene::ITriangleSelector*Selectors;
	Selectors = smgr->createOctTreeTriangleSelector(Mesh1->getMesh(0),node, 20);
	node->setTriangleSelector(Selectors);
	collMselector->addTriangleSelector(Selectors);
	shootMselector->addTriangleSelector(Selectors);
	Selectors->drop();
	Selectors=0;

}
#endif
//ÇáÇÈÑÇÌ
#ifndef ADD_BARAJ

		postion[0].set(6783.021,0,-865.022 );
		postion[1].set(6793.451,0,6436.806);
		postion[2].set(14070.012,0,6470.544 );
		postion[3].set(14077.979,0,-881.02);
		
		rotation[0].set( 0, 0, 0);
		
		Mesh1= smgr->getMesh("baraj.b3d");
for(int i=0;i<4;i++)
{
	 scene::ISceneNode*node = smgr->addOctTreeSceneNode(Mesh1->getMesh(0),0,501);
	
	 node->setPosition(postion[i]);
	node->setRotation(rotation[i]);
	
	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setScale( irr::core::vector3df(1,1.2f,1));
	node->setMaterialFlag(video::EMF_FOG_ENABLE,true); 
	node->setMaterialFlag(video::EMF_BACK_FACE_CULLING,false);
	scene::ITriangleSelector*Selectors;
	Selectors = smgr->createOctTreeTriangleSelector(Mesh1->getMesh(0),node, 20);
	node->setTriangleSelector(Selectors);
	collMselector->addTriangleSelector(Selectors);
	shootMselector->addTriangleSelector(Selectors);
	Selectors->drop();
	Selectors=0;

}
#endif
//flag
#ifndef ADD_FLAG
		postion[0].set(19732.775,1982.193,14401.813);
		postion[1].set(12966.115,1243.903,4516.812);
		postion[2].set(12567.799,1795.702,-82.806);

		rotation[0].set( 0,0, 0);
		rotation[1].set( 0,0, 0);	
		rotation[2].set( 0,0, 0);	
		Mesh1= smgr->getMesh("flag.b3d");
for(int i=0;i<3;i++)
{
	scene::IAnimatedMeshSceneNode*node = smgr->addAnimatedMeshSceneNode(Mesh1,0,501);
	
	 node->setPosition(postion[i]);
	node->setRotation(rotation[0]);
	
	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setScale( irr::core::vector3df(0.5f,0.8f,0.7f));
	node->setMaterialFlag(video::EMF_FOG_ENABLE,true); 
	node->setFrameLoop(0,19);
	node->setLoopMode(true);
node->setAnimationSpeed(10);
node->setMaterialFlag(video::EMF_FOG_ENABLE,true);
}
#endif
#ifndef ADD_HEALTH
postion[0].set(11699.3,100,5373.6);
if(fun.RandomRange(0,1))
postion[1].set(8483.8,20,5035.8);
else
postion[1].set(6866.8,20,424.5);

Mesh1= smgr->getMesh("helth.b3d");
int Nid=600;
for(int i=0;i<2;i++)
{
	scene::ISceneNode*node =smgr->addOctTreeSceneNode(Mesh1->getMesh(0),0,Nid);
	node->setPosition(postion[i]);
	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setScale( irr::core::vector3df(1,1.2f,1));
	HEALTH Hnode;
	Hnode.healtCount=30;
	Hnode.snId=Nid;
	Hnode.HealthPlace=core::rect<float>(postion[i].X+30,postion[i].Z+30,postion[i].X-30,postion[i].Z-30);

Hnode.HealthPlace.repair();
HealthArry.push_back(Hnode);
Nid++;
}
#endif

Winlocation=core::rect<float>(27598,21106,26189,17580);
Winlocation.repair();
//-----------------------------------------------------------------------------------------



	collMselector->addTriangleSelector(hideShabcSelector);//add shbc 
//-----------------------------------------------------------------------------------------------------

delete []postion;
delete []rotation;


}

void BuildWeoponCLass()
{
	
	for(int i=0;i<LVLP_Weopcount;i++)
	{
	LVLWeop->weap[LW[i].Wnum].GP_isHold=true;
	LVLWeop->weap[LW[i].Wnum].GP_TotalShotCount=LW[i].totalShotCount;
	LVLWeop->weap[LW[i].Wnum].GP_ShotInStorgeCount=LW[i].storgeShotCount;
	}
}


};
class CLevels_2 : public CLevels
{
private:


public: 
CLevels_2(IrrlichtDevice *device)
{
	Dev=device;
	smgr=Dev->getSceneManager();
	driver=Dev->getVideoDriver();
	LVLWeop=new CWeapon();
	BuildLevel();
	BuildWeoponCLass();
}
void BuildLevel()
{
LVLnumber=2;
LVLname="Test";
LVLpostion=core::vector3df(0,0,0);
//LVLP_strPoint=core::vector3df(3747,80,1174);//end level
LVLP_strPoint=core::vector3df(-174,80,474);

LVLP_strRout=core::vector3df(50,90,50);
LVLP_strWeopon=2;
LVLP_Weopcount=3;
//-----------------------------------
LW=new levelWeopon[3];//two weopon to this level
//first weopen;
LW[0].Wnum=2;//m16
LW[0].totalShotCount=60;
LW[0].storgeShotCount=30;
//secand weopen
LW[1].Wnum=4;//perg
LW[1].totalShotCount=0;
LW[1].storgeShotCount=1;

LW[2].Wnum=3;//klshn
LW[2].totalShotCount=60;
LW[2].storgeShotCount=30;


//------------------------------


 //create mselector
	collMselector=smgr->createMetaTriangleSelector();
	shootMselector=smgr->createMetaTriangleSelector();
	video::ITexture*textures;
	scene::ITriangleSelector*LevelSelector;
	//-------------------------------------------------------------------------------
 //1-add main trrant level
	
	Dev->getVideoDriver()->setFog(video::SColor(255,100,100,100),true,2000,9000,0.01f,false,false);
	Dev->getFileSystem()->addZipFileArchive("data/lv11.pk3");
    bspmesh = smgr->getMesh("./map/mapp.bsp");

	bspnode=smgr->addOctTreeSceneNode(bspmesh->getMesh(0),0,501);

	bspnode->setPosition(core::vector3df(0,0,0));
	bspnode->setMaterialFlag(video::EMF_LIGHTING, false);

	bspnode->setScale( irr::core::vector3df(1,1.2f,1));
	
	LevelSelector = smgr->createOctTreeTriangleSelector(bspmesh->getMesh(0), bspnode, 20);
	bspnode->setTriangleSelector(LevelSelector);
	
	collMselector->addTriangleSelector(LevelSelector);
	shootMselector->addTriangleSelector(LevelSelector);
	LevelSelector->drop();
	LevelSelector=0;

		scene::ISceneNode* skybox = smgr->addSkyBoxSceneNode(
		Dev->getVideoDriver()->getTexture("./env/irrlicht2_up.jpg"),
		Dev->getVideoDriver()->getTexture("./env/irrlicht2_dn.jpg"),
		Dev->getVideoDriver()->getTexture("./env/irrlicht2_lf.jpg"),
		Dev->getVideoDriver()->getTexture("./env/irrlicht2_rt.jpg"),
		Dev->getVideoDriver()->getTexture("./env/irrlicht2_ft.jpg"),
		Dev->getVideoDriver()->getTexture("./env/irrlicht2_bk.jpg"));
	
Winlocation=core::rect<float>(3839,22,3052,635);
Winlocation.repair();

}

void BuildWeoponCLass()
{
	
	for(int i=0;i<LVLP_Weopcount;i++)
	{
	LVLWeop->weap[LW[i].Wnum].GP_isHold=true;
	LVLWeop->weap[LW[i].Wnum].GP_TotalShotCount=LW[i].totalShotCount;
	LVLWeop->weap[LW[i].Wnum].GP_ShotInStorgeCount=LW[i].storgeShotCount;
	}
}


};
class CLevels_3 : public CLevels
{
private:


public: 
CLevels_3(IrrlichtDevice *device)
{
	Dev=device;
	smgr=Dev->getSceneManager();
	driver=Dev->getVideoDriver();
	LVLWeop=new CWeapon();
	BuildLevel();
	BuildWeoponCLass();
}
void BuildLevel()
{
LVLnumber=2;
LVLname="Test";
LVLpostion=core::vector3df(0,0,0);
LVLP_strPoint=core::vector3df(-230,150,-299);
LVLP_strRout=core::vector3df(50,90,50);
LVLP_strWeopon=2;
LVLP_Weopcount=2;
//-----------------------------------
LW=new levelWeopon[3];//two weopon to this level
//first weopen;
LW[0].Wnum=2;//m16
LW[0].totalShotCount=60;
LW[0].storgeShotCount=30;
//secand wep
LW[1].Wnum=3;//klshn
LW[1].totalShotCount=60;
LW[1].storgeShotCount=30;


//------------------------------


 //create mselector
	collMselector=smgr->createMetaTriangleSelector();
	shootMselector=smgr->createMetaTriangleSelector();
	video::ITexture*textures;
	scene::ITriangleSelector*LevelSelector;
	//-------------------------------------------------------------------------------
 //1-add main trrant level
	
	Dev->getVideoDriver()->setFog(video::SColor(255,100,100,100),true,2000,9000,0.01f,false,false);
	Dev->getFileSystem()->addZipFileArchive("data/lv11.pk3");
    bspmesh = smgr->getMesh("./map/house.bsp");

	bspnode=smgr->addOctTreeSceneNode(bspmesh->getMesh(0),0,501);

	bspnode->setPosition(core::vector3df(0,0,0));
	bspnode->setMaterialFlag(video::EMF_LIGHTING, false);

	bspnode->setScale( irr::core::vector3df(1,1.2f,1));
	
	LevelSelector = smgr->createOctTreeTriangleSelector(bspmesh->getMesh(0), bspnode, 20);
	bspnode->setTriangleSelector(LevelSelector);
	
	collMselector->addTriangleSelector(LevelSelector);
	shootMselector->addTriangleSelector(LevelSelector);
	LevelSelector->drop();
	LevelSelector=0;

		scene::ISceneNode* skybox = smgr->addSkyBoxSceneNode(
		Dev->getVideoDriver()->getTexture("./env/irrlicht2_up.jpg"),
		Dev->getVideoDriver()->getTexture("./env/irrlicht2_dn.jpg"),
		Dev->getVideoDriver()->getTexture("./env/irrlicht2_lf.jpg"),
		Dev->getVideoDriver()->getTexture("./env/irrlicht2_rt.jpg"),
		Dev->getVideoDriver()->getTexture("./env/irrlicht2_ft.jpg"),
		Dev->getVideoDriver()->getTexture("./env/irrlicht2_bk.jpg"));
	
Winlocation=core::rect<float>(27598,21106,26189,17580);
Winlocation.repair();
}

void BuildWeoponCLass()
{
	
	for(int i=0;i<LVLP_Weopcount;i++)
	{
	LVLWeop->weap[LW[i].Wnum].GP_isHold=true;
	LVLWeop->weap[LW[i].Wnum].GP_TotalShotCount=LW[i].totalShotCount;
	LVLWeop->weap[LW[i].Wnum].GP_ShotInStorgeCount=LW[i].storgeShotCount;
	}
}


};


#endif
