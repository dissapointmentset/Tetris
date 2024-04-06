#pragma once

class figure {
public:
	figure();
	int getkol(){
		return numcubes;
	}
	void setfigure(int n, int m[]) {
		numcubes = n;
		for (int i = 0; i < n; i++) {
			shape[i] = m[i];
		}
	}
private:
	int numcubes;
	int shape[];
};