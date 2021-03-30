/**
 * @author Lukas Paukert
 * @date 03.05.2020
 */

#pragma once

#include <iostream>
#include <vector>
#include <utility>

#include "CItem.h"

class CInventory {
private:
    static const int MAX_CAPACITY = 10;

    /** Index of currently equipped item in m_Contents */
    size_t m_EquippedItem = 0;
    size_t m_Capacity = 0;
    std::vector<CItem> m_Contents;
    /** Menu items for actions with one concrete item */
    std::vector<std::pair<int, std::string>> m_ItemMenuActions;

    /**
     * @brief Gets menu items based on current items in inventory
     * @return menu items that each one represents one item in inventory
     */
    std::vector<std::pair<int, std::string>> getMenuItems() const;

public:
    CInventory();

    /**
     * @brief Adds an item to the inventory
     * @param[in] item          item which should be added to the inventory
     * @return true if the item was added to inventory successfully otherwise return false (inventory is full)
     */
    bool addItem(const CItem & item);

    /**
     * @brief Set capacity of the inventory
     * @param[in] capacity      new capacity of the inventory
     * @return true if was the capacity set successfully otherwise return false (capacity is bigger than MAX_CAPACITY)
     */
    bool setCapacity(size_t capacity);

    /**
     * @brief Get the strength of the currently equipped item
     * @return int with strength of the item
     */
    int getEquippedItemStrength() const;

    /**
     * @brief Get the luck of the currently equipped item
     * @return int with luck of the item
     */
    int getEquippedItemLuck() const;

    /**
     * @brief Checks the number of items in the inventory
     * @return true if the inventory is empty otherwise return false
     */
    bool isEmpty() const;

    /**
     * @brief Checks the number of items in inventory
     * @return true if the inventory is full (number of items == capacity) otherwise return false
     */
    bool isFull() const;

    /**
     * @brief Displays the items in inventory and allows to equip/drop items 
     */
    void manage();

    /**
     * @brief Prints the inventory to ostream
     * @param[out] out          ostream to which should be inventory printed
     * @param[in] self          CInventory object which is printed
     * @return std::ostream& with printed inventory
     */
    friend std::ostream & operator<<(std::ostream & out, const CInventory & self);

    /**
     * @brief Loads inventory from istream
     * @param[in] in            istream from which is inventory loaded
     * @param[out] self         CInventory object to which is inventory loaded
     * @return std::istream& with remaining data
     */
    friend std::istream & operator>>(std::istream & in, CInventory & self);
};
