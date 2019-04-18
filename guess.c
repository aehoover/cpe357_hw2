/* /////////////////////////
Name: Ashley E. Hoover
Course: CPE357-05-2194
Instructor: Professor Planck
Assignment #: 2
///////////////////////// */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcs.h"

int main()
{
	Node **tree = malloc( sizeof( Node * ) * INITIAL_SIZE );
	FILE *file;
	int i;
	int player_wins = FALSE;
	int numNodes = 0;

	for ( i = 0; i < INITIAL_SIZE; i++ )
	{
		tree[i] = NULL;
	}

	if ( tree == NULL )
	{
		printf( "Error, not enough space for tree \n" );
		exit( 1 );
	}

	file = fopen( "qa.db", "r" );

	if ( !file )
	{
		printf( "Unable to read qa.db. Starting fresh.\n" );

		file = fopen( "qa.db", "w" );
	}
	else
	{
		/* Code to read in from the file and build the tree */

		buildTree( file, tree, INITIAL_SIZE, &numNodes );
		printTree( tree );
	}

	/* ////////// LOGIC FOR GUESSING GAME ////////////////////////////// */

	fclose( file );

	if ( tree[0] )
	{
		/* ask questions */

	}

	return 0;
}