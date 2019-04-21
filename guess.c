/* /////////////////////////
Name: Ashley E. Hoover
Course: CPE357-05-2194
Instructor: Professor Planck
Assignment #: 2
///////////////////////// */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funcs.h"

int main()
{
	Node **tree = malloc( sizeof( Node * ) * INITIAL_SIZE );
	FILE *file;
	int i;
	int computer_wins = FALSE;
	int numNodes = 0;
	char *userInput = NULL;
	Node *current = NULL;

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
	}

	/* ////////// LOGIC FOR GUESSING GAME ////////////////////////////// */

	fclose( file );

	/* ask questions */
	current = tree[0];
	
	while ( TRUE )
	{
		if ( current == NULL )
		{
			/* No question or animal, computer loses. */
			break;
		}
		else if ( current->type == 'Q' )
		{
			/* Ask question stored in current node, if 
			answer is no, move to left child. If answer
			is yes, move to right child. */

			int id = -1;

			printf( "%s\n", current->data );
			/*scanf( " %s", &userInput );*/

			userInput = input();
			/*printf( "User input was: %s\n", userInput );*/

			if ( userInput[0] == 'y' || userInput[0] == 'Y' )
			{
				/* move to right node */
				id = findRightChild( current->ID );
			}
			else
			{
				/* Move to left node */
				id = findLeftChild( current->ID );
			}

			clearInput( userInput );

			current = searchByID( id, tree, numNodes );
		}
		else if ( current->type == 'A' )
		{
			/* Guess if it is that animal. If yes, 
			computer wins, break. If no, computer
			loses, move to add animal, break. */

			printf( "Is it %s? \n", current->data );
			/*scanf( " %s", &userInput );*/

			userInput = input();

			if ( userInput[0] == 'y' || userInput[0] == 'Y' )
			{
				printf( "yes\n" );
				computer_wins = TRUE;
			}

			clearInput( userInput );

			break;
		}
	}

	if ( computer_wins )
	{
		/* Print victory message */

		printf( "My, am I clever. :) Thanks for playing.\n" );
	}
	else
	{
		/* Add new animal and question nodes */
		printf( "How disapointing.\n" );
	}

	/* Game over. Open file for writing and write updated tree
	to the file. Close file and exit porgram. */

	return 0;
}