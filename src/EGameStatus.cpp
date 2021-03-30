/**
 * @author Lukas Paukert
 * @date 20.05.2020
 */

#include <stdexcept>

#include "EGameStatus.h"

using namespace std;

ostream & operator<<(ostream & out, const EGameStatus & self) {

    string value;
    if (self == EGameStatus::RUNNING)
        value = "RUNNING";
    else
        // Never should happen
        throw logic_error("It is NOT possible to save finished game");

    out << value;
    return out;
}

istream & operator>>(istream & in, EGameStatus & self) {

    string loadedStatus;
    if (!(in >> loadedStatus))
        return in;

    if (loadedStatus == "CREATING_CHARACTER")
        self = EGameStatus::CREATING_CHARACTER;
    else if (loadedStatus == "RUNNING")
        self = EGameStatus::RUNNING;
    else
        in.setstate(ios::failbit);

    return in;
}
