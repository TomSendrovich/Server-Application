//
// Created by guy on 18/01/2020.
//
#include "MatrixProblem.h"
#include "Cell.h"
#define WALL -1

MatrixProblem::MatrixProblem(vector<vector<string>> matrix, Cell* init, Cell* goal, int rowSize, int colSize) {
  _rowSize = rowSize;
  _colSize = colSize;
  auto* initState = new State<Cell*>(init);
  auto* goalState = new State<Cell*>(goal);
  _initState = initState;
  _goalState = goalState;
  initMatrix(matrix);
}

void MatrixProblem::initMatrix(vector<vector<string>> matrix) {
  vector<vector<Cell*>> newMatrix;
  vector<Cell*> matrixRow;

  int rowIndex = 0, colIndex = 0;
  for (auto& row : matrix) {
    colIndex = 0;
    for (string strValue : row) {
      int integerValue = stoi(strValue);
      Cell* c = new Cell(pair<int, int>(rowIndex, colIndex), integerValue);
      matrixRow.push_back(c);
      colIndex++;
    }
    newMatrix.push_back(matrixRow);
    matrixRow.clear();
    rowIndex++;
  }

  _matrix = newMatrix;
}

State<Cell*>* MatrixProblem::getInitialState() { return _initState; }
State<Cell*>* MatrixProblem::getGoalState() { return _goalState; }
bool MatrixProblem::isGoalState(State<Cell*>* state) {
  int oneR = state->getState()->getRow();
  int oneC = state->getState()->getCol();
  int twoR = _goalState->getState()->getRow();
  int twoC = _goalState->getState()->getCol();

  return oneR == twoR && oneC == twoC;
}
list<State<Cell*>*> MatrixProblem::getAllPossibleStates(State<Cell*>* state) {

  list<State<Cell*>*> list;

  int row = state->getState()->getRow();
  int col = state->getState()->getCol();

  ///up successor
  if (isValidPosition(row - 1, col)) {
    Cell* c = getCell(row - 1, col);
    if (c->getValue() != WALL) {
      auto* successor = new State<Cell*>(c);
      successor->setParent(state);
      list.push_back(successor);
    }
  }

  ///left successor
  if (isValidPosition(row, col - 1)) {
    Cell* c = getCell(row, col - 1);
    if (c->getValue() != WALL) {
      auto* successor = new State<Cell*>(c);
      successor->setParent(state);
      list.push_back(successor);
    }
  }

  ///right successor
  if (isValidPosition(row, col + 1)) {
    Cell* c = getCell(row, col + 1);
    if (c->getValue() != WALL) {
      auto* successor = new State<Cell*>(c);
      successor->setParent(state);
      list.push_back(successor);
    }
  }

  ///down successor
  if (isValidPosition(row + 1, col)) {
    Cell* c = getCell(row + 1, col);
    if (c->getValue() != WALL) {
      auto* successor = new State<Cell*>(c);
      successor->setParent(state);
      list.push_back(successor);
    }
  }

  return list;
}
bool MatrixProblem::isValidPosition(int row, int col) {
  return !(row == -1 || row == _rowSize || col == -1 || col == _colSize);
}
vector<vector<Cell*>> MatrixProblem::getMatrix() { return _matrix; }
Cell* MatrixProblem::getCell(int row, int col) { return getMatrix().at(row).at(col); }
int MatrixProblem::getMatrixRowSize() { return _rowSize; }
int MatrixProblem::getMatrixColSize() { return _colSize; }

