/*
writen by (Younes khafaja) - 2008-2009
You are free to use this code as you see fit
email : lighting-team@hotmail.com
*/
#include <irrKlang.h>
using namespace irrklang;
#ifndef SND_H
#define SND_H

class CSolderSounds
{
private:

irrklang::ISoundSource*soldrshootM16,*soldrshootBrgnv;
irrklang::ISoundSource*hitplayer,*hitplayer2,*sidrhit,*sidrhit1,*sidrhit2,*sidrhit3,*sidrhit4;

public:
ISoundEngine*SEngine; 
CSolderSounds(ISoundEngine*Engine)
{
SEngine=Engine;
soldrshootM16=SEngine->addSoundSourceFromFile("sounds/sldrshootM16.wav");
soldrshootBrgnv=SEngine->addSoundSourceFromFile("sounds/sldrshootBrgnv.wav");

hitplayer=SEngine->addSoundSourceFromFile("sounds/hitPlyer.ogg");
hitplayer2=SEngine->addSoundSourceFromFile("sounds/hitPlyer2.ogg");

sidrhit=SEngine->addSoundSourceFromFile("sounds/hit1.ogg");
sidrhit1=SEngine->addSoundSourceFromFile("sounds/hit2.ogg");
sidrhit2=SEngine->addSoundSourceFromFile("sounds/hit3.ogg");
sidrhit3=SEngine->addSoundSourceFromFile("sounds/hit4.ogg");
sidrhit4=SEngine->addSoundSourceFromFile("sounds/hit5.ogg");
}
void playSldrShootSound(float volume)
{
soldrshootM16->setDefaultVolume(volume);
SEngine->play2D(soldrshootM16);
}
void playSldrShootBrgnvSound(float volume)
{
soldrshootBrgnv->setDefaultVolume(volume);
SEngine->play2D(soldrshootBrgnv);
}

void playhitSound(bool close)
{
	if (close)
	SEngine->play2D(hitplayer2);
	else
	SEngine->play2D(hitplayer);
}
void playSldrHitSound(float volume,int SonudType =1 )
{
		if (SonudType==1)
		{
			sidrhit->setDefaultVolume(volume);
			SEngine->play2D(sidrhit);
		}
		else if (SonudType==2)
		{
			sidrhit1->setDefaultVolume(volume);
			SEngine->play2D(sidrhit1);
		}
		else if (SonudType==3)
		{
			sidrhit2->setDefaultVolume(volume);
			SEngine->play2D(sidrhit2);
		}
		else if (SonudType==4)
		{
			sidrhit3->setDefaultVolume(volume);
			SEngine->play2D(sidrhit3);
		}
		else if (SonudType==5)
		{
			sidrhit4->setDefaultVolume(volume);
			SEngine->play2D(sidrhit4);
		}
}


};
//-------------------------------------------------------------------------------------
class CPlayerSounds
{
private:

irrklang::ISoundSource*takeShoot,*swapWeop,*Mzoom,*youkilled,*takeHealth;
public:
ISoundEngine*SEngine; 
CPlayerSounds(ISoundEngine*Engine)
{
SEngine=Engine;
takeShoot=SEngine->addSoundSourceFromFile("sounds/take_2Shoot.wav");
swapWeop=SEngine->addSoundSourceFromFile("sounds/SwapWeop.wav");
Mzoom=SEngine->addSoundSourceFromFile("sounds/usezoom.wav");
youkilled=SEngine->addSoundSourceFromFile("sounds/youkilled.wav");
takeHealth=SEngine->addSoundSourceFromFile("sounds/takeHealth.ogg");

}
void PlaytakeWeopSound()
{
SEngine->play2D(takeShoot);
}
void PlaySwapWeopSound()
{
SEngine->play2D(swapWeop);
}

void PlayUseZoomSound()
{
SEngine->play2D(Mzoom);
}
void PlayYouKilledSound()
{
SEngine->play2D(youkilled);
}
void PlayTakeKealthSound()
{
SEngine->play2D(takeHealth);
}
void PlayWinMusicSound()
{
SEngine->play2D("sounds/WinMusic.ogg");
}
void PlayendMusicSound()
{
SEngine->play2D("sounds/endMusic.ogg");
}

};
//-------------------------------------------------------------------------------------
class CGameSounds
{
private:

irrklang::ISoundSource*clicksnd,*clicksnd2,*clicksnd3,*ClickStartG,*music1,*music2,*music3,*music4;
public:
ISoundEngine*SEngine; 
CGameSounds(ISoundEngine*Engine)
{
SEngine=Engine;
clicksnd=SEngine->addSoundSourceFromFile("sounds/CLick.wav");
ClickStartG=SEngine->addSoundSourceFromFile("sounds/click_StartGame.wav");
clicksnd2=SEngine->addSoundSourceFromFile("sounds/Click2.wav");
clicksnd3=SEngine->addSoundSourceFromFile("sounds/111.ogg");
music1=SEngine->addSoundSourceFromFile("sounds/music1.ogg");
music2=SEngine->addSoundSourceFromFile("sounds/music2.ogg");
music3=SEngine->addSoundSourceFromFile("sounds/music3.ogg");
music4=SEngine->addSoundSourceFromFile("sounds/music4.ogg");


}
void PlayClickSound()
{
SEngine->play2D(clicksnd);
}
void PlayClick2Sound()
{
SEngine->play2D(clicksnd2);
}
void PlayClick3Sound()
{
SEngine->play2D(clicksnd3);
}
void PlayStartGameSound()
{
SEngine->play2D(ClickStartG);
}

void PlayMusic1Sound()
{
SEngine->play2D(music1,true);
}
void PlayMusic2Sound()
{
SEngine->play2D(music2,true);
}
void PlayMusic3Sound()
{
music3->setDefaultVolume(0.5f);
SEngine->play2D(music3,true);
}
void PlayMusic4Sound()
{
SEngine->play2D(music4,true);
}
};

#endif
