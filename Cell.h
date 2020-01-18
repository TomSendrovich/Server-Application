//
// Created by guy on 16/01/2020.
//

#ifndef MILSTONE2__CELL_H_
#include "Position.h"
#define MILSTONE2__CELL_H_

class Cell {

  Position _position = Position(0, 0);
  int _value;

 public:
  Cell(Position position, int value) {
    _position = position;
    _value = value;
  }
 /* Cell(int row, int col, int value) {
    _position = new Position(row, col);
    _value = value;
  }*/
  const Position& GetPosition() const { return _position; }
  int getValue() const { return _value; }
  void setValue(int value) { _value = value; }

};

#endif //MILSTONE2__CELL_H_
