//
// Created by guy on 18/01/2020.
//

#include "Cell.h"

Cell::Cell(pair<int, int> position, int value) {
  _position = position;
  _value = value;
}
int Cell::getValue() { return _value; }
void Cell::setValue(int value) { _value = value; }
pair<int, int> Cell::getPosition() { return _position; }
int Cell::getRow() { return getPosition().first; }
int Cell::getCol() { return getPosition().second; }
bool Cell::equal(Cell* other) { return this->getPosition() == other->getPosition(); }
