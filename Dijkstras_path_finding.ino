#include <sparki.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 16 // number of nodes

// Setup for defining the coordinates of the graph. Not needed in this case
/*
int len = 60;
int wid = 32;
int array_x[16];
int array_y[16];
*/
int adjacency_mat[16][16];

// Store the shorests paths for each node of the graph
int path_final[V][V];

int minDistance(int dist[], bool sptSet[]) {
    // Initialize min value
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
 
    return min_index;
}

void printPath(int parent[], int j, int nodey, int count) {
    // Base Case : If j is source
    if (parent[j]==-1)
        return;

    count++;
    printPath(parent, parent[j], nodey, count);
    path_final[nodey][V-count] = j;
    
    //printf("%d ", j);
}

int printSolution(int dist[], int n, int parent[]) {
    //int nodey = 0;
    int count = 0;
    //int src = 0;
    //printf("Vertex\t  Distance\tPath");
    for (int i = 1; i < V; i++)
    {
        //printf("\n%d -> %d \t\t %d\t\t%d ", src, i, dist[i], src);
        printPath(parent, i, i, count);
    }
}

void dijkstra(int graph[V][V], int src) {
    int dist[V];  // The output array. dist[i] will hold
                  // the shortest distance from src to i
 
    // sptSet[i] will true if vertex i is included / in shortest
    // path tree or shortest distance from src to i is finalized
    bool sptSet[V];
 
    // Parent array to store shortest path tree
    int parent[V];
 
    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
    {
        parent[0] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
 
    // Distance of source vertex from itself is always 0
    dist[src] = 0;
 
    // Find shortest path for all vertices
    for (int count = 0; count < V-1; count++)
    {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to src
        // in first iteration.
        int u = minDistance(dist, sptSet);
 
        // Mark the picked vertex as processed
        sptSet[u] = true;
 
        // Update dist value of the adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < V; v++)
 
            // Update dist[v] only if is not in sptSet, there is
            // an edge from u to v, and total weight of path from
            // src to v through u is smaller than current value of
            // dist[v]
            if (!sptSet[v] && graph[u][v] &&
                dist[u] + graph[u][v] < dist[v])
            {
                parent[v]  = u;
                dist[v] = dist[u] + graph[u][v];
            }  
    }
 
    // calculate the constructed distance and path arrays
    printSolution(dist, V, parent);
}

void move_sparki(int goal) {
  // Must point Sparki from node 0->1
  // After moving to a new node, sparki always rotates back to this orienattion to make things simpler
  
  // Assumes the source is node 0
  int current_node = 0;
  for (int i = 0; i < V; i++) {

    // The path's are storred in a matrix padded with 0's, so you need to ignore those
    if (path_final[goal][i] == 0) {
      continue;
    }
   
    //move to -> path_final[goal][i]
    // Go up
    if (current_node - path_final[goal][i] == -4) { //Change to (-4) if 4X4
      sparki.moveLeft(90);
      delay(50);
      sparki.moveForward(10);
      delay(50);
      sparki.moveRight(90);
      delay(50);
    }

    // Go down
    if (current_node - path_final[goal][i] == 4) { //Change to (4) if 4X4
      sparki.moveRight(90);
      delay(50);
      sparki.moveForward(10);
      delay(50);
      sparki.moveLeft(90);
      delay(50);   
    }

    // Go right
    if (current_node - path_final[goal][i] == -1) {
      sparki.moveForward(15);
      delay(50);
    }

    // Go left
    if (current_node - path_final[goal][i] == 1) {
      sparki.moveLeft(180);
      delay(50);
      sparki.moveForward(15);
      delay(50);
      sparki.moveRight(180);  
      delay(50);   
    }

    // update position
    current_node = path_final[goal][i];
  }
  //Add something here if you want Sparki to do something once it has reached its goal
}

/*
void createCost() {
    int x = 4;
    int y = 4;
    int n = x*y;
    int map[4][4] = {{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}};
    //int cost[16][16] = {0};
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            // Right neighbors
            if (i < x-1) {
                if (map[i][j] && map[i+1][j]) {
                    adjacency_mat[(x*j)+i+1][(x*j)+i] = 1;
                }
            }

            // Left neighbors
            if (i > 0) {
                if (map[i][j] && map[i-1][j]) {
                    adjacency_mat[(x*j)+i-1][(x*j)+i] = 1;
                }
            }


            // Up neighbors
            if (j > 0) {
                if (map[i][j] && map[i][j-1]) {
                    adjacency_mat[(x*j)+i-x][(x*j)+i] = 1;
                }
            }

            // Down neighbors
            if (j < y-1) {
                if (map[i][j] && map[i][j+1]) {
                    adjacency_mat[(x*j)+i+x][(x*j)+i] = 1;
                }
            }
        }
    }
}
*/

void setup() {
  // put your setup code here, to run once:

  // This actaully isn't necceary, beacuse we can travel between nodes just based on the fixed distance between them
  // We don't need the actual coordinates unless we are doing inverse kinematics. 

  /*
  for (int i = 0; i < 16; i++) {
    array_x[i] = (i%4)*(len/4) + len/8;
    array_y[i] = (i%4)*(wid/4) + wid/8;
  }
  */

  //graph set up
  //createCost();

  // Adjacency Matrix
  // 0 -> not connected
  // 1 -> its a neighbor node
  // 100 -> an obstacle you want to go around/avoid
  // The orientation of this adjacency matrix must correspond with how you labeled the nodes in your movement calculations
  /*
  int graph[V][V] = {{0, 1, 0, 100, 0, 0, 0, 0, 0},
                     {1, 0, 1, 0, 100, 0, 0, 0, 0},
                     {0, 1, 0, 0, 0, 1, 0, 0, 0},
                     {1, 0, 0, 0, 100, 0, 1, 0, 0},
                     {0, 1, 0, 100, 0, 1, 0, 1, 0},
                     {0, 0, 1, 0, 100, 0, 0, 0, 1},
                     {0, 0, 0, 100, 0, 0, 0, 1, 0},
                     {0, 0, 0, 0, 100, 0, 1, 0, 1},
                     {0, 0, 0, 0, 0, 1, 0, 1, 0}
    };
    */

    int graph[V][V] = {{

0,  1,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},  

{1,  0,  1,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},  

{0,  1,  0,  1,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0},  

{0,  0,  1,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0},  

{1,  0,  0,  0,  0,  1,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0},  

{0,  1,  0,  0,  1,  0,  1,  0,  0,  1,  0,  0,  0,  0,  0,  0},  

{0,  0,  1,  0,  0,  1,  0,  1,  0,  0,  1,  0,  0,  0,  0,  0},  

{0,  0,  0,  1,  0,  0,  1,  0,  0,  0,  0,  1,  0,  0,  0,  0},  

{0,  0,  0,  0,  1,  0,  0,  0,  0,  1,  0,  0,  1,  0,  0,  0},  

{0,  0,  0,  0,  0,  1,  0,  0,  1,  0,  1,  0,  0,  1,  0,  0},  

{0,  0,  0,  0,  0,  0,  1,  0,  0,  1,  0,  1,  0,  0,  1,  0},  

{0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  1,  0,  0,  0,  0,  1},  

{0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  1,  0,  0},  

{0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  1,  0,  1,  0},  

{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  1,  0,  1},  

{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  1,  0}

      
    };

    for (int i = 0; i < 16; i++) {
    if (graph[i][4] == 1) {
      graph[i][4] = 99;
    }
    if (graph[i][5] == 1) {
      graph[i][5] = 99;
    }
    if (graph[i][3] == 1) {
      graph[i][3] = 99;
    }
    if (graph[i][7] == 1) {
      graph[i][7] = 99;
    }
    if (graph[i][12] == 1) {
      graph[i][12] = 99;
    }
    if (graph[i][14] == 1) {
      graph[i][14] = 99;
    }
    else {
      continue;
    } 
  }
    // Calculate the shortest paths and store them
    dijkstra(graph, 0);

    // Move sparki based on those paths and given a "goal" node
    move_sparki(13);

}

void loop() {
  // put your main code here, to run repeatedly:
}
