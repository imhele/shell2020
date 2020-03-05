#include "../../../main.h"

bool testLinkListUnshift()
{
  struct LinkList *head = LinkListUnshift(NULL, 1, 2);
  bool flag = (long)head->value == 1 && (long)head->next->value == 2;
  LinkListFree(&head);
  return flag;
}

bool testLinkListFree()
{
  struct LinkList *head = LinkListUnshift(NULL, 1, 2);
  LinkListFree(&head);
  return head == NULL;
}

bool testLinkListGetter()
{
  struct LinkList *head = LinkListUnshift(NULL, 3, 4, 5);
  bool flag = (long)LinkListGetter(head, 0) == 3 && (long)LinkListGetter(head, 2) == 5;
  LinkListFree(&head);
  return flag;
}

int main()
{
  HLIB_ASSERT_TEST(testLinkListUnshift);
  HLIB_ASSERT_TEST(testLinkListFree);
  HLIB_ASSERT_TEST(testLinkListGetter);
}
