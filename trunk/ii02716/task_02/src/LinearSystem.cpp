#include "LinearSystem.h"

double LinearSystem::calculateNext(float y1) const {  

    return a * y1 + b * u;

}
