#include <stdio.h>
#include <stdlib.h>

#include "checkit.h"
#include "funcs.h"

void test_createNode()
{
   Node *nodePtr = createNode( "0QDoes it hunt mice?\n" );

   checkit_int( nodePtr->ID, 0 );
   checkit_char( nodePtr->type, 'Q' );
   checkit_string( nodePtr->data, "Does it hunt mice?\n" );

   free( nodePtr );
   
}

void test_createNode2()
{
   Node *nodePtr = createNode( NULL );

   checkit_int( nodePtr, 0 );
}

int main(void)
{
   test_createNode();
   test_createNode2();

   return 0;
}
