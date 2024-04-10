#include "gameplay.h"
#include "Figures.h"
#include <SFML/Graphics.hpp>
#include <time.h>
#include <cmath>
#include <iostream>


class game: public gameplay {

private:
	sf::Clock clock;
	float timer;
	int score;
	float delay;
	int M = 0;
	int N = 0;
	int* field;
	int w = 34;
	bool ad = true;
	int colorNum = 1;
public:	
	game(int m, int n, int* arr, int wx, float d) {
		this->M = m;
		N = n;
		field = arr;
		w = wx;
		delay = d;
	};
	void delayer(float k){
		delay = k;
	};
	void appear(figure m) {
		if (ad) {// ѕервое по€вление тетрамино на поле?
			if (m.a[0].x == 0)
				for (int i = 0; i < m.getkol(); i++) {
					m.a[i].x = m.shape[i] % 3;
					m.a[i].y = m.shape[i] / 3;
				}
			ad = false;
		}
	};
	bool check(figure m) {
		for (int i = 0; i < m.getkol(); i++)
			if (m.a[i].x < 0 || m.a[i].x >= N || m.a[i].y >= M)
				return 0;
			else if (field[m.a[i].y * N + m.a[i].x])
				return 0;
		return 1;
	};
	void downpress() {
		delay = 0.05;
	};
	void rightpress(figure m) {
		for (int i = 0; i < m.getkol(); i++) {
			m.b[i] = m.a[i];
			m.a[i].x += 1;
		}
	};
	void leftpress(figure m) {
		for (int i = 0; i < m.getkol(); i++) {
			m.b[i] = m.a[i];
			m.a[i].x -= 1;
		}
	};
	void exit(figure m) {
		if (!check(m)) {
			for (int i = 0; i < m.getkol(); i++)
				m.a[i] = m.b[i];
		}
	};
	void rotate(figure m) {
		Point p = m.a[1];// указываем центр вращени€
		for (int i = 0; i < m.getkol(); i++) {
			int x = m.a[i].y - p.y;// y - y0
			int y = m.a[i].x - p.x;// x - x0
			m.a[i].x = p.x - x;
			m.a[i].y = p.y + y;
		}exit(m);
	};
	void setdelay(float k) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			delay = k;
	};
	int fall(figure m) {
		if (timer > delay) {
			// √оризонтальное перемещение
			for (int i = 0; i < m.getkol(); i++) {
				m.b[i] = m.a[i];
				m.a[i].y += 1;
			}

			// ≈сли вышли за пределы пол€ после перемещени€, то возвращаем старые координаты
			if (!check(m)) {
				for (int i = 0; i < m.getkol(); i++)
					field[m.b[i].y * N + m.b[i].x] = colorNum;
				colorNum = 1 + rand() % 8;
				// ѕервое по€вление тетрамино на поле?
				for (int i = 0; i < m.getkol(); i++) {
					m.a[i].x = m.shape[i] % 3;
					m.a[i].y = m.shape[i] / 3;
				}
			}
			timer = 0;
		}return colorNum;
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
	void settimer() {
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
	};
};