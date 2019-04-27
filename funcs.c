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

char * readline( FILE * file )
{
	int size = INITIAL_SIZE;
	char *oneLine = ( char * ) malloc( sizeof( char ) * size );
	char c;
	int i = 0;

	if ( oneLine == NULL )
	{
		printf("malloc has failed.\n" );
		exit( 1 );
	}

	for ( i = 0; i < size; i++ )
	{
		oneLine[i] = '\0';
	}

	i = 0;

	while ( TRUE )
	{
		c = getc( file );

		if ( c == EOF || c == '\n' )
		{
			break;
		}
		else if ( i < size )
		{
			oneLine[i] = c;
			i++;
		}
		else
		{
			int temp = i;
			size = ( sizeof( char ) * ( size * 2 ) );

			oneLine = realloc( oneLine, 
				( sizeof( char ) * size ) );

			if ( oneLine == NULL )
			{
				printf( "realloc has failed.\n" );
			}

			for ( i = i; i < size; i++ )
			{
				oneLine[i] = '\0';
			}

			i = temp;

			oneLine[i] = c;
			i++;
		}
	}

	if ( i == 0 && c == EOF )
	{
		free( oneLine );
		oneLine = NULL;
	}
	else if ( i == ( size - 1 ) )
	{
		oneLine = realloc( oneLine, sizeof( char ) * ( size + 1 ) );
		oneLine[i + 1] = '\0';
	}
		
	return oneLine;
	
}

Node * createNode( char *string )
{
	Node *newNode = ( Node* ) malloc( sizeof( Node ) );

	if ( newNode == NULL )
	{
		printf( "malloc has failed.\n" );
		exit( 1 );
	}
	else if ( string == NULL )
	{
		free( newNode );
		newNode = NULL;
	}
	else if ( string[0] == 'N' )
	{
		newNode->type = 'N';
	}
	else
	{
		newNode->type = string[0];
		newNode->freePtr = string;
		newNode->data = &( string[1] );
	}

	return newNode;
}

void buildTree( FILE * file, Node **arr, int *arrSize, int *numNodes )
{
	char *lineFromFile = NULL;
	int i = 0;
	int idCounter = 0;

	while ( ( lineFromFile = readline( file ) ) != NULL )
	{
		Node *newNode = createNode( lineFromFile );

		if ( newNode != NULL && ( newNode->type == 'Q' || newNode->type == 'A' ) )
		{
			( *numNodes )++;
			newNode->ID = idCounter;
			idCounter++;
		}
		else if ( newNode->type == 'N' )
		{
			free( newNode );
			idCounter++;
			continue;
		}

		if ( i == *arrSize )
		{
			int j = i;
			arr = realloc( arr, ( sizeof( *arrSize ) * 2 ) );
			*arrSize *= 2;

			if ( arr == NULL )
			{
				printf( "realloc failed.\n" );
				exit( 1 );
			}

			for ( j = j; j < *arrSize * 2; j++ )
			{
				arr[j] = NULL;
			}
		}

		arr[i] = newNode;
		i++;
	}
}

void printTree( Node **arr )
{
	int i = 0;

	printf( "Guessing Game Decision Tree\n" );
	printf( "===========================\n" );

	while ( arr[i] != NULL )
	{
		printf( "\nNode: %d\n", arr[i]->ID );
		printf( "Type: %c\n", arr[i]->type );
		printf( "%s\n", arr[i]->data );
		printf( "Index: %d\n", i );
		i++;
	}

}

int findLeftChild( int nodeID )
{
	int leftChild = ( nodeID * 2 ) + 1;

	return leftChild;
}

int findRightChild( int nodeID )
{
	int rightChild = ( nodeID * 2 ) + 2;

	return rightChild;
}

Node * searchByID( int nodeID, Node **tree, int numNodes )
{
	int i;
	Node *target = NULL;

	for ( i = 0; i < numNodes; i++ )
	{
		if ( tree[i]->ID == nodeID )
		{
			target = tree[i];
			break;
		}
	}

	return target;
}

char * input()
{
	int size = 101;
	char c = '\0';
	int i = 0;
	char *inputPtr = NULL;
	inputPtr = ( char * ) malloc( sizeof( char ) * size );

	if ( inputPtr == NULL )
	{
		printf( "malloc has failed.\n" );
		exit( 1 );
	}

	while ( TRUE )
	{
		c = getchar();

		if ( i == size )
		{
			size *= 2;
			inputPtr = realloc( inputPtr, sizeof( char ) * size );

			if ( inputPtr == NULL )
			{
				printf( "realloc has failed.\n" );
				exit( 1 );
			}
		}

		if ( c == '\n' )
		{
			inputPtr[i] = '\0';
			break;
		}
		else
		{
			inputPtr[i] = c;
		}

		i++;
	}

	return inputPtr;
}

void clearInput( char *inputString )
{
	int i;
	int len = strlen( inputString );

	for ( i = 0; i < len; i++ )
	{
		inputString[i] = '\0';
	}

	free( inputString );

}

void freeTree( Node *tree[], int numNodes )
{
	int i;

	for ( i = 0; i < numNodes; i++ )
	{
		/*free( &( tree[i]->data )[-2] );*/
		if ( tree[i]->freePtr != NULL )
		{
			free( tree[i]->freePtr );
		}

		free( tree[i] );
	}

	free( tree );
}

void writeTree( FILE * file, Node **arr, int numNodes )
{
	int i;
	int currentID = 0;
	/*int end = arr[numNodes]->ID + 1;*/

	for ( i = 0; arr[i] != NULL ; i++ )
	{
		int ID = arr[i]->ID;
		char type = arr[i]->type;
		int j = 0;

		if ( ID != currentID )
		{
			putc( 'N', file );
			putc( '\n', file );
			currentID++;
			i--;
			continue;
		}
		else
		{
			putc( type, file );

			while ( ( arr[i]->data )[j] != '\0' )
			{
				putc( ( arr[i]->data )[j], file );
				j++;
			}

			putc( '\n', file );
			currentID++;
		}
	}
}

void sortTree( Node **tree, int numNodes )
{
	int i;
	int swap_made;

	do
	{
		swap_made = FALSE;

		for ( i = 0; i < ( numNodes - 1 ); i++ )
		{
			if ( tree[i + 1]->ID < tree[i]->ID )
			{
				Node *temp = tree[i];
				tree[i] = tree[i + 1];
				tree[i + 1] = temp;

				swap_made = TRUE;
			}
		}
		
	}while ( swap_made );
}