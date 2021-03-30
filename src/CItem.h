/**
 * @author Lukas Paukert
 * @date 03.05.2020
 */

#pragma once

#include <iostream>
#include <string>

class CItem {
private:
    static const int MAX_NAME_LENGTH = 40;

    std::string m_Name;
    /** Item increase player strength by m_Strength e.g. 5 */
    int m_Strength = 0;
    /** Item increase player luck by m_Luck e.g. 5 */
    int m_Luck = 0;

public:
    CItem() = default;

    /**
     * @brief Getter for m_Strength variable
     * @return int with item strength
     */
    int getStrength() const;

    /**
     * @brief Getter for m_Luck variable
     * @return int with item luck
     */
    int getLuck() const;

    /**
     * @brief Get basic information about item
     * @return std::string with basic information about item
     */
    std::string getInformation() const;

    /**
     * @brief Prints item to ostream
     * @param[out] out      ostream to which should be item printed
     * @param[in] self      CItem object which should be printed
     * @return std::ostream& with printed item
     */
    friend std::ostream & operator<<(std::ostream & out, const CItem & self);

    /**
     * @brief Loads item from istream
     * @param[in] in        istream from which should be item loaded
     * @param[out] self     CItem object to which is item loaded
     * @return std::istream& with remaining data
     */
    friend std::istream & operator>>(std::istream & in, CItem & self);
};
