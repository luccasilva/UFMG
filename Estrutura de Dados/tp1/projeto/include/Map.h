#ifndef MAP_H
#define MAP_H

#include <string>
#include <iostream>
#include <fstream>

class Map {

  public:
    Map(int rows, int cols);
    void deleteMap(int rows);
    void readMap(std::ifstream &mapFile,int rows,int cols);
    void printMap(int rows,int cols);
    void getHeight(std::string info);
    void getWidth(std::string info);
    char checkPlace(int row,int col);
    void updatePlace(char update, int row,int col);

  private:
    char **map;

};

#endif