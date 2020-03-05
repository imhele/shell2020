#include "../../../main.h"

struct MapItem a = {(void *)1, (void *)10};
struct MapItem b = {(void *)2, (void *)20};
struct MapItem c = {(void *)1, (void *)30};

bool testMapHas()
{
  struct LinkList *map = LinkListUnshift(NULL, &a, &b, ENDARG);
  bool flag = MapHas(map, a.key, ENDARG) && MapHas(map, b.key, ENDARG);
  LinkListFree(&map);
  return flag;
}

bool testMapGet()
{
  struct LinkList *map = LinkListUnshift(NULL, &a, &b, ENDARG);
  bool flag = MapGet(map, a.key, ENDARG)->value == a.value;
  LinkListFree(&map);
  return flag;
}

bool testMapSet()
{

  struct LinkList *map = LinkListUnshift(NULL, &a, &b, ENDARG);
  bool flag = MapGet(map, a.key, ENDARG)->value == a.value;
  map = MapSet(map, c.key, c.value, ENDARG);
  flag = flag && MapGet(map, a.key, ENDARG)->value == c.value;
  LinkListFree(&map);
  return flag;
}

int main()
{
  HLIB_ASSERT_TEST(testMapHas);
  HLIB_ASSERT_TEST(testMapGet);
  HLIB_ASSERT_TEST(testMapSet);
}
