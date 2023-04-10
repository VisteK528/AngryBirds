#include "src/bird.hpp"
#include <SFML/Graphics.hpp>
#include "box2d/include/box2d/box2d.h"
#include <iostream>
#include <cstdint>

const float SCALE = 30.0f;
const float DEG = 57.29577f;

b2Vec2 Gravity(0.0f, 9.f);
b2World World(Gravity);

void setWall(int x, int y, int w, int h)
{
    b2PolygonShape gr;
    gr.SetAsBox(w/SCALE, h/SCALE);

    b2BodyDef bdef;
    bdef.position.Set(x/SCALE, y/SCALE);

    b2Body *b_ground = World.CreateBody(&bdef);
    b_ground->CreateFixture(&gr, 1);

}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1203, 600), "EITI Volleyball");
    window.setFramerateLimit(120);

    sf::Texture t1, t2, t3, t4;
    t1.loadFromFile("textures/background.png");
    t2.loadFromFile("textures/bird_red.png");
    t3.loadFromFile("textures/bird_blue.png");
    t4.loadFromFile("textures/bird_green.png");

    sf::Sprite sBackground(t1);
    sf::Sprite sBall(t2);
    sf::Sprite sBall2(t3);
    sf::Sprite sBall3(t4);

    sBall.setOrigin(20, 20);
    sBall2.setOrigin(20, 20);
    sBall3.setOrigin(20, 20);

    // Podłoże
    setWall(580, 590, 2000, 10);
    // Prawa ściana
    setWall(1193, 0, 10, 600);
    // Lewa ściana
    setWall(-10, 0, 10, 600);

    Bird bird(&World, 0.2f, 5.f, 1.f, b2Vec2(-10,0), "ball");
    Bird bird2(&World, 0.2f, 20.f, 0.5f, b2Vec2(3, 5), "ball2");
    Bird bird3(&World, 0.2f, 10.f, 0.5f, b2Vec2(0, 0), "ball3");

    while(window.isOpen())
    {
        sf::Event e;
        while(window.pollEvent(e))
        {
            if(e.type == sf::Event::Closed) window.close();
        }
        World.Step(1/120.0f, 8, 3);
        window.draw(sBackground);
        for(b2Body *it = World.GetBodyList(); it != 0; it = it->GetNext())
        {
            b2Vec2 pos = it->GetPosition();
            float angle = it->GetAngle();

            uintptr_t data = it->GetUserData().pointer;
            if(data != 0)
            {
                Data *i = reinterpret_cast<Data *>(data);
                if(i->text == "ball")
                {
                    sBall.setRotation(angle*DEG);
                    sBall.setPosition(pos.x*SCALE+20, pos.y*SCALE+20);
                    window.draw(sBall);

                }
                else if(i->text == "ball2")
                {
                    sBall2.setPosition(pos.x*SCALE+20, pos.y*SCALE+20);
                    sBall2.setRotation(angle*DEG);
                    window.draw(sBall2);

                }
                else if(i->text == "ball3")
                {
                    sBall3.setPosition(pos.x*SCALE+20, pos.y*SCALE+20);
                    sBall3.setRotation(angle*DEG);
                    window.draw(sBall3);

                }
            }
        }
        window.display();
    }

    return 0;
}