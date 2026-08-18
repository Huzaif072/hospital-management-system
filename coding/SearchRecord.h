#ifndef SEARCHRECORD_H
#define SEARCHRECORD_H

#include <SFML/Graphics.hpp>
#include "PatientList.h"

class SearchRecord {
public:
    static void execute(sf::RenderWindow& window, sf::Font& font, PatientList& patientList);
};

#endif
