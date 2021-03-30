/**
 * @author Lukas Paukert
 * @date 04.05.2020
 */

#pragma once

#include <iostream>
#include <utility>
#include <vector>

#include "EAction.h"

class COption {
private:
    static const int MAX_TEXT_LENGTH = 70;

    EAction m_Action;
    int m_Target = 0;
    std::vector<int> m_Rewards;
    std::string m_Text;
    bool m_Visibility = true;

public:
    COption() = default;

    /**
     * @brief Construct a new COption object
     * @param[in] action    type of action
     * @param[in] text      text which describes the option
     */
    COption(EAction action, std::string text);

    /**
     * @brief Getter for m_Action variable
     */
    EAction getAction() const;

    /**
     * @brief Getter for m_Target variable
     */
    int getTarget() const;

    /**
     * @brief Getter for m_Rewards variable 
     */
    std::vector<int> getRewards() const;

    /**
     * @brief Getter for m_Text variable
     */
    std::string getText() const;

    /**
     * @brief Getter for m_Visibility variable
     */
    bool isVisible() const;

    /**
     * @brief Setter for m_Visibility variable
     */
    void setVisibility(bool visible);

    /**
     * @brief Prints the option to ostream
     * @param[out] out      ostream to which is option printed
     * @param[in] self      COption object which is printed
     * @return std::ostream& with printed option
     */
    friend std::ostream & operator<<(std::ostream & out, const COption & self);

    /**
     * @brief Loads the COption from istream
     * @param[in] in        istream from which is COption loaded
     * @param[out] self     COption object to which is option loaded
     * @return std::istream& with remaining data
     */
    friend std::istream & operator>>(std::istream & in, COption & self);
};
