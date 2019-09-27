
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare> //@QUESTION: class Compare std::less
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    return 2 * currentIdx;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return (2 * currentIdx) + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    return currentIdx/2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    if(2 * currentIdx < _elems.size()) return true;  //QUESTION(Done) : >= ??
    else return false;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    if(!hasAChild(currentIdx)) return 0;
    else {
      size_t left = this->leftChild(currentIdx);
      size_t right = this->rightChild(currentIdx);

      //@ consider only has the left child
      if(right < _elems.size()) {
        if (higherPriority(_elems[left], _elems[right])) return left;
        else return right;
      }
      return left;
    }
    // return 0;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
    if(!hasAChild(currentIdx)) return;

    size_t minChildIdx = maxPriorityChild(currentIdx);
    if(higherPriority(_elems[minChildIdx], _elems[currentIdx])) {
      std::swap(_elems[minChildIdx],_elems[currentIdx]);
      heapifyDown(minChildIdx);
    }
    // else return;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
    _elems.push_back(T()); //@!!!!!!!!!!
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    // @TODO Construct a heap using the buildHeap algorithm
    _elems.push_back(T());
    _elems.insert(_elems.end() , elems.begin(), elems.end());
    // for(const T & i : elems) {
    //   _elems.push_back(i);
    // }
    // std::sort(_elems.begin() + 1, _elems.end());
    size_t size = _elems.size();
    for (unsigned i = parent(size-1); i > 0; i--) {
      heapifyDown(i);
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    if(!empty()) {
      size_t size = _elems.size();
      T minValue = _elems[1];
      _elems[1] = _elems[size -1];
      _elems.pop_back();

      heapifyDown(1);
      return minValue;
    }
    else return T();
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    if(!empty()) return _elems[1];
    return T(); //@ QUESTION: WHAT IS T() used to do?
    // int();
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    size_t size = _elems.size();
    _elems.push_back(elem);
    heapifyUp(size);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    T origin = _elems[idx];
    _elems[idx] = elem;
    if(higherPriority(origin, elem)) heapifyDown(idx);
    else heapifyUp(idx);

}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    // return _elems.size() < 2;
    return _elems.size() == 1;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
