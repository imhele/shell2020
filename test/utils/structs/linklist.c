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
  HLIB_ASSERT_TEST(testLinkListGetter);
}
