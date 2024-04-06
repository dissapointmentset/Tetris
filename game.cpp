#include "gameplay.h"
#include "Figures.h"


class game:gameplay {
public:
	figure m[];
	void appear(){}
	bool check(){
	
	}
	void downpress(){}
	void rightpress(){}
	void leftpress(){}
	void rotate(){}
	void setdelay(float k){
		delay = k;
	}
	void move(){}
	void delet(){}
	void draw(){}
private:
	float delay;
};