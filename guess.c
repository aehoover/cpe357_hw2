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

	for ( i = 0; i < INITIAL_SIZE; i++ )
	{
		tree[i] = '\0';
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

		buildTree( file, tree );
		printTree( tree );

	}

	fclose( file );

	return 0;
}