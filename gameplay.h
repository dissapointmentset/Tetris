#pragma once
#include "Figures.h"
class gameplay {
public:
	gameplay(){}
	virtual void appear(figure m) = 0;
	virtual bool check(figure m) = 0;
	virtual void downpress() = 0;
	virtual void rightpress(figure m) = 0;
	virtual void leftpress(figure m) = 0;
	virtual void rotate(figure m) = 0;
	virtual void setdelay(float k) = 0;
	virtual void delet() = 0;
	virtual bool udied() = 0;
	virtual void settimer() = 0;
	virtual int fall(figure m) = 0;
	virtual void exit(figure m) = 0;
	virtual void delayer(float k) = 0;
	//virtual void drawt(figure m) = 0;
};
