#include <SFML/Graphics.hpp>
#include <time.h>
#include <cmath>
#include <iostream>
#include "Figures.h"
#include "game.cpp"
#include <vector>
//#include "game.cpp"

using namespace sf;

const int M = 25;// высота игрового поля
const int N = 10;// ширина игрового поля
int score = 0;
int flag = 0;

// игровое поле
int w = 34;

Point a[5];
Point b[5];

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



bool startgame(){
    Font font;
    font.loadFromFile("Cyber Trunk.ttf");
    int field[M][N] = { 0 };
    srand(time(0));

    RenderWindow window(VideoMode(N * w * 1.7, M * w), "Tetris!");

    // Создание и загрузка текстуры
    Texture t;
    t.loadFromFile("C:/Users/panin/Downloads/color.png");
    // Создание спрайта
    Sprite tiles(t);

    // Переменные для горизонтального перемещения и вращения
    int dx = 0;// Переменная для горизонтального перемещения тетрамино
    int colorNum = 1;
    bool rotate = false;// переменная для вращения тетрамино
    // Переменные для таймера и задержки
    float timer = 0, delay = 0.3;
    // Часы (таймер)
    Clock clock;
    bool ad = true;
    // Главный цикл приложения: выполняется, пока открыто окно
    int n = rand() % 10;
    game tetris(M, N, *field, w);
    while (window.isOpen()) {

        if (tetris.udied()) { window.close(); }

        // Получаем время, прошедшее с начала отсчета, и конвертируем его в секунды
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        // Обрабатываем события в цикле
        Event event;
        while (window.pollEvent(event))
        {
            // Пользователь нажал на «крестик» и хочет закрыть окно?
            if (event.type == Event::Closed)
                // тогда закрываем его
                window.close();

            // Была ли нажата клавиша на клавиатуре?
            if (event.type == Event::KeyPressed)
                // Эта кнопка – стрелка вверх?
                if (event.key.code == Keyboard::Up)
                    rotate = true;
            // Или стрелка вправо?
                else if (event.key.code == Keyboard::Right)
                    dx = 1;
            // Или может стрелка влево?
                else if (event.key.code == Keyboard::Left)
                    dx = -1;
        }

        if (Keyboard::isKeyPressed(Keyboard::Down))
            delay = 0.05;

        tetris.rightpress(figures[n], dx, a, b);

        // Если вышли за пределы поля после перемещения, то возвращаем старые координаты 
        if (!tetris.check(figures[n], a)) {
            for (int i = 0; i < figures[n].getkol(); i++)
                a[i] = b[i];
        }

        // Вращение
        if (rotate) {
            tetris.rotate(figures[n], a, b);
        }

        // Движение тетрамино вниз («тик» таймера)
        if (timer > delay) {
            // Горизонтальное перемещение
            colorNum = tetris.fall(figures[n], a, b, &n);

            timer = 0;
        }

        // Первое появление тетрамино на поле?
        if (ad) {
            tetris.appear(figures[n], a);
            ad = false;
        }

        tetris.delet();

        dx = 0; // горизонтальное перемещение
        rotate = false;// вращение
        delay = 0.3;// цвет

        // Отрисовка окна
        window.clear(Color::Black);

        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++) {
                if (field[i][j] == 0)
                    continue;
                tiles.setTextureRect(IntRect(field[i][j] * w, 0, w, w));
                tiles.setPosition(j * w, i * w);
                window.draw(tiles);
            }

        for (int i = 0; i < figures[n].getkol(); i++) {
            tiles.setTextureRect(IntRect(colorNum * w, 0, w, w));
            // Устанавливаем позицию каждого кусочка тетрамино
            tiles.setPosition(a[i].x * w, a[i].y * w);
            // Отрисовка спрайта
            window.draw(tiles);
        }
        Vertex line[] =
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
        scoreshow.setString(std::to_string(tetris.getscore()));
        scoreshow.setCharacterSize(40);
        text.setFillColor(Color::White);
        scoreshow.move(350, 80);
        window.draw(scoreshow);
        RectangleShape rect;
        rect.setSize(Vector2f(N * w - 1, w));
        rect.setFillColor(Color::Red);
        // Отрисовка окна
        window.display();
    }
    RenderWindow losescreen(VideoMode(N* w * 1.7, M* w), "");
    Text text;
    text.setFont(font);
    text.setString("Your score: ");
    text.setCharacterSize(60);
    text.setFillColor(Color::White);
    text.move(N* w * 0.5, M* w * 0.2);
    Text scoreshow;
    scoreshow.setFont(font);
    scoreshow.setString(std::to_string(tetris.getscore()));
    scoreshow.setCharacterSize(60);
    text.setFillColor(Color::White);
    scoreshow.move(N* w * 0.5, M* w * 0.4);

    while (losescreen.isOpen()) {
        Vector2i mouse = Mouse::getPosition(losescreen);
        RectangleShape button;
        button.setSize(Vector2f(N * 0.5 * (w - 1), w));
        button.setFillColor(Color::Red);
        button.setPosition(N * w / 2, M * w / 2);
        losescreen.clear(Color::Black);
        losescreen.draw(button);
        losescreen.draw(scoreshow);
        losescreen.draw(text);
        Event event;
        while (losescreen.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                losescreen.close(); return 0;
            }
            if (event.type == Event::MouseButtonPressed)
                if (event.key.code == Mouse::Left)
                    if (button.getGlobalBounds().contains(mouse.x, mouse.y)) {
                        losescreen.close(); return 1;
                    }
            losescreen.draw(scoreshow);
        }losescreen.display();

    }
}
void gameruning(){
    if (startgame()) { gameruning(); }
}
int main()
{

    Font font;
    font.loadFromFile("Cyber Trunk.ttf");
    RenderWindow menu(VideoMode(N * w * 1.7, M * w), "Menu");
    while (menu.isOpen()) {
        Vector2i mouse = Mouse::getPosition(menu);
        RectangleShape button;
        button.setSize(Vector2f(N * 0.5 * (w), w));
        button.setFillColor(Color::Red);
        button.setPosition(N * w / 2, M * w / 2);
        /*Text tb;
        tb.setFont(font);
        tb.setFillColor(Color::Black);
        tb.setOrigin(tb.getGlobalBounds().getSize() / 2.f + tb.getLocalBounds().getPosition());
        tb.setPosition(button.getPosition() + (button.getSize() / 2.f));*/
        menu.clear(Color::Black);
        menu.draw(button);
       // menu.draw(tb);
        Event event;
        while (menu.pollEvent(event))
        {
            // Ïîëüçîâàòåëü íàæàë íà «êðåñòèê» è õî÷åò çàêðûòü îêíî?
            if (event.type == Event::Closed) {
                // òîãäà çàêðûâàåì åãî
                menu.close(); return 0;
            }
            if (event.type == Event::MouseButtonPressed)
                if (event.key.code == Mouse::Left)
                    if (button.getGlobalBounds().contains(mouse.x, mouse.y)) {
                        menu.close();
                    }

        }menu.display();

    }
    gameruning();
    return 0;
}
