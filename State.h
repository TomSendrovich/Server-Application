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
  double _cost;
  bool isDiscovered;

 public:
  //State(T cell, const State<T>& parent, double cost) : _state(cell), _parent(parent), _cost(cost) {}
  State(T state) : _state(state) {
    isDiscovered=false;
  }
  void setState(T cell) { _state = cell; }
  const State<T>& getParent() const { return _parent; }
  void setParent(const State<T>& parent) { _parent = parent; }
  double getCost() const { return _cost; }
  void setCost(int cost) { _cost = cost; }
  void setIsDiscovered(bool is_discovered) {
    isDiscovered = is_discovered;
  }
  bool getIsDiscovered() const {
    return isDiscovered;
  }
  T getState() const { return _state; }

  bool equals(State<T>& other) {
    return _state.getPosition.getRow() == other.getState().getPosition().getRow()
        && _state.getPosition.getCol() == other.getState().getPosition().getCol();
  }
};

#endif //MILSTONE2__STATE_H_

