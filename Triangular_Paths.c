#include<stdio.h>
#include<stdbool.h>

struct Node {
    int nodeid;          // Identifier for the node
    int adjcount;        // Count of adjacent nodes
    int adjs[10];        // Array of adjacent node identifiers
    int costs[10];       // Array of travel costs to each adjacent node
};

// Function to add a node to the graph
// p: pointer to the array of nodes
// nid: the node identifier to add
// count: current number of nodes in the graph
// Returns: the updated count of nodes after addition
int addNode(struct Node *p, int nid, int count) {
    int i;
    // Search through existing nodes to prevent duplication
    for (i = 0; i < count; i++) {
        if (p[i].nodeid == nid) break;
    }
    // If node not found, add new node
    if (i == count) {
        p[count].nodeid = nid;
        p[count].adjcount = 0;
        count++;
    }
    return count;
}

// Adds an edge between two specified nodes
// p: pointer to the array of nodes
// nid1: identifier for the first node
// nid2: identifier for the second node
// cost: travel cost between the two nodes
// count: number of nodes currently in the graph
void addAdjacent(struct Node *p, int nid1, int nid2, int cost, int count) {
    int i;
    // Find the first node and add the second as adjacent
    for (i = 0; i < count; i++) {
        if (p[i].nodeid == nid1) {
            int c = p[i].adjcount;
            p[i].adjs[c] = nid2;
            p[i].costs[c] = cost;
            p[i].adjcount++;
            break;
        }
    }
}

// Checks if a node ID is already included in a list
// list: the list of node IDs
// lcount: number of elements in the list
// nid: the node ID to check for
// Returns: 1 if present, 0 otherwise
int added(int *list, int lcount, int nid) {
    for (int i = 0; i < lcount; i++) {
        if (list[i] == nid) return 1;
    }
    return 0;
}

// Recursive function to find and print all paths from 'start' to 'end'
// p: pointer to the array of nodes
// count: number of nodes in the graph
// start: starting node ID for the path
// end: ending node ID for the path
// list: array to hold the path
// clist: array to hold the cost of each leg of the path
// lcount: current length of the path
void findpath(struct Node *p, int count, int start, int end, int *list, int *clist, int lcount) {
    if (list[lcount - 1] == end) {
        // Base case: if the last node in the path is the destination
        int tcost = 0;
        printf("\n");
        // Print the path and calculate total cost
        for (int i = 0; i < lcount; i++) {
            printf(" %d ", list[i]);
            tcost += clist[i];
        }
        printf(" cost = %d", tcost);
        return;
    }

    // Recurse: find the next nodes that can be visited from the current node
    int index = -1;
    for (int i = 0; i < count; i++) {
        if (p[i].nodeid == start) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        for (int i = 0; i < p[index].adjcount; i++) {
            if (!added(list, lcount, p[index].adjs[i])) {
                list[lcount] = p[index].adjs[i];
                clist[lcount] = p[index].costs[i];
                findpath(p, count, p[index].adjs[i], end, list, clist, lcount + 1);
            }
        }
    }
}

// Determines if two nodes are directly connected
// x, y: Nodes to be checked for adjacency
// Returns: true if y is an adjacent of x, false otherwise
bool adjacent(struct Node x, struct Node y) {
    for (int i = 0; i < x.adjcount; i++) {
        if (x.adjs[i] == y.nodeid) return true;
    }
    return false;
}

int main() {
    struct Node nodes[50]; // Array to store nodes
    int nodecount = 0;     // Number of nodes currently in the graph
    int n1, n2, c;

    // Input loop to receive node connections and costs
    while (true) {
        printf("n1, n2, cost ? ");
        scanf("%d %d %d", &n1, &n2, &c);
        if (n1 == -9 || n2 == -9 || c == -9) break;

        nodecount = addNode(nodes, n1, nodecount);
        nodecount = addNode(nodes, n2, nodecount);

        addAdjacent(nodes, n1, n2, c, nodecount);
        addAdjacent(nodes, n2, n1, c, nodecount);
    }

    // Check and count all triangles in the graph
    int count = 0;
    for (int i = 0; i < nodecount; i++) {
        for (int j = i + 1; j < nodecount; j++) {
            for (int k = j + 1; k < nodecount; k++) {
                if (adjacent(nodes[i], nodes[j]) &&
                    adjacent(nodes[j], nodes[k]) &&
                    adjacent(nodes[k], nodes[i])) {
                    count++;
                    printf("Triangle found: %d %d %d\n", nodes[i].nodeid, nodes[j].nodeid, nodes[k].nodeid);
                }
            }
        }
    }
    printf("Total triangles: %d\n", count);

    return 0;
}
