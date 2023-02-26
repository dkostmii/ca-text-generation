#pragma once

#include <stdexcept>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <functional>

#include <stdlib.h>
#include <time.h>

int nth_digit(int a, int n, int base);
int mod(int a, int n);
int cycle(int value, int min, int max);

std::string surround(std::string str, std::pair<std::string, std::string> surround_strings);
std::string join(std::vector<std::string> strings, std::string separator);

void print_vec(
    std::vector<int> vec,
    std::string separator = ", ",
    std::pair<std::string, std::string> brackets = std::pair<std::string, std::string>("[ ", " ]"),
    std::function<std::string(int)> const& string_transformer = [](int vec) {
        return std::to_string(vec);
    });

void print_ca(std::vector<int> state, std::vector<std::string> alphabet = { " ", "X" });

std::string gen_alphabet(unsigned char start, size_t size, std::string except = "", std::string include = "");

int collect(std::vector<int> vec, int base);
std::vector<int> deconstruct(int n, int base, int fixed_size = -1);
void seed_random_n(unsigned int seed = time(0));
int random_n(int min, int max);
template <typename T> T choose(std::vector<T> vec) {
    auto id = random_n(0, vec.size() - 1);
    return vec[id];
}
std::string filter_except(std::string str, std::string except);

std::string capitalize(std::string text);
