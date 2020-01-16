//
// Created by guy on 13/01/2020.
//

#ifndef MILSTONE2__STATE_H_
//using namespace std;
#define MILSTONE2__STATE_H_
#include "Position.h"
template<typename T>
class State {

  T _cell;
  State<T> _parent;
  int _weight; //values of all parents, included this cell

 public:
  State(T cell, const State<T>& parent, int weight) : _cell(cell), _parent(parent), _weight(weight) {}
  T getCell() const { return _cell; }
  void setCell(T cell) { _cell = cell; }
  const State<T>& getParent() const { return _parent; }
  void setParent(const State<T>& parent) { _parent = parent; }
  int getWeight() const { return _weight; }
  void setWeight(int weight) { _weight = weight; }
};

#endif //MILSTONE2__STATE_H_
