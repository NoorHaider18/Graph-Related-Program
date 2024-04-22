#include <stdio.h>

// Define a structure for a node in the graph
struct Node
{
    int nodeid;         // Node ID
    int adjcount;       // Number of adjacent nodes
    int adjs[10];       // Array to store IDs of adjacent nodes
    int costs[10];      // Array to store costs associated with adjacent nodes
};

// Function to add a node to the graph
// Parameters:
// - p: Pointer to the array of nodes
// - nid: Node ID to be added
// - count: Current number of nodes in the graph
// Returns: Updated count of nodes in the graph
int addNode(struct Node *p, int nid, int count)
{
    int i = 0, ncount = count;
    // Check if the node with the given ID already exists
    for (i = 0; i < count; i++)
    {
        if (p[i].nodeid == nid)
        {
            break;
        }
    }
    // If the node doesn't exist, add it to the graph
    if (i == count)
    {
        p[i].nodeid = nid;
        p[i].adjcount = 0;
        ncount++;
    }
    return ncount;
}

// Function to add an adjacent node to a given node in the graph
// Parameters:
// - p: Pointer to the array of nodes
// - nid1: ID of the node to which the adjacent node is to be added
// - nid2: ID of the adjacent node
// - cost: Cost associated with the connection between the two nodes
// - count: Current number of nodes in the graph
void addAdjacent(struct Node *p, int nid1, int nid2, int cost, int count)
{
    int i = 0, index;
    // Find the index of the node to which the adjacent node is to be added
    for (i = 0; i < count; i++)
    {
        if (p[i].nodeid == nid1)
        {
            index = i;
            break;
        }
    }
    // Add the adjacent node and its associated cost to the specified node
    int c = p[index].adjcount;
    p[index].adjs[c] = nid2;
    p[index].costs[c] = cost;
    p[index].adjcount = c + 1;
}

// Function to check if a node is already present in a list
// Parameters:
// - list: Array of node IDs
// - lcount: Current number of nodes in the list
// - nid: Node ID to be checked
// Returns: 1 if the node is present, 0 otherwise
int added(int *list, int lcount, int nid)
{
    int i = 0;
    for (i = 0; i < lcount; i++)
    {
        if (list[i] == nid)
        {
            return 1;
        }
    }
    return 0;
}

// Function to find a path between two nodes in the graph
// Parameters:
// - p: Pointer to the array of nodes
// - count: Current number of nodes in the graph
// - start: ID of the starting node
// - end: ID of the ending node
// - list: Array to store the path of node IDs
// - clist: Array to store the costs associated with the path
// - lcount: Current number of nodes in the path
void findPath(struct Node *p, int count, int start, int end, int *list, int *clist, int lcount)
{
    int index = 0, i = 0;

    // Check if the end node is reached
    if (list[lcount - 1] == end)
    {
        // Print the path and its total cost
        int tcost = 0;
        printf("\n");
        for (i = 0; i < lcount; i++)
        {
            printf(" %d ", list[i]);
            tcost += clist[i];
        }
        printf(" cost = %d", tcost);
        return;
    }

    // Find the index of the starting node in the array of nodes
    for (i = 0; i < count; i++)
    {
        if (p[i].nodeid == start)
        {
            index = i;
            break;
        }
    }

    // Explore adjacent nodes recursively
    for (i = 0; i < p[index].adjcount; i++)
    {
        // Check if the adjacent node is already in the path
        int a = added(list, lcount, p[index].adjs[i]);
        if (a == 0)
        {
            // Add the adjacent node to the path and recursively find the path
            list[lcount] = p[index].adjs[i];
            clist[lcount] = p[index].costs[i];
            lcount++;

            findPath(p, count, p[index].adjs[i], end, list, clist, lcount);
            lcount--;
        }
    }
}

// Main function
int main()
{
    // Declare variables
    struct Node nodes[50];
    int nodecount = 0;
    int n1 = 0, n2 = 0, c = 0;

    // Input nodes and their connections
    while (1)
    {
        printf("n1, n2, cost ? ");
        scanf("%d %d %d", &n1, &n2, &c);
        if (n1 == -9 || n2 == -9 || c == -9)
        {
            break;
        }
        nodecount = addNode(&nodes[0], n1, nodecount);
        nodecount = addNode(&nodes[0], n2, nodecount);

        addAdjacent(&nodes[0], n1, n2, c, nodecount);
        addAdjacent(&nodes[0], n2, n1, c, nodecount);
    }

    // Input start and end nodes
    int start, end;
    printf("start, end ? ");
    scanf("%d %d", &start, &end);
    // Initialize arrays for storing the path
    int list[50], clist[50], lcount = 0;
    list[0] = start;
    clist[0] = 0;
    lcount = 1;

    // Find and print the path between the start and end nodes
    findPath(nodes, nodecount, start, end, list, clist, lcount);

    return 0;
}
