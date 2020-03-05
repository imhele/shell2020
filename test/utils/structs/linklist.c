#include "../../../main.h"

bool testLinkListUnshift()
{
  struct LinkList *head = LinkListUnshift(NULL, 2, NULL);
  head = LinkListUnshift(head, 1, NULL);
  bool flag = (long)head->value == 1 && (long)head->next->value == 2;
  LinkListFree(&head);
  return flag;
}

bool testLinkListFree()
{
  struct LinkList *head = LinkListUnshift(NULL, 1, 2, NULL);
  LinkListFree(&head);
  return head == NULL;
}

bool testLinkListPush()
{
  struct LinkList *head = LinkListPush(NULL, 1, 2, NULL);
  head = LinkListPush(head, 3, NULL);
  bool flag = (long)LinkListGetter(head, 0) == 1 && (long)LinkListGetter(head, 2) == 3;
  LinkListFree(&head);
  return flag;
}

bool testLinkListLength()
{
  struct LinkList *head = LinkListPush(NULL, 1, 2, 3, NULL);
  bool flag = LinkListLength(head) == 3;
  LinkListFree(&head);
  return flag;
}

bool testLinkListSlice()
{
  bool flag = true;
  struct LinkList *new_head;
  struct LinkList *head = LinkListPush(NULL, 1, 2, 3, 4, NULL);

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

bool testLinkListGetter()
{
  struct LinkList *head = LinkListUnshift(NULL, 3, 4, 5, NULL);
  bool flag = (long)LinkListGetter(head, 0) == 3 && (long)LinkListGetter(head, 2) == 5;
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
  HLIB_ASSERT_TEST(testLinkListGetter);
}
