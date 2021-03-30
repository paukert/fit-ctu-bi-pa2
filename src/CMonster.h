/**
 * @author Lukas Paukert
 * @date 03.05.2020
 */

#pragma once

#include "CCreature.h"

class CMonster : public CCreature {

public:
    CMonster() = default;

    /**
     * @brief Method that is used for attacking opponent
     * @param[in] opponent      CEntity object which is being attacked
     */
    void attack(CEntity & opponent) override;

    /**
     * @brief Method that cares about defending against opponents attacks
     * @param[in] opponent      the entity which is attacking
     * @param[in] damage        number of damage with which is opponent attacking
     * @param[in] canDefend     variable which determines if opponent can defend
     */
    void defend(CEntity & opponent, int damage, bool canDefend) override;

    /**
     * @brief Prints CMonster to ostream
     * @param[out] out          ostream to which is CMonster printed
     * @return std::ostream& with printed monster
     */
    std::ostream & print(std::ostream & out) const override;

    /**
     * @brief Loads CMonster from istream
     * @param[in] in            istream from which is monster loaded 
     * @param[out] self         CMonster object to which is monster loaded
     * @return std::istream& with remaining data
     */
    friend std::istream & operator>>(std::istream & in, CMonster & self);
};
