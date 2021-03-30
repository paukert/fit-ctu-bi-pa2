/**
 * @author Lukas Paukert
 * @date 16.05.2020
 * @source I learned basic features of ncurses library and reused some source code from following sources:
 * @source menu: https://www.youtube.com/watch?v=3YiPdibiQHA
 * @source user input: https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/scanw.html
 */

#include <curses.h>

#include "interface.h"

using namespace std;

void Interface::initializeCurses() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
}

void Interface::finishCurses() {
    endwin();
}

string Interface::getInput(const string & text) {

    char input[100];
    mvprintw((LINES/2)-2, (COLS-text.size())/2, text.c_str());

    // Display users input on the screen
    echo();
    mvgetstr(LINES/2, (COLS/2)-2, input);
    // Stop displaying user input on the screen
    noecho();
    clear();
    return string(input);
}

void Interface::print(const string & text) {

    string help("Press some key to continue");

    mvprintw(LINES/2, (COLS-text.size())/2, text.c_str());
    mvprintw(LINES-2, (COLS-help.size())/2, help.c_str());
    getch();
    clear();
}

void Interface::printLocation(const string & title, const string & text) {

    mvprintw(1, (COLS-title.size())/2, title.c_str());
    printw("\n\n");
    printw(text.c_str());
}

void Interface::printInventory(const string & text) {
    mvprintw(3, (COLS-text.size())/2, text.c_str());
}

int Interface::printMenu(const vector<std::pair<int, std::string>> & options, bool spaceBeforeLast) {

    int pressedKey;
    size_t currentItem = 0;
    size_t optionsCount = options.size();

    int consoleHeight = LINES, consoleWidth = COLS;

    // Menu height is determined by number of options + borders
    int menuHeight = (spaceBeforeLast ? static_cast<int>(optionsCount) + MENU_BORDERS_HEIGHT + 1 : static_cast<int>(optionsCount) + MENU_BORDERS_HEIGHT);
    // Menu width is determined by the longest option + borders
    int menuWidth = 0, optionLength;

    for (const auto & record : options) {
        optionLength = record.second.size();
        if (optionLength > menuWidth)
            menuWidth = optionLength;
    }

    menuWidth += MENU_BORDERS_WIDTH;

    string help("Choose one option from menu using up and down arrows and confirm it by pressing enter :)");
    mvprintw(consoleHeight-2, (consoleWidth-help.size())/2, help.c_str());

    WINDOW * menuWin = newwin(menuHeight, menuWidth, (consoleHeight-menuHeight)/2, (consoleWidth-menuWidth)/2);
    box(menuWin, 0, 0);
    refresh();
    wrefresh(menuWin);
    keypad(menuWin, true);

    while(true) {
        for (size_t i = 0; i < optionsCount; i++) {
            if (i == currentItem)
                wattron(menuWin, A_REVERSE);
            mvwprintw(menuWin, (spaceBeforeLast && i == optionsCount-1 ? i+3 : i+2), (menuWidth-options.at(i).second.size())/2, options.at(i).second.c_str());
            wattroff(menuWin, A_REVERSE);
        }

        pressedKey = wgetch(menuWin);
        switch (pressedKey) {
            case KEY_UP:
                if (currentItem != 0)
                    currentItem--;
                break;
            case KEY_DOWN:
                if (currentItem != optionsCount-1)
                    currentItem++;
                break;
            default:
                break;
        }

        if (pressedKey == ENTER_KEY)
            break;
    }

    wclear(menuWin);
    wrefresh(menuWin);
    delwin(menuWin);
    clear();

    return options.at(currentItem).first;
}

vector<int> Interface::setupPlayer(int availablePoints) {

    int pressedKey;
    size_t currentItem = 0;
    vector<pair<string, int>> attributes {{"Health: %8d", ATTRIBUTES_VALUE}, {"Strength: %6d", ATTRIBUTES_VALUE}, {"Luck: %10d", ATTRIBUTES_VALUE}};

    int consoleHeight = LINES, consoleWidth = COLS;
    int menuHeight = ATTRIBUTES_COUNT + MENU_BORDERS_HEIGHT + 2;
    int menuWidth = ATTRIBUTES_LENGTH + MENU_BORDERS_WIDTH;

    string help("Customize your skills with arrows and confirm it by pressing enter :)");
    string hint("Hint: every skill point has to be used");
    mvprintw(LINES-4, (consoleWidth-help.size())/2, help.c_str());
    mvprintw(LINES-2, (consoleWidth-hint.size())/2, hint.c_str());

    WINDOW * menuWin = newwin(menuHeight, menuWidth, (consoleHeight-menuHeight)/2, (consoleWidth-menuWidth)/2);
    box(menuWin, 0, 0);
    refresh();
    wrefresh(menuWin);
    keypad(menuWin, true);

    while(true) {

        for (size_t i = 0; i < ATTRIBUTES_COUNT; i++) {
            if (i == currentItem)
                wattron(menuWin, A_REVERSE);
            mvwprintw(menuWin, i+2, 3, attributes[i].first.c_str(), attributes[i].second);
            wattroff(menuWin, A_REVERSE);
        }

        mvwprintw(menuWin, ATTRIBUTES_COUNT+3, 3, "Remaining: %5d", availablePoints);

        pressedKey = wgetch(menuWin);
        switch (pressedKey) {
            case KEY_UP:
                if (currentItem != 0)
                    currentItem--;
                break;
            case KEY_DOWN:
                if (currentItem != ATTRIBUTES_COUNT-1)
                    currentItem++;
                break;
            case KEY_RIGHT:
                if (availablePoints != 0) {
                    attributes[currentItem].second++;
                    availablePoints--;
                }
                break;
            case KEY_LEFT:
                if (attributes[currentItem].second != ATTRIBUTES_VALUE) {
                    attributes[currentItem].second--;
                    availablePoints++;
                }
                break;
            default:
                break;
        }

        if (pressedKey == ENTER_KEY && availablePoints == 0)
            break;
    }

    wclear(menuWin);
    wrefresh(menuWin);
    delwin(menuWin);
    clear();

    vector<int> result = {attributes[0].second, attributes[1].second, attributes[2].second};
    return result;
}
