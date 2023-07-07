#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <fstream>
#include <iostream>
#include <math.h>
#include <string>

using namespace sf;
using namespace std;

struct Map {
    vector<string> tilemap;
    int h = 0;
    int w = 0;
    Texture texture;
    Map(string file, string textureFile) {
        ifstream mapfile(file);
        string line;
        while (getline(mapfile, line)) {
            line.pop_back();
            tilemap.push_back(line);
            int n = tilemap[h].length();
            if (w != 0 && w != n / 2) {
                cout << "ERROR: Map width mismatch!" << endl;
                exit(1);
            }
            w = n / 2;
            h++;
        }
        texture.loadFromFile(textureFile);
    }
    char at(int x, int y) { return tilemap[y][x * 2]; }
    Sprite spriteAt(int x, int y) {
        Sprite sprite;
        sprite.setTexture(texture);
        int entity;
        int style;
        if (tilemap[y][x * 2] == ' ') {
            entity = 0;
        } else if (tilemap[y][x * 2] == '#') {
            entity = 2;
        } else if (tilemap[y][x * 2] == 'D') {
            entity = 5;
        } else if (tilemap[y][x * 2] == 'K') {
            entity = 6;
        } else if (tilemap[y][x * 2] == '~') {
            entity = 7;
        } else {
            cout << "ERROR: Incorrect map tile!" << tilemap[y][x * 2] << endl;
            exit(1);
        }
        if ('0' <= tilemap[y][x * 2 + 1] && tilemap[y][x * 2 + 1] <= '9') {
            style = tilemap[y][x * 2 + 1] - '0';
        } else if (islower(tilemap[y][x * 2 + 1])) {
            style = tilemap[y][x * 2 + 1] - 'a';
            entity++;
        } else if (isupper(tilemap[y][x * 2 + 1])) {
            style = tilemap[y][x * 2 + 1] - 'A';
            entity += 2;
        } else if (tilemap[y][x * 2 + 1] == ' ') {
            style = 0;
        } else {
            cout << "ERROR: Incorrect map tile style!";
            exit(1);
        }
        sprite.setTextureRect(IntRect(style * 32, entity * 32, 32, 32));
        sprite.setPosition(x * 32, y * 32);
        return sprite;
    }
};

struct Character {
    int style;
    int direction;
    float x;
    float y;
    float speed;
    float currentFrame;
    int width;
    int shift;
    Texture texture;
    Character(string file) {
        style = 0;
        speed = 75;
        width = 24;
        shift = 0;
        texture.loadFromFile(file);
    }
    void update(float elapsed) {
        currentFrame += 6 * elapsed;
        if (currentFrame >= 3) currentFrame -= 3;
    }
    void move(Map map, float elapsed, float dx, float dy) {
        float d = sqrt(pow(dx, 2) + pow(dy, 2));
        if (d != 0) {
            dx /= d;
            dy /= d;
            x += dx * speed * elapsed;
            y += dy * speed * elapsed;
            bool oj = false;
            for (int ty = 0; ty < map.h && oj; ty++) {
                for (int tx = 0; tx < map.w && oj; tx++) {
                    if (FloatRect(tx * 32, ty * 32, 32, 32)
                            .intersects(FloatRect(x, y, width, 32))) {
                        if (map.at(x, y) == '#') {
                            x -= dx * speed * elapsed;
                            oj = true;
                        }
                    }
                }
            }
            if (oj) {
                oj = false;
                for (int ty = 0; ty < map.h && oj; ty++) {
                    for (int tx = 0; tx < map.w && oj; tx++) {
                        if (FloatRect(tx * 32, ty * 32, 32, 32)
                                .intersects(FloatRect(x, y, width, 32))) {
                            if (map.at(x, y) == '#') {
                                x += dx * speed * elapsed;
                                y -= dx * speed * elapsed;
                                oj = true;
                            }
                        }
                    }
                }
            }
            if (oj) {
                oj = false;
                for (int ty = 0; ty < map.h && oj; ty++) {
                    for (int tx = 0; tx < map.w && oj; tx++) {
                        if (FloatRect(tx * 32, ty * 32, 32, 32)
                                .intersects(FloatRect(x, y, width, 32))) {
                            if (map.at(x, y) == '#') {
                                x -= dx * speed * elapsed;
                                oj = true;
                            }
                        }
                    }
                }
            }
            if (abs(dx) >= abs(dy)) {
                if (dx > 0) {
                    direction = 1;
                } else {
                    direction = 3;
                }
            } else if (dy > 0) {
                direction = 2;
            } else {
                direction = 0;
            }
        }
    }
    Sprite sprite() {
        Sprite sprite;
        sprite.setTexture(texture);
        sprite.setTextureRect(
            IntRect(width * int(currentFrame), direction * 32 + style * 128, 24, 32));
        sprite.setPosition(x, y);
        return sprite;
    }
};

int main() {
    const int windowWidth = 640;
    const int windowHeight = 480;

    srand(time(NULL));

    Character player("Sprites.png");
    player.x = 50;
    player.y = 50;

    Character npc("LabNPCs.png");
    npc.x = 100;
    npc.y = 100;
    npc.shift = 204;
    npc.width = 32;
    npc.speed = 30;

    RenderWindow window(VideoMode(windowWidth, windowHeight), "palvers works!");

    Map map("map", "tileset.png");

    Clock clock;
    while (window.isOpen()) {
        float elapsed = clock.restart().asSeconds();
        player.update(elapsed);

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Num1)) {
            player.style = 0;
        }
        if (Keyboard::isKeyPressed(Keyboard::Num2)) {
            player.style = 1;
        }

        float dx = 0;
        float dy = 0;
        if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) {
            dy -= 1;
        }
        if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) {
            dx -= 1;
        }
        if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)) {
            dy += 1;
        }
        if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) {
            dx += 1;
        }
        player.move(map, elapsed, dx, dy);

        dx = player.x - npc.x;
        dy = player.y - npc.y;
        float d = sqrt(pow(dx, 2) + pow(dy, 2));
        if (d <= 128) {
            if (d <= npc.speed * elapsed) {
                npc.x = player.x;
                npc.y = player.y;
            } else {
                npc.move(map, elapsed, dx, dy);
            }
        }

        FloatRect view(player.x + 12 - windowWidth / 2, player.y + 16 - windowHeight / 2,
                       windowWidth, windowHeight);
        if (view.top < 0) view.top = 0;
        if (view.left < 0) view.left = 0;
        if (view.top > map.h * 32 - view.height) view.top = map.h * 32 - view.height;
        if (view.left > map.h * 32 - view.width) view.left = map.h * 32 - view.width;

        window.clear(Color::Black);
        window.setView(View(FloatRect(view.left, view.top, view.width, view.height)));
        for (int y = 0; y < map.h; y++) {
            for (int x = 0; x < map.w; x++) {
                window.draw(map.spriteAt(x, y));
            }
        }
        window.draw(player.sprite());
        window.draw(npc.sprite());
        window.display();
    }
    return 0;
}

// if (map.at(npc.x / 32, (npc.y + 15) / 32) == '#' ||
//     map.at(npc.x / 32, (npc.y + 1) / 32 + 1) == '#') {
//     cout << "ok" << endl;
//     if (dx >= 0) {
//         cout << "10\n\n\n";
//         npc.move(npcspeed * elapsed, 2);
//     }
//     if (dx < 0) {
//         cout << "11n\n\n";
//         npc.move(-npcspeed * elapsed, 2);
//     }
// }
// if (map.at((npc.x + 1) / 32, (npc.y) / 32 + 1) == '#' ||
//     map.at((npc.x - 7) / 32 + 1, (npc.y) / 32 + 1) == '#') {
//     cout << "ok" << endl;
//     if (dy >= 0) {
//         cout << "20\n\n\n";
//         npc.move(0, npcspeed * elapsed);
//     }
//     if (dy < 0) {
//         cout << "21\n\n\n";
//         npc.move(0, -npcspeed * elapsed);
//     }

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