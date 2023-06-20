#include <SFML/Graphics.hpp>
#include <windows.h>
#include <stdlib.h>
#include <String>
#include <iostream>
using namespace sf;
using namespace std;
int main()
{
    srand(time(NULL));
    RenderWindow window(VideoMode(600, 600), "palvers works!");
    const int H = 17;
    const int W = 50;
    float CurrentFrame = 0;
    float i = 0.1;
    int timer = -1;
    bool flag1 = 0,flag2 = 0,flag3 = 0, pers = 0;
    Sprite s, decor, m1, m2, m3;
    Texture t, t1, t2, t3;
    t.loadFromFile("wizard.png");
    t1.loadFromFile("Slime.png");
    t2.loadFromFile("mushroom.png");
    t3.loadFromFile("Wall.png");
    s.setTexture(t);
    m1.setTexture(t2);
    m2.setTexture(t2);
    m3.setTexture(t2);
    decor.setTexture(t3);
    s.setTextureRect (IntRect(0, 0, 32, 32));
    m1.setTextureRect (IntRect(0, 0, 16, 16));
    m2.setTextureRect (IntRect(16, 0, 16, 16));
    m3.setTextureRect (IntRect(32, 0, 16, 16));
    decor.setTextureRect (IntRect(0, 0, 32, 32));
    m1.setPosition (75, 75);
    m2.setPosition (100, 100);
    m3.setPosition (50, 50);
    m1.setPosition (rand()%550 + 25, rand()%550 + 25);
    m2.setPosition (rand()%550 + 25, rand()%550 + 25);
    m3.setPosition (rand()%550 + 25, rand()%550 + 25);
    String TileMap[H] = {
    "11111111111111111111111111111111111111111111111111",
    "10000000000000000000000000000000000000000000000001",
    "10000000000000000000000000000000000000000000000001",
    "10000000000000000000000000000000000000000000000001",
    "10000000000000000000000000000000000000000000000001",
    "10000000000000000000000000000000000000000000000001",
    "10000000000000000000000000000000000000000000000001",
    "10000000000000000000000000000000000000000000000001",
    "10000000000000000000000000000000000000000000000001",
    "10000000000000000000000000000000000000000000000001",
    "10000000000000000000000000000000000000000000000001",
    "10000000000000000000000000000000000000000000000001",
    "10000000000000000000000000000000000000000000000001",
    "10000000000000000000000000000000000000000000000001",
    "10000000000000000000000000000000000000000000000001",
    "10000000000000000000000000000000000000000000000001",
    "11111111111111111111111111111111111111111111111111"
    };
    while (window.isOpen())
    {
        FloatRect UserBox = s.getGlobalBounds();
        FloatRect OtherBox1 = m1.getGlobalBounds();
        FloatRect OtherBox2 = m2.getGlobalBounds();
        FloatRect OtherBox3 = m3.getGlobalBounds();
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }
        if(Keyboard::isKeyPressed(Keyboard::W))
        {
            if (pers == 1)
            {
                CurrentFrame += 0.005;
			    if (CurrentFrame > 1) CurrentFrame -= 1;
			    s.setTextureRect(IntRect(16 * int(CurrentFrame), 0, 16, 16));
		    	s.move(0, -i);
            }
            else
            {
                CurrentFrame += 0.005;
		    	if (CurrentFrame > 4) CurrentFrame -= 4;
			    s.setTextureRect(IntRect(32 * int(CurrentFrame), 64, 32, 32));
			    s.move(0, -i);
            }
        }
        if(Keyboard::isKeyPressed(Keyboard::A))
        {
            if (pers == 1)
            {
                CurrentFrame += 0.005;
			    if (CurrentFrame > 1) CurrentFrame -= 1;
			    s.setTextureRect(IntRect(16 * int(CurrentFrame), 48, 16, 16));
		    	s.move(-i, 0);
            }
            else
            {
                CurrentFrame += 0.005;
		    	if (CurrentFrame > 4) CurrentFrame -= 4;
			    s.setTextureRect(IntRect(32 * int(CurrentFrame), 32, 32, 32));
			    s.move(-i, 0);
            }
        }
        if(Keyboard::isKeyPressed(Keyboard::S))
        {
            if (pers == 1)
            {
                CurrentFrame += 0.005;
			    if (CurrentFrame > 1) CurrentFrame -= 1;
			    s.setTextureRect(IntRect(16 * int(CurrentFrame), 16, 16, 16));
		    	s.move(0, i);
            }
            else
            {
                CurrentFrame += 0.005;
		    	if (CurrentFrame > 4) CurrentFrame -= 4;
			    s.setTextureRect(IntRect(32 * int(CurrentFrame), 96, 32, 32));
			    s.move(0, i);
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            if (pers == 1)
            {
                CurrentFrame += 0.005;
			    if (CurrentFrame > 1) CurrentFrame -= 1;
			    s.setTextureRect(IntRect(16 * int(CurrentFrame), 32, 16, 16));
		    	s.move(i, 0);
            }
            else
            {
                CurrentFrame += 0.005;
		    	if (CurrentFrame > 4) CurrentFrame -= 4;
			    s.setTextureRect(IntRect(32 * int(CurrentFrame), 0, 32, 32));
			    s.move(i, 0);
            }
		}
        if (pers == 1) s.setTexture(t1);
        else s.setTexture(t);
        if(UserBox.intersects (OtherBox1) && !flag1)
        {
            timer = 3200;
            i = 0.175;
            flag1=true;
        }
        if(UserBox.intersects (OtherBox2) && !flag2)
        {
            pers = 1;
            flag2=true;
        }
        if(UserBox.intersects (OtherBox3) && !flag3)
        {
            pers = 0;
            i = 0.1;
            flag3=true;
        }
        if (timer == 0)
        {
            i = 0.1;
        }
        window.clear(Color::White);
        for (int y = 0; y < H; y++){
            for (int x = 0; x < W; x++){
                    if (TileMap[y][x] == '1') {
                    decor.setTextureRect (IntRect(0, 0, 32, 32));
                    decor.setPosition(32 * x, 32 * y);
                    window.draw(decor);}
            }
        }
        if (!flag1) window.draw(m1);
        if (!flag2) window.draw(m2);
        if (!flag3) window.draw(m3);
        window.draw(s);
        window.display();
        timer--;
    }
    return 0;
}