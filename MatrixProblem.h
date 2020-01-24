//
// Created by guy on 16/01/2020.
//

#ifndef MILSTONE2__MATRIXPROBLEM_H_
#include <vector>
#include <string>
#include "Searchable.h"
#include "Cell.h"
#define MILSTONE2__MATRIXPROBLEM_H_

class MatrixProblem : public Searchable<Cell*> {

  vector<vector<Cell*>> _matrix;
  State<Cell*>* _initState, * _goalState;
  int _size;

 public:

  MatrixProblem(vector<vector<string>> matrix, Cell* init, Cell* goal, int size);

  //override functions
  State<Cell*>* getInitialState() override;
  State<Cell*>* getGoalState() override;
  bool isGoalState(State<Cell*>* state) override;
  list<State<Cell*>*> getAllPossibleStates(State<Cell*>* state) override;

  void initMatrix(vector<vector<string>> matrix);
  int getMatrixSize();
  vector<vector<Cell*>> getMatrix();
  Cell* getCell(int row, int col);
  bool isValidPosition(int row, int col);
};

#endif //MILSTONE2__MATRIXPROBLEM_H_
