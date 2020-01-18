//
// Created by guy on 13/01/2020.
//

#ifndef MILSTONE2__STATE_H_
#include "Position.h"
#define MILSTONE2__STATE_H_
template<typename T>
class State {

  T _state;
  State<T> _parent;
  double _cost; //values of all parents, included this cell

 public:
  //State(T cell, const State<T>& parent, double cost) : _state(cell), _parent(parent), _cost(cost) {}
  State(T state) : _state(state) {}
  void setState(T cell) { _state = cell; }
  const State<T>& getParent() const { return _parent; }
  void setParent(const State<T>& parent) { _parent = parent; }
  double getCost() const { return _cost; }
  void setCost(int cost) { _cost = cost; }
  T getState() const { return _state; }

  virtual bool equals(State<T>& other) = 0;
};

#endif //MILSTONE2__STATE_H_

