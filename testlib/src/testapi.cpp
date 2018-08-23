#include <stdio.h>
#include <SFML/Graphics.hpp>

void test()
{
  std::unique_ptr<sf::RenderWindow> main_window;
  sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

  main_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(desktop.width, desktop.height, desktop.bitsPerPixel)
            , "Title", sf::Style::Fullscreen);
  printf("test\n");
}
