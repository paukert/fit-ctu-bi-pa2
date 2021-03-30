/**
 * @author Lukas Paukert
 * @date 09.05.2020
 */

#pragma once

#include <string>

namespace Tools {

    /**
     * @brief Generate random number from given range
     * @param[in] from          the lowest number which could be generated
     * @param[in] to            the highest number which could be generated
     * @return generated number
     */
    int randomNumber(int from, int to);

    /**
     * @brief Tries to convert string to number
     * @param[in] text          string to convert
     * @param[out] number       converted number
     * @return true if was conversion successful otherwise return false (string cannot be converted)
     */
    bool stringToInt(const std::string & text, int & number);

    /**
     * @brief Generates equation to user
     * @param[in] minNumber     min number which could be in equation
     * @param[in] maxNumber     max number which could be in equation
     * @return true is user solves the equation correctly otherwise returns false
     */
    bool solveEquation(int minNumber, int maxNumber);
}
