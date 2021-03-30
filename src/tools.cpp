/**
 * @author Lukas Paukert
 * @date 16.05.2020
 */

#include <random>
#include <stdexcept>

#include "interface.h"
#include "tools.h"

using namespace std;

int Tools::randomNumber(int from, int to) {
    // source: https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(from, to);
    return dis(gen);
}

bool Tools::stringToInt(const string & text, int & number) {
    try {
        number = stoi(text);
        return true;
    }
    catch (const invalid_argument & e) {
        Interface::print("Answer is not valid, try it again");
        return false;
    }
    catch (const out_of_range & e) {
        Interface::print("Answer is too long, try it again");
        return false;
    }
}

bool Tools::solveEquation(int minNumber, int maxNumber) {
    int firstNumber = randomNumber(minNumber, maxNumber);
    int secondNumber = randomNumber(minNumber, maxNumber);
    string input;
    int answer;

    do {
        input = Interface::getInput(to_string(firstNumber) + " + " + to_string(secondNumber) + " is:");
    } while (!stringToInt(input, answer));

    return answer == (firstNumber + secondNumber);
}
