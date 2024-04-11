#pragma once
#include "Figures.h"
#include "Point.h"
#include <vector>
class gameplay {
public:
	gameplay(){}
	virtual void appear(figure m, Point a[]) = 0;
	virtual bool check(figure m, Point a[]) = 0;
	virtual void rightpress(figure m, int n, Point a[], Point b[]) = 0;
	virtual void rotate(figure m, Point a[], Point b[]) = 0;
	virtual void delet() = 0;
	virtual bool udied() = 0;
	virtual int fall(figure m, Point a[], Point b[], int *n) = 0;
	virtual void exit(figure m, Point a[], Point b[]) = 0;
};
