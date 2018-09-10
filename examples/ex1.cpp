#include <stdio.h>
#include <unistd.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <fstream> //ofstream
//#include <SFML/System.hpp>
//cereal
#include <iostream>
/*
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/types/vector.hpp>
#include "cereal/types/string.hpp" 
*/
#include <string>      // for string
#include <stdexcept>   // for runtime_error
#include <neo.hpp> 
int main(void)
{
  
#if 0
  sf::Texture* tex = new sf::Texture();
  if (!tex->loadFromFile("../assets/terminal32x32.png"))
    throw std::runtime_error("Unable to load texture");
  sf::Font font;
  if (!font.loadFromFile("../assets/mactype.ttf"))
    throw std::runtime_error("Unable to load fot" );
  sf::Text text;
  text.setFont(font); // font is a sf::Font
  text.setString("Hello world");
  text.setCharacterSize(24); // in pixels, not points!
  //text.setFillColor(sf::Color::Green); error no setFillColor
  text.setStyle(sf::Text::Bold | sf::Text::Underlined);
  sf::Vector2<float> t_pos = sf::Vector2<float>(10,10);
  text.setPosition(t_pos);
  //Process tile
  sf::VertexArray vertices;
  vertices.setPrimitiveType(sf::Quads);
  vertices.resize(3 * 3 * 4);
  sf::VertexArray tileMap;
  tileMap.setPrimitiveType(sf::Quads);
  tileMap.resize(4);
  int TILES_SIZE=32;
  int i=1;
  int j=0; 
  float u = (float)i*TILES_SIZE;
  float v = (float)j*TILES_SIZE;
  tileMap[0] = sf::Vertex(sf::Vector2f(0 * TILES_SIZE, 0 * TILES_SIZE), sf::Vector2f(u, v));
  tileMap[1] = sf::Vertex(sf::Vector2f(10 * TILES_SIZE, 0 * TILES_SIZE), sf::Vector2f(u+TILES_SIZE, v));
  tileMap[2] = sf::Vertex(sf::Vector2f(10 * TILES_SIZE, 10 * TILES_SIZE), sf::Vector2f(u+TILES_SIZE, v+TILES_SIZE));
  tileMap[3] = sf::Vertex(sf::Vector2f(0 * TILES_SIZE, 10 * TILES_SIZE), sf::Vector2f(u, v+TILES_SIZE));
  tileMap[0].color = sf::Color::Red;
  tileMap[1].color = sf::Color::Blue;
  tileMap[2].color = sf::Color::Green;
  tileMap[3].color = sf::Color::White;
  float ratio = 1.0;
  tileMap[0].color.a = static_cast<sf::Uint8>(ratio * 255);
  tileMap[1].color.a = static_cast<sf::Uint8>(ratio * 255);
  tileMap[2].color.a = static_cast<sf::Uint8>(ratio * 255);
  tileMap[3].color.a = static_cast<sf::Uint8>(ratio * 255);
  
  sf::RenderWindow window;
  window.create(sf::VideoMode(800, 600), "My window",sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
  //Control the framerate
  window.setVerticalSyncEnabled(true); 
  window.setFramerateLimit(60);
  //Set Pos
  window.setPosition(sf::Vector2i(10, 50));
  //window.setSize(sf::Vector2u(640, 480));
  window.setTitle("SFML window");
  //Get window size
  sf::Vector2u size = window.getSize();
  unsigned int width = size.x;
  unsigned int height = size.y;
  printf("Size %dX%d\n", width, height);
  double angle=0.0;
  double duration_ms = 0.0;
  sf::RenderTexture rtexture;
  if (!rtexture.create(500, 500))
    return -1;
  while (window.isOpen())
  {
    clock_t start_time = clock();
    sf::Event event;
    while (window.pollEvent(event)){
      switch (event.type)
      {
        case sf::Event::Closed:
          window.close();
          break;
        case sf::Event::MouseButtonPressed:
          {
            if (event.mouseButton.button == sf::Mouse::Left)
              printf("Mouse LBTN: (%d,%d)\n",event.mouseButton.x,event.mouseButton.y);
          }
          break;
          case sf::Event::KeyPressed:
          {
            printf("KeyPressed code[%d]\n" , event.key.code);
            if (event.key.code == sf::Keyboard::Escape){
              printf("Control key[%d]\n" , event.key.control);
              printf("ALT key[%d]\n" , event.key.alt);
              printf("Shift key[%d]\n" , event.key.shift);
              printf("System key[%d]\n" , event.key.system);
              window.close();
            }
            if (event.key.code == sf::Keyboard::Left){
              angle--;
              printf("angle=%f", angle);

            }
            if (event.key.code == sf::Keyboard::Right){
              angle++;
               printf("angle=%f", angle);
            }
            if (event.key.code == sf::Keyboard::Up){
            }
            if (event.key.code == sf::Keyboard::Down){
            }
          }
          break;
        case sf::Event::Resized:
          {
            printf("resize: %dX%d\n", event.size.width, event.size.height);
          }
          break;
        default:
          break;
      }
      }
      sf::Vector2i mouse = sf::Mouse::getPosition(window);
      sf::Vector2<float> m = sf::Vector2<float>(mouse.x,mouse.y);
      duration_ms = ((clock() - start_time) * 1000.0) / CLOCKS_PER_SEC;
      //window.clear();
      rtexture.clear(sf::Color::Red);
      rtexture.draw(tileMap,tex);   // shape is a sf::Shape
      rtexture.draw(text);    // text is a sf::Text
      rtexture.display();
      window.clear(sf::Color(128, 128, 128));
      sf::Sprite sprite(rtexture.getTexture());
      window.draw(sprite);
      window.display();

  }
#endif
  return 0;
}
#if 0
#endif
