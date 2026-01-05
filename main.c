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

void assert(int condition, const char* message)
{
  if (!condition)
  {
    printf("%s\n", message);
    exit(1);
  }
}

VM* newVM()
{
  VM* vm = malloc(sizeof(VM));
  vm->stackSize = 0;
  return vm;
}

void push(VM* vm, Object* value)
{
  assert(vm->stackSize < STACK_MAX, "Stack overflow");
  vm->stack[vm->stackSize++] = value;
}

Object* pop(VM* vm)
{
  assert(vm->stackSize > 0, "Stack underflow");
  return vm->stack[--vm->stackSize];
}

int main()
{
  return 0;
}
