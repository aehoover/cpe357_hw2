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
	Node **tree = ( Node ** ) malloc( sizeof( Node * ) * INITIAL_SIZE );
	FILE *file, *outFile;
	int i;
	int computer_wins = FALSE;
	int numNodes = 0;
	char *userInput = NULL;
	Node *current = NULL;
	int treeSize = INITIAL_SIZE;

	if ( tree == NULL )
	{
		printf( "Error, not enough space for tree \n" );
		exit( 1 );
	}

	for ( i = 0; i < INITIAL_SIZE; i++ )
	{
		tree[i] = NULL;
	}

	file = fopen( "qa.db", "r" );

	if ( !file )
	{
		printf( "qa.db: No such file or directory\n" );
		printf( "Unable to read qa.db.  Starting fresh.\n" );

		file = fopen( "qa.db", "w" );
	}
	else
	{
		/* Code to read in from the file and build the tree */

		buildTree( file, tree, &treeSize, &numNodes );
		/*printTree( tree );*/
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

			printf( "Is it %s? ", current->data );
			/*scanf( " %s", &userInput );*/

			userInput = input();

			if ( userInput[0] == 'y' || userInput[0] == 'Y' )
			{
				computer_wins = TRUE;
			}

			clearInput( userInput );

			break;
		}
	}

	if ( computer_wins )
	{
		/* Print victory message */
		printf( "\nMy, am I clever.  :)\nThanks for playing.\n\n" );
	}
	else
	{
		char *animalString = NULL;
		char *newQuestion = NULL;
		char *answer = NULL;
		Node *questNode = ( Node* ) malloc( sizeof( Node ) );
		Node *animalNode = ( Node* ) malloc( sizeof( Node ) );

		if ( questNode == NULL || animalNode == NULL )
		{
			printf( "A malloc has failed.\n" );
			exit( 1 );
		}
		else if ( current != NULL )
		{
			/* Add new animal and question nodes */
			printf( "\nHow disapointing.\n" );
			printf( "What is it (with article)? " );
			animalString = input();
			printf( "What is a yes/no question that will distinguish %s from %s?\n? ", animalString, current->data );

			newQuestion = input();
			questNode->ID = current->ID;
			questNode->type = 'Q';
			questNode->data = newQuestion;
			questNode->freePtr = newQuestion;

			printf( "What is the answer to the question for %s? ", animalString );

			answer = input();

			printf( "\nI'll get it next time, I'm sure.\nThanks for playing.\n\n" );

			if ( numNodes >= treeSize - 2 )
			{
				treeSize *= 2;
				tree = realloc( tree, sizeof( Node * ) * treeSize );
			}

			tree[numNodes] = questNode;
			numNodes++;

			if ( answer[0] == 'y' || answer[0] == 'Y' )
			{
				current->ID = findLeftChild( questNode->ID );
				animalNode->ID = findRightChild( questNode->ID );
			}
			else
			{
				current->ID = findRightChild( questNode->ID );
				animalNode->ID = findLeftChild( questNode->ID );
			}

			animalNode->data = animalString;
			/*strcpy( animalNode->data, animalString );*/
			animalNode->type = 'A';
			animalNode->freePtr = animalString;

			tree[numNodes] = animalNode;
			numNodes++;

			clearInput( answer );

		}
		else
		{
			printf( "\nWhat is it (with article)? " );
			animalString = input();

			animalNode->ID = 0;
			animalNode->type = 'A';
			animalNode->data = animalString;
			animalNode->freePtr = animalString;

			tree[numNodes] = animalNode;
			numNodes++;
		}
	}

	/* Game over. Open file for writing and write updated tree
	to the file. Close file and exit porgram. */

	sortTree( tree, numNodes );

	outFile = fopen( "qa.db", "w" );
	writeTree( outFile, tree, numNodes );
	fclose( outFile );

	freeTree( tree, numNodes );

	return 0;
}