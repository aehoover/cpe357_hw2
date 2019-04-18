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
	char *oneLine = malloc( sizeof( char ) * size );
	char c;
	int i = 0;

	if ( oneLine == NULL )
	{
		printf("malloc has failed.\n" );
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
	int i = 0;

	if ( string == NULL )
	{
		free( newNode );
		newNode = NULL;
	}
	else
	{
		int letter_location = 0;
		char *ID_Nums;

		while( string[i] != 'Q' && string[i] != 'A' )
		{
			i++;
		}

 		letter_location = i;
 		
		ID_Nums = ( char * ) malloc( sizeof( char ) * ( i + 1 ) );
		
		for ( i = 0; i < letter_location; i++ )
		{
			ID_Nums[i] = string[i];
		}

		newNode->ID = atoi( ID_Nums );
		newNode->type = string[i];
		newNode->data = &( string[letter_location + 1] );

		free( ID_Nums );
	}

	return newNode;
}

void buildTree( FILE * file, Node **arr ) /* Doesn't account for resizing tree */
{
	char *lineFromFile = NULL;
	int i = 0;

	while ( ( lineFromFile = readline( file ) ) != NULL )
	{
		Node *newNode = createNode( lineFromFile );
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
		i++;
	}

}
