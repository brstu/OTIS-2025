#include <iostream>
#include "Model.h"

int main() {
	Const_ c(2.3, 3.4, 1.2, 1.05, 0.85, 0.05);
	Qs q(0.0, 0.0, 0.0);
	Model::Params p(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	find_Qs(q, c);
	PID_model(q, c,p);
	return 0;
}
