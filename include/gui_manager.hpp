#ifndef ANGRYBIRDS_GUI_MANAGER_HPP
#define ANGRYBIRDS_GUI_MANAGER_HPP

#include "widgets.hpp"
#include <SFML/Graphics.hpp>

// TODO Rename GuiManager to GuiFactory and add creating methods for TextureButton
class GuiManager {
private:
    sf::Font font;
    std::pair<sf::Color, sf::Color> background_colors;
    std::pair<sf::Color, sf::Color> text_colors;
public:
    GuiManager(sf::Font& font, std::pair<sf::Color, sf::Color> widget_default_background_color, std::pair<sf::Color,
               sf::Color> widget_default_text_color);
    std::unique_ptr<ui::Text> createText(std::string text, unsigned int font_size, sf::Vector2f position,
                                         sf::Color color, ui::ORIGIN origin=ui::ORIGIN::NW);
    std::unique_ptr<ui::Text> createText(std::string text, unsigned int font_size, sf::Vector2f position,
                                         ui::ORIGIN origin=ui::ORIGIN::NW);
    std::unique_ptr<ui::Button> createButton(std::string text, unsigned int font_size, sf::Vector2f position,
                                           sf::Vector2f dimensions, std::pair<sf::Color,
                                           sf::Color> background_color, std::pair<sf::Color,
                                           sf::Color> text_color, ui::ORIGIN origin=ui::ORIGIN::NW);
    std::unique_ptr<ui::Button> createButton(std::string text, unsigned int font_size, sf::Vector2f position,
                                             sf::Vector2f dimensions, ui::ORIGIN origin=ui::ORIGIN::NW);

    const std::pair<sf::Color, sf::Color> &getBackgroundColors() const;
    const std::pair<sf::Color, sf::Color> &getTextColors() const;
    const sf::Font &getFont() const;
};


#endif //ANGRYBIRDS_GUI_MANAGER_HPP
