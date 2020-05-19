#pragma once

#include <vector>
#include <iostream>
#include <map>
#include <fstream>

class Node
{
public:
	Node();
	Node(double);
	void connect_to(Node*, double);
	void con_trigger(Node*, double&);
	void add_val(double);
	void send_vals();
	void activate();
	double get_val();
	void set_val(double);
	void backprop(double, double);
	void save(std::ofstream&);
	friend std::ostream& operator<<(std::ostream&, Node*);
private:
	double value;
	std::vector<Node*> nodes;
	std::vector<double> weights;
	std::map<Node*, double&> con_this;
};

