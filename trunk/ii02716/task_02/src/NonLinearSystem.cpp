#include "NonLinearSystem.h"

double NonlinearSystem::calculateNext(float y1, float y0) const {  

    return a * y1 - b * y0 * y0 + c * u + d * sin(u);

}
