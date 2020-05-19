#include "Network.h"
#include <iostream>
#include <ctime>

Network::Network(int in, int hCount, int hSize, int out) :init{ false } {
	for (int i = 0; i < in; i++) {
		input.push_back(new Node{});
	}
	input.push_back(new Node{ 1 });
	for (int i = 0; i < hCount; i++) {
		std::vector<Node*> temp;
		for (int x = 0; x < hSize; x++) {
			temp.push_back(new Node{});
		}
		hidden.push_back(temp);
	}
	for (int i = 0; i < out; i++) {
		output.push_back(new Node{});
	}

	std::srand(std::time(nullptr));
	for (auto n : input) {
		for (auto i : hidden[0]) {
			n->connect_to(i, (double)std::rand()/RAND_MAX);
		}
	}
	for (int i = 0; i < hidden.size()-1; i++) {
		for (auto n : hidden[i]) {
			for (auto x : hidden[i + 1]) {
				n->connect_to(x, (double)std::rand() / RAND_MAX);
			}
		}
	}
	for (auto n : hidden[hidden.size() - 1]) {
		for (auto i : output) {
			n->connect_to(i, (double)std::rand() / RAND_MAX);
		}
	}
}

Network::Network(std::ifstream& ifs) :init{ false } {
	int in;
	int hCount;
	int hSize;
	int out;
	ifs >> in;
	ifs >> hCount;
	ifs >> hSize;
	ifs >> out;

	for (int i = 0; i < in; i++) {
		input.push_back(new Node{});
	}
	input.push_back(new Node{ 1 });
	for (int i = 0; i < hCount; i++) {
		std::vector<Node*> temp;
		for (int x = 0; x < hSize; x++) {
			temp.push_back(new Node{});
		}
		hidden.push_back(temp);
	}
	for (int i = 0; i < out; i++) {
		output.push_back(new Node{});
	}
	for (auto n : input) {
		for (auto i : hidden[0]) {
			double t;
			ifs >> t;
			n->connect_to(i, t);
		}
	}
		for (int i = 0; i < hidden.size() - 1; i++) {
			for (auto n : hidden[i]) {
				for (auto x : hidden[i + 1]) {
					double t;
					ifs >> t;
					n->connect_to(x, t);
				}
			}
		}
		for (auto n : hidden[hidden.size() - 1]) {
			for (auto i : output) {
				double t;
				ifs >> t;
				n->connect_to(i, t);
			}
		}
	}

void Network::set_input(std::vector<double> ins) {
	for (int i = 0; i < input.size()-1; i++) {
		input[i]->set_val(ins[i]);
	}
	for (auto arr : hidden) {
		for (auto n : arr) {
			n->set_val(0);
		}
	}
	for (auto n : output) {
		n->set_val(0);
	}
	init = true;
}

double Network::think() {
	if (!init) {
		std::cerr << "Input not intialized, using default values" << std::endl;
		std::vector<double> temp;
		for (int i = 0; i < input.size(); i++) {
			temp.push_back(1);
		}
		set_input(temp);
	}
	for (auto n : input) {
		n->send_vals();
	}
	for (auto arr : hidden) {
		for (auto n : arr) {
			//n->activate();
			n->send_vals();
		}
	}
	for (auto n : output) {
		//n->activate();
	}

	int index{ -1 };
	double max{-1};

	for (int i = 0; i < output.size(); i++) {
		if (output[i]->get_val() > max) {
			max = output[i]->get_val();
			index = i;
		}
	}
	return max;
}

std::ostream& operator<<(std::ostream& ost, Network& n) {
	for (auto node : n.input) {
		ost << node << "\t";
	}
	ost << std::endl;

	for (auto arr : n.hidden) {
		for (auto node : arr) {
			ost << node << " ";
		}
		ost << std::endl;
	}

	for (auto node : n.output) {
		ost << node << "\t";
	}
	ost << std::endl;
	return ost;
}


void Network::train(std::vector<double> inp, std::vector<double> outs) {
	int outC = 0;
	for (int k = 0; k < inp.size(); k += input.size()-1) {
		std::vector<double> temp;
		for (int i = 0; i < input.size()-1; i++) {
			temp.push_back(inp[i+k]);
			std::cout << "Input: " << inp[i + k];
		}
		set_input(temp);
		double max = this->think();
		std::cout << " Output: " << max << std::endl;
		std::cout << outs[outC]-max << std::endl;
		for (auto node : output) {
			node->backprop(outs[outC] - max, 0.01);
		}
		for (auto arr : hidden) {
			for (auto node : arr) {
				node->backprop(outs[outC] - max, 0.01);
			}
		}
		outC++;
	}
}

void Network::save(std::ofstream& ofs) {
	ofs << input.size()-1 << "\n";
	ofs << hidden.size() << "\n";
	ofs << hidden[0].size() << "\n";
	ofs << output.size() << "\n";

	for (int i = 0; i < input.size(); i++) {
		input[i]->save(ofs);
	}
	for (auto arr : hidden) {
		for (auto n : arr) {
			n->save(ofs);
		}
	}
	for (auto n : output) {
		n->save(ofs);
	}
}