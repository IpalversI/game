#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <fstream>
#include <iostream>
#include <string>
using namespace sf;
using namespace std;
int main() {
    srand(time(NULL));
    int pers = 0;
    Vector2f positionScreen(0, 0);
    int windowSizeX = 640;
    int windowSizeY = 480;
    View view(FloatRect(0, 0, windowSizeX, windowSizeY));
    RenderWindow window(VideoMode(windowSizeX, windowSizeY), "palvers works!");
    bool flag1 = 0, flag2 = 0, flag3 = 0, key = 0;
    Sprite s, decor;
    Texture t, tileset;
    float CurrentFrame = 0;
    Clock clock;
    float x = 0, y = 0;
    float speed = 250;
    float timer = 0;
    int H = 0;
    int W = 0;
    vector<string> TileMap;
    ifstream mapfile("map");
    string line;
    s.setPosition(50, 50);
    while (getline(mapfile, line)) {
        line.pop_back();
        TileMap.push_back(line);
        int n = TileMap[H].length();
        if (W != 0 && W != n / 2) {
            cout << "ERROR: Map width mismatch!" << endl;
            return 1;
        }
        W = n / 2;
        H++;
    }
    int vw = W * 32 - windowSizeX;
    int vh = H * 32 - windowSizeY;
    t.loadFromFile("Sprites.png");
    tileset.loadFromFile("tileset.png");
    s.setTexture(t);
    decor.setTexture(tileset);
    s.setTextureRect(IntRect(0, 0, 24, 32));
    decor.setTextureRect(IntRect(32, 32, 32, 32));
    while (window.isOpen()) {
        float elapsed = clock.restart().asSeconds();
        x = s.getPosition().x;
        y = s.getPosition().y;
        FloatRect UserBox = s.getGlobalBounds();
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        CurrentFrame += 0.0075;
        if (CurrentFrame > 3) CurrentFrame -= 3;
        if (Keyboard::isKeyPressed(Keyboard::Num1)) {
            pers = 0;
        }
        if (Keyboard::isKeyPressed(Keyboard::Num2)) {
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
        if (TileMap[int((s.getPosition().y + 16) / 32)][int((s.getPosition().x) / 32) * 2] == '#' ||
            TileMap[int((s.getPosition().y + 16) / 32)]
                   [(int((s.getPosition().x - 8) / 32) + 1) * 2] == '#' ||
            TileMap[int((s.getPosition().y) / 32) + 1][int((s.getPosition().x) / 32) * 2] == '#' ||
            TileMap[int((s.getPosition().y) / 32) + 1]
                   [(int((s.getPosition().x - 8) / 32) + 1) * 2] == '#') {
            s.setPosition(x, y);
        }
        if (TileMap[int((s.getPosition().y + 16) / 32)][int((s.getPosition().x) / 32) * 2] == '~' ||
            TileMap[int((s.getPosition().y + 16) / 32)]
                   [(int((s.getPosition().x - 8) / 32) + 1) * 2] == '~' ||
            TileMap[int((s.getPosition().y) / 32) + 1][int((s.getPosition().x) / 32) * 2] == '~' ||
            TileMap[int((s.getPosition().y) / 32) + 1]
                   [(int((s.getPosition().x - 8) / 32) + 1) * 2] == '~') {
            s.setPosition(x, y);
        }
        if (TileMap[int((s.getPosition().y + 16) / 32)][int((s.getPosition().x) / 32) * 2] == 'D' ||
            TileMap[int((s.getPosition().y + 16) / 32)]
                   [(int((s.getPosition().x - 8) / 32) + 1) * 2] == 'D' ||
            TileMap[int((s.getPosition().y) / 32) + 1][int((s.getPosition().x) / 32) * 2] == 'D' ||
            TileMap[int((s.getPosition().y) / 32) + 1]
                   [(int((s.getPosition().x - 8) / 32) + 1) * 2] == 'D') {
            if (!key) s.setPosition(x, y);
        }
        if (TileMap[int((s.getPosition().y) / 32)][int((s.getPosition().x) / 32) * 2] == 'K') {
            TileMap[int((s.getPosition().y) / 32)][int((s.getPosition().x) / 32) * 2] = ' ';
            key = true;
        }
        positionScreen.x = s.getPosition().x + 32 - (windowSizeX / 2);
        positionScreen.y = s.getPosition().y + 32 - (windowSizeY / 2);
        if (positionScreen.x < 0) positionScreen.x = 0;
        else if (positionScreen.x > vw) positionScreen.x = vw;
        if (positionScreen.y < 0) positionScreen.y = 0;
        else if (positionScreen.y > vh) positionScreen.y = vh;
        view.reset(FloatRect(positionScreen.x, positionScreen.y, windowSizeX, windowSizeY));
        window.clear(Color::Black);
        window.setView(view);
        for (int y = 0; y < H; y++) {
            for (int x = 0; x < W; x++) {
                int entity;
                int style;
                if (TileMap[y][x * 2] == ' ') {
                    entity = 0;
                } else if (TileMap[y][x * 2] == '#') {
                    entity = 2;
                } else if (TileMap[y][x * 2] == 'D') {
                    entity = 5;
                } else if (TileMap[y][x * 2] == 'K') {
                    entity = 6;
                } else if (TileMap[y][x * 2] == '~') {
                    entity = 7;
                } else {
                    cout << "ERROR: Incorrect map tile!" << TileMap[y][x * 2] << endl;
                    return 1;
                }
                if ('0' <= TileMap[y][x * 2 + 1] && TileMap[y][x * 2 + 1] <= '9') {
                    style = TileMap[y][x * 2 + 1] - '0';
                } else if (islower(TileMap[y][x * 2 + 1])) {
                    style = TileMap[y][x * 2 + 1] - 'a';
                    entity++;
                } else if (isupper(TileMap[y][x * 2 + 1])) {
                    style = TileMap[y][x * 2 + 1] - 'A';
                    entity += 2;
                } else if (TileMap[y][x * 2 + 1] == ' ') {
                    style = 0;
                } else {
                    cout << "ERROR: Incorrect map tile style!";
                    return 1;
                }
                decor.setTextureRect(IntRect(style * 32, entity * 32, 32, 32));
                decor.setPosition(32 * x, 32 * y);
                window.draw(decor);
            }
        }
        window.draw(s);
        window.display();
    }
    return 0;
}