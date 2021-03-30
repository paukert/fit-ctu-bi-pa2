/**
 * @author Lukas Paukert
 * @date 10.05.2020
 */

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <utility>

const int ENTER_KEY = 10;

const int MENU_BORDERS_HEIGHT = 4;
const int MENU_BORDERS_WIDTH = 8;

const int ATTRIBUTES_COUNT = 3;
const int ATTRIBUTES_LENGTH = 14;
const int ATTRIBUTES_VALUE = 20;

namespace Interface {

    /**
     * @brief Initialize ncurses library
     */
    void initializeCurses();

    /**
     * @brief Ends displaying game on console with ncurses library
     */
    void finishCurses();

    /**
     * @brief Gets input from user
     * @param[in] text              text which is displayed to user above input in console
     * @return string with input from user
     */
    std::string getInput(const std::string & text);

    /**
     * @brief Prints text to console window, aligned to center
     * @param[in] text              text to print
     */
    void print(const std::string & text);

    /**
     * @brief Prints title and text about location to console window
     * @param[in] title             title to print
     * @param[in] text              text to print
     */
    void printLocation(const std::string & title, const std::string & text);

    /**
     * @brief Prints text about inventory aligned to center to console
     * @param[in] text              text to print
     */
    void printInventory(const std::string & text);

    /**
     * @brief Prints menu to console window and allows user to choose one concrete option
     * @param[in] options           options to display
     * @param[in] spaceBeforeLast   bool that determines if there should be blank row before last menu item
     * @return ID of selected option
     */
    int printMenu(const std::vector<std::pair<int, std::string>> & options, bool spaceBeforeLast);

    /**
     * @brief Lets user split his skill points to his skills
     * @param[in] availablePoints   number of available points to split
     * @return number of points which user assigned to his skills (health, strength, luck)
     */
    std::vector<int> setupPlayer(int availablePoints);
}
