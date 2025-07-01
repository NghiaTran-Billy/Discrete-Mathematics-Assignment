#include "tsm.h"

class Ant
{
public:
    long long citiesStatus;
    vector<int> pos;
    float currentcost;
};

string Traveling(int edgeList[][3], int numEdge, char start)
{

    int num_vertices = 0;

    int **edge1 = new int *[numEdge];
    for (int i = 0; i < numEdge; ++i)
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
    for (int i = 0; i < numEdge; ++i)
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

    for (int i = 0; i < numEdge; ++i)
    {
        edge1[i][0] = countarr[edge1[i][0]];
        edge1[i][1] = countarr[edge1[i][1]];
    }

    float **G = new float *[num_vertices];
    for (int i = 0; i < num_vertices; ++i)
    {
        G[i] = new float[num_vertices]{};
    }

    for (int j = 0; j < numEdge; ++j)
    {
        G[edge1[j][0]][edge1[j][1]] = edge1[j][2];
    }

    if (num_vertices <= 20)
    {
        int masknum = pow(2, num_vertices);
        int **dp = new int *[masknum];
        int **path = new int *[masknum];
        for (int i = 0; i < masknum; ++i)
        {
            dp[i] = new int[num_vertices];
            path[i] = new int[num_vertices];
            for (int j = 0; j < num_vertices; ++j)
            {
                dp[i][j] = -1;
                path[i][j] = -1;
            }
        }

        int start1;
        start1 = countarr[start];

        string route;
        for (int i = 0; i < 256; ++i)
        {
            if (countarr[i] == start1)
            {
                char temp = i;
                route.push_back(temp);
                route.push_back(' ');
                break;
            }
        }

        for (int i = 0; i < num_vertices; ++i)
        {
            if (i == start1 || G[i][start1] == 0)
                continue;
            dp[masknum - 1][i] = G[i][start1];
        }

        for (int mask = (1 << num_vertices) - 2; mask > 0; --mask)
        {
            if (!(mask & (1 << start1)))
                continue;
            for (int i = 0; i < num_vertices; ++i)
            {
                if (!(mask & (1 << i)) || (i == start1 && mask != (1 << start1)))
                    continue;
                for (int j = 0; j < num_vertices; ++j)
                {
                    if (mask & (1 << j) || G[i][j] == 0 || (dp[mask | (1 << j)][j] == -1))
                        continue;

                    if (dp[mask][i] < dp[mask | (1 << j)][j] + G[i][j] && dp[mask][i] != -1)
                    {
                        continue;
                    }
                    else
                    {
                        dp[mask][i] = dp[mask | (1 << j)][j] + G[i][j];
                        path[mask][i] = j;
                    }
                }
                if (mask == (1 << start1) && dp[1 << start1][start1] != -1)
                {
                    int maskcopy = mask;
                    int nextvertex = path[maskcopy][i];
                    while (maskcopy != masknum - 1)
                    {
                        for (int k = 0; k < 256; ++k)
                        {
                            if (countarr[k] == nextvertex)
                            {
                                char temp = k;
                                route.push_back(temp);
                                route.push_back(' ');
                                maskcopy = maskcopy | (1 << nextvertex);
                                nextvertex = path[maskcopy][nextvertex];
                                break;
                            }
                        }
                    }
                    for (int i = 0; i < 256; ++i)
                    {
                        if (countarr[i] == start1)
                        {
                            char temp = i;
                            route.push_back(temp);
                            break;
                        }
                    }
                }
            }
        }

        if (dp[1 << start1][start1] == -1)
        {
            for (int i = 0; i < numEdge; ++i)
            {
                delete[] edge1[i];
            }
            delete[] edge1;

            for (int i = 0; i < num_vertices; ++i)
            {
                delete[] G[i];
            }
            delete[] G;

            for (int i = 0; i < masknum; ++i)
            {
                delete[] dp[i];
                delete[] path[i];
            }
            delete[] dp;
            delete[] path;
            return "";
        }

        for (int i = 0; i < numEdge; ++i)
        {
            delete[] edge1[i];
        }
        delete[] edge1;

        for (int i = 0; i < num_vertices; ++i)
        {
            delete[] G[i];
        }
        delete[] G;

        for (int i = 0; i < masknum; ++i)
        {
            delete[] dp[i];
            delete[] path[i];
        }
        delete[] dp;
        delete[] path;
        return route;
    }

    else
    {
        int Q = 4;
        float rho = 0.1;
        int bestCost = -1;
        vector<int> bestTour;
        int currentCost = 0;
        int alpha = 1;
        int beta = 4;
        Ant **ants = new Ant *[num_vertices];
        float **pheromone = new float *[num_vertices];
        for (int i = 0; i < num_vertices; ++i)
        {
            ants[i] = new Ant;
            ants[i]->citiesStatus = 1 << i;
            ants[i]->pos.push_back(i);
            ants[i]->currentcost = 0;
            pheromone[i] = new float[num_vertices];
            for (int j = 0; j < num_vertices; ++j)
            {
                if (G[i][j] != 0)
                {
                    pheromone[i][j] = 100;
                    G[i][j] = 100.0 / G[i][j];
                }
            }
        }

        for (int iterations = 0; iterations < 200; ++iterations)
        {
            for (int antNum = 0; antNum < num_vertices; ++antNum)
            {
                bool roadExist = false;
                for (int steps = 0; steps < num_vertices - 1; ++steps)
                {
                    roadExist = false;
                    vector<float> probability(num_vertices, 0);
                    float sumprob = 0;
                    for (int j = 0; j < num_vertices; ++j)
                    {
                        if ((ants[antNum]->citiesStatus & 1 << j) == 0)
                        {
                            sumprob += (pow(pheromone[ants[antNum]->pos.back()][j], alpha) * pow(G[ants[antNum]->pos.back()][j], beta));
                        }
                    }
                    if (sumprob != 0)
                    {
                        roadExist = true;
                        for (int j = 0; j < num_vertices; ++j)
                        {
                            if ((ants[antNum]->citiesStatus & 1 << j) == 0)
                            {
                                probability[j] = (pow(pheromone[ants[antNum]->pos.back()][j], alpha) * pow(G[ants[antNum]->pos.back()][j], beta)) / sumprob;
                            }
                        }
                    }
                    else
                    {
                        break;
                    }

                    vector<float> culmulative(num_vertices, 0);
                    for (int j = 0; j < num_vertices; ++j)
                    {
                        if (probability[j] == 0)
                        {
                            continue;
                        }
                        for (int k = j; k < num_vertices; ++k)
                        {
                            culmulative[j] += probability[k];
                        }
                    }

                    random_device rd;
                    mt19937 gen(rd());
                    uniform_real_distribution<float> dist(0.0, 1.0);
                    float randNum = dist(gen);
                    float firsthead = 0;
                    int firstindex;
                    for (int search = num_vertices - 1; search >= 0; --search)
                    {
                        if (culmulative[search] != 0)
                        {
                            firsthead = culmulative[search];
                            firstindex = search;
                            break;
                        }
                    }
                    if (0 <= randNum && randNum <= firsthead)
                    {
                        ants[antNum]->citiesStatus = ants[antNum]->citiesStatus | 1 << (firstindex);
                        ants[antNum]->currentcost += 100.0 / G[ants[antNum]->pos.back()][firstindex];
                        ants[antNum]->pos.push_back(firstindex);
                        continue;
                    }
                    float back = 0;
                    for (int i = 0; i < num_vertices - 1; ++i)
                    {
                        if (culmulative[num_vertices - 1 - i] == 0)
                        {
                            continue;
                        }
                        back = culmulative[num_vertices - 1 - i];
                        if (back == 1)
                        {
                            ants[antNum]->citiesStatus = ants[antNum]->citiesStatus | 1 << (num_vertices - 1 - i);
                            ants[antNum]->currentcost += 100.0 / G[ants[antNum]->pos.back()][num_vertices - 1 - i];
                            ants[antNum]->pos.push_back(num_vertices - 1 - i);
                            break;
                        }
                        float head = 0;
                        int index;
                        for (int l = num_vertices - 2 - i; l >= 0; --l)
                        {
                            if (culmulative[l] == 0)
                            {
                                continue;
                            }
                            head = culmulative[l];
                            index = l;
                            break;
                        }
                        if (back != 0 && head != 0 && back <= randNum && randNum <= head)
                        {
                            ants[antNum]->citiesStatus = ants[antNum]->citiesStatus | 1 << index;
                            ants[antNum]->currentcost += 100.0 / G[ants[antNum]->pos.back()][index];
                            ants[antNum]->pos.push_back(index);
                            break;
                        }
                    }
                }
                if (roadExist == true && G[ants[antNum]->pos.back()][ants[antNum]->pos.front()] != 0)
                {
                    ants[antNum]->currentcost += 100.0 / G[ants[antNum]->pos.back()][ants[antNum]->pos.front()];
                    ants[antNum]->pos.push_back(ants[antNum]->pos.front());
                    if (ants[antNum]->currentcost < bestCost || bestCost == -1)
                    {
                        bestCost = ants[antNum]->currentcost;
                        bestTour = ants[antNum]->pos;
                    }
                }
                else
                {
                    ants[antNum]->currentcost = 0;
                }
            }
            int **deltaPheromone = new int *[num_vertices];
            for (int i = 0; i < num_vertices; ++i)
            {
                deltaPheromone[i] = new int[num_vertices]();
            }
            for (int antNum = 0; antNum < num_vertices; ++antNum)
            {
                for (int i = 0; i < ants[antNum]->pos.size() - 1; ++i)
                {
                    if (ants[antNum]->currentcost != 0)
                    {
                        deltaPheromone[ants[antNum]->pos[i]][ants[antNum]->pos[i + 1]] += Q / (float)ants[antNum]->currentcost;
                    }
                }
            }
            for (int i = 0; i < num_vertices; ++i)
            {
                for (int j = 0; j < num_vertices; ++j)
                {
                    pheromone[i][j] = (1 - rho) * pheromone[i][j] + deltaPheromone[i][j];
                }
            }
            for (int i = 0; i < num_vertices; ++i)
            {
                delete[] deltaPheromone[i];
            }
            delete[] deltaPheromone;
            for (int i = 0; i < num_vertices; ++i)
            {
                ants[i]->citiesStatus = 1 << i;
                ants[i]->pos.clear();
                ants[i]->pos.push_back(i);
                ants[i]->currentcost = 0;
            }
        }

        string route;
        int startindex;
        for (int i = 0; i < bestTour.size(); ++i)
        {
            if (bestTour[i] == countarr[start])
            {
                startindex = i;
                break;
            }
        }
        for (int i = startindex; i < bestTour.size(); ++i)
        {
            for (int j = 0; j < 256; ++j)
            {
                if (countarr[j] == bestTour[i])
                {
                    char temp = j;
                    route.push_back(temp);
                    break;
                }
            }
            route.push_back(' ');
        }
        for (int i = 1; i < startindex + 1; ++i)
        {
            for (int j = 0; j < 256; ++j)
            {
                if (countarr[j] == bestTour[i])
                {
                    char temp = j;
                    route.push_back(temp);
                    break;
                }
            }
            if (i != startindex)
            {
                route.push_back(' ');
            }
        }

        for (int i = 0; i < numEdge; ++i)
        {
            delete[] edge1[i];
        }
        delete[] edge1;

        for (int i = 0; i < num_vertices; ++i)
        {
            delete[] G[i];
            delete ants[i];
            delete[] pheromone[i];
        }
        delete[] ants;
        delete[] G;
        delete[] pheromone;

        return route;
    }
}
