#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <random>
#include "bellman.h"
#include "tsm.h"

using namespace std;
#define numOfVertices 16
int main()
{
    int G[numOfVertices][numOfVertices] = {
    { 0, 84, 23, 57, 12, 69, 31, 46, 78, 28, 95, 41, 60, 17, 52, 33},
    {84,  0, 65, 22, 73, 48,  9, 55, 40, 82, 14,  7, 68, 93, 19, 77},
    {23, 65,  0, 37, 51, 14, 61, 29, 98, 47, 86, 74,  2, 53, 35, 90},
    {57, 22, 37,  0, 88, 30, 49, 59, 13, 71, 25, 81,  6, 92, 54, 16},
    {12, 73, 51, 88,  0, 32, 89, 66,  8, 39, 97, 26, 45, 64, 21, 58},
    {69, 48, 14, 30, 32,  0, 79, 17, 67, 54, 18, 11, 56, 94, 38,  5},
    {31,  9, 61, 49, 89, 79,  0, 36, 92, 20, 75, 58, 29, 80, 27, 41},
    {46, 55, 29, 59, 66, 17, 36,  0, 83, 68, 34, 24, 90, 71, 42, 13},
    {78, 40, 98, 13,  8, 67, 92, 83,  0, 63, 57, 72, 20, 47, 96, 35},
    {28, 82, 47, 71, 39, 54, 20, 68, 63,  0, 88, 53, 15, 99, 61, 26},
    {95, 14, 86, 25, 97, 18, 75, 34, 57, 88,  0, 29, 33, 62, 11, 44},
    {41,  7, 74, 81, 26, 11, 58, 24, 72, 53, 29,  0, 70, 84, 19, 65},
    {60, 68,  2,  6, 45, 56, 29, 90, 20, 15, 33, 70,  0, 95, 43, 79},
    {17, 93, 53, 92, 64, 94, 80, 71, 47, 99, 62, 84, 95,  0, 50, 24},
    {52, 19, 35, 54, 21, 38, 27, 42, 96, 61, 11, 19, 43, 50,  0, 72},
    {33, 77, 90, 16, 58,  5, 41, 13, 35, 26, 44, 65, 79, 24, 72,  0}
};


    char allname[numOfVertices] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P'};
    char startname = 'A';
    char endname = 'P';
    int numOfEdge = 0;
    int edgematrix[numOfVertices * numOfVertices][3];

    for (int i = 0; i < numOfVertices; ++i)
    {
        for (int j = 0; j < numOfVertices; ++j)
        {
            edgematrix[numOfEdge][0] = allname[i];
            edgematrix[numOfEdge][1] = allname[j];
            edgematrix[numOfEdge][2] = G[i][j];
            ++numOfEdge;
        }
    }

    int BellmanFordValue[numOfVertices];
    int BellmanFordPrevious[numOfVertices];
    for (int i = 0; i < numOfVertices; ++i)
    {
        BellmanFordValue[i] = -1;
        BellmanFordPrevious[i] = -1;
    }

    
    for (int i = 0; i < numOfVertices; ++i)
    {
        BF(edgematrix, numOfEdge, startname, BellmanFordValue, BellmanFordPrevious);
    }

    cout << BF_Path(edgematrix, numOfEdge, startname, endname) << endl;

    Traveling(edgematrix, numOfEdge, startname);
    return 0;
}
