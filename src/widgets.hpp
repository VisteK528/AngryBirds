#ifndef WIDGETS_HPP
#define WIDGETS_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <chrono>
#include <memory>
#include <string>

namespace ui{
    typedef enum{N, S, W, E, NW, NE, SW, SE, C} ORIGIN;

    sf::Vector2f getOrigin(float width, float height, ORIGIN origin);

    class Text;
    class Button;
    class Spinbox;
}

class ui::Text: public sf::Drawable {
private:
    unsigned int font_size;
    std::string text_string;
    sf::Color text_color;
    sf::Font font;
    sf::Vector2f position;
    sf::Text text;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    void setFontSize(unsigned int size);

    void setPosition(sf::Vector2f position);

    void setTextColor(sf::Color color);

    void setFont(sf::Font &font);

    void setString(std::string text);

    void setOrigin(ORIGIN origin);

    float getWidth() const;

    /**@brief Function short description
     *
     * */
    float getHeight() const;

    Text(std::string text_str, sf::Font &font, unsigned int size, sf::Color color, sf::Vector2f position,
         ORIGIN origin = NW);

};

class ui::Button: public sf::Drawable{
private:
    //bool active;
    bool clicked;
    sf::Vector2f origin_coords;

    sf::Vector2f position;
    sf::Vector2f relative_position;
    sf::Vector2f dimensions;
    std::pair<sf::Color, sf::Color> background_color;
    std::pair<sf::Color, sf::Color> text_color;
    std::string text_str;

    sf::Font font;
    unsigned int font_size;

    sf::Texture texture;
    std::unique_ptr<ui::Text> text;
    sf::RectangleShape shape;


    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    const sf::Vector2f &getPosition() const;

    const sf::Vector2f &getRelativePosition() const;

    const sf::Vector2f &getDimensions() const;

    const std::pair<sf::Color, sf::Color> &getBackgroundColor() const;

    const std::pair<sf::Color, sf::Color> &getTextColor() const;

    const std::string &getTextStr() const;

    const sf::Font &getFont() const;

    unsigned int getFontSize() const;

    void setText(const std::string &textStr);
    //void setActive(bool active=true);

    Button(std::string text_str, sf::Font &font, unsigned int size, std::pair<sf::Color, sf::Color> background_color, std::pair<sf::Color, sf::Color> text_color, sf::Vector2f position, sf::Vector2f dimensions, ORIGIN origin);
    bool update(sf::Vector2f mouse_position);

};
#endif