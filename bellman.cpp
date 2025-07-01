#include "bellman.h"

void BF(int edgeList[][3], int numEdges, char start_vertices, int BFValue[], int BFPrev[])
{
    int num_vertices = 0;

    int **edge1 = new int *[numEdges];
    for (int i = 0; i < numEdges; ++i)
    {
        edge1[i] = new int[3];
        edge1[i][0] = edgeList[i][0];
        edge1[i][1] = edgeList[i][1];
        edge1[i][2] = edgeList[i][2];
    }

    int countarr[256];
    for (int i = 0; i < 256; ++i)
    {
        countarr[i] = -1;
    }
    for (int i = 0; i < numEdges; ++i)
    {
        ++countarr[edge1[i][0]];
        ++countarr[edge1[i][1]];
    }

    int mark = 0;

    for (int i = 0; i < 256; ++i)
    {
        if (countarr[i] != -1)
        {
            ++num_vertices;
            countarr[i] = mark++;
        }
    }

    if (countarr[start_vertices] == -1)
    {
        BFPrev[num_vertices - 1] = 0;
        for (int i = 0; i < numEdges; ++i)
        {
            delete[] edge1[i];
        }
        delete[] edge1;
        return;
    }

    for (int i = 0; i < numEdges; ++i)
    {
        edge1[i][0] = countarr[edge1[i][0]];
        edge1[i][1] = countarr[edge1[i][1]];
    }

    int **G = new int *[num_vertices];
    for (int i = 0; i < num_vertices; ++i)
    {
        G[i] = new int[num_vertices]{};
    }

    for (int j = 0; j < numEdges; ++j)
    {
        G[edge1[j][0]][edge1[j][1]] = edge1[j][2];
    }

    int start;
    start = countarr[start_vertices];
    if (BFValue[start] == -1)
    {
        BFValue[start] = 0;
        for (int i = 0; i < num_vertices; ++i)
        {
            if (BFValue[i] == -1 && G[start][i] > 0)
            {
                BFValue[i] = G[start][i];
                BFPrev[i] = start;
            }
        }
        for (int i = 0; i < num_vertices; ++i)
        {
            delete[] G[i];
        }
        delete[] G;
        for (int i = 0; i < numEdges; ++i)
        {
            delete[] edge1[i];
        }
        delete[] edge1;
        return;
    }
    int *Tempvalue = new int[num_vertices];
    for (int i = 0; i < num_vertices; ++i)
    {
        Tempvalue[i] = BFValue[i];
    }

    for (int u = 0; u < num_vertices; ++u)
    {
        if (Tempvalue[u] != -1)
        {
            for (int v = 0; v < num_vertices; ++v)
            {

                if (G[u][v] != 0)
                {
                    if ((G[u][v] + Tempvalue[u] < BFValue[v]) || BFValue[v] == -1)
                    {
                        BFValue[v] = G[u][v] + Tempvalue[u];
                        BFPrev[v] = u;
                    }
                }
            }
        }
    }
    delete[] Tempvalue;
    for (int i = 0; i < num_vertices; ++i)
    {
        delete[] G[i];
    }
    delete[] G;
    for (int i = 0; i < numEdges; ++i)
    {
        delete[] edge1[i];
    }
    delete[] edge1;
}
string BF_Path(int edge[][3], int numberOfEdges, char startVertex, char goalVertex)
{

    int **edge1 = new int *[numberOfEdges];
    for (int i = 0; i < numberOfEdges; ++i)
    {
        edge1[i] = new int[3];
        edge1[i][0] = edge[i][0];
        edge1[i][1] = edge[i][1];
        edge1[i][2] = edge[i][2];
    }

    int num_vertices = 0;
    int countarr[256]{};
    for (int i = 0; i < 256; ++i)
    {

        countarr[i] = -1;
    }
    for (int i = 0; i < numberOfEdges; ++i)
    {
        ++countarr[edge1[i][0]];
        ++countarr[edge1[i][1]];
    }

    int mark = 0;

    for (int i = 0; i < 256; ++i)
    {
        if (countarr[i] != -1)
        {
            ++num_vertices;
            countarr[i] = mark++;
        }
    }

    if (countarr[startVertex] == -1)
    {
        for (int i = 0; i < numberOfEdges; ++i)
        {
            delete[] edge1[i];
        }
        delete[] edge1;
        string s;
        return s;
    }

    for (int i = 0; i < numberOfEdges; ++i)
    {
        edge1[i][0] = countarr[edge1[i][0]];
        edge1[i][1] = countarr[edge1[i][1]];
    }

    int **G = new int *[num_vertices];
    for (int i = 0; i < num_vertices; ++i)
    {
        G[i] = new int[num_vertices]{};
    }

    for (int j = 0; j < numberOfEdges; ++j)
    {
        G[edge1[j][0]][edge1[j][1]] = edge1[j][2];
    }

    int *value_arr = new int[num_vertices];
    int *prev_arr = new int[num_vertices];
    for (int i = 0; i < num_vertices; i++)
    {
        value_arr[i] = -1;
        prev_arr[i] = -1;
    }
    int startpoint = countarr[startVertex];
    int endpoint = countarr[goalVertex];
    if (value_arr[startpoint] == -1)
    {
        for (int i = 0; i < num_vertices; ++i)
        {
            if (value_arr[i] == -1 && G[startpoint][i] > 0)
            {
                value_arr[i] = G[startpoint][i];
                prev_arr[i] = startpoint;
            }
            value_arr[startpoint] = 0;
        }
    }

    for (int iterations = 0; iterations < num_vertices - 1; ++iterations)
    {
        int *Tempvalue = new int[num_vertices];
        for (int i = 0; i < num_vertices; ++i)
        {
            Tempvalue[i] = value_arr[i];
        }
        for (int u = 0; u < num_vertices; ++u)
        {
            for (int v = 0; v < num_vertices; ++v)
            {
                if (G[u][v] != 0 && Tempvalue[u] != -1 && ((G[u][v] + Tempvalue[u] < value_arr[v]) || value_arr[v] == -1))
                {
                    value_arr[v] = G[u][v] + Tempvalue[u];
                    prev_arr[v] = u;
                }
            }
        }
        delete[] Tempvalue;
    }
    string S;
    int mark1 = endpoint;
    char step;
    while (mark1 != -1)
    {
        for (int i = 0; i < 256; ++i)
        {
            if (countarr[i] == mark1)
            {
                step = i;
            }
        }
        string str(1, step);
        if (mark1 != endpoint)
        {
            S += " " + str;
        }
        else
            S += str;
        if (mark1 == prev_arr[mark1])
        {
            mark1 = -1;
        }
        else
        {
            mark1 = prev_arr[mark1];
        }
    }
    int length = S.length();
    string S2;
    for (int i = length - 1; i >= 0; --i)
    {
        S2.push_back(S[i]);
    }
    delete[] value_arr;
    delete[] prev_arr;
    for (int i = 0; i < num_vertices; ++i)
    {
        delete[] G[i];
    }
    delete[] G;
    for (int i = 0; i < numberOfEdges; ++i)
    {
        delete[] edge1[i];
    }
    delete[] edge1;
    return S2;
}
