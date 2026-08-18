#ifndef DISPLAYRECORD_H
#define DISPLAYRECORD_H

#include <SFML/Graphics.hpp>
#include "PatientList.h"

class DisplayRecord {
public:
    static void execute(sf::RenderWindow& window, sf::Font& font, PatientList& patientList);
};

#endif