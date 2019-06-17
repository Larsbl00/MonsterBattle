#include <iostream>

#include "InputReader.h"
#include "InputDelegate.h"


class Test: public InputDelegate
{
    public:

    void onKeyPress(const char* input)
    {
        std::cout << "Pressed: " << input << std::endl;
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
