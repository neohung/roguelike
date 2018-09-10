#ifndef __NEO_HPP__
#define __NEO_HPP__

#include <stdio.h>

namespace neo
{
  enum Flags { DEFAULT = 1 };

  template <class T>
  class StaticObject
  {
    private:
      static T & instance;
      static void instantiate( T const & ) {}
      static T & create()
      {
        //Here to static create T
        static T t;
        instantiate(instance);
        return t;
      }
      StaticObject( StaticObject const & /*other*/ ) {}
    public:
      static T & getInstance()
      {
        return create();
      }
  };
  template <class T> T & StaticObject<T>::instance = StaticObject<T>::create();

  class test1{
    public:
      test1(){
        printf("Init test1\n");
      }
    private:
      int id;
  };
}

#endif
