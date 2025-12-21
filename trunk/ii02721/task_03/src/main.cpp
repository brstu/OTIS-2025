#include "PID.h"

int main(){
double temp;
double desired_temp;
std::cout << "Enter desired temp " << std::endl;
std::cin >> desired_temp;
std::cout << "Enter start temp " << std::endl;
std::cin >> temp;
PID_model(desired_temp,temp);
return 0;
}
