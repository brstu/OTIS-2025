#include <iostream>
#include <vector>
#include "../src/Class.h"
#include "../src/PID.h"


int main()
{
    PID p;
    int range = p.iterGet();
    for (int i = 0; i < range; i++) {
        p.SetU(i);
        p.SetY(i);
    }
    return 0;
}

