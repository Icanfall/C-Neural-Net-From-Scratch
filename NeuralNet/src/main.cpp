#include <iostream>
#include <string>
#include "Network.h"
#include <map>
#include <cmath>

double fu(double x) {
	return std::pow(x, 2) - 3.0 * x + 6.0;
}

int main() {
	std::ifstream ifs{ "untitled.nn" };
	Network n{ ifs };
	std::vector<double> inp;
	std::vector<double> outs;
	for (double i = 0; i < 5; i += 0.01) {
		inp.push_back(i);
		double o = fu(i);
		outs.push_back(o);
	}
	n.set_input(std::vector<double>{2.0});
	double temp = n.think();
	std::cout << n << std::endl;
	//std::ofstream ofs{ "untitled.nn" };
	//n.save(ofs);
}