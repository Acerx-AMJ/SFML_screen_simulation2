#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

constexpr int pscale = 7;
constexpr int cwidth = 3 * pscale;
constexpr int cheight = 5 * pscale;
constexpr int padding = 1 * pscale;
constexpr int width = cwidth * 25;
constexpr int height = cheight + padding * 2;

int main() {
   sf::RenderWindow window (sf::VideoMode(width, height), "Screen Simulation", sf::Style::Titlebar | sf::Style::Close);
   window.setFramerateLimit(60);
   sf::Event event;

   while (window.isOpen()) {
      window.pollEvent(event);
      if (event.type == sf::Event::EventType::Closed) {
         window.close();
      }

      window.clear();
      window.display();
   }
   return 0;
}
