/**
 * @author Lukas Paukert
 * @date 16.05.2020
 */

#include <fstream>

#include "CGame.h"
#include "interface.h"

using namespace std;

bool CGame::isCreatingCharacter() const {
    return m_GameStatus == EGameStatus::CREATING_CHARACTER;
}

bool CGame::verifyOptions(const map<int, CLocation> & locations) const {
    for (const auto & location : locations) {
        for (const auto & option : location.second.getOptions()) {
            if (option.second.getAction() == EAction::TRAVEL &&
                option.second.getTarget() != m_EndLocation &&
                locations.count(option.second.getTarget()) == 0)
                return false;
        }
    }
    return true;
}

bool CGame::manageLocation(int locationID) {

    CLocation & currentLocation = m_Locations[locationID];
    int selectedItem = currentLocation.chooseOption();
    COption & selectedOption = currentLocation.getOption(selectedItem);
    EAction action = selectedOption.getAction();
    m_Player.heal();

    switch (action) {
        case EAction::PICK_UP:
            if (m_Player.getInventory().isFull()) {
                Interface::print("Your inventory is currently full :/");
                break;
            }
            m_Player.getInventory().addItem(currentLocation.getItem(selectedOption.getTarget()));
            currentLocation.removeItem(selectedOption.getTarget());
            currentLocation.removeOption(selectedItem);
            break;
        case EAction::FIGHT:
            m_Player.attack(currentLocation.getCreature(selectedOption.getTarget()));
            for (const int optionID : selectedOption.getRewards())
                currentLocation.getOption(optionID).setVisibility(true);
            currentLocation.removeCreature(selectedOption.getTarget());
            currentLocation.removeOption(selectedItem);
            break;
        case EAction::TRAVEL:
            m_Player.setPosition(selectedOption.getTarget());
            if (m_Player.getPosition() == m_EndLocation) {
                m_GameStatus = EGameStatus::END;
                return false;
            }
            break;
        case EAction::SAVE:
            return false;
        case EAction::SHOW_INVENTORY:
            if (m_Player.getInventory().isEmpty()) {
                Interface::print("There is not any item in your inventory :(");
                break;
            }
            m_Player.getInventory().manage();
            break;
    }
    return true;
}

bool CGame::save(const string & filePath) const {
    ofstream outFile(filePath, ios::trunc);
    if (outFile.fail())
        return false;

    outFile << *this;
    outFile.close();

    return !outFile.fail();
}

void CGame::run() {
    while (true) {
        if (isCreatingCharacter()) {
            Interface::print(m_GameName + " by " + m_Author);
            m_Player.createHero();
            m_GameStatus = EGameStatus::RUNNING;
        }

        if (!manageLocation(m_Player.getPosition()) || !m_Player.isAlive())
            break;
    }

    if (!m_Player.isAlive()) {
        Interface::print("You died. Game over :(");
        return;
    }

    if (m_GameStatus == EGameStatus::END) {
        Interface::print("Congratulation! You win :)");
        return;
    }

    save(m_SavePath);
}

void CGame::setSavePath(const string & path) {
    m_SavePath = path;
}

bool CGame::load(const string & filePath) {
    ifstream inFile(filePath);
    if (inFile.fail())
        return false;

    inFile >> *this;
    inFile.close();

    return !inFile.fail();
}

ostream & operator<<(ostream & out, const CGame & self) {

    if (!(out << self.m_GameName << endl) ||
        !(out << self.m_Author << endl) ||
        !(out << self.m_GameStatus << endl) ||
        !(out << self.m_EndLocation << endl << endl))
        return out;

    if (!(out << self.m_Locations.size() << endl << endl))
        return out;

    for (const auto & record : self.m_Locations) {
        if (!(out << record.first << endl))
            return out;
        if (!(out << record.second))
            return out;
    }

    if (!(out << self.m_Player))
        return out;

    return out;
}

istream & operator>>(istream & in, CGame & self) {

    if (!getline(in >> ws, self.m_GameName) || self.m_GameName.size() > CGame::MAX_NAME_LENGTH ||
        !getline(in >> ws, self.m_Author) || self.m_Author.size() > CGame::MAX_NAME_LENGTH ||
        !(in >> self.m_GameStatus) ||
        !(in >> self.m_EndLocation)) {
        in.setstate(ios::failbit);
        return in;
    }

    size_t locationsCount;
    if (!(in >> locationsCount))
        return in;

    CLocation location;
    int locationID;
    map<int, CLocation> locations;
    for (size_t i = 0; i < locationsCount; i++) {
        if (!(in >> locationID) || !(in >> location))
            return in;
        auto result = locations.insert({locationID, move(location)});
        if (!result.second) {
            in.setstate(ios::failbit);
            return in;
        }
    }
    if (!self.verifyOptions(locations)) {
        in.setstate(ios::failbit);
        return in;
    }
    self.m_Locations.merge(locations);

    if (!self.isCreatingCharacter()) {
        if (!(in >> self.m_Player) || self.m_Locations.count(self.m_Player.getPosition()) == 0) {
            in.setstate(ios::failbit);
            return in;
        }
    }
    else {
        size_t inventoryCapacity;
        int skillPoints;
        if (!(in >> inventoryCapacity) || !self.m_Player.getInventory().setCapacity(inventoryCapacity) ||
            !(in >> skillPoints) || !self.m_Player.setSkillPoints(skillPoints)) {
            in.setstate(ios::failbit);
            return in;
        }
    }

    return in;
}
