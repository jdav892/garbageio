#include <stdio.h>
#include <stdlib.h>

#define STACK_MAX 256

typedef enum
{
  OBJ_INT,
  OBJ_PAIR
} ObjectType;

typedef struct sObject
{
  ObjectType type;

  union
  {
    //OBJ_INT
    int value;

    //OBJ_PAIR
    struct
    {
      struct sObject* head;
      struct sObject* tail;
    };
  };
} Object;

typedef struct
{
  Object* stack[STACK_MAX];
  int stackSize;
} VM;

VM* newVM()
{
  VM* vm = malloc(sizeof(VM));
  vm->stackSize = 0;
  return vm;
}

int main()
{
  return 0;
}
