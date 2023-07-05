#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <fstream>
#include <iostream>
#include <math.h>
#include <string>
using namespace sf;
using namespace std;
int main() {
    srand(time(NULL));
    int pers = 0;
    Vector2f positionScreen(0, 0);
    int windowSizeX = 640;
    int windowSizeY = 480;
    int r1Player, r2Player, radius = 128;
    float dx, dy, zx, zy;
    View view(FloatRect(0, 0, windowSizeX, windowSizeY));
    RenderWindow window(VideoMode(windowSizeX, windowSizeY), "palvers works!");
    bool flag1 = 0, flag2 = 0, flag3 = 0, key = 0;
    float enemy_speed_x, enemy_speed_y;
    Sprite s, npc, decor;
    Texture t, tnpc, tileset;
    float CurrentFrame = 0, npcCurrentFrame = 0;
    Clock clock;
    float x = 0, y = 0, npcx = 0, npcy = 0;
    float speed = 75, npcspeed = 30;
    float timer = 0;
    int H = 0;
    int W = 0;
    float k = 0;
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
    tnpc.loadFromFile("LabNPCs.png");
    tileset.loadFromFile("tileset.png");
    s.setTexture(t);
    npc.setTexture(tnpc);
    decor.setTexture(tileset);
    s.setTextureRect(IntRect(0, 0, 24, 32));
    npc.setTextureRect(IntRect(204, 16, 24, 32));
    decor.setTextureRect(IntRect(32, 32, 32, 32));
    npc.setPosition(450, 64);
    while (window.isOpen()) {
        float elapsed = clock.restart().asSeconds();
        x = s.getPosition().x;
        y = s.getPosition().y;
        npcx = npc.getPosition().x;
        npcy = npc.getPosition().y;
        FloatRect UserBox = s.getGlobalBounds();
        FloatRect NpcBox = npc.getGlobalBounds();
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        CurrentFrame += 6 * elapsed;
        npcCurrentFrame += 3 * elapsed;
        if (CurrentFrame >= 3) CurrentFrame -= 3;
        if (npcCurrentFrame >= 3) npcCurrentFrame -= 3;
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
        // if (npc.getPosition().x == 450) {
        //     if (npc.getPosition().y == 64) {
        //         enemy_speed_x = 0;
        //         enemy_speed_y = 0;
        //     }
        // }
        // if (npc.getPosition().x == 450) {
        //     if (npc.getPosition().y == 300) {
        //         enemy_speed_x = -0;
        //         enemy_speed_y = 0;
        //     }
        // }
        // if (npc.getPosition().x == 300) {
        //     if (npc.getPosition().y == 300) {
        //         enemy_speed_x = 0;
        //         enemy_speed_y = -0;
        //     }
        // }
        // if (npc.getPosition().x == 300) {
        //     if (npc.getPosition().y == 64) {
        //         enemy_speed_x = 0;
        //         enemy_speed_y = 0;
        //     }
        // }
        // npc.move(enemy_speed_x, enemy_speed_y);
        dx = s.getPosition().x - npc.getPosition().x;
        dy = s.getPosition().y - npc.getPosition().y;
        float d = sqrt(pow(dx, 2) + pow(dy, 2));
        if (d <= radius) {
            if (d <= npcspeed * elapsed) {
                npc.setPosition(s.getPosition().x, s.getPosition().y);
            } else {
                dx = dx / d;
                dy = dy / d;
                npc.move(dx * npcspeed * elapsed, dy * npcspeed * elapsed);
            }
            if (abs(dx) > abs(dy) && dx  >=0) npc.setTextureRect(IntRect(204 + 32 * int(npcCurrentFrame), 64, 24, 32));
            if (abs(dy) > abs(dx) && dy  >= 0) npc.setTextureRect(IntRect(204 + 32 * int(npcCurrentFrame), 16, 24, 32));
            if (abs(dy) > abs(dx) && dy < 0) npc.setTextureRect(IntRect(204 + 32 * int(npcCurrentFrame), 160, 24, 32));
            if (abs(dx) >= abs(dy) && dx  < 0) npc.setTextureRect(IntRect(204 + 32 * int(npcCurrentFrame), 112, 24, 32));
        }
        if (TileMap[int((s.getPosition().y + 16) / 32)][int((s.getPosition().x) / 32) * 2] == '#' ||
            TileMap[int((s.getPosition().y + 16) / 32)][(int((s.getPosition().x - 8) / 32) + 1) * 2] == '#' ||
            TileMap[int((s.getPosition().y) / 32) + 1][int((s.getPosition().x) / 32) * 2] == '#' ||
            TileMap[int((s.getPosition().y) / 32) + 1][(int((s.getPosition().x - 8) / 32) + 1) * 2] == '#') {
            s.setPosition(x, y);
        }
        if (TileMap[int((s.getPosition().y + 16) / 32)][int((s.getPosition().x) / 32) * 2] == '~' ||
            TileMap[int((s.getPosition().y + 16) / 32)][(int((s.getPosition().x - 8) / 32) + 1) * 2] == '~' ||
            TileMap[int((s.getPosition().y) / 32) + 1][int((s.getPosition().x) / 32) * 2] == '~' ||
            TileMap[int((s.getPosition().y) / 32) + 1][(int((s.getPosition().x - 8) / 32) + 1) * 2] == '~') {
            s.setPosition(x, y);
        }
        if (TileMap[int((s.getPosition().y + 16) / 32)][int((s.getPosition().x) / 32) * 2] == 'D' ||
            TileMap[int((s.getPosition().y + 16) / 32)][(int((s.getPosition().x - 8) / 32) + 1) * 2] == 'D' ||
            TileMap[int((s.getPosition().y) / 32) + 1][int((s.getPosition().x) / 32) * 2] == 'D' ||
            TileMap[int((s.getPosition().y) / 32) + 1][(int((s.getPosition().x - 8) / 32) + 1) * 2] == 'D') {
            if (!key) s.setPosition(x, y);
        }
        if (TileMap[int((s.getPosition().y) / 32)][int((s.getPosition().x) / 32) * 2] == 'K') {
            TileMap[int((s.getPosition().y) / 32)][int((s.getPosition().x) / 32) * 2] = ' ';
            key = true;
        }
        if (TileMap[int((npc.getPosition().y + 16) / 32)][int((npc.getPosition().x) / 32) * 2] == '#' ||
            TileMap[int((npc.getPosition().y + 16) / 32)][(int((npc.getPosition().x - 8) / 32) + 1) * 2] == '#' ||
            TileMap[int((npc.getPosition().y) / 32) + 1][int((npc.getPosition().x) / 32) * 2] == '#' ||
            TileMap[int((npc.getPosition().y) / 32) + 1][(int((npc.getPosition().x - 8) / 32) + 1) * 2] == '#') {
            npc.setPosition(npcx, npcy);
        }
        if (TileMap[int((npc.getPosition().y + 15) / 32)][int((npc.getPosition().x) / 32) * 2] == '#' ||
            TileMap[int((npc.getPosition().y) / 32) + 1][int((npc.getPosition().x) / 32) * 2] == '#' ) {
            cout << "hdfhgdf\n";
            if(rand()%2 == 0){
                while(TileMap[int((npc.getPosition().y + 15) / 32)][int((npc.getPosition().x) / 32) * 2] == '#' ||
            TileMap[int((npc.getPosition().y) / 32) + 1][int((npc.getPosition().x) / 32) * 2] == '#' ){
                npc.move(npcspeed*elapsed, 0);
                }
            }else{
                while(TileMap[int((npc.getPosition().y + 15) / 32)][int((npc.getPosition().x) / 32) * 2] == '#' ||
            TileMap[int((npc.getPosition().y) / 32) + 1][int((npc.getPosition().x) / 32) * 2] == '#' ){
                npc.move(-1*npcspeed*elapsed, 0);
                }
            }
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
        window.draw(npc);
        window.display();
    }
    return 0;
}
