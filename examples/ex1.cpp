#include <stdio.h>
#include <unistd.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <time.h>

//#include <boost/archive/text_oarchive.hpp>
//#include <boost/archive/text_iarchive.hpp>
#include <fstream> //ofstream
//#include <SFML/System.hpp>
//cereal
#include <iostream>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/types/vector.hpp>
#include "cereal/types/string.hpp" 
//class Texture
struct MyRecordData
{
  unsigned char x, y;
  float z;
  template <class Archive>
  // This method lets cereal know which data members to serialize
  void serialize( Archive & ar )
  {
    ar( x, y, z );
  }
};
struct SomeData
{
  int id;
  std::shared_ptr<std::unordered_map<unsigned int, MyRecordData>> data;
  template <class Archive>
  void save( Archive & ar ) const //For cereal::BinaryOutputArchive
  {
    ar(data);
  }
  template <class Archive>
  void load( Archive & ar )
  {
    //static int32_t idGen = 0;
    //id = idGen++;
    ar(data);
  }
};
int main(void)
{
  //std::ofstream ofs("out.cereal", std::ios::binary);
  //cereal::BinaryOutputArchive oarchive(ofs);
  //std::ofstream ofs("out.xml", std::ios::binary);
  std::ofstream ofs("out.xml");
  cereal::XMLOutputArchive xo_archive( ofs );
  std::string name = "neo";
  int age = 26;
  bool arr[] = {true, false, false};
  std::vector<int> vec = {1, 2, 3, 4, 5};
  xo_archive( 
           cereal::make_nvp("Name", name),
           cereal::make_nvp("Age", age),
           cereal::make_nvp("Num", vec),
           cereal::make_nvp("Boolean_Data", arr) );
  //ofs.close(); 
  //std::ifstream ifs("out.xml", std::ios::binary);
  std::ifstream ifs("out.xml",std::ifstream::in );
  //ifs.close(); 
  cereal::XMLInputArchive xi_archive( ifs );
  std::string n1;
  int a1;
  bool arr1[3];
  //xi_archive( cereal::make_nvp("Name", n1) );
  //ifs.close(); 
  /*
  std::string n1;
  int a1;
  bool arr1[3];
  xi_archive( cereal::make_nvp("Name", n1) );
  printf("Name=%s\n",n1.c_str());
  */
//SomeData mydata;
  //oarchive(mydata);
  //ofs.close();
  /*
  std::ifstream ifs("out.cereal", std::ios::binary);
  cereal::BinaryInputArchive iarchive(ifs);   
  SomeData m1;
  iarchive(m1);
  ifs.close();
*/
  std::unique_ptr<sf::Texture> tex;
  tex = std::make_unique<sf::Texture>();
  if (!tex->loadFromFile("../assets/terminal32x32.png"))
    throw std::runtime_error("Unable to load texture" );
  sf::Font font;
  if (!font.loadFromFile("../assets/mactype.ttf"))
    throw std::runtime_error("Unable to load fot" );
  sf::Text text;
  text.setFont(font); // font is a sf::Font
  text.setString("Hello world");
  text.setCharacterSize(24); // in pixels, not points!
  text.setFillColor(sf::Color::Green);
  text.setStyle(sf::Text::Bold | sf::Text::Underlined);
  sf::Vector2<float> t_pos = sf::Vector2<float>(10,10);
  text.setPosition(t_pos);
  sf::Texture* ptex = tex.get();
  //sf::RectangleShape shape(sf::Vector2f(120, 50));
  //shape.setSize(sf::Vector2f(100, 100));
  //shape.setFillColor(sf::Color(150, 50, 250));

  sf::VertexArray vertices;
  vertices.setPrimitiveType(sf::Quads);
  vertices.resize(3 * 3 * 4);
  //int idx = 0;
  //vertices[idx].position = sf::Vector2f(static_cast<float>(0), static_cast<float>(0));
  //vertices[idx+1].position = sf::Vector2f(static_cast<float>(10), static_cast<float>(0));
  //vertices[idx+2].position = sf::Vector2f(static_cast<float>(10), static_cast<float>(10));
  //vertices[idx+3].position = sf::Vector2f(static_cast<float>(0), static_cast<float>(10));
  sf::VertexArray tileMap;
  tileMap.setPrimitiveType(sf::Quads);
  tileMap.resize(4);
  //(sf::Quads);
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
  /*
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 2; ++j){
      float u = (float)i*TILES_SIZE;
      float v = (float)j*TILES_SIZE;
      tileMap.append(sf::Vertex(sf::Vector2f(i * TILES_SIZE, j * TILES_SIZE), sf::Vector2f(u, v)));
      tileMap.append(sf::Vertex(sf::Vector2f((i + 1) * TILES_SIZE, j * TILES_SIZE), sf::Vector2f(u + TILES_SIZE, v)));
      tileMap.append(sf::Vertex(sf::Vector2f((i + 1) * TILES_SIZE, (j + 1) * TILES_SIZE), sf::Vector2f(u + TILES_SIZE, v + TILES_SIZE)));
      tileMap.append(sf::Vertex(sf::Vector2f(i * TILES_SIZE, (j + 1) * TILES_SIZE), sf::Vector2f(u, v + TILES_SIZE)));
    }
  */

  //sf::Color bgsfml = color_to_sfml(target.background);
  //bgsfml.a = 0;
  //vertices[bg_idx].color = bgsfml;
  //vertices[vertex_idx].texCoords = sf::Vector2f(static_cast<float>(texture_x), static_cast<float>(texture_y) );
  //vertices[vertex_idx+1].texCoords = sf::Vector2f(static_cast<float>(texture_x + font_width), static_cast<float>(texture_y) );
  //vertices[vertex_idx+2].texCoords = sf::Vector2f(static_cast<float>(texture_x + font_width), static_cast<float>(texture_y + font_height) );
  //vertices[vertex_idx+3].texCoords = sf::Vector2f(static_cast<float>(texture_x), static_cast<float>(texture_y + font_height) );


 sf::ConvexShape shape;


  //sf::CircleShape shape(50);
  //sf::Texture* pt = tex.get();
  //shape.setTexture(pt); // texture is a sf::Texture
  //shape.setTextureRect(sf::IntRect(10, 10, 100, 100));

  //sf::Sprite sprite;
  //sf::Texture* pt = tex.get();
  //sprite.setTexture(*tex);
  //sf::Sprite sp = sprite(tex);

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
  //sf::Clock clock;
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
      //sprite.setPosition(m);
      //sprite.setRotation(angle);
      //sf::Time elapsed = clock.restart();
      //float sec = elapsed.asSeconds();
      //printf("elapsed %f, (%d,%d)\n", sec, mouse.x,mouse.y);
      duration_ms = ((clock() - start_time) * 1000.0) / CLOCKS_PER_SEC;
      //printf("duration_ms=%f, (%d,%d)\n",duration_ms, mouse.x,mouse.y);
      //Clean
      //window.clear();
       rtexture.clear(sf::Color::Red);
   // Draw stuff to the texture
  // rtexture.draw(sprite);  // sprite is a sf::Sprite
    rtexture.draw(tileMap,ptex);   // shape is a sf::Shape
    //rtexture.draw(triangle);
    rtexture.draw(text);    // text is a sf::Text
   // We're done drawing to the texture
   rtexture.display();

      window.clear(sf::Color(128, 128, 128));
       sf::Sprite sprite(rtexture.getTexture());
      //window.draw(particles);
      window.draw(sprite);
       //window.draw(tileMap,ptex);
       //window.draw(vertices,rtexture);
     
      window.display();
    //}
  }
  return 0;
}
