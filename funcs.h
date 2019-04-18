/* /////////////////////////
Name: Ashley E. Hoover
Course: CPE357-05-2194
Instructor: Professor Planck
Assignment #: 2
///////////////////////// */ 
#define TRUE 1
#define FALSE 0
#define INITIAL_SIZE 100

typedef struct Node
{
	int ID;
	char type;
	char *data;

} Node; 

char * readline( FILE * file );
/* Reads a single line from a file up to the newline character and returns
a pointer to that line. */

Node * createNode( char *string );
/* Takes a string of input formatted as #(Q_or_A)_string_text, dynamically 
allocates a new node and fills in its member variables, then returns a
pointer to that node. If the line passed to it is NULL, returns NULL */

void buildTree( FILE * file, Node **arr, int arrSize, int *numNodes );
/* */

void printTree( Node **arr );
/* Takes a pointer to an array of Node pointers ( the tree ) and prints
the Nodes in numerical order by ID. For use in testing. */

int findLeftChild( int nodeID );
/* Takes a nodeID and returns the ID of that node's left child */

int findRightChild( int nodeID );
/* Takes a nodeID and returns the ID of that node's right child */

void ask( int nodeID, Node *tree, int numNodes );
/* */

Node * searchByID( int nodeID, Node **tree, int numNodes );
/* */