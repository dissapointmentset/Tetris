#pragma once
class gameplay {
public:
	virtual void appear() = 0;
	virtual bool check() = 0;
	virtual void downpress() = 0;
	virtual void rightpress() = 0;
	virtual void leftpress() = 0;
	virtual void rotate() = 0;
	virtual void setdelay(float k) = 0;
	virtual void move() = 0;
	virtual void delet() = 0;
	virtual void draw() = 0;
	virtual void udied() = 0;
};
