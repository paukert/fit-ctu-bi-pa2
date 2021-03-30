/**
 * @author Lukas Paukert
 * @date 16.05.2020
 */

#include "CWizard.h"
#include "interface.h"

using namespace std;

void CWizard::attack(CEntity & opponent) {
    opponent.defend(*this, m_Strength, false);
}

void CWizard::defend(CEntity & opponent, int damage, [[maybe_unused]] bool canDefend) {

    m_Health -= damage;

    if (m_Health <= 0) {
        Interface::print("You attacked " + m_Name + " for " + to_string(damage) + " damage, the wizard is dead!");
        return;
    }

    Interface::print("You attacked " + m_Name + " for " + to_string(damage) + " damage. Wizard has " + to_string(m_Health) + " health left.");
    attack(opponent);
}

ostream & CWizard::print(ostream & out) const {
    if (!(out << "WIZARD" << endl) ||
        !(out << m_Name << endl) ||
        !(out << m_Health << endl) ||
        !(out << m_Strength << endl))
        return out;
    return out;
}

istream & operator>>(istream & in, CWizard & self) {
    if (!getline(in >> ws, self.m_Name) ||
        !(in >> self.m_Health) || self.m_Health <= 0 ||
        !(in >> self.m_Strength) || self.m_Strength <= 0) {
        in.setstate(ios::failbit);
        return in;
    }
    return in;
}
