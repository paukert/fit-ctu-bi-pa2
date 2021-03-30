/**
 * @author Lukas Paukert
 * @date 16.05.2020
 */

#include "CItem.h"

using namespace std;

int CItem::getStrength() const {
    return m_Strength;
}

int CItem::getLuck() const {
    return m_Luck;
}

string CItem::getInformation() const {
    return m_Name + " (strength: " + to_string(m_Strength) + "; luck: " + to_string(m_Luck) + ")";
}

ostream & operator<<(ostream & out, const CItem & self) {

    if (!(out << self.m_Name << endl) ||
        !(out << self.m_Strength << endl) ||
        !(out << self.m_Luck << endl << endl))
        return out;

    return out;
}

istream & operator>>(istream & in, CItem & self) {

    if (!getline(in >> ws, self.m_Name) || self.m_Name.size() > CItem::MAX_NAME_LENGTH ||
        !(in >> self.m_Strength) || self.m_Strength < 0 ||
        !(in >> self.m_Luck) || self.m_Luck < 0) {
        in.setstate(ios::failbit);
        return in;
    }

    return in;
}
