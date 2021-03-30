/**
 * @author Lukas Paukert
 * @date 16.05.2020
 */

#include "CPlayer.h"
#include "tools.h"
#include "interface.h"

using namespace std;

void CPlayer::attack(CEntity & opponent) {
    int damage = m_Strength;

    Interface::print("Solve this equation to attack opponent for double damage.");

    if (Tools::solveEquation(10, 30)) {
        Interface::print("Your answer is right! Damage will be doubled.");
        damage *= 2;
    } else {
        Interface::print("Your answer is wrong! Damage will not be doubled.");
    }

    if (Tools::randomNumber(1, 100) <= m_Luck + m_Inventory.getEquippedItemLuck())
        damage *= 2;
    damage += m_Inventory.getEquippedItemStrength();

    opponent.defend(*this, damage, true);
}

void CPlayer::defend(CEntity & opponent, int damage, bool canDefend) {

    if (canDefend) {
        Interface::print("Solve this equation to decrease damage from opponent attack.");

        if (Tools::solveEquation(10, 30)) {
            Interface::print("Your answer is right! Damage will be decreased.");
            damage /= 2;
        } else {
            Interface::print("Your answer is wrong! Damage is unchanged.");
        }
    }

    m_Health -= damage;
    if (m_Health <= 0) {
        Interface::print("You received " + to_string(damage) + " damage.");
        return;
    }

    Interface::print("You have " + to_string(m_Health) + " health left after defend.");
    attack(opponent);
}

void CPlayer::createHero() {
    vector<int> attributes = Interface::setupPlayer(m_SkillPoints);
    m_MaxHealth = attributes[0];
    m_Strength = attributes[1];
    m_Luck = attributes[2];
}

bool CPlayer::isAlive() const {
    return m_Health > 0;
}

void CPlayer::heal() {
    m_Health = m_MaxHealth;
}

void CPlayer::setPosition(int position) {
    m_Position = position;
}

int CPlayer::getPosition() const {
    return m_Position;
}

bool CPlayer::setSkillPoints(int skillPoints) {
    if (skillPoints > MAX_SKILL_POINTS || skillPoints < 0)
        return false;
    m_SkillPoints = skillPoints;
    return true;
}

CInventory & CPlayer::getInventory() {
    return m_Inventory;
}

ostream & operator<<(ostream & out, const CPlayer & self) {

    if (!(out << self.m_MaxHealth << endl) ||
        !(out << self.m_Strength << endl) ||
        !(out << self.m_Luck << endl) ||
        !(out << self.m_Position << endl) ||
        !(out << self.m_Inventory))
        return out;

    return out;
}

istream & operator>>(istream & in, CPlayer & self) {

    if (!(in >> self.m_MaxHealth) || self.m_MaxHealth <= 0 ||
        !(in >> self.m_Strength) || self.m_Strength <= 0 ||
        !(in >> self.m_Luck) || self.m_Luck <= 0 ||
        !(in >> self.m_Position) ||
        !(in >> self.m_Inventory)) {
        in.setstate(ios::failbit);
        return in;
    }

    return in;
}
