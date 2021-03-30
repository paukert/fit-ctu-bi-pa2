/**
 * @author Lukas Paukert
 * @date 03.05.2020
 */

#pragma once

#include <string>
#include <map>
#include <iostream>

#include "EGameStatus.h"
#include "CLocation.h"
#include "CPlayer.h"

class CGame {
private:
    static const int MAX_NAME_LENGTH = 40;

    /** Name of the game */
    std::string m_GameName;
    /** Author of the game */
    std::string m_Author;
    /** Path to the file, where should be game saved */
    std::string m_SavePath;
    EGameStatus m_GameStatus = EGameStatus::CREATING_CHARACTER;
    /** ID of the final location, when player reaches it, the game ends */
    int m_EndLocation = 0;

    CPlayer m_Player;

    /** All locations are stored in this map, key is location ID */
    std::map<int, CLocation> m_Locations;

    /**
     * @brief Checks the current game status
     * @return true if game status is CREATING_CHARACTER otherwise returns false
     */
    bool isCreatingCharacter() const;

    /**
     * @brief Verify options for TRAVEL action to non existing location
     * @return true if no error is found otherwise returns false
     */
    bool verifyOptions(const std::map<int, CLocation> & locations) const;

    /**
     * @brief Displays concrete location and handles it's actions
     * @param[in] locationID    ID of location which should be managed
     * @return true if should be displayed some location in next loop otherwise returns false (game ends)
     */
    bool manageLocation(int locationID);

    /**
     * @brief Method that saves current game into save file
     * @param[in] filePath      path to file where the game should be saved
     * @return true if was saving successful otherwise returns false
     */
    bool save(const std::string & filePath) const;

public:
    CGame() = default;

    /**
     * @brief Method that starts the main game loop
     */
    void run();

    /**
     * @brief Setter for member variable m_SavePath
     * @param[in] path          path to file, where should be game saved
     */
    void setSavePath(const std::string & path);

    /**
     * @brief Handles loading game from file
     * @param[in] filePath      path to the file, from which should be game loaded
     * @return true if the game was loaded successfully otherwise returns false
     */
    bool load(const std::string & filePath);

    /**
     * @brief Prints whole game to ostream
     * @param[out] out          ostream to which should be game printed
     * @param[in] self          CGame object which is printed
     * @return std::ostream& with printed game
     */
    friend std::ostream & operator<<(std::ostream & out, const CGame & self);

    /**
     * @brief Loads the game from istream
     * @param[in] in            istream from which is game loaded
     * @param[out] self         CGame object to which is game loaded
     * @return std::istream& with remaining data
     */
    friend std::istream & operator>>(std::istream & in, CGame & self);
};
