//
// Created by rkindela on 19-01-20.
//

#ifndef HIGHLIFE_GAMEKEYBOARD_H
#define HIGHLIFE_GAMEKEYBOARD_H

#include <vector>

using namespace std;
struct InitialPattern
{
    int birth;
    int alive;

    InitialPattern(int b, int a):birth(b), alive(a){}
    bool checkBirthCondition(int neighbors);
    bool checkAliveCondition(int neighbors);
    bool checkNumber(int base, int target);
};

class HighLife {
private:
    int rows;
    int cols;
    bool** keyboard;
    InitialPattern ipattern;
public:
    HighLife(int _rows, int _cols, int birth = 3, int alive = 23);
    ~HighLife();
    bool cellState(int r, int c);
    int numberOfAliveNeighbors(int r, int c);
    bool updateCellState(int r, int c);
    inline void setCellState(int r, int c, bool state){keyboard[r][c] = state;}
    void run();
};


#endif //HIGHLIFE_GAMEKEYBOARD_H
