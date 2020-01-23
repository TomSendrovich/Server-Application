//
// Created by guy on 18/01/2020.
//
#include "MatrixProblem.h"
#include "Cell.h"
#define WALL -1

MatrixProblem::MatrixProblem(vector<vector<string>> matrix, Cell* init, Cell* goal, int size) {
  _size = size;
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
bool MatrixProblem::isGoalState(State<Cell*>* state) { return state == _goalState; }
list<State<Cell*>*> MatrixProblem::getAllPossibleStates(State<Cell*>* state) {

  list<State<Cell*>*> list;

  int row = state->getState()->getRow();
  int col = state->getState()->getCol();

  if (isValidPosition(row - 1, col - 1)) {
    Cell* c = getCell(row - 1, col - 1);
    if (c->getValue() != WALL) {
      list.push_back(new State<Cell*>(c));
    }
  }
  if (isValidPosition(row - 1, col)) {
    Cell* c = getCell(row - 1, col);
    if (c->getValue() != WALL) {
      list.push_back(new State<Cell*>(c));
    }
  }
  if (isValidPosition(row - 1, col + 1)) {
    Cell* c = getCell(row - 1, col + 1);
    if (c->getValue() != WALL) {
      list.push_back(new State<Cell*>(c));
    }
  }
  if (isValidPosition(row, col - 1)) {
    Cell* c = getCell(row, col - 1);
    if (c->getValue() != WALL) {
      list.push_back(new State<Cell*>(c));
    }
  }
  if (isValidPosition(row, col + 1)) {
    Cell* c = getCell(row, col + 1);
    if (c->getValue() != WALL) {
      list.push_back(new State<Cell*>(c));
    }
  }
  if (isValidPosition(row + 1, col - 1)) {
    Cell* c = getCell(row + 1, col - 1);
    if (c->getValue() != WALL) {
      list.push_back(new State<Cell*>(c));
    }
  }
  if (isValidPosition(row + 1, col)) {
    Cell* c = getCell(row + 1, col);
    if (c->getValue() != WALL) {
      list.push_back(new State<Cell*>(c));
    }
  }
  if (isValidPosition(row + 1, col + 1)) {
    Cell* c = getCell(row + 1, col + 1);
    if (c->getValue() != WALL) {
      list.push_back(new State<Cell*>(c));
    }
  }

  return list;
}
bool MatrixProblem::isValidPosition(int row, int col) {
  int size = getMatrixSize();
  return !(row == -1 || row == size || col == -1 || col == size);
}
string MatrixProblem::to_string() { return "MatrixProblem"; }
int MatrixProblem::getMatrixSize() { return _size; }
vector<vector<Cell*>> MatrixProblem::getMatrix() { return _matrix; }
Cell* MatrixProblem::getCell(int row, int col) { return getMatrix().at(row).at(col); }
int MatrixProblem::hashFunc(vector<vector<string>> matrix) {
  int counter = 1;
  int sum = 0;

  for (auto& row : matrix) {
    for (string strValue : row) {
      int integerValue = stoi(strValue);
      sum += integerValue * counter;
      sum = sum % C;
      counter++;
    }
  }

  return sum;
}
