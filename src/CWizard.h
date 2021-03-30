/**
 * @author Lukas Paukert
 * @date 11.05.2020
 */

#pragma once

#include "CCreature.h"

class CWizard : public CCreature {

public:
    CWizard() = default;

    /**
     * @brief Method that is used for attacking opponent
     * @param[in] opponent      CEntity object which is being attacked
     */
    void attack(CEntity & opponent) override;

    /**
     * @brief Method that cares about defending against opponents attacks
     * @param[in] opponent      the entity which is attacking
     * @param[in] damage        number of damage with which is opponent attacking
     * @param[in] canDefend     this variable is unused because wizard has no defend options and always is attacked with full damage
     */
    void defend(CEntity & opponent, int damage, [[maybe_unused]] bool canDefend) override;

    /**
     * @brief Prints creature to ostream
     * @param[out] out          ostream to which should be CWizard object printed
     * @return std::ostream& with printed wizard
     */
    std::ostream & print(std::ostream & out) const override;

    /**
     * @brief Function that is used for loading wizard from save file
     * @param[in] in            istream from which should be wizard loaded
     * @param[out] self         CWizard object to which is wizard loaded
     * @return std::istream& with remaining data
     */
    friend std::istream & operator>>(std::istream & in, CWizard & self);
};
