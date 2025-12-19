#include "LinearSystem.h"

float LinearSystem::calculateNext(float y1) const {  

    return a * y1 + b * u;

}