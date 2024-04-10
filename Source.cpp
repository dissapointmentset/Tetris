#include <SFML/Graphics.hpp>
#include <time.h>
#include <cmath>
#include <iostream>
#include "Figures.h"
#include "game.cpp"
//#include "game.cpp"

using namespace sf;

const int M = 25;// ������ �������� ����
const int N = 10;// ������ �������� ����
int score = 0;
int flag = 0;

int field[M][N] = { 0 };// ������� ����
int w = 34;

//struct Point
//{
//    int x, y;
//}a[4], b[4];

int stickar[] = { 1,4,7,10 };
figure stick((sizeof(stickar) / sizeof(int)),stickar);

int lgar[] = { 0,1,4,7 };
figure lg((sizeof(lgar) / sizeof(int)), lgar);

int rgar[] = { 1,2,4,7 };
figure rg((sizeof(rgar) / sizeof(int)),rgar);

int sqar[] = { 0,1,3,4 };
figure sq((sizeof(sqar) / sizeof(int)), sqar);

int piar[] = { 1,4,7,5 };
figure pi((sizeof(piar) / sizeof(int)),piar);

int sar[] = { 1,4,3,6 };
figure s((sizeof(sar) / sizeof(int)),sar);

int zar[] = { 1,4,5,8 };
figure z((sizeof(zar) / sizeof(int)),zar);

int crossar[] = { 1,4,7,5,3};
figure cross((sizeof(crossar) / sizeof(int)), crossar);

int danonar[] = {0,1,2,3,5};
figure danon((sizeof(danonar) / sizeof(int)),danonar);

int alar[] = {0,1,2,4,7};
figure al((sizeof(alar) / sizeof(int)),alar);

figure figures[10] = {stick, lg, rg, sq, s,z,pi,cross, danon, al};


game tetris(M ,N, *field, w, 0.3);
int main()
{
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < figures[i].getkol(); j++) {
            figures[i].a[j].x = figures[i].shape[j] % 3;
            figures[i].a[j].y = figures[i].shape[j] / 3;
        }
    }
//    srand(time(0));
//
//    RenderWindow menu(VideoMode(N * w * 1.7, M * w), "Menu");
//menuopen:
//    while (menu.isOpen()) {
//        Vector2i mouse = Mouse::getPosition(menu);
//        RectangleShape button;
//        button.setSize(Vector2f(N * 0.5 * (w - 1), w));
//        button.setFillColor(Color::Red);
//        button.setPosition(N * w / 2, M * w / 2);
//        menu.clear(Color::Black);
//        menu.draw(button);
//        Event event;
//        while (menu.pollEvent(event))
//        {
//            // ������������ ����� �� �������� � ����� ������� ����?
//            if (event.type == Event::Closed) {
//                // ����� ��������� ���
//                menu.close(); return 0;
//            }
//            if (event.type == Event::MouseButtonPressed)
//                if (event.key.code == Mouse::Left)
//                    if (button.getGlobalBounds().contains(mouse.x, mouse.y)) {
//                        menu.close();
//                        goto gameplay;
//                    }
//
//        }menu.display();
//
//    }
//
//gameplay:
    RenderWindow window(VideoMode(N * w * 1.7, M * w), "Tetris!");

    // �������� � �������� ��������
    Texture t;
    t.loadFromFile("C:/Users/panin/Downloads/color.png");
    // �������� �������
    Sprite tiles(t);
    tiles.setTextureRect(IntRect(5 * w, 0, w, w));
    bool rotate = false;
    int color = 1;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            // ������������ ����� �� �������� � ����� ������� ����?
            if (event.type == Event::Closed) {
                // ����� ��������� ���
                window.close();
            }
        }
        int n = 2;
        int dx = 0;
        //// ���� �� ������ ������� �� ����������?
        if (event.type == Event::KeyPressed)
            // ��� ������ � ������� �����?
            if (event.key.code == Keyboard::Up)
                tetris.rotate(figures[n]);
        // ��� ������� ������?
            else if (event.key.code == Keyboard::Right) {
                for (int i = 0; i < figures[n].getkol(); i++) {
                    //figures[n].b[i] = figures[n].a[i];
                    figures[n].a[i].x += 1;
                }
            }
                // ��� ����� ������� �����?
            else if (event.key.code == Keyboard::Left) {
                for (int i = 0; i < figures[n].getkol(); i++) {
                    //figures[n].b[i] = figures[n].a[i];
                    figures[n].a[i].x += -1;
                }
            }

        
        
        for (int i = 0; i < figures[n].getkol(); i++) {
            // ������������� ������� ������� ������� ���������
            tiles.setPosition(figures[n].a[i].x * w, figures[n].a[i].y * w);
            // ��������� �������
            window.draw(tiles);
        }

        Vertex line[] =//����� ������� ����� � ����
        {
            Vertex(Vector2f(340, 0)),
            Vertex(Vector2f(340, 3000))
        };
        line->color = Color::White;
        window.draw(line, 2, Lines);
        Font font;
        font.loadFromFile("Cyber Trunk.ttf");
        Text text;
        text.setFont(font);
        text.setString("Score:");
        text.setCharacterSize(60);
        text.setFillColor(Color::White);
        text.move(350, 10);
        window.draw(text);
        Text scoreshow;
        scoreshow.setFont(font);
        scoreshow.setString(std::to_string(score));
        scoreshow.setCharacterSize(40);
        text.setFillColor(Color::White);
        scoreshow.move(350, 80);
        window.draw(scoreshow);
        RectangleShape rect;
        rect.setSize(Vector2f(N * w - 1, w));
        rect.setFillColor(Color::Red);
       // window.draw(rect);
        //��������� ����
        window.display();
    }
}