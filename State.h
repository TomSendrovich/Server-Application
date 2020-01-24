//
// Created by guy on 13/01/2020.
//

#ifndef MILSTONE2__STATE_H_
#define MILSTONE2__STATE_H_
template<typename T>
class State {

  T _state;
  State<T>* _parent;
  int _cost, _pathCost, _heuristicCost;
  bool _isDiscovered;

  void setCost(int cost) { _cost = cost; }

 public:
  State(T state) : _state(state) {
    setParent(nullptr);
    setIsDiscovered(false);
    setCost(state->getValue());
    setPathCost(state->getValue());
  }
  ~State() = default;
  //void setState(T cell) { _state = cell; }
  State<T>* getParent() { return _parent; }
  void setParent(State<T>* parent) { _parent = parent; }
  int getCost() { return _cost; }
  int getPathCost() { return _pathCost; }
  void setPathCost(int pathCost) { _pathCost = pathCost; }
  void setIsDiscovered(bool is_discovered) { _isDiscovered = is_discovered; }
  bool isDiscovered() { return _isDiscovered; }
  T getState() { return _state; }
  int getHeuristicCost() const { return _heuristicCost; }
  void setHeuristicCost(int heuristic_cost) { _heuristicCost = heuristic_cost; }
  bool operator==(State<T>* other) {
    int oneR = _state->getPosition().first;
    int oneC = _state->getPosition().second;
    T cell = other->getState();
    int twoR = cell->getPosition().first;
    int twoC = cell->getPosition().second;

    return oneR == twoR && oneC == twoC;
  }
};

#endif //MILSTONE2__STATE_H_

