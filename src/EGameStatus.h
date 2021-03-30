/**
 * @author Lukas Paukert
 * @date 03.05.2020
 */

#pragma once

#include <iostream>

/**
 * Enum class that represents state of the current game
 */
enum class EGameStatus {
    CREATING_CHARACTER = 0,
    RUNNING,
    END
};

/**
 * @brief Prints EGameStatus to ostream
 * @param[out] out      ostream to which should be EGameStatus printed
 * @param[in] self      EGameStatus which is printed
 * @return std::ostream& with printed EGameStatus
 */
std::ostream & operator<<(std::ostream & out, const EGameStatus & self);

/**
 * @brief Loads EGameStatus from istream
 * @param[in] in        istream from which should be EGameStatus loaded
 * @param[out] self     EGameStatus to which is status loaded
 * @return std::istream& with remaining stream
 */
std::istream & operator>>(std::istream & in, EGameStatus & self);
