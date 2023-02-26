#include <iostream>
#include <vector>
#include "CellularAutomata.h"
#include "TextGenerator.h"
#include "functions.h"

int main()
{
	try {
		seed_random_n(123);
		auto tab = "        ";
		TextGenerator* tgen = new TextGenerator();
		std::cout << tgen->next_subsentence(2, true) << std::endl << std::endl;

		for (int i = 0; i < 30; i++) {
			std::cout << tab << tgen->next_sentence(random_n(1, 7)) << std::endl;
		}
		delete tgen;

		std::cout << std::endl;
	}
	catch (const std::invalid_argument& e) {
		std::cout << e.what();
	}
}

void test_ca() {
	std::vector<int> initial_state = { 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0 };

	std::vector<std::string> alphabet = { " ", "X", "O" };
	try {
		CellularAutomata ca(initial_state, 90);

		print_ca(ca.get_state(), alphabet);
		std::cout << std::endl;

		for (int i = 0; i < 30; i++) {
			print_ca(ca.next_state(), alphabet);
			std::cout << std::endl;
		}
	}
	catch (const std::invalid_argument& e) {
		std::cout << e.what();
	}
}
