/**
 * @author Lukas Paukert
 * @date 16.05.2020
 */

#include "COption.h"

using namespace std;

COption::COption(EAction action, string text)
    : m_Action(action), m_Text(move(text)) {}

EAction COption::getAction() const {
    return m_Action;
}

int COption::getTarget() const {
    return m_Target;
}

vector<int> COption::getRewards() const {
    return m_Rewards;
}

string COption::getText() const {
    return m_Text;
}

bool COption::isVisible() const {
    return m_Visibility;
}

void COption::setVisibility(bool visible) {
    m_Visibility = visible;
}

ostream & operator<<(ostream & out, const COption & self) {

    if (!(out << self.m_Action << endl) ||
        !(out << self.m_Target << endl) ||
        !(out << self.m_Rewards.size() << endl))
        return out;

    for (const size_t reward : self.m_Rewards)
        if (!(out << reward << " "))
            return out;

    if (!(out << endl << self.m_Text << endl) ||
        !(out << boolalpha << self.m_Visibility << endl << endl))
        return out;
    return out;
}

istream & operator>>(istream & in, COption & self) {

    size_t rewardsCount;
    if (!(in >> self.m_Action) || !(in >> self.m_Target) || !(in >> rewardsCount))
        return in;

    int reward;
    for (size_t i = 0; i < rewardsCount; i++) {
        if (!(in >> reward))
            return in;
        self.m_Rewards.emplace_back(reward);
    }

    if (!getline(in >> ws, self.m_Text) || self.m_Text.size() > COption::MAX_TEXT_LENGTH) {
        in.setstate(ios::failbit);
        return in;
    }

    if (!(in >> boolalpha >> self.m_Visibility))
        return in;

    return in;
}
