#include "game_state.hpp"

GameState::GameState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states): State(window, states) {
    init();
    initWorld();
}

GameState::~GameState() {

}

void GameState::init() {
    sf::Texture t1, t2, t3, t4;
    t1.loadFromFile("textures/background.png");
    t2.loadFromFile("textures/bird_red.png");
    t3.loadFromFile("textures/bird_blue.png");
    t4.loadFromFile("textures/bird_green.png");
    textures = {t1, t2, t3, t4};
}

void GameState::initWorld() {
    this->gravity = b2Vec2(0.0f, 9.81f);
    this->world = std::make_shared<b2World>(this->gravity);

    background = sf::Sprite(textures[0]);
    bird = Bird(this->world, 0.2f, 5.f, 1.f, b2Vec2(-10,0), "ball", textures[1]);
    bird2 = Bird(this->world, 0.2f, 20.f, 0.5f, b2Vec2(3, 5), "ball2", textures[2]);
    bird3 = Bird(this->world, 0.2f, 10.f, 0.5f, b2Vec2(0, 0), "ball3", textures[3]);

    // Podłoże
    setWall(580, 590, 2000, 10);
    // Prawa ściana
    setWall(1193, 0, 10, 600);
    // Lewa ściana
    setWall(-10, 0, 10, 600);
}

void GameState::update(const float &dt) {
    world->Step(1/120., 8, 3);
    bird.update();
    bird2.update();
    bird3.update();
}

void GameState::render(std::shared_ptr<sf::RenderTarget> target) {
    target->draw(background);
    target->draw(bird);
    target->draw(bird2);
    target->draw(bird3);
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
