#include "gameplay.h"
#include "Figures.h"
#include <SFML/Graphics.hpp>
#include <time.h>
#include <cmath>
#include <iostream>


class game: public gameplay {

private:
	sf::Texture t;
	sf::Sprite tiles;
	int score;
	int M = 0;
	int N = 0;
	int* field;
	int w = 34;
	int colorNum = 1;
public:	
	game(int m, int n, int* arr, int wx) {
		M = m;
		N = n;
		field = arr;
		w = wx;
		score = 0;
	};

	void settexture() {
		t.loadFromFile("C:/Users/panin/Downloads/color.png");
		// —оздание спрайта
		sf::Sprite tiles(t);
	}

	sf::Sprite gettexture() {
		return tiles;
	}

	int getscore() {
		return score;
	}

	void appear(figure m, Point a[]) {
		if (a[0].x == 0)
			for (int i = 0; i < m.getkol(); i++) {
				a[i].x = m.shape[i] % 3;
				a[i].y = m.shape[i] / 3;
			}
	};
	bool check(figure m, Point a[]) {
		for (int i = 0; i < m.getkol(); i++)
			if (a[i].x < 0 || a[i].x >= N || a[i].y >= M)
				return 0;
			else if (field[a[i].y * N + a[i].x])
				return 0;
		return 1;
	};
	void rightpress(figure m, int n, Point a[], Point b[]) {
		for (int i = 0; i < m.getkol(); i++) {
			b[i] = a[i];
			a[i].x += n;
		}
	};
	void exit(figure m, Point a[], Point b[]) {
		if (!check(m, a)) {
			for (int i = 0; i < m.getkol(); i++)
				a[i] = b[i];
		}
	};
	void rotate(figure m, Point a[], Point b[]) {
		Point p = a[1];// указываем центр вращени€
		for (int i = 0; i < m.getkol(); i++) {
			int x = a[i].y - p.y;// y - y0
			int y = a[i].x - p.x;// x - x0
			a[i].x = p.x - x;
			a[i].y = p.y + y;
		}exit(m, a, b);
	};
	int fall(figure m, Point a[], Point b[], int *n) {
		
			// √оризонтальное перемещение
			for (int i = 0; i < m.getkol(); i++) {
				b[i] = a[i];
				a[i].y += 1;
			}
			// ≈сли вышли за пределы пол€ после перемещени€, то возвращаем старые координаты
			if (!check(m, a)) {
				for (int i = 0; i < m.getkol(); i++)
					field[b[i].y * N + b[i].x] = colorNum;
				colorNum = 1 + rand() % 8;
				*n = rand() % 10;
				for (int i = 0; i < m.getkol(); i++) {
					a[i].x = m.shape[i] % 3;
					a[i].y = m.shape[i] / 3;
				}
			}
			return colorNum;
	};
	void delet() {
		int k = M - 1;
		int scorer = 0;
		for (int i = M - 1; i > 0; i--) {
			int count = 0;
			for (int j = 0; j < N; j++) {
				if (field[i * N + j])
					count++;
				field[k * N + j] = field[i * N + j];

			}
			if (count < N) {
				k--;
			}
			else { scorer++; }

		}score += scorer;
	};
	bool udied() {
		for (int i = 0; i < N; i++) {
			if ((field[i] != 0) || (field[N + i] != 0)) {
				return 1; break;
			}
			else { return 0; }
		}
	};
};