LinearParams lp{0.8, 0.1};
double y_next = linearModel(y, u, lp);

NonlinearParams nlp{0.8, 0.01, 0.05, 0.005};
double y_next_nl = nonlinearModel(y, y_prev, u, u_prev, nlp);
