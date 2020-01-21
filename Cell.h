//
// Created by guy on 16/01/2020.
//

#ifndef MILSTONE2__CELL_H_
#include <utility>
using namespace std;
#define MILSTONE2__CELL_H_

class Cell {

  pair<int,int> _position;
  int _value;

 public:
  Cell(pair<int, int> position, int value);
  pair<int, int> getPosition();
  int getRow();
  int getCol();
  int getValue();
  void setValue(int value);
  ~Cell() = default;
  bool equal(Cell* other);

};

#endif //MILSTONE2__CELL_H_
