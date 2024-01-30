// DFS maze solver

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cell.h"
#include "matrix.h"
#include "Maze.h"
#include "Stack.h"
bool checkVisited(struct cell v, bool **visited);
bool checkInBounds(Maze m, struct cell v);

bool solve(Maze m) {
    // TODO: Complete this function
    //       Feel free to add helper functions
    int rowNum = MazeHeight(m);
    int columnNum = MazeWidth(m);
    bool **visited = createBoolMatrix(rowNum, columnNum);
    visited[0][0] = false;
    visited[rowNum - 1][columnNum - 1] = false;
    struct cell **predecessor = createCellMatrix(rowNum, columnNum);
    //  grab maze entry
    Item src = MazeGetStart(m);
    //  no path if entry is a wall, error
    if (MazeIsWall(m, src)) {
        return false;
    }
    Stack s = StackNew();
    StackPush(s, src);
    while (!StackIsEmpty(s)) {
        Item v = StackPop(s);
        if (checkVisited(v, visited)) { //  1
            continue;
        }
        if (MazeVisit(m, v)) {
            struct cell curr = v;
            MazeMarkPath(m, v);
            while ((curr.row != src.row) || (curr.col != src.col)) { // v
                curr = predecessor[curr.row][curr.col];
                MazeMarkPath(m, curr);
            }
            freeBoolMatrix(visited);
            freeCellMatrix(predecessor);
            StackFree(s);
            return true;
        }
        
        visited[v.row][v.col] = true;
        //  for all edges of v, denoted as w, check if w has been visited, if not push to stack
        //  up
        Item w = {v.row + 1, v.col};
        if (checkInBounds(m, w)) {  //  1
            if (!MazeIsWall(m, w)) {
                if (!checkVisited(w, visited)) {
                    predecessor[w.row][w.col] = v;
                    StackPush(s, w);
                }  
            }
        }
        //  down
        Item x = {v.row - 1, v.col};
        if (checkInBounds(m, x)) {
            if (!MazeIsWall(m, x)) {
                if (!checkVisited(x, visited)) {
                    predecessor[x.row][x.col] = v;
                    StackPush(s, x);
                }
            }
        }
        //  right
        Item y = {v.row, v.col + 1};
        if (checkInBounds(m, y)) {
            if (!MazeIsWall(m, y)) {
                if (!checkVisited(y, visited)) {
                    predecessor[y.row][y.col] = v;
                    StackPush(s, y);
                }
            }
        }
        //  left
        Item z = {v.row, v.col - 1};
        if (checkInBounds(m, z)) {
            if (!MazeIsWall(m, z)) {
                if (!checkVisited(z, visited)) {
                    predecessor[z.row][z.col] = v;
                    StackPush(s, z);
                }
            }
        }
    }
    freeBoolMatrix(visited);
    freeCellMatrix(predecessor);
    StackFree(s);
    return false;
}

bool checkVisited(struct cell v, bool **visited) {
    if (visited[v.row][v.col]) {
        return true;
    }
    return false;
}

bool checkInBounds(Maze m, struct cell v) {
    int rowNum = MazeHeight(m);
    int columnNum = MazeWidth(m);
    if (v.row < 0 || v.row > rowNum - 1 ) {
        return false;
    }
    if (v.col < 0 || v.col > columnNum - 1) {
        return false;
    }
    return true;
}