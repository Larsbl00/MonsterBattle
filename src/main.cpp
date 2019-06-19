#include <iostream>

#include "InputReader.h"
#include "InputDelegate.h"


class Test: public monsterbattle::InputDelegate
{
    public:

    void onKeyPress(char input)
    {
        std::cout << "Pressed: " << input << std::endl;
    }

    void onKeyRelease(char input)
    {
        std::cout << "Let go of: " << input << std::endl;
    }
};

int main(void)
{
    Test t;
    monsterbattle::InputReader reader(t);

    while(1)
    {
        reader.update();
    }
    return 0;
}
