#include "NonLinearSystem.h"

double NonlinearSystem::calculateNext(double y1, double y0) const {  

    return a * y1 - b * y0 * y0 + c * u + d * sin(u);

}
