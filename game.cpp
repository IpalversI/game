#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <String>
using namespace sf;
using namespace std;
int main() {
    srand(time(NULL));
    int pers = 0;
    Vector2f positionScreen(0, 0);
    int windowSizeX = 640;
    int windowSizeY = 480;
    View view(FloatRect(0,0, windowSizeX, windowSizeY));
    RenderWindow window(VideoMode(windowSizeX, windowSizeY), "palvers works!");
    bool flag1 = 0, flag2 = 0, flag3 = 0, key = 0;
    Sprite s, decor, m1, m2, m3;
    Texture t, t1, t2, t3, t4;
    float CurrentFrame = 0;
    Clock clock;
    float x = 0, y = 0;
    float speed = 50;
    float timer = 0;
    const int H = 25;
    const int W = 50;
    String TileMap[H] = {"        W                 RR                      ",
                         "        W                 RR                      ",
                         "        D                 RR                      ",
                         "  K     D                RR                       ",
                         "        W                RR                       ",
                         "WWWWWWWWW               RR                        ",
                         "                        RR                        ",
                         "                        RR                        ",
                         "                        RR                        ",
                         "                                                  ",
                         "                       RR                         ",
                         "                       RR                         ",
                         "                       RR                         ",
                         "                       RR                         ",
                         "                       RR                         ",
                         "                       RR                         ",
                         "                       RR                         ",
                         "                      RR                          ",
                         "                      RR                          ",
                         "                      RR                          ",
                         "                      RR                          ",
                         "                      RR                          ",
                         "                      RR                          ",
                         "                     RR                           ",
                         "                     RR                           "};
    t.loadFromFile("Sprites.png");
    t2.loadFromFile("mushroom.png");
    t3.loadFromFile("TileSet.png");
    t4.loadFromFile("water.png");
    s.setTexture(t);
    m1.setTexture(t2);
    m2.setTexture(t2);
    m3.setTexture(t2);
    decor.setTexture(t3);
    s.setTextureRect(IntRect(0,0, 24, 32));
    m1.setTextureRect(IntRect(0, 0, 16, 16));
    m2.setTextureRect(IntRect(16, 0, 16, 16));
    m3.setTextureRect(IntRect(32, 0, 16, 16));
    decor.setTextureRect(IntRect(32, 32, 32, 32));
    m1.setPosition(50, 50);
    m2.setPosition(rand() % 1536 + 32, rand() % 736 + 32);
    m3.setPosition(rand() % 1536 + 32, rand() % 736 + 32);
    while (TileMap[int(m1.getPosition().y / 32)][int(s.getPosition().x / 32)] != ' ') {
        m1.setPosition(rand() % 1536 + 32, rand() % 736 + 32);
    }
    while (TileMap[int(m2.getPosition().y / 32)][int(s.getPosition().x / 32)] != ' ') {
        m2.setPosition(rand() % 1536 + 32, rand() % 736 + 32);
    }
    while (TileMap[int(m3.getPosition().y / 32)][int(s.getPosition().x / 32)] != ' ') {
        m3.setPosition(rand() % 1536 + 32, rand() % 736 + 32);
    }
    while (window.isOpen()) {
        float elapsed = clock.restart().asSeconds();
        x = s.getPosition().x;
        y = s.getPosition().y;
        FloatRect UserBox = s.getGlobalBounds();
        FloatRect OtherBox1 = m1.getGlobalBounds();
        FloatRect OtherBox2 = m2.getGlobalBounds();
        FloatRect OtherBox3 = m3.getGlobalBounds();
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        CurrentFrame += 0.0075;
        if (CurrentFrame > 3) CurrentFrame -= 3;
        if (Keyboard::isKeyPressed(Keyboard::Num1))
        {
            pers = 0;
        }
        if (Keyboard::isKeyPressed(Keyboard::Num2))
        {
            pers = 1;
        }
        if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) {
                s.setTextureRect(IntRect(24 * int(CurrentFrame), pers * 128, 24, 32));
                s.move(0, -speed * elapsed);
        }
        if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) {
                s.setTextureRect(IntRect(24 * int(CurrentFrame), 96 + pers * 128, 24, 32));
                s.move(-speed * elapsed, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)) {
                s.setTextureRect(IntRect(24 * int(CurrentFrame), 64 + pers * 128, 24, 32));
                s.move(0, speed * elapsed);
        }
        if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) {
                s.setTextureRect(IntRect(24 * int(CurrentFrame), 32 + pers * 128, 24, 32));
                s.move(speed * elapsed, 0);
        }
        if (TileMap[int((s.getPosition().y + 16)/32)][int((s.getPosition().x)/32)] == 'W'||
            TileMap[int((s.getPosition().y + 16)/32)][int((s.getPosition().x - 8)/32) + 1] == 'W'||
            TileMap[int((s.getPosition().y)/32) + 1][int((s.getPosition().x)/32)] == 'W'||
            TileMap[int((s.getPosition().y)/32) + 1][int((s.getPosition().x - 8)/32) + 1] == 'W') {
                s.setPosition(x,y);
            }
        if (TileMap[int((s.getPosition().y + 16)/32)][int((s.getPosition().x)/32)] == 'R'||
            TileMap[int((s.getPosition().y + 16)/32)][int((s.getPosition().x - 8)/32) + 1] == 'R'||
            TileMap[int((s.getPosition().y)/32) + 1][int((s.getPosition().x)/32)] == 'R'||
            TileMap[int((s.getPosition().y)/32) + 1][int((s.getPosition().x - 8)/32) + 1] == 'R') {
                s.setPosition(x,y);
            }
        if (TileMap[int((s.getPosition().y + 16)/32)][int((s.getPosition().x)/32)] == 'D'||
            TileMap[int((s.getPosition().y + 16)/32)][int((s.getPosition().x - 8)/32) + 1] == 'D'||
            TileMap[int((s.getPosition().y)/32) + 1][int((s.getPosition().x)/32)] == 'D'||
            TileMap[int((s.getPosition().y)/32) + 1][int((s.getPosition().x - 8)/32) + 1] == 'D') {
                if (!key)s.setPosition(x,y);
            }
        if (TileMap[int((s.getPosition().y)/32)][int((s.getPosition().x)/32)] == 'K') {
                TileMap[int((s.getPosition().y)/32)][int((s.getPosition().x)/32)] = ' ';
                key = true;
            }
        if (UserBox.intersects(OtherBox1) && !flag1) {
            timer = 100;
            speed = 250;
            flag1 = true;
        }
        if (UserBox.intersects(OtherBox2) && !flag2) {
            pers = 1;
            flag2 = true;
        }
        if (UserBox.intersects(OtherBox3) && !flag3) {
            pers = 0;
            speed = 50;
            flag3 = true;
        }
        if (timer <= 0) {
            speed = 50;
            timer = 0;
        } else timer -= elapsed;
        positionScreen.x = s.getPosition().x + 32 - (windowSizeX / 2);
        positionScreen.y = s.getPosition().y + 32 - (windowSizeY / 2);
        if (positionScreen.x < 0) positionScreen.x = 0;
        else if (positionScreen.x > 960) positionScreen.x = 960;
        if (positionScreen.y < 0) positionScreen.y = 0;
        else if (positionScreen.y > 320) positionScreen.y = 320;
        view.reset(FloatRect(positionScreen.x, positionScreen.y, windowSizeX, windowSizeY));
        window.clear(Color::Black);
        window.setView(view);
        for (int y = 0; y < H; y++) {
            for (int x = 0; x < W; x++) {
                decor.setTexture(t3);
                if (TileMap[y][x] == ' ') {
                    decor.setTextureRect(IntRect(32, 32, 32, 32));
                } else if (TileMap[y][x] == 'W') {
                    decor.setTextureRect(IntRect(112, 0, 32, 32));
                } else if (TileMap[y][x] == 'D') {
                    decor.setTextureRect(IntRect(112, 32, 32, 32));
                } else if (TileMap[y][x] == 'K') {
                    decor.setTextureRect(IntRect(112, 64, 32, 32));
                } else if (TileMap[y][x] == 'R') {
                    decor.setTexture(t4);
                    decor.setTextureRect(IntRect(0, 0, 32, 32));
                }
                decor.setPosition(32 * x, 32 * y);
                window.draw(decor);
            }
        }
        if (!flag1) window.draw(m1);
        if (!flag2) window.draw(m2);
        if (!flag3) window.draw(m3);
        window.draw(s);
        window.display();
        timer =- elapsed;
    }
    return 0;
}