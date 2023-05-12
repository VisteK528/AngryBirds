#include "widgets.hpp"

sf::Vector2f ui::getOrigin(float width, float height, ORIGIN origin)
{
    switch (origin) {
        case N:
            return {width/2, 0};
        case S:
            return {width/2, height};
        case W:
            return {0, height/2};
        case E:
            return {width, height/2};
        case NE:
            return {width, 0};
        case SW:
            return {0, height};
        case SE:
            return {width, height};
        case C:
            return {width/2, height/2};
        default:
            return {0, 0};
    }
}

ui::Text::Text(std::string text_str, sf::Font& font, unsigned int font_size, sf::Color color, sf::Vector2f position, ORIGIN origin)
{
    // Assign variables
    setString(std::move(text_str));
    setFontSize(font_size);
    setFont(font);
    setTextColor(color);
    setOrigin(origin);
    setPosition(position);
}

void ui::Text::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(text, states);
}

void ui::Text::setString(std::string text)
{
    this->text_string = text;
    this->text.setString(text);
}

void ui::Text::setPosition(sf::Vector2f position)
{
    this->position = position;
    this->text.setPosition(position);
}

void ui::Text::setFontSize(unsigned int font_size)
{
    this->font_size = font_size;
    this->text.setCharacterSize(font_size);
}

void ui::Text::setFont(sf::Font &font)
{
    this->font = font;
    this->text.setFont(font);
}

void ui::Text::setTextColor(sf::Color color)
{
    this->text_color = color;
    this->text.setFillColor(color);
}

void ui::Text::setOrigin(ORIGIN origin)
{
    this->text.setOrigin(getOrigin(getWidth(), this->text.getCharacterSize(), origin));
}

float ui::Text::getWidth() const
{
    return this->text.getGlobalBounds().width;
}

float ui::Text::getHeight() const
{
    return this->text.getGlobalBounds().height;
}

ui::Button::Button(std::string text_str, sf::Font &font, unsigned int size, std::pair<sf::Color, sf::Color> background_color, std::pair<sf::Color, sf::Color> text_color, sf::Vector2f position, sf::Vector2f dimensions, ORIGIN origin){
    this->text_str = text_str;
    this->font = font;
    this->font_size = size;
    this->background_color = background_color;
    this->text_color = text_color;
    this->dimensions = dimensions;
    this->origin_coords = getOrigin(dimensions.x, dimensions.y, origin);
    this->position = position;
    this->relative_position = sf::Vector2f(position.x-origin_coords.x, position.y-origin_coords.y);
    this->clicked = true;

    shape.setSize(dimensions);
    shape.setFillColor(background_color.first);
    shape.setOrigin(origin_coords);
    shape.setPosition(position);

    this->text = std::make_unique<ui::Text>(text_str, font, font_size, text_color.first,sf::Vector2f(relative_position.x+dimensions.x/2, relative_position.y+dimensions.y/2), ui::ORIGIN::C);
}

bool ui::Button::update(sf::Vector2f mouse_position) {
    if(mouse_position.x >= relative_position.x && mouse_position.x <= relative_position.x+dimensions.x && mouse_position.y >= relative_position.y && mouse_position.y <= relative_position.y+dimensions.y){
        shape.setFillColor(background_color.second);
        text->setTextColor(text_color.second);
    }
    else{
        shape.setFillColor(background_color.first);
        text->setTextColor(text_color.first);
    }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        if(!clicked){
            clicked = true;
            if(mouse_position.x >= relative_position.x && mouse_position.x <= relative_position.x+dimensions.x && mouse_position.y >= relative_position.y && mouse_position.y <= relative_position.y+dimensions.y){
                return true;
            }
        }
    }
    else{
        clicked = false;
    }
    return false;
}

void ui::Button::setText(const std::string &textStr) {
    text_str = textStr;
    this->text->setString(textStr);
}

/*void ui::Button::setActive(bool active) {
    if(!active){
        this->shape.setFillColor(sf::Color(255, 255, 255, 255));
    }
}*/

void ui::Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(shape, states);
    target.draw(*text, states);
}

const sf::Vector2f &ui::Button::getPosition() const {
    return position;
}

const sf::Vector2f &ui::Button::getRelativePosition() const {
    return relative_position;
}

const sf::Vector2f &ui::Button::getDimensions() const {
    return dimensions;
}

const std::pair<sf::Color, sf::Color> &ui::Button::getBackgroundColor() const {
    return background_color;
}

const std::pair<sf::Color, sf::Color> &ui::Button::getTextColor() const {
    return text_color;
}

const std::string &ui::Button::getTextStr() const {
    return text_str;
}

const sf::Font &ui::Button::getFont() const {
    return font;
}

unsigned int ui::Button::getFontSize() const {
    return font_size;
}