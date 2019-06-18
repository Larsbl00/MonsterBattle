#include <iostream>

#include "InputReader.h"
#include "InputDelegate.h"


class Test: public InputDelegate
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
    InputReader reader(t);

    while(1)
    {
        reader.update();
    }
    return 0;
}
