#include "../../../main.h"

bool testLinkListUnshift()
{
  struct LinkList *head = LinkListUnshift(NULL, 2, ENDARG);
  head = LinkListUnshift(head, 1, ENDARG);
  bool flag = (long)head->value == 1 && (long)head->next->value == 2;
  LinkListFree(&head);
  return flag;
}

bool testLinkListFree()
{
  struct LinkList *head = LinkListUnshift(NULL, 1, 2, ENDARG);
  LinkListFree(&head);
  return head == NULL;
}

bool testLinkListPush()
{
  struct LinkList *head = LinkListPush(NULL, 1, 2, ENDARG);
  head = LinkListPush(head, 3, ENDARG);
  bool flag = (long)LinkListGetter(head, 0) == 1 && (long)LinkListGetter(head, 2) == 3;
  LinkListFree(&head);
  return flag;
}

bool testLinkListLength()
{
  struct LinkList *head = LinkListPush(NULL, 1, 2, 3, ENDARG);
  bool flag = LinkListLength(head) == 3;
  LinkListFree(&head);
  return flag;
}

bool testLinkListSlice()
{
  bool flag = true;
  struct LinkList *new_head;
  struct LinkList *head = LinkListPush(NULL, 1, 2, 3, 4, ENDARG);

  new_head = LinkListSlice(head, 0, 3);
  flag = flag && new_head != head;
  flag = flag && LinkListLength(new_head) == 3;
  flag = flag && (long)LinkListGetter(new_head, 1) == 2;
  LinkListFree(&new_head);

  new_head = LinkListSlice(head, -3, 3);
  flag = flag && LinkListLength(new_head) == 2;
  flag = flag && (long)LinkListGetter(new_head, 0) == 2;
  flag = flag && (long)LinkListGetter(new_head, 1) == 3;
  LinkListFree(&new_head);

  LinkListFree(&head);
  return flag;
}

bool testLinkListLocate()
{
  struct LinkList *head = LinkListUnshift(NULL, 3, 4, 5, ENDARG);
  bool flag = LinkListLocate(head, 2) == head->next->next;
  LinkListFree(&head);
  return flag;
}

bool testLinkListGetter()
{
  struct LinkList *head = LinkListUnshift(NULL, 3, 4, 5, ENDARG);
  bool flag = (long)LinkListGetter(head, 0) == 3 && (long)LinkListGetter(head, 2) == 5;
  LinkListFree(&head);
  return flag;
}

bool testLinkListCopyHead()
{
  struct LinkList *head = LinkListUnshift(NULL, 1, 2, ENDARG);
  struct LinkList *copied = LinkListCopyHead(head);
  bool flag = copied != head && copied->next == head->next;
  LinkListFree(&head);
  free(copied);
  return flag;
}

bool testLinkListConcat()
{
  bool flag = true;
  struct LinkList *a = LinkListPush(NULL, 1, 2, ENDARG);
  struct LinkList *b = LinkListPush(NULL, 3, 4, ENDARG);
  struct LinkList *concated = LinkListConcat(NULL, a, NULL, b, ENDARG);
  flag = flag && LinkListLength(concated) == 4;
  flag = flag && (long)LinkListGetter(concated, 0) == 1;
  flag = flag && (long)LinkListGetter(concated, 3) == 4;
  LinkListFreeN(&a, &b, &concated, ENDARG);
  return flag;
}

bool __testLinkListFind(void *value, int index, struct LinkList *head)
{
  return (long)value == 2;
}

bool testLinkListFind()
{
  struct LinkList *head = LinkListPush(NULL, 1, 2, 3, ENDARG);
  struct LinkList *result = LinkListFind(head, __testLinkListFind);
  bool flag = result != head && result == head->next;
  LinkListFree(&head);
  return flag;
}

bool testLinkListSome()
{
  bool flag = true;
  struct LinkList *head_a = LinkListPush(NULL, 1, 2, 3, ENDARG);
  struct LinkList *head_b = LinkListPush(NULL, 4, 5, 6, ENDARG);
  flag = flag && LinkListSome(head_a, __testLinkListFind);
  flag = flag && !LinkListSome(head_b, __testLinkListFind);
  LinkListFreeN(&head_a, &head_b, ENDARG);
  return flag;
}

void *__testLinkListMap(void *value, int index, struct LinkList *head)
{
  return (void *)((long)value - 1);
}

bool testLinkListMap()
{
  struct LinkList *head = LinkListPush(NULL, 1, 2, 3, ENDARG);
  struct LinkList *result = LinkListMap(head, __testLinkListMap);
  bool flag = result != head && (long)LinkListGetter(result, 2) == 2;
  LinkListFree(&head);
  LinkListFree(&result);
  return flag;
}

void __testLinkListForeach(void *value, int index, struct LinkList *head)
{
  LinkListLocate(head, index)->value = value - 1;
}

bool testLinkListForeach()
{
  struct LinkList *head = LinkListPush(NULL, 1, 2, 3, ENDARG);
  LinkListForeach(head, __testLinkListForeach);
  bool flag = (long)LinkListGetter(head, 2) == 2;
  LinkListFree(&head);
  return flag;
}

void *__testLinkListReduce(void *memo, void *value, int index, struct LinkList *head)
{
  return (void *)((long)memo + (long)value);
}

bool testLinkListReduce()
{
  struct LinkList *head = LinkListPush(NULL, 1, 2, 3, ENDARG);
  void *result = LinkListReduce(head, __testLinkListReduce, (void *)0);
  bool flag = (long)result == 6;
  LinkListFree(&head);
  return flag;
}

int main()
{
  HLIB_ASSERT_TEST(testLinkListUnshift);
  HLIB_ASSERT_TEST(testLinkListFree);
  HLIB_ASSERT_TEST(testLinkListPush);
  HLIB_ASSERT_TEST(testLinkListLength);
  HLIB_ASSERT_TEST(testLinkListSlice);
  HLIB_ASSERT_TEST(testLinkListLocate);
  HLIB_ASSERT_TEST(testLinkListGetter);
  HLIB_ASSERT_TEST(testLinkListCopyHead);
  HLIB_ASSERT_TEST(testLinkListConcat);
  HLIB_ASSERT_TEST(testLinkListFind);
  HLIB_ASSERT_TEST(testLinkListSome);
  HLIB_ASSERT_TEST(testLinkListMap);
  HLIB_ASSERT_TEST(testLinkListForeach);
  HLIB_ASSERT_TEST(testLinkListReduce);
  return 0;
}
