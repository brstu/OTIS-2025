#include <iostream>
#include <vector>
#include "C:\Users\Boss\Desktop\OTIS-2025\trunk\ii02714\task_03\src\linear.h"
#include "C:\Users\Boss\Desktop\OTIS-2025\trunk\ii02714\task_03\src\Class.h"
#include "C:\Users\Boss\source\repos\otis3\otis3\PID.h"


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

