#include "../../../main.h"

bool testMapHas()
{
  struct MapItem *a = HLIB_CALLOC(struct MapItem);
  struct MapItem *b = HLIB_CALLOC(struct MapItem);
  a->key = (void *)1, a->value = (void *)10;
  b->key = (void *)2, b->value = (void *)20;
  struct Map *map = LinkListPush(MapCreate(), a, b, ENDARG);

  bool flag = MapHas(map, a->key, ENDARG) && MapHas(map, b->key, ENDARG);
  MapFree(&map);
  return flag;
}

bool testMapGet()
{
  struct MapItem *a = HLIB_CALLOC(struct MapItem);
  struct MapItem *b = HLIB_CALLOC(struct MapItem);
  a->key = (void *)1, a->value = (void *)10;
  b->key = (void *)2, b->value = (void *)20;
  struct Map *map = LinkListPush(MapCreate(), a, b, ENDARG);

  bool flag = MapGet(map, a->key, ENDARG)->value == a->value;
  MapFree(&map);
  return flag;
}

bool testMapSet()
{
  bool flag = true;
  struct Map *map = MapCreate();
  MapSet(map, (void *)1, (void *)10, ENDARG);

  flag = flag && MapGet(map, (void *)1, ENDARG)->value == (void *)10;
  void *deleted_value = MapSet(map, (void *)1, (void *)20, ENDARG);
  flag = flag && deleted_value == (void *)10;
  flag = flag && MapGet(map, (void *)1, ENDARG)->value == (void *)20;
  MapFree(&map);
  return flag;
}

bool testMapFree()
{
  struct MapItem *item = HLIB_CALLOC(struct MapItem);
  struct Map *map = LinkListPush(MapCreate(), item, ENDARG);
  MapFree(&map);
  return map == NULL;
}

int main()
{
  HLIB_ASSERT_TEST(testMapHas);
  HLIB_ASSERT_TEST(testMapGet);
  HLIB_ASSERT_TEST(testMapSet);
  HLIB_ASSERT_TEST(testMapFree);
}
