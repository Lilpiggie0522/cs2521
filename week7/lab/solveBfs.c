// BFS maze solver

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cell.h"
#include "matrix.h"
#include "Maze.h"
#include "Queue.h"
bool checkInBounds(Maze m, int row, int col);
bool checkVisited(bool **visited, int row, int col);
void neibourOperation(Item w, Maze m, bool **visited, struct cell **predecessor, Queue q, Item v);
bool solve(Maze m) {
    // TODO: Complete this function
    //       Feel free to add helper functions
    int rowNum = MazeHeight(m);
    int columnNum = MazeWidth(m);
    //  strores true or false to see if a cell is wall
    bool **visited = createBoolMatrix(rowNum, columnNum);
    visited[0][0] = false;
    visited[rowNum - 1][columnNum - 1] = false;
    struct cell **predecessor = createCellMatrix(rowNum, columnNum);

    //  grab maze entry
    struct cell src = MazeGetStart(m);
    
    //  no path if entry is a wall, error
    if (MazeIsWall(m, src)) {
        return false;
    }

    Queue q = QueueNew();
    QueueEnqueue(q, src);
    visited[src.row][src.col] = true;
    predecessor[src.row][src.col] = src;
    while (!QueueIsEmpty(q)) { //   v
        Item v = QueueDequeue(q);
        if (!MazeIsWall(m, v)) {
            if (MazeVisit(m, v)) {
                struct cell curr = v;
                MazeMarkPath(m, v);
                while ((curr.row != src.row) || (curr.col != src.col)) {
                    curr = predecessor[curr.row][curr.col];
                    MazeMarkPath(m, curr);
                }
                freeBoolMatrix(visited);
                freeCellMatrix(predecessor);
                QueueFree(q);
                return true;
            }
        }
        //  up
        Item w = {v.row + 1, v.col};
        neibourOperation(w, m, visited, predecessor, q, v);
        //  down
        Item h = {v.row - 1, v.col};
        neibourOperation(h, m, visited, predecessor, q, v);
        //  left
        Item l = {v.row, v.col - 1};
        neibourOperation(l, m, visited, predecessor, q, v);
        //  right
        Item f = {v.row, v.col + 1};
        neibourOperation(f, m, visited, predecessor, q, v);
    }
    freeBoolMatrix(visited);
    freeCellMatrix(predecessor);
    QueueFree(q);
    return false;
}

bool checkInBounds(Maze m, int row, int col) {
    int rowNum = MazeHeight(m);
    int columnNum = MazeWidth(m);
    if (row < 0 || row > rowNum - 1 ) {
        return false;
    }
    if (col < 0 || col > columnNum - 1) {
        return false;
    }
    return true;
}

bool checkVisited(bool **visited, int row, int col) {
    if (visited[row][col]) {
        return true;
    }
    return false;
}

void neibourOperation(Item w, Maze m, bool **visited, struct cell **predecessor, Queue q, Item v) {
    
    if (checkInBounds(m, w.row, w.col)) {
        if (MazeIsWall(m, w)) {
            return;
        }
        if (!checkVisited(visited, w.row, w.col)) { // 1
            visited[w.row][w.col] = true;
            predecessor[w.row][w.col] = v;
            QueueEnqueue(q, w);
        }
    }
}