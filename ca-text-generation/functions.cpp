#include "functions.h"

int nth_digit(int a, int n, int base) {
    if (n < 1)
        throw std::invalid_argument("Expecgted n >= 1");

    if (base == 0)
        throw std::invalid_argument("Expected base != 0");

    if (a < 0 && base > 0)
        a = -a;

    for (int i = 1; i < n; i++)
        a = a / base;

    return a % base;
}

int mod(int a, int n) {
    bool reverse = a < 0;
    int result = reverse ? n : 0;

    if (reverse) {
        for (int i = 0; i > a; i--) {
            --result;
            if (result < 0) {
                result = n - 1;
            }
        }
    }
    else {
        for (int i = 0; i < a; i++) {
            ++result;
            if (result > n - 1) {
                result = 0;
            }
        }
    }

    return result;
}

int cycle(int value, int min, int max) {
    if (min > max) {
        throw std::invalid_argument("Expected min <= max");
    }

    return mod(value, max - min + 1) + min;
}

std::string surround(std::string str, std::pair<std::string, std::string> surround_strings) {
    return surround_strings.first + str + surround_strings.second;
}

std::string join(std::vector<std::string> strings, std::string separator) {
    std::string result = "";

    int strings_size = strings.size();

    for (int i = 0; i < strings_size; i++) {
        result += strings[i];

        if (i < strings_size - 1) {
            result += separator;
        }
    }

    return result;
}

void print_vec(
    std::vector<int> vec,
    std::string separator,
    std::pair<std::string, std::string> brackets,
    std::function<std::string(int)> const& string_transformer) {

    std::vector<std::string> strings;

    std::transform(vec.begin(), vec.end(), std::back_inserter(strings), string_transformer);

    std::cout << surround(join(strings, separator), brackets);
}

void print_ca(std::vector<int> state, std::vector<std::string> alphabet) {
    int alphabet_size = alphabet.size();

    print_vec(state, "", std::pair<std::string, std::string>("", ""), [alphabet, alphabet_size](int vec) {
        if (vec > alphabet_size) {
            throw std::invalid_argument("Expected vec to be in range [0, " + std::to_string(alphabet_size) + ")");
        }

    return alphabet[vec];
        });
}

std::string gen_alphabet(unsigned char start, size_t size, std::string except, std::string include) {
    std::string result = "";

    auto current = start;
    auto except_size = except.size();
    auto include_size = include.size();

    for (size_t i = 0; i < size; i++) {
        if (except_size > 0 && except.find(current) == std::string::npos) {
            result += current;
        }
        current++;
    }

    if (include_size > 0) {
        for (auto include_char : include) {
            if (result.find(include_char) == std::string::npos) {
                result += include_char;
            }
        }
    }

    return result;
}

int collect(std::vector<int> vec, int base) {
    if (base == 0) {
        throw std::invalid_argument("Expected base != 0");
    }

    int result = 0;
    int vec_size = vec.size();

    for (int i = 0; i < vec_size; i++) {
        result += vec[i] * pow(base, vec_size - i - 1);
    }

    return result;
}

std::vector<int> deconstruct(int n, int base, int fixed_size) {
    if (base == 0) {
        throw std::invalid_argument("Expected base != 0");
    }

    if (fixed_size == 0 || fixed_size < -1) {
        throw std::invalid_argument("Expected fixed_size to be either -1 or be greater than 0");
    }

    std::vector<int> result = {};

    int nth = 1;
    int digit = nth_digit(n, nth, base);

    while (digit > 0 || nth == 1) {
        result.push_back(digit);

        nth++;
        digit = nth_digit(n, nth, base);
    }

    if (nth > fixed_size) {
        throw std::invalid_argument("Expected fixed_size <= " + std::to_string(fixed_size));
    }

    for (int i = nth; i < fixed_size; i++) {
        result.push_back(0);
    }

    std::reverse(result.begin(), result.end());

    return result;
}

void seed_random_n(unsigned int seed) {
    srand(seed);
}

int random_n(int min, int max) {
    return cycle(rand(), min, max);
}

std::string filter_except(std::string str, std::string except) {
    std::string result = "";

    std::copy_if(str.begin(), str.end(), std::back_inserter(result), [except](char ch) {
        return except.find(ch) == std::string::npos;
    });

    return result;
}

std::string capitalize(std::string text) {
    if (text.size() < 1)
        return text;

    std::string result = "";

    std::transform(text.begin(), ++text.begin(), std::back_inserter(result), std::toupper);

    if (text.size() < 2)
        return result;

    std::transform(++text.begin(), text.end(), std::back_inserter(result), std::tolower);

    return result;
}