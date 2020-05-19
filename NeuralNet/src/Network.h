#pragma once

#include <vector>
#include "Node.h"
#include <map>
#include <fstream>

class Network
{
public:
	Network(int, int, int, int);
	Network(std::ifstream&);
	void set_input(std::vector<double>);
	double think();
	void train(std::vector<double> inp, std::vector<double> outs);
	void save(std::ofstream&);
	friend std::ostream& operator<<(std::ostream&, Network&);
private:
	std::vector<Node*> input;
	std::vector<std::vector<Node*>> hidden;
	std::vector<Node*> output;
	bool init;
};

