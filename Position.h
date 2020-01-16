//
// Created by guy on 16/01/2020.
//

#ifndef MILSTONE2__POSITION_H_
#define MILSTONE2__POSITION_H_

class Position {
  int _row, _col;

 public:
  Position(int row, int col) : _row(row), _col(col) {}
  int getRow() const { return _row; }
  void setRow(int row) { _row = row; }
  int getCol() const { return _col; }
  void setCol(int col) { _col = col; }
};

#endif //MILSTONE2__POSITION_H_
