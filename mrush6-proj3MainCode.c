/* CS211 Summer 2022 Project 3

	Mustafa Rushdi,5/22/2022

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

int DebugMode;

/* TODO: create VertexNode and Polygon data types using typedef */

typedef struct vertexNode {
  int ID;
  struct vertexNode * next;
}
VertexNode;

typedef struct {
  VertexNode * vertices;
  int nVertices;
  int min;
  int max;
}
Polygon;

/* TODO: uncomment these function prototypes.
     Functions appear below main, in the order listed here. */

int addVertexToPolygon(Polygon * polygon, int vertexID);
VertexNode * findVertexInPolygon(Polygon polygon, int vertexID, int * location);
int size(Polygon polygon);
int isEmpty(Polygon polygon);
int remove1stVertexFromPolygon(Polygon * polygon);
void MinAndMaxFunction(Polygon polygon);

int main(int argc, char const * argv[]) {
  Polygon * p = NULL;
  p = (Polygon * ) malloc(sizeof(Polygon));
  p -> nVertices = 0;
  p -> vertices = NULL;

  /* TODO: Global variable DebugMode: if -d argument is given, additional information should be printed out as the program runs. */
  /* Look at lab 4 for help on this */
  DebugMode = FALSE;
  for (int i = 0; i < argc; i++) {
    if (strcmp(argv[i], "-d") == 0) {
      DebugMode = TRUE;
    }
  }

  /* TODO: Read data for the vertices comprising a Polygon (build a polygon) from standard input */
  /* Read data until a negative integer is read */

  //while loop used to take in user inputs and add it to the linked list
  int userInput;
  while (1) {
    scanf("%d", & userInput);
    if (userInput < 0) {
      break;
    } else {
      // if statment used to indicate weather the returning value is 0 then countinue and read in the next input else print the error message
      if (addVertexToPolygon(p, userInput) == 0) {
        continue;
      } else {
        printf("Something went wrong");
      }
    }
  }

  /* TODO: Report the Polygon's number of vertices, the specific list of vertex indecies, 
           and the minimum and maximum indices in the list.                           
  */

  if(DebugMode ==TRUE){
	  printf("the size is %d\n",size(*p));
  }

  // the first statment is used to print how many vertices are in the linked list
  printf("This polygon has %d vertices, with indices ", size( * p));
  // this is a function call to print out the min and max value within thge linked list
  MinAndMaxFunction( * p);

  /* TODO: Read data for a second set of vertices, and for each vertex ID search the Polygon's list of vertices, 
             if a matching vertex ID is found, report the address of the VertexNode where the ID was found. 
    */
  /* Read data until a negative integer is read */

  // we create a pointer to an interger so we can update the position of the value in whihc the second set of value matches a certain node
  int userInput2;
  int * position = NULL;
  int positions = 0;
  position = & positions;
  VertexNode * inputFound = NULL;
  while (1) {
    scanf("%d", & userInput2);
    if (userInput2 < 0) {
      break;
    } else {
      inputFound = findVertexInPolygon( * p, userInput2, & positions);
      //if statment to dertine weather the Node pointter is node or if it isnt if it is print the userInput else print the addres and position at which it is at
      if (inputFound == NULL) {
        printf("Vertex %d was not found.\n", userInput2);
      } else {
        printf("Vertex %d was found in VertexNode %d at address %p.\n", userInput2, positions, inputFound);
      }
    }
    //resets the position for the next value 
    * position = 0;
  }
  /* TODO: Make sure you free any dynamically allocated memory before the program ends.  
Use Valgrind to check, because TAs will. */

  //here we are looping through the remove vertex funtion until the list is empty
  int functionResults;
  while ((functionResults = remove1stVertexFromPolygon(p)) != -1) {
    if(isEmpty(*p)==1){
      break;
    }
    if(DebugMode == TRUE){
      printf("the values freed are %d \n", functionResults);
    }
  }
  free(p);
  p = NULL;
  return 0;
}

/* TODO: function definitions */

// function to add vertex to polygon
int addVertexToPolygon(Polygon * polygon, int vertexID) {
  int results;
  int dupplicateResult = 1;
  VertexNode * newNode = (VertexNode * ) malloc(sizeof(VertexNode));
  VertexNode * tempNode = NULL;
  //if the linked list is empty set the newly allocated node as the head
  if (polygon -> vertices == NULL) {
    newNode -> ID = vertexID;
    newNode -> next = NULL;
    polygon -> vertices = newNode;
    //if the list is not empty we go into another while loop to indicate weather there is a noide within the linked list that has the same value as the user input if it does we set a variable to zero  and free the memmory
    } else if (polygon -> vertices != NULL) {
    tempNode = polygon -> vertices;
    while (tempNode != NULL) {
      if (tempNode -> ID == vertexID) {
        dupplicateResult = 0;
        free(newNode);
        newNode = NULL;
        break;
      }
      tempNode = tempNode -> next;
    }
    //here if the value returned isnt from the while loop isnt zero and is set to its original value 1 we have the newNode set as the header
    if (dupplicateResult != 0) {
      newNode -> ID = vertexID;
      newNode -> next = polygon -> vertices;
      polygon -> vertices = newNode;
    }
  }
  if (polygon -> vertices != NULL) {
    results = 0;
  } else {
    results = -1;
  }
  return results;
};

/*
Return 0 if the vertex ID is successfully added to the polygon, or -1 otherwise.
Add vertices to the head of the linked list.
*/

//while loop to get the location and return the pointer at which the the values are the same at and break if there isnt any similarity then location as -1 and set as NULL
VertexNode * findVertexInPolygon(Polygon polygon, int vertexID, int * location) {
  while (polygon.vertices != NULL) {
    if (vertexID == polygon.vertices -> ID) {
      return polygon.vertices;
      if(DebugMode == TRUE){
        printf("Return true if the the vertex was found \n");
      }
      break;
    }
    * location += 1;
    polygon.vertices = polygon.vertices -> next;
  }
  * location = -1;
  return NULL;
};
/*
Return the address of the VertexNode in which the vertex ID was found.
If the vertex was not found, return NULL.

Use pointers to follow the links in the linked list, not a for loop.
Count as you go, and set * location to the position in the list or -1.
*/

//Return the number of vertices in the polygon.
int size(Polygon polygon) {
  while (polygon.vertices != NULL) {
    polygon.nVertices += 1;
    polygon.vertices = polygon.vertices -> next;
  }
  return polygon.nVertices;
};

//Return 1 if the polygon contains no vertices, or 0 otherwise.
int isEmpty(Polygon polygon) {
  if (polygon.vertices == NULL) {
    polygon.nVertices = 1;
  } else if (polygon.vertices != NULL) {
    polygon.nVertices = 0;
  }
  return polygon.nVertices;
};

//funvtion used to find the min and max values within the linked list
void MinAndMaxFunction(Polygon polygon) {
  //here we set polygon mmax and min to the first value at the head of the list
  polygon.max = polygon.vertices -> ID;
  polygon.min = polygon.vertices -> ID;
  //we then loop throught the linked list to first print out the nodes then using if staments to find the min and max;
  while (polygon.vertices != NULL) {
    printf("%d ", polygon.vertices -> ID);
    if (polygon.vertices -> ID > polygon.max) {
      polygon.max = polygon.vertices -> ID;
    }
    if (polygon.vertices -> ID < polygon.min) {
      polygon.min = polygon.vertices -> ID;
    }
    //go to the next node;
    polygon.vertices = polygon.vertices -> next;
  }
  printf("\nThe min and max vertices found are %d and %d respectively.\n", polygon.min, polygon.max);
}

//Removes one vertex from the Polygon from the head of the linked list,
//frees up memory associated with the VertexNode.
//Return the ID of the removed vertex if a vertex was successfully removed, or -1 otherwise.
int remove1stVertexFromPolygon(Polygon * polygon) {
  VertexNode * pTemp = NULL;
  int ID;
  if (isEmpty( * polygon) == 1) {
    ID = -1;
    if(DebugMode == TRUE){
      printf("if the linked list is empty then print %d\n ", ID);
    }
    return ID;
  } else {
    pTemp = polygon -> vertices;
    ID = polygon -> vertices -> ID;
    polygon -> vertices = pTemp -> next;
    pTemp -> next = NULL;
    free(pTemp);
    return ID;
    if(DebugMode == TRUE){
      printf("this will return the nade value that is getting deleted %d\n ", ID);
    }
  }
};
