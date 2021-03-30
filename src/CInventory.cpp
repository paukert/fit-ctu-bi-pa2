/**
 * @author Lukas Paukert
 * @date 16.05.2020
 */

#include "CInventory.h"
#include "interface.h"

using namespace std;

vector<pair<int, string>> CInventory::getMenuItems() const {

    vector<pair<int, string>> content;
    size_t itemID = 0;

    for (const CItem & item : m_Contents) {
        if (itemID != m_EquippedItem)
            content.emplace_back(make_pair(itemID, item.getInformation()));
        itemID++;
    }

    content.emplace_back(make_pair(-1, "Exit inventory"));

    return content;
}

CInventory::CInventory() {
    m_ItemMenuActions.emplace_back(make_pair(0, "Equip item"));
    m_ItemMenuActions.emplace_back(make_pair(1, "Drop item (cannot be retrieved)"));
    m_ItemMenuActions.emplace_back(make_pair(2, "Back to inventory"));
}

bool CInventory::addItem(const CItem & item) {
    if (m_Contents.size() >= m_Capacity)
        return false;
    m_Contents.emplace_back(item);
    return true;
}

bool CInventory::setCapacity(size_t capacity) {
    if (capacity > MAX_CAPACITY)
        return false;
    m_Capacity = capacity;
    return true;
}

int CInventory::getEquippedItemStrength() const {
    if (m_Contents.empty())
        return 0;
    return m_Contents[m_EquippedItem].getStrength();
}

int CInventory::getEquippedItemLuck() const {
    if (m_Contents.empty())
        return 0;
    return m_Contents[m_EquippedItem].getLuck();
}

bool CInventory::isEmpty() const {
    return m_Contents.empty();
}

bool CInventory::isFull() const {
    return m_Capacity == m_Contents.size();
}

void CInventory::manage() {

    while (true) {
        Interface::printInventory("Equipped item: " + m_Contents[m_EquippedItem].getInformation());
        int selectedItem = Interface::printMenu(getMenuItems(), m_Contents.size() != 1);
        if (selectedItem == -1)
            break;

        Interface::printInventory("Item: " + m_Contents[selectedItem].getInformation());
        int action = Interface::printMenu(m_ItemMenuActions, true);
        switch (action) {
            case 0:
                m_EquippedItem = selectedItem;
                break;
            case 1:
                if (static_cast<size_t>(selectedItem) < m_EquippedItem)
                    m_EquippedItem--;
                m_Contents.erase(m_Contents.begin() + selectedItem);
                break;
            default:
                break;
        }
    }
}

ostream & operator<<(ostream & out, const CInventory & self) {

    if (!(out << self.m_Capacity << endl) ||
        !(out << self.m_Contents.size() << endl))
        return out;

    for (const CItem & item : self.m_Contents)
        if (!(out << item))
            return out;

    if (!(out << self.m_EquippedItem << endl))
        return out;

    return out;
}

istream & operator>>(istream & in, CInventory & self) {

    size_t ownedItemsCount;
    if (!(in >> self.m_Capacity) || self.m_Capacity > CInventory::MAX_CAPACITY || !(in >> ownedItemsCount)) {
        in.setstate(ios::failbit);
        return in;
    }

    CItem item;
    for (size_t i = 0; i < ownedItemsCount; i++) {
        if (!(in >> item) || !self.addItem(item)) {
            in.setstate(ios::failbit);
            return in;
        }
    }

    if (!(in >> self.m_EquippedItem) || (!self.m_Contents.empty() && self.m_Contents.size() <= self.m_EquippedItem)) {
        in.setstate(ios::failbit);
        return in;
    }

    return in;
}
