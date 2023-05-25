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
    typedef enum{LEFT, MIDDLE, RIGHT, NONE} BUTTON_STATE;

    sf::Vector2f getOrigin(float width, float height, ORIGIN origin);

    class Text;
    class Button;
    class TextureButton;
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
    Text(std::string text_str, sf::Font &font, unsigned int size, sf::Color color, sf::Vector2f position,
         ORIGIN origin = NW);

    void setFontSize(unsigned int size);
    void setPosition(sf::Vector2f position);
    void setTextColor(sf::Color color);
    void setFont(sf::Font &font);
    void setString(std::string text);
    void setOrigin(ORIGIN origin);
    float getWidth() const;
    float getHeight() const;
    sf::Vector2f getPosition() const;
    void updatePosition(std::pair<double, double> change_ratio, const std::shared_ptr<sf::RenderWindow>& window);
};

class ui::Button: public sf::Drawable{
private:
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
    Button(std::string text_str, sf::Font &font, unsigned int size, std::pair<sf::Color, sf::Color> background_color, std::pair<sf::Color, sf::Color> text_color, sf::Vector2f position, sf::Vector2f dimensions, ORIGIN origin);
    const sf::Vector2f &getPosition() const;
    const sf::Vector2f &getRelativePosition() const;
    const sf::Vector2f &getDimensions() const;
    const std::pair<sf::Color, sf::Color> &getBackgroundColor() const;
    const std::pair<sf::Color, sf::Color> &getTextColor() const;
    const std::string &getTextStr() const;
    const sf::Font &getFont() const;
    unsigned int getFontSize() const;
    void setText(const std::string &textStr);
    void setPosition(const sf::Vector2f& position);
    void updatePosition(std::pair<double, double> change_ratio, const std::shared_ptr<sf::RenderWindow>& window);
    void update(sf::Vector2f mouse_position);
    bool handleInput(sf::Vector2f mouse_position, const sf::Event& e);
};

class ui::TextureButton: public sf::Drawable{private:
    sf::Vector2f origin_coords;
    ORIGIN btn_origin=NW;

    sf::Vector2f position;
    sf::Vector2f relative_position;
    sf::Vector2f dimensions;

    sf::Texture texture;
    sf::Sprite background_sprite;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
public:
    TextureButton()=default;
    TextureButton(sf::Texture& button_texture, sf::Vector2f position, ORIGIN origin);
    const sf::Vector2f &getPosition() const;
    const sf::Vector2f &getRelativePosition() const;
    sf::Vector2u getDimensions() const;
    void setPosition(const sf::Vector2f btn_position);
    void updatePosition(std::pair<double, double> change_ratio, const std::shared_ptr<sf::RenderWindow>& window);
    void updateTexture(sf::Texture& button_texture);
    void update(sf::Vector2f mouse_position);
    BUTTON_STATE handleInput(sf::Vector2f mouse_position, const sf::Event& e);
};
#endif