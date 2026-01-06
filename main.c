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
  unsigned char marked;
  ObjectType type;
  struct sObject* next;

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
  Object* firstObject;
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
//initializes VM
VM* newVM()
{
  VM* vm = malloc(sizeof(VM));
  vm->stackSize = 0;
  return vm;
}
// functions to manipulate the stack
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

Object* newObject(VM* vm, ObjectType type)
{
  Object* object = malloc(sizeof(Object));
  object->type = type;
  object->marked = 0;

  //Insert into the list of allocated objects
  object->next = vm->firstObject;
  vm->firstObject = object;

  return object;
}

void pushInt(VM* vm, int intValue)
{
  Object* object = newObject(vm, OBJ_INT);
  object->value = intValue;
  push(vm, object);
}

Object* pushPair(VM* vm)
{
  Object* object = newObject(vm, OBJ_PAIR);
  object->tail = pop(vm);
  object->head = pop(vm);

  push(vm, object);
  return object;
}

void mark(Object* object)
{
  /*
   * If already marked, finish.
   * Check this first to avoid recursing on cycles in object graph
   * */
  if(object->marked) return;

  object->marked = 1;

  if(object->type == OBJ_PAIR)
  {
    mark(object->head);
    mark(object->tail);
  }
}

void markAll(VM* vm)
{
  for (int i = 0; i < vm->stackSize; i++)
  {
    mark(vm->stack[i]);
  }
}

int main()
{
  return 0;
}
