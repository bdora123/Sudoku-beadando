#ifndef APPLICATION_HPP_INCLUDED
#define APPLICATION_HPP_INCLUDED

#include "Window.hpp"
#include "../SudokuWindow.hpp"

namespace W{//w nevterben vagyunk, hogy ne kelljen includalni a widgeteket

class Application
{
    const int X,Y;

    SudokuWindow Ablak;

public:
    Application(int _X, int _Y):X(_X),Y(_Y){gout.open(X,Y);}
    void run();
};

}
#endif // APPLICATION_HPP_INCLUDED
