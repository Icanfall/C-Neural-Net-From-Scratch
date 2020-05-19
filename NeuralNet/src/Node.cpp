#include "Node.h"
#include <cmath>

Node::Node() :value{ 0 } {};

Node::Node(double v) :value{ v } {};

void Node::connect_to(Node* n, double d) {
	nodes.push_back(n);
	weights.push_back(d);
	n->con_trigger(this, weights[weights.size()-1]);
}

void Node::con_trigger(Node* n, double& d) {
	con_this.insert(std::pair<Node*, double&>(n, d));
}

void Node::add_val(double d) {
	value += d;
}

void Node::send_vals() {
	for (int i = 0; i < nodes.size(); i++) {
		nodes[i]->add_val(value * weights[i]);
	}
}

void Node::activate() {
	value = std::exp(value) / (1.0 + std::exp(value));
}

double Node::get_val() {
	return value;
}

void Node::set_val(double d) {
	value = d;
}

void Node::backprop(double diff, double delta) {

}

void Node::save(std::ofstream& ost) {
	for (double w : weights) {
		ost << w << "\n";
	}
}

std::ostream& operator<<(std::ostream& ost, Node* n) {
	ost << n->value;
	return ost;
}