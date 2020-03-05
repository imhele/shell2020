#include "../../../main.h"

int testLinkListUnshift()
{
  struct LinkList *head = LinkListUnshift(NULL, 1, 2);
  int flag = (int)head->value == 1 && (int)head->next->value == 2;
  LinkListFree(&head);
  return flag;
}

int main()
{
  HLIB_ASSERT_TEST(testLinkListUnshift);
}
