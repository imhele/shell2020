#include "../../../main.h"

bool testMapCreate()
{
  int *test = HLIB_CALLOC(int);
  struct Map *map = MapCreate(test);
  bool flag = test == map->value;
  MapFree(&map);
  return flag;
}

bool testMapHas()
{
  struct MapItem *a = HLIB_CALLOC(struct MapItem);
  struct MapItem *b = HLIB_CALLOC(struct MapItem);
  a->key = (void *)1, a->value = (void *)10;
  b->key = (void *)2, b->value = (void *)20;
  struct Map *map = LinkListPush(MapCreate(NULL), a, b, ENDARG);

  bool flag = MapHas(map, a->key, DEFAULTARG) && MapHas(map, b->key, DEFAULTARG);
  MapFree(&map);
  return flag;
}

bool testMapGet()
{
  struct MapItem *a = HLIB_CALLOC(struct MapItem);
  struct MapItem *b = HLIB_CALLOC(struct MapItem);
  a->key = (void *)1, a->value = (void *)10;
  b->key = (void *)2, b->value = (void *)20;
  struct Map *map = LinkListPush(MapCreate(NULL), a, b, ENDARG);

  bool flag = MapGet(map, a->key, DEFAULTARG)->value == a->value;
  MapFree(&map);
  return flag;
}

bool testMapSet()
{
  bool flag = true;
  struct Map *map = MapCreate(NULL);
  MapSet(map, (void *)1, (void *)10, DEFAULTARG);

  flag = flag && MapGet(map, (void *)1, DEFAULTARG)->value == (void *)10;
  void *deleted_value = MapSet(map, (void *)1, (void *)20, DEFAULTARG);
  flag = flag && deleted_value == (void *)10;
  flag = flag && MapGet(map, (void *)1, DEFAULTARG)->value == (void *)20;
  MapFree(&map);
  return flag;
}

bool testMapFree()
{
  struct MapItem *item = HLIB_CALLOC(struct MapItem);
  struct Map *map = LinkListPush(MapCreate(NULL), item, ENDARG);
  MapFree(&map);
  return map == NULL;
}

int main()
{
  HLIB_ASSERT_TEST(testMapCreate);
  HLIB_ASSERT_TEST(testMapHas);
  HLIB_ASSERT_TEST(testMapGet);
  HLIB_ASSERT_TEST(testMapSet);
  HLIB_ASSERT_TEST(testMapFree);
  return 0;
}
