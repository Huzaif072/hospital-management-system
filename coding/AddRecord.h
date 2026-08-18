#ifndef ADDRECORD_H
#define ADDRECORD_H

#include <SFML/Graphics.hpp>
#include "PatientList.h"

class AddRecord {
public:
    static void execute(sf::RenderWindow& window, sf::Font& font, PatientList& patientList);
};

#endif
