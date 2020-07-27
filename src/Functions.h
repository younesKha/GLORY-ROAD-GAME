/*
writen by (Younes khafaja) - 2008-2009
You are free to use this code as you see fit
email : lighting-team@hotmail.com
*/
#ifndef FUNCTINS_H
#define FUNCTINS_H
#include <stdlib.h>
#include <time.h>
class Functins
{
private:

public:
Functins()
{
srand( time(0));
}
int RandomRange(int a,int b)
{
return a + rand() % (b - a + 1);
}
};

//array struct contain dead solder weobin 
struct DeadSoldrWeop
{
	
	int weopType;
	core::rect<float>WeopPlace;
	int ShootCount;

}; 
core::array<DeadSoldrWeop> DSWArry;

struct HEALTH
{
	core::rect<float>HealthPlace;
	int healtCount;
	int snId;
}; 
core::array<HEALTH> HealthArry;

core::rect<float>Winlocation;
#endif

