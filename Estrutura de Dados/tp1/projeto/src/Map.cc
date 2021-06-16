#include "Map.h"

Map::Map(int rows,int cols){
  this->map = new char*[rows];
  for (int i = 0; i < rows; ++i){
      map[i] = new char[cols];
  }
}

void Map::deleteMap(int rows){
  for (int i = 0; i < rows; ++i)
    delete [] map[i];

  delete [] this->map;
}

void Map::readMap(std::ifstream &mapFile,int rows,int cols){
  char test = 'X';
  int controlRows = 0;
  int controlCols = 0;

  for (int i=0; i<rows*(2*cols)-1; i++ ){
      mapFile.get(test);
      if (test == 'R' || test == 'O'|| test == '.'|| test == 'B'|| test == 'H'){
          map[controlRows][controlCols]=test;
          controlCols++;
          if (controlCols>=cols){
              controlCols=0;
              controlRows++;
        }
      }
  }
}

void Map::printMap(int rows,int cols){
  for (int i=0; i<rows; i++ ){
      for (int j=0; j<cols; j++ ){
          std::cout << map[i][j] << " ";
        }
        std::cout << std::endl;    
    }
}

char Map::checkPlace(int row,int col){
  return this->map[row][col];
}

void Map::updatePlace(char update, int row,int col){
  this->map[row][col]=update;
}