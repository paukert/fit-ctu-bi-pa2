/**
 * @author Lukas Paukert
 * @date 03.05.2020
 */

#pragma once

class CEntity {
protected:
    int m_Strength = 0;
    int m_Health = 0;

public:
    CEntity() = default;

    /**
     * @brief Method that is used for attacking opponent
     * @param[in] opponent      CEntity object which is being attacked
     */
    virtual void attack(CEntity & opponent) = 0;

    /**
     * @brief Method that cares about defending against opponents attacks
     * @param[in] opponent      the entity which is attacking
     * @param[in] damage        number of damage with which is opponent attacking
     * @param[in] canDefend     variable which determines if opponent can defend
     */
    virtual void defend(CEntity & opponent, int damage, bool canDefend) = 0;
};
