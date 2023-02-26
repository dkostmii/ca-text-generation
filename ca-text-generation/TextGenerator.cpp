#include "TextGenerator.h"
#include "functions.h"

CellularAutomata* TextGenerator::init_default() {
	std::vector<int> initial_state = deconstruct(random_n(1, 56768721332), 2, 16);
	return new CellularAutomata(initial_state, choose<int>(std::vector<int> { 29, 92, 11, 39, 55, 177, 244, 189, 233 }), choose<int>(std::vector<int>{ 3, 5, 7, 9, 11 }), 2);
}

void TextGenerator::restore_state() {
	std::vector<int> initial_state = deconstruct(random_n(1, 56768721332), 2, 16);
	auto new_ca = new CellularAutomata(initial_state, choose<int>(std::vector<int> { 29, 92, 11, 39, 55, 177, 244, 189, 233 }), choose<int>(std::vector<int>{ 3, 5, 7, 9, 11 }), 2);

	delete this->ca;

	this->ca = new_ca;
}

TextGenerator::TextGenerator() : TextGenerator(this->init_default())
{ }

TextGenerator::TextGenerator(CellularAutomata* ca) {
	this->ca = ca;
	this->vowels = "eyuioa";
	this->consonants = gen_alphabet('a', 26, this->vowels);
	this->whitespace = " ";
	this->punctuation = std::vector<std::string> {
		surround("-", std::pair<std::string, std::string>(this->whitespace, this->whitespace)),
		surround(":", std::pair<std::string, std::string>("", this->whitespace)),
		surround(";", std::pair<std::string, std::string>("", this->whitespace)),
		surround(",", std::pair<std::string, std::string>("", this->whitespace)),
	};
	this->surroundings = std::vector<std::pair<std::string, std::string>>{
		std::pair<std::string, std::string>("(", ")"),
		std::pair<std::string, std::string>("\"", "\""),
		std::pair<std::string, std::string>("\'", "\'"),
		std::pair<std::string, std::string>("\`", "\`"),
	};
	this->sentence_ending = ".!?";
}

std::string TextGenerator::next_char(std::string alphabet) {
	auto state = this->ca->next_state();

	auto alphabet_id = cycle(
		collect(state, this->ca->get_bit_depth()),
		0,
		alphabet.size() - 1);

	return std::string(1, alphabet[alphabet_id]);
}

std::string TextGenerator::next_syllable(std::string prev_syllable) {
	std::string result = "";

	int syllable_size;

	switch (prev_syllable.size()) {
		case 2:
			syllable_size = choose<int>(std::vector<int> { 1, 3 });
			break;

		case 3:
			syllable_size = random_n(1, 2);
			break;

		default:
			syllable_size = random_n(1, 3);
			break;
	}

	std::string buff = "";

	switch (syllable_size) {
		case 1:
			result += next_char(filter_except(this->vowels, prev_syllable));
			break;
		case 2:
			buff = next_char(filter_except(this->consonants, prev_syllable)) + next_char(this->vowels);
			result += next_char(buff);
			result += next_char(filter_except(buff, result));
			break;
		case 3:
			result += next_char(filter_except(this->consonants, prev_syllable));
			result += next_char(this->vowels);
			result += next_char(this->consonants);
			break;

		default:
			throw std::invalid_argument("Expected syllable size in range [1, 3]");
	}

	return result;
}

std::string TextGenerator::next_word(int min_word_size, bool capitalize_word) {
	std::string result = "";
	std::string prev_syllable = "";

	while (result.size() < min_word_size) {
		prev_syllable = next_syllable(prev_syllable);
		result += prev_syllable;
	}

	if (capitalize_word) {
		result = capitalize(result);
	}

	restore_state();

	return result;
}

std::string TextGenerator::next_subsentence(int word_count, bool capitalize, bool surround_subsentence) {
	std::string result = "";

	for (int i = 0; i < word_count; i++) {
		result += next_word(random_n(2, 11), i == 0 && capitalize);

		if (i < word_count - 1) {
			result += this->whitespace;
		}
	}

	if (surround_subsentence) {
		auto surrounding_id = cycle(
			collect(this->ca->get_state(), this->ca->get_bit_depth()),
			0,
			this->surroundings.size() - 1
		);

		auto surrounding = this->surroundings[surrounding_id];

		result = surround(result, surrounding);
	}

	return result;
}

std::string TextGenerator::next_sentence(int subsentence_count) {
	std::string result = "";

	for (int i = 0; i < subsentence_count; i++) {
		result += next_subsentence(random_n(1, 8), i == 0, random_n(0, 6) == 2 && i > 0);

		if (i < subsentence_count - 1) {
			auto punctuation_id = cycle(
				collect(this->ca->get_state(), this->ca->get_bit_depth()),
				0,
				this->punctuation.size() - 1
			);

			auto punctuation = this->punctuation[punctuation_id];

			result += punctuation;
		}
		else if (i == subsentence_count - 1) {
			result += next_char(this->sentence_ending);
		}
	}

	return result;
}

TextGenerator::~TextGenerator()
{
	delete this->ca;
}
