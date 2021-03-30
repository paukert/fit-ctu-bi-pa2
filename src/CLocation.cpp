/**
 * @author Lukas Paukert
 * @date 16.05.2020
 */

#include "CLocation.h"
#include "interface.h"
#include "CMonster.h"
#include "CWizard.h"

using namespace std;

vector<pair<int, string>> CLocation::getOptionsForMenu() const {

    vector<pair<int, string>> options;
    for (const auto & record : m_Options)
        if (record.second.isVisible())
            options.emplace_back(make_pair(record.first, record.second.getText()));

    return options;
}

bool CLocation::verifyOptions(const map<int, COption> & options) const {
    for (const auto & option : options) {
        if ((option.second.getAction() == EAction::FIGHT && m_Creatures.count(option.second.getTarget()) == 0) ||
            (option.second.getAction() == EAction::PICK_UP && m_Items.count(option.second.getTarget()) == 0))
            return false;

        for (int reward : option.second.getRewards())
            if (options.count(reward) == 0)
                return false;
    }
    return true;
}

istream & CLocation::loadCreatures(istream & in, map<int, unique_ptr<CCreature>> & creatures) {

    size_t creaturesCount;
    if (!(in >> creaturesCount))
        return in;

    int creatureID;
    string creatureType;
    pair<map<int, unique_ptr<CCreature>>::iterator, bool> result;

    for (size_t i = 0; i < creaturesCount; i++) {
        if (!(in >> creatureID) || !(in >> creatureType))
            return in;

        if (creatureType == "MONSTER") {
            CMonster monster;
            if (!(in >> monster))
                return in;
            result = creatures.insert({creatureID, make_unique<CMonster>(move(monster))});
        }
        else if (creatureType == "WIZARD") {
            CWizard wizard;
            if (!(in >> wizard))
                return in;
            result = creatures.insert({creatureID, make_unique<CWizard>(move(wizard))});
        }
        else
            result.second = false;

        if (!result.second) {
            in.setstate(ios::failbit);
            return in;
        }
    }
    return in;
}

istream & CLocation::loadItems(istream & in, map<int, CItem> & items) {

    size_t itemsCount;
    if (!(in >> itemsCount))
        return in;

    for (size_t i = 0; i < itemsCount; i++) {
        int itemID;
        CItem item;
        if (!(in >> itemID) || !(in >> item))
            return in;
        auto result = items.insert({itemID, move(item)});

        if (!result.second) {
            in.setstate(ios::failbit);
            return in;
        }
    }
    return in;
}

istream & CLocation::loadOptions(istream & in, map<int, COption> & options) {

    int maxOptionID = 0;
    size_t optionsCount;
    if (!(in >> optionsCount) || optionsCount > MAX_OPTIONS) {
        in.setstate(ios::failbit);
        return in;
    }

    for (size_t i = 0; i < optionsCount; i++) {
        int optionID;
        COption option;
        if (!(in >> optionID) || !(in >> option))
            return in;
        auto result = options.insert({optionID, move(option)});
        if (!result.second) {
            in.setstate(ios::failbit);
            return in;
        }

        if (maxOptionID < optionID)
            maxOptionID = optionID;
    }
    options.insert({maxOptionID+1, {EAction::SHOW_INVENTORY, "Open inventory"}});
    options.insert({maxOptionID+2, {EAction::SAVE, "Save game"}});
    return in;
}

int CLocation::chooseOption() const {

    Interface::printLocation(m_Title, m_Text);
    int selectedItem = Interface::printMenu(getOptionsForMenu(), false);

    return selectedItem;
}

CCreature & CLocation::getCreature(int creatureID) {
    return *m_Creatures[creatureID];
}

CItem & CLocation::getItem(int itemID) {
    return m_Items[itemID];
}

COption & CLocation::getOption(int optionID) {
    return m_Options[optionID];
}

map<int, COption> CLocation::getOptions() const {
    return m_Options;
}

void CLocation::removeCreature(int creatureID) {
    m_Creatures.erase(creatureID);
}

void CLocation::removeItem(int itemID) {
    m_Items.erase(itemID);
}

void CLocation::removeOption(int optionID) {
    m_Options.erase(optionID);
}

ostream & operator<<(ostream & out, const CLocation & self) {
    if (!(out << self.m_Title << endl) || !(out << self.m_Text << endl << endl))
        return out;

    if (!(out << self.m_Creatures.size() << endl << endl))
        return out;
    for (const auto & record : self.m_Creatures) {
        if (!(out << record.first << endl))
            return out;
        if (!(record.second->print(out)))
            return out;
    }

    if (!(out << self.m_Items.size() << endl << endl))
        return out;
    for (const auto & record : self.m_Items) {
        if (!(out << record.first << endl))
            return out;
        if (!(out << record.second))
            return out;
    }

    if (!(out << self.m_Options.size() - 2 << endl << endl))
        return out;
    for (const auto & record : self.m_Options) {
        if (record.second.getAction() == EAction::SHOW_INVENTORY || record.second.getAction() == EAction::SAVE)
            return out;
        if (!(out << record.first << endl))
            return out;
        if (!(out << record.second))
            return out;
    }

    return out;
}

istream & operator>>(istream & in, CLocation & self) {

    if (!getline(in >> ws, self.m_Title) || self.m_Title.size() > CLocation::MAX_TITLE_LENGTH ||
        !getline(in >> ws, self.m_Text) || self.m_Text.size() > CLocation::MAX_TEXT_LENGTH) {
        in.setstate(ios::failbit);
        return in;
    }

    map<int, unique_ptr<CCreature>> creatures;
    if (!self.loadCreatures(in, creatures))
        return in;
    self.m_Creatures.merge(creatures);

    map<int, CItem> items;
    if (!self.loadItems(in, items))
        return in;
    self.m_Items.merge(items);

    map<int, COption> options;
    if (!self.loadOptions(in, options) || !self.verifyOptions(options)) {
        in.setstate(ios::failbit);
        return in;
    }
    self.m_Options.merge(options);

    return in;
}
