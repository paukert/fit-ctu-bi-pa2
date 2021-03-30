/**
 * @author Lukas Paukert
 * @date 02.06.2020
 */

#pragma once

#include <iostream>
#include <utility>
#include <string>

#include "CEntity.h"

class CCreature : public CEntity {
protected:
    std::string m_Name;

public:
    CCreature() = default;

    /**
     * @brief Prints CCreature object to ostream
     * @param[out] out      ostream to which is creature printed
     * @return std::ostream& with printed creature
     */
    virtual std::ostream & print(std::ostream & out) const = 0;

    /**
     * @brief Calls print virtual method
     * @param[out] out      ostream to which should be creature printed
     * @param[in] self      CCreture object on which should be print method called
     * @return std::ostream& with printed creature
     */
    friend std::ostream & operator<<(std::ostream & out, const CCreature & self) {
        return self.print(out);
    }
};
