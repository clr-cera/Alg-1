#include "skipList.h"

typedef struct cell_{
  Word value;
  struct cell_* next;
}cellObj;
typedef cellObj* Cell;

typedef struct skipList_{

}skipListObj;
typedef skipListObj* SkipList;
