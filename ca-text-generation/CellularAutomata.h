#pragma once

#include <vector>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <iterator>

class CellularAutomata
{
private:
	int rule;
	int window;
	std::vector<int> state;
	std::vector<int> initial_state;
	int cell_bit_depth;

public:
	CellularAutomata(std::vector<int> initial_state, int rule, int window = 3, int cell_bit_depth = 2);
	CellularAutomata(CellularAutomata* ca);

private:
	int map_neighbors(std::vector<int> neighbors);
	std::vector<int> get_neighbors(int at);

public:
	std::vector<int> get_state();
	std::vector<int> next_state();
	int get_bit_depth();
};

