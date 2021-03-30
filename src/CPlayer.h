/**
 * @author Lukas Paukert
 * @date 03.05.2020
 */

#pragma once

#include <iostream>

#include "CEntity.h"
#include "CInventory.h"

class CPlayer : public CEntity {
private:
    static const int MAX_SKILL_POINTS = 500;

    int m_Position = 1;
    int m_Luck = 0;
    int m_MaxHealth = 0;
    int m_SkillPoints = 0;
    CInventory m_Inventory;

public:
    CPlayer() = default;

    /**
     * @brief Method that is used for attacking opponent
     * @param[in] opponent          CEntity object which is being attacked
     */
    void attack(CEntity & opponent) override;

    /**
     * @brief Method that cares about defending against opponents attacks
     * @param[in] opponent          the entity which is attacking
     * @param[in] damage            number of damage with which is opponent attacking
     * @param[in] canDefend         variable which determines if opponent can defend
     */
    void defend(CEntity & opponent, int damage, bool canDefend) override;

    /**
     * @brief Allows player to customise his skills and sets m_MaxHealth, m_Strength and m_Luck
     */
    void createHero();

    /**
     * @brief Finds out if player is alive
     * @return true if player health is > 0 otherwise returns false
     */
    bool isAlive() const;

    /**
     * @brief Sets player m_Health to m_MaxHealth
     */
    void heal();

    /**
     * @brief Setter for m_Position variable
     * @param[in] position          new player position
     */
    void setPosition(int position);

    /**
     * @brief Getter for m_Position variable
     * @return current player position
     */
    int getPosition() const;

    /**
     * @brief Setter for m_SkillPoints variable
     * @param[in] skillPoints       number of skill points
     * @return true if number of skill points is less than constant MAX_SKILL_POINTS otherwise returns false
     */
    bool setSkillPoints(int skillPoints);

    /**
     * @brief Gets the players inventory
     * @return reference to players inventory
     */
    CInventory & getInventory();

    /**
     * @brief Prints player to ostream
     * @param[out] out              ostream to which should be player printed
     * @param[in] self              player who should be printed
     * @return std::ostream& with printed player
     */
    friend std::ostream & operator<<(std::ostream & out, const CPlayer & self);

    /**
     * @brief Loads player from istream
     * @param[in] in                istream from which should be player loaded
     * @param[out] self             CPlayer object to which is player loaded
     * @return std::istream& with remaining data
     */
    friend std::istream & operator>>(std::istream & in, CPlayer & self);
};
