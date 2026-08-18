#ifndef DELETERECORD_H
#define DELETERECORD_H

#include <SFML/Graphics.hpp>
#include "PatientList.h"

class DeleteRecord {
public:
    static void execute(sf::RenderWindow& window, sf::Font& font, PatientList& patientList);
};

#endif
