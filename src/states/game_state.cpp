#include "game_state.hpp"

GameState::GameState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states): State(window, states) {
    init();
    initWorld();
}

GameState::~GameState() {

}

void GameState::init() {
    sf::Texture t1, t2, t3, t4, t5;
    t1.loadFromFile("textures/background.png");
    t2.loadFromFile("textures/bird_red.png");
    t3.loadFromFile("textures/bird_blue.png");
    t4.loadFromFile("textures/bird_yellow.png");
    t5.loadFromFile("textures/wood_1x1.png");
    textures = {t1, t2, t3, t4, t5};
}

void GameState::initWorld() {
    this->gravity = b2Vec2(0.0f, 9.81f);
    this->world = std::make_shared<b2World>(this->gravity);

    // INFORMACJE O ŚWIECIE
    // 1 metr = 10 pikseli
    // 1 stopień = 57.29577 radiana
    // Świat ma wymiary 1280x720 pikseli
    // Świat ma wymiary 128x72 metry

    background = sf::Sprite(textures[0]);
    bird = Bird(this->world, 0.2f, 60.f, 1.f, b2Vec2(-10,0), "ball", textures[1]);
    bird2 = Bird(this->world, 0.2f, 65.f, 0.5f, b2Vec2(3, 5), "ball2", textures[2]);
    bird3 = Bird(this->world, 0.2f, 70.f, 0.5f, b2Vec2(0, 0), "ball3", textures[3]);

    // Ustawienie boxów
    box1 = Box(this->world, 0.2f, 3.f, 60.f, "box1", textures[4]);
    box2 = Box(this->world, 0.2f, 7.f, 60.f, "box2", textures[4]);
    box3 = Box(this->world, 0.2f, 11.f, 60.f, "box3", textures[4]);
    box4 = Box(this->world, 0.2f, 7.f, 56.f, "box4", textures[4]);
    box5 = Box(this->world, 0.2f, 7.f, 52.f, "box5", textures[4]);
    box6 = Box(this->world, 0.2f, 7.f, 48.f, "box6", textures[4]);

    // Podłoże
    setWall(640, 630, 1280, 10);
    // Prawa ściana
    setWall(1280, 360, 10, 640);
    // Lewa ściana
    setWall(0, 360, 10, 640);
}

void GameState::update(const float &dt) {
    world->Step(dt, 8, 3);

    // Ustawienie pozycji ptaków
    bird.update();
    bird2.update();
    bird3.update();

    // Ustawienie pozycji boxów
    box1.update();
    box2.update();
    box3.update();
    box4.update();
    box5.update();
    box6.update();

}

void GameState::render(std::shared_ptr<sf::RenderTarget> target) {
    target->draw(background);

    // Rysowanie ptaków
    target->draw(bird);
    target->draw(bird2);
    target->draw(bird3);

    // Rysowanie boxów
    target->draw(box1);
    target->draw(box2);
    target->draw(box3);
    target->draw(box4);
    target->draw(box5);
    target->draw(box6);
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
