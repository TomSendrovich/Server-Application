//
// Created by guy on 13/01/2020.
//

#ifndef MILSTONE2__STATE_H_
#define MILSTONE2__STATE_H_
template<typename T>
class State {

  T _state;
  State<T>* _parent;
  int _cost, _pathCost;
  bool _isDiscovered;

 public:
  State(T state) : _state(state) {
    setParent(nullptr);
    setIsDiscovered(false);
  }
  ~State() = default;
  //void setState(T cell) { _state = cell; }
  State<T>* getParent() { return _parent; }
  void setParent(State<T>* parent) { _parent = parent; }
  int getCost() { return _cost; }
  //void setCost(int cost) { _cost = cost; }
  int getPathCost() { return _pathCost; }
  void setPathCost(int pathCost) { _pathCost = pathCost; }
  void setIsDiscovered(bool is_discovered) { _isDiscovered = is_discovered; }
  bool isDiscovered() { return _isDiscovered; }
  T getState() { return _state; }
  bool operator==(const State<T>* other) { return (_state == other->state); }
};

#endif //MILSTONE2__STATE_H_

