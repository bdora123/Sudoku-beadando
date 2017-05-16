#include "W/Application.hpp"

using namespace std;
using namespace W; //a nevter, hogy ne kelljen includalni minden fejlecet

int main()
{
    Application MyApplication(800,600);
    MyApplication.run();
    return 0;
}
