#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

void BF(int edgeList[][3],int numEdges,char start_vertices,int BFValue[],int BFPrev[]);
string BF_Path(int edge[][3], int numberOfEdges, char startVertex, char goalVertex);

