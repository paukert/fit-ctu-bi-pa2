/**
 * @author Lukas Paukert
 * @date 05.05.2020
 */

#pragma once

#include <iostream>

/**
 * Enum class that represents type of option which can player choose from
 */
enum class EAction {
    FIGHT = 0,
    TRAVEL,
    PICK_UP,
    SHOW_INVENTORY,
    SAVE
};

/**
 * @brief Prints EAction to ostream
 * @param[out] out      ostream to which should be EAction printed
 * @param[it] self      EAction which is printed
 * @return std::ostream& with printed EAction
 */
std::ostream & operator<<(std::ostream & out, const EAction & self);

/**
 * @brief Loads EAction from istream
 * @param[in] in        istream from which should be EAction loaded
 * @param[out] self     EAction to which is action loaded
 * @return std::istream& with remaining data
 */
std::istream & operator>>(std::istream & in, EAction & self);
