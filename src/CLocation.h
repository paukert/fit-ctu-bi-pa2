/**
 * @author Lukas Paukert
 * @date 03.05.2020
 */

#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <map>
#include <memory>

#include "CCreature.h"
#include "COption.h"
#include "CItem.h"

class CLocation {
private:
    static const int MAX_TITLE_LENGTH = 50;
    static const int MAX_TEXT_LENGTH = 800;
    static const int MAX_OPTIONS = 5;

    std::string m_Title;
    std::string m_Text;

    /** All creatures located on this area are stored here, key is creature ID */
    std::map<int, std::unique_ptr<CCreature>> m_Creatures;

    /** All items located on this area are stored here, key is item ID */
    std::map<int, CItem> m_Items;

    /** All possible options for this location are stored here, key is option ID */
    std::map<int, COption> m_Options;

    /**
     * @brief Gets all visible options from this location
     * @return vector of pairs, first is option ID, second is text which describes the option
     */
    std::vector<std::pair<int, std::string>> getOptionsForMenu() const;

    /**
     * @brief Verify options after loading them from file
     * @param[in] options       loaded options
     * @return true if no error was found otherwise returns false
     */
    bool verifyOptions(const std::map<int, COption> & options) const;

    /**
     * @brief Loads all creatures from istream
     * @param[in] in            istream from which should be creatures loaded
     * @param[out] creatures    map to which are creatures saved
     * @return std::istream& with remaining data
     */
    std::istream & loadCreatures(std::istream & in, std::map<int, std::unique_ptr<CCreature>> & creatures);

    /**
     * @brief Loads all items located on this location from istream
     * @param[in] in            istream from which should be items loaded
     * @param[out] items        map to which are items saved
     * @return std::istream& with remaining data
     */
    std::istream & loadItems(std::istream & in, std::map<int, CItem> & items);

    /**
     * @brief Loads all options of this location from istream
     * @param[in] in            istream from which should be options loaded
     * @param[out] options      map to which are options saved
     * @return std::istream& with remaining data
     */
    std::istream & loadOptions(std::istream & in, std::map<int, COption> & options);

public:
    CLocation() = default;

    /**
     * @brief Prints story (m_Text variable) and allows player to choose one option from menu
     * @return ID of selected option
     */
    int chooseOption() const;

    /**
     * @brief Getter for specific creature
     * @param[in] creatureID    ID of creature to get
     * @return CCreature& with specified ID
     */
    CCreature & getCreature(int creatureID);

    /**
     * @brief Getter for specific item
     * @param[in] itemID        ID of item to get
     * @return CItem& with specified ID
     */
    CItem & getItem(int itemID);

    /**
     * @brief Getter for specific option
     * @param[in] optionID      ID of option to get
     * @return COption& with specified ID
     */
    COption & getOption(int optionID);

    /**
     * @brief Getter for m_Options variable
     */
    std::map<int, COption> getOptions() const;

    /**
     * @brief Remove creature from m_Creatures
     * @param[in] creatureID    ID of creature to remove
     */
    void removeCreature(int creatureID);

    /**
     * @brief Remove item from m_Items
     * @param[in] itemID        ID of item to remove
     */
    void removeItem(int itemID);

    /**
     * @brief Remove option from m_Options
     * @param[in] optionID      ID of option to remove
     */
    void removeOption(int optionID);

    /**
     * @brief Prints location to ostream
     * @param[out] out          ostream to which should be location printed
     * @param[in] self          location which should be printed
     * @return std::ostream& with printed location
     */
    friend std::ostream & operator<<(std::ostream & out, const CLocation & self);

    /**
     * @brief Loads location from istream
     * @param[in] in            istream from which should be location loaded
     * @param[out] self         CLocation object to which should be location loaded
     * @return std::istream& with remaining data
     */
    friend std::istream & operator>>(std::istream & in, CLocation & self);
};
