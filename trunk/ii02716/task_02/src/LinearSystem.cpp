#include "LinearSystem.h"

double LinearSystem::calculateNext(double y1) const {  

    return a * y1 + b * u;

}
