#include <SFML/Graphics.hpp>
#include <time.h>
#include <cmath>
#include <iostream>
using namespace sf;

const int M = 25;// высота игрового поля
const int N = 10;// ширина игрового поля
int score = 0;
int flag = 0;

int field[M][N] = { 0 };// игровое поле
int w = 34;

struct Point
{
    int x, y;
}a[4], b[4];

// Массив фигурок-тетрамино
int figures[7][4] = {
    1,3,5,7, // I
    2,4,5,7, // S
    3,5,4,6, // Z
    3,5,4,7, // T
    2,3,5,7, // L
    3,5,7,6, // J
    2,3,4,5, // O
};

// Проверка на выход за границы игрового поля
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
                // Пользователь нажал на «крестик» и хочет закрыть окно?
                if (event.type == Event::Closed) {
                    // тогда закрываем его
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
        float timer = 0, delay = 0.9;
        // Часы (таймер)
        Clock clock;
        bool ad = true;
        // Главный цикл приложения: выполняется, пока открыто окно
        while (window.isOpen())
        {

            for (int i = 0; i < N; i++) {
                if ((field[0][i] != 0) || (field[1][i] != 0)) {
                    window.close(); goto menuopen;
                }
            }

            // Получаем время, прошедшее с начала отсчета, и конвертируем его в секунды
            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;

            // Обрабатываем события в цикле
            Event event;
            while (window.pollEvent(event))
            {
                // Пользователь нажал на «крестик» и хочет закрыть окно?
                if (event.type == Event::Closed) {
                    // тогда закрываем его
                    window.close();
                }

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

            // Горизонтальное перемещение
            for (int i = 0; i < 4; i++) {
                b[i] = a[i];
                a[i].x += dx;
            }

            // Если вышли за пределы поля после перемещения, то возвращаем старые координаты 
            if (!check()) {
                for (int i = 0; i < 4; i++)
                    a[i] = b[i];
            }

            // Вращение
            if (rotate) {
                Point p = a[1];// указываем центр вращения
                for (int i = 0; i < 4; i++) {
                    int x = a[i].y - p.y;// y - y0
                    int y = a[i].x - p.x;// x - x0
                    a[i].x = p.x - x;
                    a[i].y = p.y + y;
                }

                // Если вышли за пределы поля после поворота, то возвращаем старые координаты 
                if (!check()) {
                    for (int i = 0; i < 4; i++)
                        a[i] = b[i];
                }
            }

            // Движение тетрамино вниз («тик» таймера)
            if (timer > delay) {
                // Горизонтальное перемещение
                for (int i = 0; i < 4; i++) {
                    b[i] = a[i];
                    a[i].y += 1;
                }

                // Если вышли за пределы поля после перемещения, то возвращаем старые координаты
                if (!check()) {
                    for (int i = 0; i < 4; i++)
                        field[b[i].y][b[i].x] = colorNum;
                    colorNum = 1 + rand() % 8;
                    int n = rand() % 7;// задаем тип тетрамино
                    // Первое появление тетрамино на поле?
                    for (int i = 0; i < 4; i++) {
                        a[i].x = figures[n][i] % 2;
                        a[i].y = figures[n][i] / 2;
                    }
                }
                timer = 0;
            }

            // Первое появление тетрамино на поле?
            if (ad) {
                int n = rand() % 7;// указываем тип тетрамино
                // Первое появление тетрамино на поле?
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


            dx = 0; // горизонтальное перемещение
            rotate = false;// вращение
            delay = 0.9;// цвет

            // Отрисовка окна
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
                // Устанавливаем позицию каждого кусочка тетрамино
                tiles.setPosition(a[i].x * w, a[i].y * w);
                // Отрисовка спрайта
                window.draw(tiles);
            }
            Vertex line[] =//линия раздела очков и игры
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
            //Отрисовка окна
            window.display();
        }
    
}