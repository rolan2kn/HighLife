//
// Created by rkindela on 19-01-20.
//

#include "HighLife.h"
#include <cmath>


HighLife::HighLife(int _rows, int _cols, int birth, int alive)
:rows(_rows), cols(_cols), ipattern(birth, alive)
{
    this->keyboard = new bool* [rows];
    for (int i = 0; i < rows; i++)
    {
        this->keyboard[i] = new bool[cols];
        for (int j = 0; j < cols;j++)
            this->keyboard[i][j] = false;
    }
}

HighLife::~HighLife()
{
    for (int i = 0; i < rows; i++)
    {
        delete [] this->keyboard;
    }
    delete [] this->keyboard;
}

bool HighLife::cellState(int r, int c)
{
    if (r < 0 || r > rows)
        throw "array overflow";
    if (c < 0 || c > cols)
        throw "array overflow";

    return this->keyboard[r][c];
}

int HighLife::numberOfAliveNeighbors(int r, int c)
{
    int col_n[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int row_n[8] = {0, -1, -1, -1, 0, 1, 1, 1};

    int neighbors = 0;
    for (int idx = 0; idx < 8; idx++)
    {
        int nc = (col_n[idx] + c)%cols;
        int nr = (row_n[idx] + r)%rows;

        if (nc > -1 && nc < cols && nr > -1 && nr < rows)
        {
            if (keyboard[nr][nc])
                ++neighbors;
        }
    }

    return neighbors;
}

bool HighLife::updateCellState(int r, int c)
{
    /**
     * 1. Una célula nace de un espacio muerto si tiene 3 vecinos vivos.
     * 2. Una célula sobrevive en la próxima generación si tiene 2 o 3 vecinos.
     * */

    bool currentState = this->cellState(r, c);
    int neighbors = this->numberOfAliveNeighbors(r, c);

    if (!currentState)
    {
        if (ipattern.checkBirthCondition(neighbors)) // nace si tiene 3 vecinos vivos
        {
            currentState = true;
            keyboard[r][c] = currentState;
        }
    }
    else
    {
        currentState = false;       // muere
        if (ipattern.checkAliveCondition(neighbors))   // a menos que tenga 2 o 3 vecinos
        {
            currentState = true;
        }
    }

    return currentState;
}

void HighLife::run()
{
    bool** newGeneration = new bool*[rows];
    for (int i = 0; i < rows; i++)
    {
        newGeneration[i] = new bool[cols];
        for (int j = 0; j < cols; j++)
        {
            newGeneration[i][j] = this->updateCellState(i, j);
        }
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            keyboard[i][j] = newGeneration[i][j];
        }
        delete [] newGeneration[i];
    }
    delete [] newGeneration;
}


bool InitialPattern::checkBirthCondition(int neighbors)
{
    return this->checkNumber(birth, neighbors);
}

bool InitialPattern::checkAliveCondition(int neighbors)
{
    return this->checkNumber(alive, neighbors);
}

bool InitialPattern::checkNumber(int base, int target)
{
    if (base == target)
        return true;
    if (base == 0)
        return false;

    int cipher_number = ceil(log10(base))-1;
    bool was_found = false;

    int base_clon = base;
    while(cipher_number > -1 && !was_found)
    {
        int pow_num = pow(10, cipher_number);
        int digit = base_clon / pow_num;
        was_found = digit == target;
        base_clon %= pow_num;
        --cipher_number;
    }
    return was_found;
}