#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

constexpr int pscale = 7;
constexpr int cwidth = 3 * pscale;
constexpr int cheight = 5 * pscale;

constexpr int padding = 1 * pscale;
constexpr int border = 1;

constexpr int width = cwidth * 25;
constexpr int height = cheight + padding * 2;

struct Pixel {
   sf::RectangleShape pixel;
   bool on = false;

   Pixel() {
      pixel.setSize(sf::Vector2f(pscale - border, pscale - border));
      pixel.setFillColor(sf::Color::Black);
      pixel.setOutlineColor(sf::Color::Black);
      pixel.setOutlineThickness(border);
   }

   void set(bool on) {
      this->on = on;
      pixel.setFillColor(on ? sf::Color(255, 125, 0) : sf::Color::Black);
   }
};

int main() {
   sf::RenderWindow window (sf::VideoMode(width, height), "Screen Simulation", sf::Style::Titlebar | sf::Style::Close);
   window.setFramerateLimit(60);
   sf::Event event;
   std::vector<std::vector<Pixel>> pixels;

   for (int y = 0; y < height; y += pscale) {
      std::vector<Pixel> row;
      for (int x = 0; x < width; x += pscale) {
         Pixel pixel;
         pixel.pixel.setPosition(x, y);
         pixel.set(true);
         row.push_back(pixel);
      }
      pixels.push_back(row);
   }

   while (window.isOpen()) {
      window.pollEvent(event);
      if (event.type == sf::Event::EventType::Closed) {
         window.close();
      }

      window.clear();
      for (const auto& row : pixels) {
         for (const auto& pixel : row) {
            window.draw(pixel.pixel);
         }
      }
      window.display();
   }
   return 0;
}
