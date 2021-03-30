/**
 * @author Lukas Paukert
 * @date 21.05.2020
 */

#include <stdexcept>

#include "EAction.h"

using namespace std;

std::ostream & operator<<(ostream & out, const EAction & self) {

    string value;
    if (self == EAction::FIGHT)
        value = "FIGHT";
    else if (self == EAction::TRAVEL)
        value = "TRAVEL";
    else if (self == EAction::PICK_UP)
        value = "PICK_UP";
    else
        // Never should happen
        throw logic_error("This option type should NOT be included in the save file");

    out << value;
    return out;
}

istream & operator>>(istream & in, EAction & self) {

    string loadedAction;
    if (!(in >> loadedAction))
        return in;

    if (loadedAction == "FIGHT")
        self = EAction::FIGHT;
    else if (loadedAction == "PICK_UP")
        self = EAction::PICK_UP;
    else if (loadedAction == "TRAVEL")
        self = EAction::TRAVEL;
    else
        in.setstate(ios::failbit);

    return in;
}
