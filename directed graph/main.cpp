#include<iostream>
// Dijkstra's algorithm using Adjacency list (directed, weighted)

// vertices stored in an array

constexpr int maxVertex = 10;
constexpr int inf = 10000;

using namespace std;

class arcNode
{
public:
    int adjacentVertex;  //index of an adjacent vertex
    int weight;
    arcNode *next;  // to other adjacent vertex 

    arcNode(int i, int w)
    {
        adjacentVertex = i;
        weight = w;
        next = NULL;
    }
};

class vertexNode
{
public:
    char data;      // -1 means no void
    arcNode *firstArc;     // NULL by default
};

class graphAdjList  // graph adjacent list
{
    vertexNode vertex[maxVertex];
    int numVertex;
    int numArc;
    
public:

    graphAdjList()
    {
        for (int i = 0; i < maxVertex; i++)
        {
            vertex[i].data = -1;
            vertex[i].firstArc = NULL;
        }
    }

    void createGraph();

    void insertArc(int i, int j, int w);

    void printGraphList();

    int getWeight(int tail, int head);

    void dijkstra(int start);
};

void graphAdjList::createGraph()
{
    // cout<<"input number of vertices: ";
    // cin>>numVertex;

    // for(int i = 0; i < numVertex; i++)
    // {
    //     cout<<"Input vertex "<<i;
    //     cin>>vertex[i].data;
    // }

    numVertex = 5;
    vertex[0].data = 'A';
    vertex[1].data = 'B';
    vertex[2].data = 'C';
    vertex[3].data = 'D';
    vertex[4].data = 'E';
}


// i is the tail vertex of the arc
// j is the head vertex of the arc
// w is the weight of the 
// 这里需要用尾插法 insert new node at the end
void graphAdjList::insertArc(int i, int j, int w)
{
    arcNode *instEdge = new arcNode(j, w);

    arcNode *temp = vertex[i].firstArc;
    // if firstArc is NULL, instEdge is the firstArc
    if (!temp)  
    {
        vertex[i].firstArc = instEdge;
        return;
    }

    // if temp is not NULL, go to the end arc pointer
    while(temp->next)  
    {
        temp = temp->next;
    }
    // insert the arc at the end
    temp->next = instEdge;
}

void graphAdjList::printGraphList()
{
    for (int i = 0; i < numVertex; i++)
    {
        cout<<vertex[i].data<<": ";
        arcNode *temp = vertex[i].firstArc;
        while (temp)
        {
            cout<<" - "<<temp->weight<<" -> "<<vertex[temp->adjacentVertex].data<<'\t';
            temp = temp->next;
        }
        cout<<'\n';
        
    }
}

// return weight between two vertices
// if the two vertices are the same, return 0
// if the two vertices are not connected, return inf
int graphAdjList::getWeight(int tail, int head)
{
    if (tail == head)
    {
        return 0;
    }

    arcNode *temp = vertex[tail].firstArc;
    while (temp)
    {
        if (temp->adjacentVertex == head)
        {
            return temp->weight;
        }
        temp = temp->next;
    }
    return inf;
    
}

void graphAdjList::dijkstra(int start)
{
    // visited = true : the shortest path obtained
    bool visited[numVertex];
    for (int i = 0; i < numVertex; i++)    
    {
        visited[i] = false;
    } 
    visited[start] = true;

// store the distance between vertices
    int distance[numVertex];
    for (int i = 0; i < numVertex; i++)
    {
       distance[i] = getWeight(start, i);
    }
    
// record passing vertices
    int u;
    for (int i = 0; i < numVertex; i++)
    {
        
        // find the shortest arc
        int cost = inf;
        for (int j = 0; j < numVertex; j++)
        {
            if (!visited[j] && distance[j] < cost)
            {
                // find the closest vertex
                u = j;  
                cost = distance[j];
            }
        }

        visited[u] = true;
//  u is the closest vertex index

        for (int j = 0; j < numVertex; j++)
        {
            // find other path from unvisited vertex
            int newDis = getWeight(u, j);
            if (!visited[j] && newDis + distance[u] < distance[j])
            {
                distance[j] = newDis + distance[u];
            }
        }
    }
    cout<<"shortest path using dijkstra's algorithm: \n";   
    for (int i = 0; i < numVertex; i++)
    {
        cout<<"Shortes distance between "<<vertex[start].data<<" and "<<vertex[i].data<<" is "<<distance[i]<<'\n';
    }
}

int main()
{
    graphAdjList graph;
    graph.createGraph();
// vertex = {A, B, C, D, E}
    graph.insertArc(0, 1, 1);
    graph.insertArc(0, 2, 2);
    graph.insertArc(1, 2, 2);
    graph.insertArc(1, 3, 2);
    graph.insertArc(2, 3, 3);
    graph.insertArc(3, 4, 4);
    graph.insertArc(4, 0, 5);

    graph.printGraphList();
    graph.dijkstra(0);
}