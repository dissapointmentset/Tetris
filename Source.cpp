#include <SFML/Graphics.hpp>
#include <time.h>
#include <cmath>
#include <iostream>
using namespace sf;

const int M = 25;// ������ �������� ����
const int N = 10;// ������ �������� ����
int score = 0;
int flag = 0;

int field[M][N] = { 0 };// ������� ����
int w = 34;

struct Point
{
    int x, y;
}a[4], b[4];

// ������ �������-���������
int figures[7][4] = {
    1,3,5,7, // I
    2,4,5,7, // S
    3,5,4,6, // Z
    3,5,4,7, // T
    2,3,5,7, // L
    3,5,7,6, // J
    2,3,4,5, // O
};

// �������� �� ����� �� ������� �������� ����
bool check() {
    for (int i = 0; i < 4; i++)
        if (a[i].x < 0 || a[i].x >= N || a[i].y >= M)
            return 0;
        else if (field[a[i].y][a[i].x])
            return 0;

    return 1;
}


int main()
{
   
        srand(time(0));
        menuopen:
        RenderWindow menu(VideoMode(N * w * 1.7, M * w), "Menu");
        while (menu.isOpen()) {
            Vector2i mouse = Mouse::getPosition(menu);
            RectangleShape button;
            button.setSize(Vector2f(N * 0.5 * (w - 1), w));
            button.setFillColor(Color::Red);
            button.setPosition(N * w / 2, M * w / 2);
            menu.clear(Color::Black);
            menu.draw(button);
            Event event;
            while (menu.pollEvent(event))
            {
                // ������������ ����� �� �������� � ����� ������� ����?
                if (event.type == Event::Closed) {
                    // ����� ��������� ���
                    menu.close(); return 0;
                }
                if (event.type == Event::MouseButtonPressed)
                    if (event.key.code == Mouse::Left)
                        if (button.getGlobalBounds().contains(mouse.x, mouse.y)) {
                            menu.close();
                            goto gameplay;
                        }

            }menu.display();

        }

        gameplay:
        RenderWindow window(VideoMode(N * w*1.7, M * w), "Tetris!");

        // �������� � �������� ��������
        Texture t;
        t.loadFromFile("C:/Users/panin/Downloads/color.png");
        // �������� �������
        Sprite tiles(t);

        // ���������� ��� ��������������� ����������� � ��������
        int dx = 0;// ���������� ��� ��������������� ����������� ���������
        int colorNum = 1;
        bool rotate = false;// ���������� ��� �������� ���������
        // ���������� ��� ������� � ��������
        float timer = 0, delay = 0.9;
        // ���� (������)
        Clock clock;
        bool ad = true;
        // ������� ���� ����������: �����������, ���� ������� ����
        while (window.isOpen())
        {

            for (int i = 0; i < N; i++) {
                if ((field[0][i] != 0) || (field[1][i] != 0)) {
                    window.close(); goto menuopen;
                }
            }

            // �������� �����, ��������� � ������ �������, � ������������ ��� � �������
            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;

            // ������������ ������� � �����
            Event event;
            while (window.pollEvent(event))
            {
                // ������������ ����� �� �������� � ����� ������� ����?
                if (event.type == Event::Closed) {
                    // ����� ��������� ���
                    window.close();
                }

                // ���� �� ������ ������� �� ����������?
                if (event.type == Event::KeyPressed)
                    // ��� ������ � ������� �����?
                    if (event.key.code == Keyboard::Up)
                        rotate = true;
                // ��� ������� ������?
                    else if (event.key.code == Keyboard::Right)
                        dx = 1;
                // ��� ����� ������� �����?
                    else if (event.key.code == Keyboard::Left)
                        dx = -1;
            }


            if (Keyboard::isKeyPressed(Keyboard::Down))
                delay = 0.05;

            // �������������� �����������
            for (int i = 0; i < 4; i++) {
                b[i] = a[i];
                a[i].x += dx;
            }

            // ���� ����� �� ������� ���� ����� �����������, �� ���������� ������ ���������� 
            if (!check()) {
                for (int i = 0; i < 4; i++)
                    a[i] = b[i];
            }

            // ��������
            if (rotate) {
                Point p = a[1];// ��������� ����� ��������
                for (int i = 0; i < 4; i++) {
                    int x = a[i].y - p.y;// y - y0
                    int y = a[i].x - p.x;// x - x0
                    a[i].x = p.x - x;
                    a[i].y = p.y + y;
                }

                // ���� ����� �� ������� ���� ����� ��������, �� ���������� ������ ���������� 
                if (!check()) {
                    for (int i = 0; i < 4; i++)
                        a[i] = b[i];
                }
            }

            // �������� ��������� ���� (���� �������)
            if (timer > delay) {
                // �������������� �����������
                for (int i = 0; i < 4; i++) {
                    b[i] = a[i];
                    a[i].y += 1;
                }

                // ���� ����� �� ������� ���� ����� �����������, �� ���������� ������ ����������
                if (!check()) {
                    for (int i = 0; i < 4; i++)
                        field[b[i].y][b[i].x] = colorNum;
                    colorNum = 1 + rand() % 8;
                    int n = rand() % 7;// ������ ��� ���������
                    // ������ ��������� ��������� �� ����?
                    for (int i = 0; i < 4; i++) {
                        a[i].x = figures[n][i] % 2;
                        a[i].y = figures[n][i] / 2;
                    }
                }
                timer = 0;
            }

            // ������ ��������� ��������� �� ����?
            if (ad) {
                int n = rand() % 7;// ��������� ��� ���������
                // ������ ��������� ��������� �� ����?
                if (a[0].x == 0)
                    for (int i = 0; i < 4; i++) {
                        a[i].x = figures[n][i] % 2;
                        a[i].y = figures[n][i] / 2;
                    }
                ad = false;
            }
            int k = M - 1;
            int scorer = 0;
            for (int i = M - 1; i > 0; i--) {
                int count = 0;
                for (int j = 0; j < N; j++) {
                    if (field[i][j])
                        count++;
                    field[k][j] = field[i][j];

                }
                if (count < N) {
                    k--;
                }
                else { scorer++; }

            }score += scorer;


            dx = 0; // �������������� �����������
            rotate = false;// ��������
            delay = 0.9;// ����

            // ��������� ����
            window.clear(Color::Black);
            if (field[0][0] == 0)
                for (int i = 0; i < M; i++)
                    for (int j = 0; j < N; j++) {
                        if (field[i][j] == 0)
                            continue;
                        tiles.setTextureRect(IntRect(field[i][j] * w, 0, w, w));
                        tiles.setPosition(j * w, i * w);
                        window.draw(tiles);
                    }

            for (int i = 0; i < 4; i++) {
                tiles.setTextureRect(IntRect(colorNum * w, 0, w, w));
                // ������������� ������� ������� ������� ���������
                tiles.setPosition(a[i].x * w, a[i].y * w);
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
            window.draw(rect);
            //��������� ����
            window.display();
        }
    
}