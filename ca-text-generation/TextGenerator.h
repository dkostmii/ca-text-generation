#pragma once
#include "CellularAutomata.h"
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

class TextGenerator
{
private:
	CellularAutomata* ca;
	std::string vowels;
	std::string consonants;
	std::string whitespace;
	std::vector<std::string> punctuation;
	std::vector<std::pair<std::string, std::string>> surroundings;
	std::string sentence_ending;
	CellularAutomata* init_default();
	void restore_state();
	TextGenerator(CellularAutomata* ca);

public:
	TextGenerator();

	std::string next_char(std::string alphabet);
	std::string next_syllable(std::string prev_syllable = "");
	std::string next_word(int min_word_size = 10, bool capitalize = false);
	std::string next_subsentence(int word_count, bool capitalize = false, bool surround = false);
	std::string next_sentence(int subsentence_count);

	~TextGenerator();
};

