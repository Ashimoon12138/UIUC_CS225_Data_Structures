/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() {
  // @TODO: graded in MP3.1
     head_ = NULL;
     tail_ = NULL;
     length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_); //TODO??
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  if(tail_==NULL)
  return NULL;//
  else
  return List<T>::ListIterator(tail_->next); //TODO??
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ///TODO delete every ListNode using loop
  ///also set the variable to 0
  ListNode* ptr = head_;

  while (ptr != NULL) {
    if (ptr->next != NULL) {
      ptr = ptr->next;
      delete ptr -> prev;
    }
    else {
      delete ptr;
      ptr = NULL;
    }

  }


  length_ = 0;
  head_ = NULL;
  tail_ = NULL;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;

  if (head_ != NULL) {
    head_ ->prev = newNode;
    head_ = newNode;
  }
  if (tail_ == NULL) {
    head_ = newNode;
    tail_ = newNode;
  }
  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = NULL;
  newNode -> prev = tail_;
  if (tail_ != NULL) {
    tail_ -> next = newNode;
    tail_ = newNode;
  }
  if (tail_ == NULL) {
    head_ = newNode;
    tail_ = newNode;
  }
  // newNode = NULL; // QUESTION: DONE: NO NEED TODO, because is tack
  length_++;

}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  if (splitPoint == 0)
  return start;

  ListNode * curr = start;
  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL) {
      curr->prev->next = NULL;
      curr->prev = NULL;
      return curr;
  }

  return NULL;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.FAILED:
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  ListNode* curr = head_;
  if (curr == NULL || curr == tail_ || curr->next == tail_) {
    return;
  }
  ListNode* temp = tail_;
  while(curr->next != tail_) {
    temp->next = curr->next;
    temp = temp->next;
    temp->prev = tail_;
    tail_ = temp;
    curr -> next = curr->next->next;
    curr ->next -> prev = curr;
    curr = curr -> next;
    tail_->next =NULL;
  }
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  if (startPoint == endPoint)
  return;
  if (startPoint == NULL || endPoint == NULL)
  return;
  // if(startPoint == head_)
  // head_ = endPoint;

  ListNode* currRvs =startPoint->next;
  ListNode* prevRvs = startPoint;
  ListNode* nextRvs = startPoint->next->next;
  if(startPoint ->prev != NULL) {
    startPoint->prev->next = endPoint;
  }
  endPoint->prev = startPoint->prev;
  startPoint->next = endPoint->next;
  if (endPoint->next != NULL) {
    endPoint->next->prev = startPoint;
  }
  prevRvs->prev = currRvs;
  while(currRvs != endPoint && currRvs != NULL) {
    currRvs->next = prevRvs;
    currRvs->prev = nextRvs;
    prevRvs = currRvs;
    currRvs = nextRvs;
    nextRvs = nextRvs->next;
  }
    currRvs ->next = prevRvs;
   ListNode* temp = startPoint;
   startPoint = endPoint;
   endPoint = temp;
   if(startPoint->prev == NULL) {
    head_ = startPoint;
  }

   if(endPoint->next == NULL) {
    tail_ = endPoint;
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  if(n < 0 || length_ <= 0)
  return;

  int m = length_/n;
  ListNode* startPoint = head_;
  ListNode* endPoint = startPoint;

  if(m == 0) {
    endPoint = tail_;
    reverse(head_, tail_);
  }

  for(int i = 0; i < m; i++) {

    for (int i =0; i<n-1; i++) {
      // endPoint = startPoint;
      endPoint = endPoint->next;
    }
    reverse(startPoint,endPoint);
    startPoint = endPoint->next;
    endPoint = startPoint;
  }

  if(endPoint == tail_ || endPoint == NULL)
  return;
  else {
    endPoint = tail_;
    reverse(startPoint,endPoint);
  }

}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  ListNode* newHead = first; //return that pointor the head of merged list;
  ListNode* currMer = first; //represent the current node pointor of the merged list;
  ListNode* merFirst = first; //represent the current node pointor used to compare in the first list;
  ListNode* merSecond = second; //same for the second list;

  if (first == NULL && second != NULL)
  return second;
  if (first != NULL && second == NULL)
  return first;
  if (first == NULL && second == NULL)
  return NULL;

    if (first->data < second->data) { //to locate the newhead used the smaller head of two list
      newHead = merFirst;
      currMer = newHead;
      merFirst = merFirst->next;
    }
    else {
      newHead = merSecond;
      currMer = newHead;
      merSecond = merSecond->next;
    }
/*traverse the whole two list, compare merFirst and merSecond one by one
  use currMer and merFirst/merSecond to adjust the list sequences   */
    while (merFirst != NULL && merSecond != NULL) {
      if(merSecond->data < merFirst->data) {
        currMer->next = merSecond;
        merSecond->prev = currMer;
        currMer = merSecond;
        merSecond = merSecond->next;
      }
      else {
        currMer->next = merFirst;
        merFirst->prev = currMer;
        currMer = merFirst;
        merFirst = merFirst->next;
      }
    }
 /*once one of the list hit the end get out of the while loop and adjust which one
    equal to null and set the other list rest nodes */
    if(merFirst == NULL) {
      currMer->next = merSecond;
      merSecond->prev = currMer;
    }
    else {
      currMer->next = merFirst;
      merFirst->prev = currMer;
    }

    return newHead; //return the newHead;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if(start == NULL)
  return NULL;

  if (chainLength == 1 || chainLength == 0) //base case
  return start;


  int n1 = chainLength/2;
  int n2 = chainLength - n1;
  ListNode* merRecur = split(start,n1);
  return merge(mergesort(start, n1), mergesort(merRecur, n2));
  //recursive: first consider the base case and then call myself
}
