#ifndef EDITRECORD_H
#define EDITRECORD_H

#include <SFML/Graphics.hpp>
#include "PatientList.h"

class EditRecord {
public:
    static void execute(sf::RenderWindow& window, sf::Font& font, PatientList& patientList);
};

#endif