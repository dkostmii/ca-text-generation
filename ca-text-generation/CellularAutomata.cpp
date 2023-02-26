#include "CellularAutomata.h"
#include "functions.h"

CellularAutomata::CellularAutomata(std::vector<int> initial_state, int rule, int window, int cell_bit_depth) {
	if (window < 3) {
		throw std::invalid_argument("Expected window >= 3");
	}

	if (window % 2 == 0) {
		throw std::invalid_argument("Expected window to be odd");
	}

	if (cell_bit_depth < 2) {
		throw std::invalid_argument("Expected cell_bit_depth >= 2");
	}

	int initial_state_size = initial_state.size();

	if (initial_state_size < window) {
		throw std::invalid_argument("Expected intial_state.size() >= " + std::to_string(window));
	}

	for (int i = 0; i < initial_state_size; i++) {
		if (initial_state[i] >= cell_bit_depth) {
			throw std::invalid_argument("Expected initial_state[" + std::to_string(i) + "] < " + std::to_string(cell_bit_depth));
		}
	}

	int min_rule = 0;

	int window_state_count = pow(cell_bit_depth, window);
	double max_rule = pow(cell_bit_depth, window_state_count) - 1;

	if (rule < min_rule || rule > max_rule) {
		throw std::invalid_argument("Expected rule in range: [" + std::to_string(min_rule) + ", " + std::to_string(max_rule) + "]");
	}

	this->window = window;
	this->rule = rule;
	this->cell_bit_depth = cell_bit_depth;
	this->state = initial_state;
	this->initial_state = initial_state;
}

CellularAutomata::CellularAutomata(CellularAutomata* ca) {
	this->window = ca->window;
	this->rule = ca->rule;
	this->cell_bit_depth = ca->cell_bit_depth;
	this->state = ca->initial_state;
	this->initial_state = ca->initial_state;
}

int CellularAutomata::map_neighbors(std::vector<int> neighbors) {
	int result = 0;
	int neighbors_size = neighbors.size();

	int rule_shift = collect(neighbors, cell_bit_depth);

	return nth_digit(rule, rule_shift + 1, cell_bit_depth);
}

std::vector<int> CellularAutomata::get_neighbors(int at) {
	int max_index = this->state.size() - 1;

	if (at < 0 || at > max_index) {
		throw std::invalid_argument("Expected at in range [0, " + std::to_string(max_index) + "]");
	}

	std::vector<int> result = {};

	int start = cycle(at - this->window / 2, 0, max_index);
	int end = cycle(at + this->window / 2, 0, max_index);

	for (int i = start; i <= end; i++) {
		result.push_back(this->state[i]);
	}

	return result;
}

std::vector<int> CellularAutomata::get_state() {
	return this->state;
}

std::vector<int> CellularAutomata::next_state() {
	std::vector<int> result = {};

	for (int i = 0; i < this->state.size(); i++) {
		result.push_back(map_neighbors(get_neighbors(i)));
	}

	for (int i = 0; i < result.size(); i++) {
		this->state[i] = result[i];
	}

	return this->state;
}

int CellularAutomata::get_bit_depth() {
	return this->cell_bit_depth;
}