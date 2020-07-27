/*
writen by (Younes khafaja) - 2008-2009
You are free to use this code as you see fit
email : lighting-team@hotmail.com
*/
#ifndef weop_H
#define weop_H
#include <irrlicht.h>
#include <irrKlang.h>

using namespace irrklang;
using namespace irr;

struct SWeaponGuns
{
int GNumber;
const wchar_t*Gname;
c8* Gpath;
c8* GTexturePath;
core::vector3df Gpostion;
core::vector3df Groution;
c8 *GfireTexturePath;
core::vector3df GfirePost;
core::position2di GshotRandom;
core::vector3df GbackPostion; //„ﬁœ«— —ÃÊ⁄ «·”·«Õ
int GRoutCamUpSpeed;//„ﬁœ«— œÊ—«‰ «·ﬂ«„Ì—« ·«⁄·Ï
bool GIsMakeZoom;
f32 GFOV;
c8* GZoomTexturePath;//’Ê—… «·ﬁ‰«’… «‰ ÊÃœ
float GZoomDegree; 
int GanimaitonSpeed;//speed change the spare
float GTimeBetShot; //«·“„‰ »Ì‰ ﬂ· ÿ·ﬁ…
float GFeameSpeed;//”—⁄… Õ—ﬂ… «·≈ÿ·«ﬁ 
int GmaxShotCount;// «ﬁ’Ï ⁄œœ „‰ «·—’«’ Ì„ﬂ‰ ÕÌ«“ … €Ì— «·„Œ“‰
int GstShotStorageCount;//⁄œœ «·—’«’ «·„Œ“‰ «·Ê«Õœ
bool GIsAutomatic;//Â· «·”·«Õ √Ê Ê„ ﬂ
bool GP_isHold;//Â· Ì„·ﬂ «··«⁄» Â« «·”·«Õ
int GP_TotalShotCount;//⁄œœ «·—’«’ «·ﬂ·Ì (€Ì— —’«’ «·„Õ“‰)«·„ÊÃÊœ „⁄ «··«⁄» 
int GP_ShotInStorgeCount;//⁄œœ «·—’«’ «·„ÊÃÊœ ›Ì «·„Œ“‰
c8* GfocusGunpath;//„”«— ’Ê—… «‘«—… + «·Œ«’… »«·”·«Õ
core::position2di GfocusGunpost;//„Êﬁ⁄ «‘«—… + ⁄·Ï «·‘«‘…
c8* GshotSoundp;//„”«— ’Ê  «ÿ·«ﬁ 
c8* GchangeStorgeSound;//„”«— ’Ê   €ÌÌ— «·„Œ“‰

};
class CWeapon
{
public:
SWeaponGuns*weap;

CWeapon()
{
weap=new SWeaponGuns[5];

weap[0].GNumber=0;
weap[0].Gname=L"x";
weap[0].Gpath="x";
weap[0].GTexturePath="x";
weap[0].Groution=core::vector3df(5,200,-5);
weap[0].Gpostion=core::vector3df(6,-10,20);
weap[0].GbackPostion=core::vector3df(7,-10,19);
weap[0].GRoutCamUpSpeed=30;
weap[0].GFeameSpeed=10;
weap[0].GfireTexturePath="x";
weap[0].GfirePost=core::vector3df(9,2,-26);
weap[0].GIsAutomatic=true;
weap[0].GIsMakeZoom=false;
weap[0].GmaxShotCount=120;
weap[0].GstShotStorageCount=30;
weap[0].GshotRandom=core::position2di(-800,800);//-------------------------
weap[0].GTimeBetShot=0.12f;	//one shot pre secand 
weap[0].GZoomDegree=0;
weap[0].GZoomTexturePath="";
weap[0].GanimaitonSpeed=30;

weap[0].GP_isHold=false;
weap[0].GP_ShotInStorgeCount=0;
weap[0].GP_TotalShotCount=0;
weap[0].GfocusGunpath="FocusGuns2.png";
weap[0].GfocusGunpost=core::position2di(383,290);
weap[0].GshotSoundp="sounds/2shoot.wav";
weap[0].GchangeStorgeSound="sounds/2changeStorge.wav";
//********************************************************************************************
weap[1].GNumber=1;
weap[1].Gname=L"x";
weap[1].Gpath="x";
weap[1].GTexturePath="x";
weap[1].Groution=core::vector3df(5,200,-5);
weap[1].Gpostion=core::vector3df(6,-10,20);
weap[1].GbackPostion=core::vector3df(7,-10,19);
weap[1].GRoutCamUpSpeed=0;
weap[1].GFeameSpeed=10;
weap[1].GfireTexturePath="x";
weap[1].GfirePost=core::vector3df(9,2,-26);
weap[1].GIsAutomatic=true;
weap[1].GIsMakeZoom=false;
weap[1].GmaxShotCount=120;
weap[1].GstShotStorageCount=30;
weap[1].GshotRandom=core::position2di(-800,800);//-------------------------
weap[1].GTimeBetShot=0.12f;	//one shot pre secand 
weap[1].GZoomDegree=0;
weap[1].GZoomTexturePath="";
weap[1].GanimaitonSpeed=30;

weap[1].GP_isHold=false;
weap[1].GP_ShotInStorgeCount=0;
weap[1].GP_TotalShotCount=0;
weap[1].GfocusGunpath="FocusGuns2.png";
weap[1].GfocusGunpost=core::position2di(383,290);
weap[1].GshotSoundp="sounds/2shoot.wav";
weap[1].GchangeStorgeSound="sounds/2changeStorge.wav";
//********************************************************************************************
weap[2].GNumber=2;
weap[2].Gname=L"M16";
weap[2].Gpath="m16.b3d";
weap[2].GTexturePath="gun.PNG";
weap[2].Groution=core::vector3df(-5,-8,-5);
weap[2].Gpostion=core::vector3df(6,-6,20);
weap[2].GbackPostion=core::vector3df(6.5,-6,19.3);
weap[2].GRoutCamUpSpeed=30;
weap[2].GFeameSpeed=20;
weap[2].GfireTexturePath="fireGun2.jpg";
weap[2].GfirePost=core::vector3df(1.5,-0.5,20);
weap[2].GIsAutomatic=true;
weap[2].GIsMakeZoom=true;
weap[2].GFOV=40;
weap[2].GmaxShotCount=120;
weap[2].GstShotStorageCount=30;
weap[2].GshotRandom=core::position2di(-800,800);//-------------------------
weap[2].GTimeBetShot=0.12f;	//one shot pre secand 
weap[2].GZoomDegree=0;
weap[2].GZoomTexturePath="";
weap[2].GanimaitonSpeed=15;

weap[2].GP_isHold=false;
weap[2].GP_ShotInStorgeCount=0;
weap[2].GP_TotalShotCount=0;
weap[2].GfocusGunpath="FocusGuns2.png";
weap[2].GfocusGunpost=core::position2di(383,290);
weap[2].GshotSoundp="sounds/2shoot.wav";
weap[2].GchangeStorgeSound="sounds/2changeStorge.wav";
//********************************************************************************************
weap[3].GNumber=3;
weap[3].Gname=L"ak47";
weap[3].Gpath="ak47.b3d";
weap[3].GTexturePath="x";
weap[3].Groution=core::vector3df(-8,-8,-5);
weap[3].Gpostion=core::vector3df(7,-6,19.7);
weap[3].GbackPostion=core::vector3df(8,-6,18.7);
weap[3].GRoutCamUpSpeed=40;
weap[3].GFeameSpeed=17;
weap[3].GfireTexturePath="fireGun3.jpg";
weap[3].GfirePost=core::vector3df(-1,1,20);
weap[3].GIsAutomatic=true;
weap[3].GIsMakeZoom=false;
weap[3].GmaxShotCount=120;
weap[3].GstShotStorageCount=30;
weap[3].GshotRandom=core::position2di(-1000,1000);//-------------------------
weap[3].GTimeBetShot=0.14f;	//one shot pre secand 
weap[3].GZoomDegree=0;
weap[3].GZoomTexturePath="";
weap[3].GanimaitonSpeed=15;

weap[3].GP_isHold=false;
weap[3].GP_ShotInStorgeCount=0;
weap[3].GP_TotalShotCount=0;
weap[3].GfocusGunpath="FocusGuns3.png";
weap[3].GfocusGunpost=core::position2di(383,290);
weap[3].GshotSoundp="sounds/3shoot.wav";
weap[3].GchangeStorgeSound="sounds/3changeStorge.wav";
//********************************************************************************************
weap[4].GNumber=4;
weap[4].Gname=L"M107";
weap[4].Gpath="m107.b3d";
weap[4].GTexturePath="x";
weap[4].Groution=core::vector3df(-3,-3,-5);
weap[4].Gpostion=core::vector3df(6,-7,20);
weap[4].GbackPostion=core::vector3df(7,-6.3,18);
weap[4].GRoutCamUpSpeed=80;
weap[4].GFeameSpeed=10;
weap[4].GfireTexturePath="fireGun4.jpg";
weap[4].GfirePost=core::vector3df(-0.9,2,22.3);
weap[4].GIsAutomatic=false;

weap[4].GmaxShotCount=120;
weap[4].GstShotStorageCount=30;
weap[4].GshotRandom=core::position2di(-100,100);//-------------------------
weap[4].GTimeBetShot=0.3f;	//two shot pre secand 

weap[4].GIsMakeZoom=true;
weap[4].GFOV=10;
weap[4].GZoomDegree=0;
weap[4].GZoomTexturePath="zoomImage.png";
weap[4].GanimaitonSpeed=15;//speed change the spare

weap[4].GP_isHold=false;
weap[4].GP_ShotInStorgeCount=0;
weap[4].GP_TotalShotCount=0;
weap[4].GfocusGunpath="FocusGubs4.png";
weap[4].GfocusGunpost=core::position2di(385,288);
weap[4].GshotSoundp="sounds/4shoot.wav";
weap[4].GchangeStorgeSound="sounds/4changeStorge.wav";
}
};
#endif