#include <stdio.h>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <time.h>

#include <boost/archive/text_oarchive.hpp>
#include <fstream> //ofstream
class test_data
{
private:
   int ia;
   int ib;
   float fc;
/*
   template<class Archive>
   void serialize(Archive & ar, const unsigned int version)
    {
        ar & ia;
        ar & ib;
        ar & fc;
    }
*/
public:
   template<class Archive>
   void serialize(Archive & ar, const unsigned int version)
    {
        ar & ia;
        ar & ib;
        ar & fc;
    }

  test_data(){}
  test_data(int a, int b, float c) :
        ia(a), ib(b), fc(c)
    {}
};
//#include <SFML/System.hpp>
int main(void)
{
  const test_data d(12, 34, 56.789f);
  std::ofstream ofs("your_filename");
  boost::archive::text_oarchive t_archive(ofs);
  t_archive << d;
  sf::RenderWindow window;
  window.create(sf::VideoMode(800, 600), "My window",sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
  //Control the framerate
  window.setVerticalSyncEnabled(true); 
  window.setFramerateLimit(60);
  //Set Pos
  window.setPosition(sf::Vector2i(10, 50));
  window.setSize(sf::Vector2u(640, 480));
  window.setTitle("SFML window");
  //Get window size
  sf::Vector2u size = window.getSize();
  unsigned int width = size.x;
  unsigned int height = size.y;
  printf("Size %dX%d\n", width, height);
  //sf::Clock clock;
  double duration_ms = 0.0;
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
      //sf::Time elapsed = clock.restart();
      //float sec = elapsed.asSeconds();
      //printf("elapsed %f, (%d,%d)\n", sec, mouse.x,mouse.y);
      duration_ms = ((clock() - start_time) * 1000.0) / CLOCKS_PER_SEC;
      printf("duration_ms=%f, (%d,%d)\n",duration_ms, mouse.x,mouse.y);
      //Clean
      window.clear();
      //window.draw(particles);
      window.display();
    //}
  }
  return 0;
}
