#pragma once
#include "Point.h"
#include <iostream>
class figure {
public:
	int shape[12];
	Point a[12];
	Point b[12];

	figure(int n, int m[]){
		numcubes = n;
		for (int i = 0; i < n; i++) {
			shape[i] = m[i];
		}
	}
	int getkol(){
		return numcubes;
	}
private:
	int numcubes;
	
};