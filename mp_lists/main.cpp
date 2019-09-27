#include "List.h"

#include "cs225/catch/catch.hpp"
#include "tests/tests_helper.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

// #include "../List.h"

using namespace std;

// template <class T>
// void  List<T>::printList(List<T>::ListNode *head) {
//   if (head == NULL) {
//     cout << "Empty list" << endl;
//     return;
//   }
//
//   ListNode *temp = head;
//   int count = 0;
//   while(temp != NULL) {
//     cout << "ListNode " << count << ": " << temp ->data << endl;
//     count++;
//     temp = temp->next;
//   }
// }


int main() {
  // Example #1
  List<int> list1;

  list1.insertBack(1);
  list1.insertBack(2);
  list1.insertBack(5);
  list1.insertBack(7);
  list1.insertBack(8);
  list1.insertBack(10);
  list1.insertBack(15);


  List<int> list2;

  list2.insertBack(0);
  list2.insertBack(6);
  list2.insertBack(9);
  list2.insertBack(11);
  list2.insertBack(13);
  list2.insertBack(14);
  list2.insertBack(19);


  // stringstream s1;
  // list2.print(s1);
  // cout << s1.str() << endl;

  // list.reverseNth(4);
  cout << list1 << endl;
  //   list.reverseNth(9);
  cout << list2 << endl;
  //     list.reverseNth(2);
  // cout << list << endl;
  // list.reverseNth(3);
  //   cout << list << endl;
  // List<T>::ListNode* list3 = merge(list1.head_, list2.head_);

  // cout<<"First List:"<<endl;
  // printList(&n_0);

  // stringstream s;
  // list.print(s);
  // cout << s.str() << endl;

  cout << "Size: " << to_string(list1.size()) << endl;
  cout << "Size: " << to_string(list2.size()) << endl;

  // ListNode *r1 = &n_22;
  // cout<<"Symmetric Difference"<<endl;
  // printList(r1);

  // r1.print(s);

  // cout << s << endl;

  cout<<endl;
  return 0;
}
