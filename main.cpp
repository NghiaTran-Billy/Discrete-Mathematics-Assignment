#include "bellman.h"
#include "tsm.h"

using namespace std;
int main()
{
    clock_t begin = clock();
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> numvertice_dist(5, 25);
    uniform_int_distribution<int> length_dist(0, 500);
    uniform_int_distribution<int> char_dist(33, 126);
    int numOfVertices = numvertice_dist(gen);
    char allname[numOfVertices];
    int G1[numOfVertices][numOfVertices];
    int G2[numOfVertices][numOfVertices];
    int chararr[256]{};
    for (int i = 0; i < numOfVertices; ++i)
    {
        bool check = false;
        while (!check)
        {
            int temp = char_dist(gen);
            if (chararr[temp] == 0)
            {
                allname[i] = temp;
                ++chararr[temp];
                check = true;
            }
        }
        for (int j = 0; j < numOfVertices; ++j)
        {
            if (i == j)
            {
                G1[i][j] = 0;
                G2[i][j] = 0;
                continue;
            }
            G1[i][j] = length_dist(gen);
            G2[i][j] = length_dist(gen);
        }
    }

    uniform_int_distribution<int> select_char_dist(0, numOfVertices - 1);
    char startname = allname[select_char_dist(gen)];
    char endname = allname[select_char_dist(gen)];

    cout << "Number of vertices: " << numOfVertices << endl
         << endl;
    cout << "G1_Matrix: " << endl;
    for (int i = 0; i < numOfVertices; ++i)
    {
        for (int j = 0; j < numOfVertices; ++j)
        {
            cout << G1[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "G2_Matrix: " << endl;
    for (int i = 0; i < numOfVertices; ++i)
    {
        for (int j = 0; j < numOfVertices; ++j)
        {
            cout << G2[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "Vertices' names: " << endl;
    for (int i = 0; i < numOfVertices; ++i)
    {
        cout << allname[i] << " ";
    }
    cout << endl
         << endl;

    cout << "Start vertex's name: " << startname << endl;
    cout << "End vertex's name: " << endname << endl
         << endl;

    int numOfEdge1 = 0;
    int edgematrix1[numOfVertices * numOfVertices][3];

    for (int i = 0; i < numOfVertices; ++i)
    {
        for (int j = 0; j < numOfVertices; ++j)
        {
            edgematrix1[numOfEdge1][0] = allname[i];
            edgematrix1[numOfEdge1][1] = allname[j];
            edgematrix1[numOfEdge1][2] = G1[i][j];
            ++numOfEdge1;
        }
    }

    int numOfEdge2 = 0;
    int edgematrix2[numOfVertices * numOfVertices][3];
    for (int i = 0; i < numOfVertices; ++i)
    {
        for (int j = 0; j < numOfVertices; ++j)
        {
            edgematrix2[numOfEdge2][0] = allname[i];
            edgematrix2[numOfEdge2][1] = allname[j];
            edgematrix2[numOfEdge2][2] = G2[i][j];
            ++numOfEdge2;
        }
    }

    int BellmanFordValue[numOfVertices];
    int BellmanFordPrevious[numOfVertices];
    int CheckIteration[numOfVertices];
    bool change = false;
    for (int i = 0; i < numOfVertices; ++i)
    {
        BellmanFordValue[i] = -1;
        BellmanFordPrevious[i] = -1;
        CheckIteration[i] = -1;
    }

    cout << "Function BF run:" << endl;
    BF(edgematrix1, numOfEdge1, startname, BellmanFordValue, BellmanFordPrevious);
    cout << "step 1:" << endl;
    cout << "Value array: ";
    for (int i = 0; i < numOfVertices; ++i)
    {
        cout << BellmanFordValue[i] << " ";
    }
    cout << endl;
    cout << "Previous array: ";
    for (int i = 0; i < numOfVertices; ++i)
    {
        cout << BellmanFordPrevious[i] << " ";
    }
    cout << endl;
    for (int j = 0; j < numOfVertices; ++j)
    {
        CheckIteration[j] = BellmanFordPrevious[j];
    }
    for (int i = 2; i < 100; ++i)
    {
        if (i % 2 != 0)
        {
            BF(edgematrix1, numOfEdge1, startname, BellmanFordValue, BellmanFordPrevious);
        }
        else
        {
            BF(edgematrix2, numOfEdge2, startname, BellmanFordValue, BellmanFordPrevious);
        }
        for (int j = 0; j < numOfVertices; ++j)
        {
            if (CheckIteration[j] != BellmanFordPrevious[j])
            {
                CheckIteration[j] = BellmanFordPrevious[j];
                change = true;
            }
        }
        if (change == true)
        {
            cout << "step " << i << ":" << endl;
            cout << "Value array: ";
            for (int i = 0; i < numOfVertices; ++i)
            {
                cout << BellmanFordValue[i] << " ";
            }
            cout << endl;
            cout << "Previous array: ";
            for (int i = 0; i < numOfVertices; ++i)
            {
                cout << BellmanFordPrevious[i] << " ";
            }
            cout << endl;
            change = false;
        }
        else
        {
            break;
        }
    }
    cout << "Finished the last step\n"
         << endl;

    cout << "Function BF_Path run:\n"
         << "The shortest path from " << startname << " to " << endname << " is: ";
    cout << BF_Path(edgematrix1, numOfEdge1, startname, endname) << endl;

    cout << "\nFunction Traveling run:" << endl;
    string route = Traveling(edgematrix1, numOfEdge1, startname);
    if (numOfVertices <= 20)
    {
        cout << "The shortest circuit using Bellman-Held-Karp algorithm is: " << route << endl;
    }
    else
    {
        cout << "The approximate shortest circuit using Ant Colony Optimization algorithm is: " << route << endl;
    }
    clock_t end = clock();
    cout << endl;
    cout << "Time running: " << (double)(end - begin) / CLOCKS_PER_SEC << endl;
    return 0;
}
