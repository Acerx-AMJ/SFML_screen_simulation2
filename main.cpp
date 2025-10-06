#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "chars.hpp"

constexpr int pscale = 7;
constexpr int cwidth = 5;
constexpr int cheight = 7;

constexpr int border = 1;
constexpr int width = cwidth * pscale * 25;
constexpr int height = cheight * pscale * 2;

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

void draw_char(int x, int y, char ch, std::vector<std::vector<Pixel>>& pixels) {
   auto it = characters.find(ch);
   if (it == characters.end()) {
      return;
   }

   for (int yy = y; yy < y + cheight && yy < pixels.size(); ++yy) {
      for (int xx = x; xx < x + cwidth && xx < pixels[0].size(); ++xx) {
         pixels[yy][xx].set(it->second[yy - y][xx - x]);
      }
   }
}

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
         row.push_back(pixel);
      }
      pixels.push_back(row);
   }

   draw_char(1, 1, '1', pixels);
   draw_char(7, 1, '2', pixels);
   draw_char(13, 1, '3', pixels);
   draw_char(19, 1, '4', pixels);
   draw_char(25, 1, '5', pixels);
   draw_char(31, 1, '6', pixels);
   draw_char(37, 1, '7', pixels);
   draw_char(43, 1, '8', pixels);
   draw_char(49, 1, '9', pixels);
   draw_char(55, 1, '0', pixels);

   while (window.isOpen()) {
      window.pollEvent(event);
      if (event.type == sf::Event::EventType::Closed) {
         window.close();
      }

      window.clear();
      for (const auto& row : pixels) {
         for (const auto& pixel : row) {
            if (pixel.on) {
               window.draw(pixel.pixel);
            }
         }
      }
      window.display();
   }
   return 0;
}
