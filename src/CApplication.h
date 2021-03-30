/**
 * @author Lukas Paukert
 * @date 03.05.2020
 * @inspiredBy David Bernhauer <bernhdav@fit.cvut.cz>, https://gitlab.fit.cvut.cz/bernhdav/pa2-minesweeper/
 */

#pragma once

#include <string>
#include <utility>
#include <vector>

const char* const PATH_TO_FILES = "./examples/";

class CApplication {
private:
    static const int MIN_CONSOLE_HEIGHT = 35;
    static const int MIN_CONSOLE_WIDTH = 100;
    static const int MAX_FILES_COUNT = 10;

    /** Contains main menu items */
    std::vector<std::pair<int, std::string>> m_MainMenu;

    /**
     * @brief Method which checks the console size
     * @return true if console size is bigger than the minimum required size otherwise returns false
     */
    bool verifyConsoleSize() const;

    /**
     * @brief Searches for file with specific extension in directory specified by PATH_TO_FILES
     * @param[in] extension         extension of the file
     * @return std::string with file path
     */
    std::string chooseFile(const std::string & extension) const;

public:
    CApplication();
    CApplication(const CApplication & app) = delete;
    CApplication & operator=(const CApplication & app) = delete;
    ~CApplication() = default;

    /**
     * @brief Method which starts the entire application
     */
    void run();
};
