//
// Created by guy on 16/01/2020.
//

#ifndef MILSTONE2__CELL_H_
#define MILSTONE2__CELL_H_

#include "Position.h"
class Cell {

  Position _position;
  int _value;

 public:
  Cell(const Position& position, int value) : _position(position), _value(value) {}
  const Position& GetPosition() const { return _position; }
  int getValue() const { return _value; }
  void setValue(int value) { _value = value; }

};

#endif //MILSTONE2__CELL_H_
