#include "game_state.hpp"

GameState::GameState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states): State(window, states) {
    init();
    initWorld();
}

GameState::~GameState() {

}

void GameState::init() {
    sf::Texture t1, t2, t3, t4, t5, t6, t7;
    t1.loadFromFile("textures/background.png");
    t2.loadFromFile("textures/birds/bird_red.png");
    t3.loadFromFile("textures/birds/bird_blue.png");
    t4.loadFromFile("textures/birds/bird_yellow.png");
    t5.loadFromFile("textures/boxes/wood/wood_1x1.png");
    t6.loadFromFile("textures/boxes/stone/stone_1x1.png");
    t7.loadFromFile("textures/boxes/glass/glass_1x1.png");

    textures = {t1, t2, t3, t4, t5, t6, t7};

    // Wygładzanie tekstur
    for(auto &t: textures){
        t.setSmooth(true);
    }
}

void GameState::initWorld() {
    this->gravity = b2Vec2(0.0f, 9.81f);
    this->world = std::make_shared<b2World>(this->gravity);
    this->contact_listener = ContactListener();

    this->world->SetContactListener(&contact_listener);

    // INFORMACJE O ŚWIECIE
    // 1 metr = 10 pikseli
    // 1 stopień = 57.29577 radiana
    // Świat ma wymiary 1280x720 pikseli
    // Świat ma wymiary 128x72 metry

    background = sf::Sprite(textures[0]);
    bird = std::make_unique<Bird>(this->world, 0.2f, 5.f, 1.f, b2Vec2(-20,0), textures[1]);
    bird2 = std::make_unique<Bird>(this->world, 0.2f, 20.f, 0.5f, b2Vec2(3, 5), textures[2]);
    bird3 = std::make_unique<Bird>(this->world, 0.2f, 10.f, 0.5f, b2Vec2(0, 0), textures[3]);

    // Ustawienie boxów
    box1 = std::make_unique<Box>(this->world, 0.2f, 3.f, 60.f, textures[4]);
    box2 = std::make_unique<Box>(this->world, 0.2f, 7.f, 60.f, textures[4]);
    box3 = std::make_unique<Box>(this->world, 0.2f, 11.f, 60.f, textures[6]);
    box4 = std::make_unique<Box>(this->world, 0.2f, 7.f, 56.f, textures[6]);
    box5 = std::make_unique<Box>(this->world, 0.2f, 7.f, 52.f, textures[5]);
    box6 = std::make_unique<Box>(this->world, 0.2f, 7.f, 48.f, textures[5]);

    // Podłoże
    setWall(640, 630, 1280, 10);
    // Prawa ściana
    setWall(1280, 360, 10, 640);
    // Lewa ściana
    setWall(0, 360, 10, 640);
}

void GameState::update(const float &dt) {
    world->Step(dt, 8, 3);
    bird->update();
    bird2->update();
    bird3->update();

    // Ustawienie pozycji boxów
    box1->update();
    box2->update();
    box3->update();
    box4->update();
    box5->update();
    box6->update();

}

void GameState::render(std::shared_ptr<sf::RenderTarget> target) {
    target->draw(background);
    target->draw(*bird);
    target->draw(*bird2);
    target->draw(*bird3);

    // Rysowanie boxów
    target->draw(*box1);
    target->draw(*box2);
    target->draw(*box3);
    target->draw(*box4);
    target->draw(*box5);
    target->draw(*box6);
}

void GameState::setWall(int x, int y, int w, int h)
{
    b2PolygonShape gr;
    gr.SetAsBox(w/SCALE, h/SCALE);

    b2BodyDef bdef;
    bdef.position.Set(x/SCALE, y/SCALE);

    b2Body *b_ground = this->world->CreateBody(&bdef);
    b_ground->CreateFixture(&gr, 1);
}
