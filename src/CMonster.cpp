/**
 * @author Lukas Paukert
 * @date 16.05.2020
 */

#include "CMonster.h"
#include "interface.h"
#include "tools.h"

using namespace std;

void CMonster::attack(CEntity & opponent) {
    opponent.defend(*this, m_Strength, true);
}

void CMonster::defend(CEntity & opponent, int damage, bool canDefend) {

    if (canDefend) {
        double random = Tools::randomNumber(5, 10) * 0.1;
        damage = static_cast<int>(damage * random);
    }

    m_Health -= damage;

    if (m_Health <= 0) {
        Interface::print("You attacked " + m_Name + " for " + to_string(damage) + " damage, the monster is dead!");
        return;
    }

    Interface::print("You attacked " + m_Name + " for " + to_string(damage) + " damage. Monster has " + to_string(m_Health) + " health left.");
    attack(opponent);
}

ostream & CMonster::print(ostream & out) const {
    if (!(out << "MONSTER" << endl) ||
        !(out << m_Name << endl) ||
        !(out << m_Health << endl) ||
        !(out << m_Strength << endl))
        return out;
    return out;
}

istream & operator>>(istream & in, CMonster & self) {
    if (!getline(in >> ws, self.m_Name) ||
        !(in >> self.m_Health) || self.m_Health <= 0 ||
        !(in >> self.m_Strength) || self.m_Strength <= 0) {
        in.setstate(ios::failbit);
        return in;
    }
    return in;
}
