/**
 * @author Lukas Paukert
 * @date 16.05.2020
 */

#include <curses.h>
#include <filesystem>
#include <stdexcept>

#include "CApplication.h"
#include "CGame.h"
#include "interface.h"

using namespace std;

bool CApplication::verifyConsoleSize() const {
    if (LINES < MIN_CONSOLE_HEIGHT || COLS < MIN_CONSOLE_WIDTH) {
        Interface::print("Console window is too small :( "
                         "Minimum required size is " + to_string(MIN_CONSOLE_WIDTH) + " columns and " + to_string(MIN_CONSOLE_HEIGHT) + " rows.");
        Interface::finishCurses();
        return false;
    }
    return true;
}

string CApplication::chooseFile(const string & extension) const {

    int fileID = 0;
    vector<string> pathToFiles;
    vector<pair<int, string>> menuItems;

    for (const auto & file : filesystem::directory_iterator(PATH_TO_FILES)) {
        if (file.path().extension() == extension && pathToFiles.size() < MAX_FILES_COUNT) {
            pathToFiles.emplace_back(file.path().string());
            menuItems.emplace_back(make_pair(fileID, file.path().filename().string()));
            fileID++;
        }
    }

    if (pathToFiles.empty())
        return "";

    int selectedItem = Interface::printMenu(menuItems, false);
    return pathToFiles[selectedItem];
}

CApplication::CApplication() {
    m_MainMenu.emplace_back(make_pair(0, "Start new game"));
    m_MainMenu.emplace_back(make_pair(1, "Load game"));
    m_MainMenu.emplace_back(make_pair(2, "Quit"));
}

void CApplication::run() {

    Interface::initializeCurses();
    if (!verifyConsoleSize())
        return;

    while (true) {
        CGame game;
        string filePath;
        int choice = Interface::printMenu(m_MainMenu, false);
        switch (choice) {
            case 0:
                filePath = chooseFile(".world");
                if (filePath.empty()) {
                    Interface::print("There are currently no game files in game dir :(");
                    break;
                }
                if (!game.load(filePath)) {
                    Interface::print("Unfortunately game dit NOT loaded successfully :(");
                    break;
                }
                game.setSavePath(filePath.replace(filePath.size()-5, 5, "save"));
                game.run();
                break;
            case 1:
                filePath = chooseFile(".save");
                if (filePath.empty()) {
                    Interface::print("You have no game saves yet, start playing today :)");
                    break;
                }
                if (!game.load(filePath)) {
                    Interface::print("Unfortunately saved game dit NOT loaded successfully :(");
                    break;
                }
                game.setSavePath(filePath);
                game.run();
                break;
            case 2:
                Interface::print("Thanks for playing :)");
                Interface::finishCurses();
                return;
            default:
                throw logic_error("Menu should NOT contain option with this ID");
        }
    }
}
