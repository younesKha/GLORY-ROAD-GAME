/*
writen by (Younes khafaja) - 2008-2009
You are free to use this code as you see fit
email : lighting-team@hotmail.com
*/

#ifndef AFNT_H
#define AFNT_H
#include <irrlicht.h>
using namespace irr;

class ArabicFont
{
private:
	IrrlichtDevice *Device;
	scene::ISceneManager* smanger;
	video::IVideoDriver*driver;
	video::ITexture*fontTxture;
	core::rect<int>LetterRect[120];
public:
	ArabicFont(IrrlichtDevice *device,c8*textureName)
	{
	Device=device;
	smanger=device->getSceneManager();
	driver=device->getVideoDriver();

	fontTxture=driver->getTexture(textureName);
	driver->makeColorKeyTexture(fontTxture, core::position2d<s32>(10,0));
	//Ã
	LetterRect[0]=core::rect<int>(191,0,195,35);
	LetterRect[1]=core::rect<int>(262,0,267,35);
	LetterRect[2]=core::rect<int>(166,0,183,35);
	LetterRect[3]=core::rect<int>(218,0,225,35);
	LetterRect[4]=core::rect<int>(198,0,215,35);
	//È
	LetterRect[5]=core::rect<int>(251,35,268,70);
	LetterRect[6]=core::rect<int>(239,35,247,70);
	LetterRect[7]=core::rect<int>(220,35,227,70);
	LetterRect[8]=core::rect<int>(191,35,208,70);

	LetterRect[9]=core::rect<int>(251,70,268,105);
	LetterRect[10]=core::rect<int>(240,70,247,105);
	LetterRect[11]=core::rect<int>(217,70,224,105);
	LetterRect[12]=core::rect<int>(188,70,206,105);

	LetterRect[13]=core::rect<int>(249,105,267,140);
	LetterRect[14]=core::rect<int>(237,105,246,140);
	LetterRect[15]=core::rect<int>(219,105,225,140);
	LetterRect[16]=core::rect<int>(189,105,207,140);

	LetterRect[17]=core::rect<int>(255,140,267,175);
	LetterRect[18]=core::rect<int>(240,140,251,175);
	LetterRect[19]=core::rect<int>(215,140,228,175);
	LetterRect[20]=core::rect<int>(191,140,203,175);

	LetterRect[21]=core::rect<int>(255,175,267,210);
	LetterRect[22]=core::rect<int>(240,175,251,210);
	LetterRect[23]=core::rect<int>(215,175,228,210);
	LetterRect[24]=core::rect<int>(191,175,203,210);

	LetterRect[25]=core::rect<int>(255,210,267,245);
	LetterRect[26]=core::rect<int>(240,210,251,245);
	LetterRect[27]=core::rect<int>(215,210,228,245);
	LetterRect[28]=core::rect<int>(191,210,203,245);

	LetterRect[29]=core::rect<int>(256,245,267,280);
	LetterRect[30]=core::rect<int>(237,245,248,280);

	LetterRect[31]=core::rect<int>(256,280,267,315);
	LetterRect[32]=core::rect<int>(237,280,248,315);

	LetterRect[33]=core::rect<int>(262,315,268,350);
	LetterRect[34]=core::rect<int>(247,315,254,350);

	LetterRect[35]=core::rect<int>(262,350,268,385);
	LetterRect[36]=core::rect<int>(247,350,254,385);

	LetterRect[37]=core::rect<int>(242,385,268,420);
	LetterRect[38]=core::rect<int>(222,385,238,420);
	LetterRect[39]=core::rect<int>(194,385,210,420);
	LetterRect[40]=core::rect<int>(156,385,182,420);

	LetterRect[41]=core::rect<int>(241,420,267,455);
	LetterRect[42]=core::rect<int>(221,420,238,455);
	LetterRect[43]=core::rect<int>(192,420,209,455);
	LetterRect[44]=core::rect<int>(154,420,180,455);

	LetterRect[45]=core::rect<int>(239,455,267,490);
	LetterRect[46]=core::rect<int>(219,455,235,490);
	LetterRect[47]=core::rect<int>(190,455,207,490);
	LetterRect[48]=core::rect<int>(151,455,179,490);

	LetterRect[49]=core::rect<int>(239,490,267,525);
	LetterRect[50]=core::rect<int>(219,490,235,525);
	LetterRect[51]=core::rect<int>(190,490,207,525);
	LetterRect[52]=core::rect<int>(151,490,179,525);

	LetterRect[53]=core::rect<int>(249,520,267,560);
	LetterRect[54]=core::rect<int>(229,520,246,560);
	LetterRect[55]=core::rect<int>(200,520,217,560);
	LetterRect[56]=core::rect<int>(170,520,188,560);

	LetterRect[57]=core::rect<int>(90,0,107,35);
	LetterRect[58]=core::rect<int>(70,0,86,35);
	LetterRect[59]=core::rect<int>(41,0,58,35);
	LetterRect[60]=core::rect<int>(13,0,60,35);

	LetterRect[61]=core::rect<int>(92,35,107,70);
	LetterRect[62]=core::rect<int>(82,35,92,70);
	LetterRect[63]=core::rect<int>(59,35,70,70);
	LetterRect[64]=core::rect<int>(37,35,47,70);

	LetterRect[65]=core::rect<int>(90,70,107,105);
	LetterRect[66]=core::rect<int>(82,70,92,105);
	LetterRect[67]=core::rect<int>(59,70,70,105);
	LetterRect[68]=core::rect<int>(37,70,47,105);

	LetterRect[69]=core::rect<int>(89,105,108,140);
	LetterRect[70]=core::rect<int>(73,105,85,140);
	LetterRect[71]=core::rect<int>(49,105,61,140);
	LetterRect[72]=core::rect<int>(20,105,38,140);

	LetterRect[73]=core::rect<int>(89,140,107,175);
	LetterRect[74]=core::rect<int>(73,140,85,175);
	LetterRect[75]=core::rect<int>(51,140,61,175);
	LetterRect[76]=core::rect<int>(20,140,39,175);

	LetterRect[77]=core::rect<int>(90,175,107,210);
	LetterRect[78]=core::rect<int>(72,175,86,210);
	LetterRect[79]=core::rect<int>(45,175,60,210);
	LetterRect[80]= core::rect<int>(16,175,34,210);

	LetterRect[81]=core::rect<int>(92,210,108,245);
	LetterRect[82]=core::rect<int>(82,210,88,245);
	LetterRect[83]=core::rect<int>(63,210,70,245);
	LetterRect[84]=core::rect<int>(35,210,52,245);

	LetterRect[85]=core::rect<int>(92,245,108,280);
	LetterRect[86]=core::rect<int>(78,245,89,280);
	LetterRect[87]=core::rect<int>(55,245,66,280);
	LetterRect[88]=core::rect<int>(28,245,43,280);

	LetterRect[89]=core::rect<int>(91,280,107,315);
	LetterRect[90]=core::rect<int>(82,280,88,315);
	LetterRect[91]=core::rect<int>(63,280,70,315);
	LetterRect[92]=core::rect<int>(34,280,51,315);

	LetterRect[93]=core::rect<int>(98,315,107,350);
	LetterRect[94]=core::rect<int>(86,315,94,350);
	LetterRect[95]=core::rect<int>(54,315,69,350);
	LetterRect[96]=core::rect<int>(30,315,42,350);

	LetterRect[97]=core::rect<int>(97,350,107,385);
	LetterRect[98]=core::rect<int>(79,350,89,385);

	LetterRect[99]=core::rect<int>(92,385,108,420);
	LetterRect[100]=core::rect<int>(77,385,84,420);
	LetterRect[101]=core::rect<int>(59,385,66,420);
	LetterRect[102]=core::rect<int>(30,385,47,420);

	LetterRect[103]=core::rect<int>(97,420,107,455);
	LetterRect[104]=core::rect<int>(85,420,93,455);
	LetterRect[105]=core::rect<int>(62,420,78,455);
	LetterRect[106]=core::rect<int>(47,420,54,455);
	LetterRect[107]=core::rect<int>(19,420,36,455);

	LetterRect[108]=core::rect<int>(95,455,107,490);
	LetterRect[109]=core::rect<int>(81,455,91,490);
	LetterRect[110]=core::rect<int>(58,455,69,490);
	LetterRect[111]=core::rect<int>(39,455,50,490);

	LetterRect[112]=core::rect<int>(102,490,106,525);
	LetterRect[113]=core::rect<int>(80,490,84,525);

	LetterRect[114]=core::rect<int>(167,70,179,105);

	LetterRect[115]=core::rect<int>(100,520,108,560);
	LetterRect[116]=core::rect<int>(80,520,90,560);
	LetterRect[117]=core::rect<int>(70,520,77,560);

	}

	void DrowText(int LNum,int txt[],core::position2di Postion,video::SColor fontColer)
	{
		core::position2di TxtPost=Postion;

		for(int i=0;i<LNum;i++)
		{
				int letrRect =txt[i];
				int nextltrRec=txt[i+1];

			driver->draw2DImage(fontTxture,TxtPost,LetterRect[letrRect],0,fontColer,true);

			if(!(i+1==LNum))
			TxtPost.X-=LetterRect[nextltrRec].getWidth();

		}
	}
};
#endif
