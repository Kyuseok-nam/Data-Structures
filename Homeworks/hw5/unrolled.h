#ifndef unrolled_h_
#define unrolled_h_
// A simplified implementation of the STL list container class,
// including the iterator, but not the const_iterators.  Three
// separate classes are defined: a Node class, an iterator class, and
// the actual list class.  The underlying list is doubly-linked, but
// there is no dummy head node and the list is not circular.
#include <cassert>
#include <array>
#include <iostream>

const int NUM_ELEMENTS_PER_NODE = 6;
// -----------------------------------------------------------------
// NODE CLASS
template <class T>
class Node {
public:
    Node(): next_(NULL),prev_(NULL),num_elements(0) {}
    Node(const T& v){ next_=NULL; prev_=NULL; num_elements = 1; elements[0]=v;}
    Node(const Node<T>& v){
        next_ = NULL;
        prev_ = NULL;
        num_elements = v.num_elements;
        for(int i=0; i< v.num_elements;i++){
            elements[i] = v.elements[i];
        }
    }
    // REPRESENTATION
    Node<T>* next_;
    Node<T>* prev_;
    int num_elements;
    T elements[NUM_ELEMENTS_PER_NODE];
};

// A "forward declaration" of this class is needed
template <class T> class UnrolledLL;

// -----------------------------------------------------------------
// LIST ITERATOR
template <class T>
class list_iterator {
public:
    // default constructor, copy constructor, assignment operator, & destructor
    list_iterator(Node<T>* p=NULL,int o = 0) : ptr_(p),offset(o) {}
    // NOTE: the implicit compiler definitions of the copy constructor,
    // assignment operator, and destructor are correct for this class

    // dereferencing operator gives access to the value at the pointer
    T& operator*()  { return ptr_->elements[offset];  }

    // increment & decrement operators
    list_iterator<T>& operator++() { // pre-increment, e.g., ++iter
        if(offset == (ptr_->num_elements)-1 ){
            ptr_ = ptr_->next_;
            offset = 0;
        }
        else{
            offset+=1;
        }
        return *this;
    }
    list_iterator<T> operator++(int) { // post-increment, e.g., iter++
        list_iterator<T> temp(*this);
        if(offset == (ptr_->num_elements)-1 ){
            ptr_ = ptr_->next_;
            offset = 0;
        }
        else{
            offset+=1;
        }
        return temp;
    }
    list_iterator<T>& operator--() { // pre-decrement, e.g., --iter
        if(offset == 0){
            ptr_ = ptr_->prev_;
            offset = ptr_->num_elements-1;
        }
        else{
            offset -=1;
        }
        return *this;
    }
    list_iterator<T> operator--(int) { // post-decrement, e.g., iter--
        list_iterator<T> temp(*this);
        if(offset == 0){
            ptr_ = ptr_->prev_;
            offset = ptr_->num_elements-1;
        }
        else{
            offset -=1;
        }
        return temp;
    }
    // the dslist class needs access to the private ptr_ member variable
    friend class UnrolledLL<T>;

    // Comparions operators are straightforward
    bool operator==(const list_iterator<T>& r) const {
        return ptr_ == r.ptr_ && offset == r.offset; }
    bool operator!=(const list_iterator<T>& r) const {
        return (ptr_ != r.ptr_ || offset != r.offset); }

private:
    // REPRESENTATION
    Node<T>* ptr_;    // ptr to node in the list
    int offset;
};

// -----------------------------------------------------------------
// LIST CLASS DECLARATION
// Note that it explicitly maintains the size of the list.
template <class T>
class UnrolledLL {
public:
    // default constructor, copy constructor, assignment operator, & destructor
    UnrolledLL() : head_(NULL), tail_(NULL), size_(0) {}
    UnrolledLL(const UnrolledLL<T>& old) { copy_list(old); }
    UnrolledLL& operator= (const UnrolledLL<T>& old);
    ~UnrolledLL() { destroy_list(); }

    typedef list_iterator<T> iterator;

    // simple accessors & modifiers
    unsigned int size() const { return size_; }
    bool empty() const { return head_ == NULL; }
    void clear() { destroy_list(); }

    // read/write access to contents
    const T& front() const { return head_->elements[0];  }
    T& front() { return head_->elements[0]; }
    const T& back() const { return tail_->elements[tail_->num_elements-1]; }
    T& back() { return tail_->elements[tail_->num_elements-1]; }

    // modify the linked list structure
    void push_front(const T& v);
    void pop_front();
    void push_back(const T& v);
    void pop_back();
    void print(std::ostream& ostr);

    iterator erase(iterator itr);
    iterator insert(iterator itr, const T& v);
    iterator begin() { return iterator(head_,0); }
    iterator end() { return iterator(NULL,0); }

private:
    // private helper functions
    void copy_list(const UnrolledLL<T>& old);
    void destroy_list();

    //REPRESENTATION
    Node<T>* head_;
    Node<T>* tail_;
    unsigned int size_;
};

// -----------------------------------------------------------------
// LIST CLASS IMPLEMENTATION
template <class T>
UnrolledLL<T>& UnrolledLL<T>::operator= (const UnrolledLL<T>& old) {
    // check for self-assignment
    if (&old != this) {
        destroy_list();
        copy_list(old);
    }
    return *this;
}

template <class T>
void UnrolledLL<T>::push_front(const T& v) {
    Node<T>* tmp = head_;
    //if the list is empty
    if(!head_){
        Node<T>* newp = new Node<T>(v);
        head_ = tail_ = newp;
    }
    //if there's at least one node
    else{
        //if the elements array is not full in the head node
        if(tmp->num_elements < NUM_ELEMENTS_PER_NODE){
            int num = tmp->num_elements;
            for(int i=num;i>0;i--){
                tmp->elements[i] = tmp->elements[i-1];
            }
            tmp->elements[0] = v;
            tmp->num_elements +=1;
        }
        //if the elements array is full in head node
        else{
            Node<T>* newp = new Node<T>(v);
            head_->prev_ = newp;
            newp->next_ = head_;
            head_ = newp;
        }
    }
    size_++;
}

template <class T>
void UnrolledLL<T>::pop_front() {
    Node<T>* tmp = head_;
    //if it is a empty list
    if(tmp == NULL){}
    //if the head node has only 1 element inside
    else if(tmp->num_elements==1){
        //if the list has only one node
        if(tmp->next_ == NULL){
            delete head_;
            head_ = NULL;
            tail_ = NULL;
        }
        //if the list has more than one node
        else{
            head_ = tmp->next_;
            delete tmp;
            head_->prev_ = NULL;
        }
        size_--;
    }
    // if the head node has more than 1 elements inside
    else{
        int num = tmp->num_elements;
        for(int i=0; i<num-1;i++){
            tmp->elements[i] = tmp->elements[i+1];
        }
        tmp->num_elements -= 1;
        size_--;
    }
}

template <class T>
void UnrolledLL<T>::push_back(const T& v) {
    // special case: initially empty list
    if (!tail_) {
        Node<T>* newp = new Node<T>(v);
        head_ = tail_ = newp;
    }
    // normal case: at least one node already
    else {
        //if the array in tail node is not full
        if(tail_->num_elements <NUM_ELEMENTS_PER_NODE){
            tail_->elements[tail_->num_elements] = v;
            tail_->num_elements +=1;
        }
        //if the array in tail node is full
        else{
            Node<T>* newp = new Node<T>(v);
            newp->prev_ = tail_;
            tail_->next_ = newp;
            tail_ = newp;
        }
    }
    ++size_;
}

template <class T>
void UnrolledLL<T>::pop_back() {
    Node<T>*tmp = tail_;
    //if the list is empty
    if(tmp == NULL){}
    //if there is only 1 elements in tail node
    else if(tmp->num_elements == 1){
        //if there is only one node in list
        if(tmp->prev_ == NULL){
            delete tmp;
            head_ = NULL;
            tail_ = NULL;
        }
        //if there's more than one node in list
        else{
            tail_ = tmp->prev_;
            delete tmp;
            tail_->next_ = NULL;
        }
        --size_;
    }
    //if there is more than 1 element in tail node
    else{
        tmp->num_elements-=1;
        --size_;
    }
}

//print function that prints the elements inside the list
template <class T>
void UnrolledLL<T>::print(std::ostream& ostr) {
    UnrolledLL<T>::iterator itr = this->begin();
    int node_num = 1;
    while(itr.ptr_ != NULL){
        std::cout<<"Node "<<node_num<<": ";
        for(int i=0;i<itr.ptr_->num_elements;i++){
            ostr<<itr.ptr_->elements[i]<<" ";
        }
        ostr<<std::endl;
        itr.ptr_ = itr.ptr_->next_;
        node_num++;
    }
    ostr<<std::endl;
}



// do these lists look the same (length & contents)?
template <class T>
bool operator== (UnrolledLL<T>& left, UnrolledLL<T>& right) {
    if (left.size() != right.size()) return false;
    typename UnrolledLL<T>::iterator left_itr = left.begin();
    typename UnrolledLL<T>::iterator right_itr = right.begin();
    // walk over both lists, looking for a mismatched value
    while (left_itr != left.end()) {
      if (*left_itr != *right_itr) return false;
      left_itr++; right_itr++;
    }
    return true;
}


template <class T>
bool operator!= (UnrolledLL<T>& left, UnrolledLL<T>& right){ return !(left==right); }


template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::erase(iterator itr) {
    assert (size_ > 0);
    --size_;
    //if there is only one element in that node
    if(itr.ptr_ -> num_elements ==1){
        iterator result(itr.ptr_->next_,0);
        // One node left in the list.
        if (itr.ptr_ == head_ && head_ == tail_) {
          head_ = tail_ = NULL;
        }
        // Removing the head in a list with at least two nodes
        else if (itr.ptr_ == head_) {
          head_ = head_->next_;
          head_->prev_ = NULL;
        }
        // Removing the tail in a list with at least two nodes
        else if (itr.ptr_ == tail_) {
          tail_ = tail_->prev_;
          tail_->next_ = NULL;
        }
        // Normal remove
        else {
          itr.ptr_->prev_->next_ = itr.ptr_->next_;
          itr.ptr_->next_->prev_ = itr.ptr_->prev_;
        }
        delete itr.ptr_;
        return result;
    }
    //if there is more than 1 element in that node
    else{
        for(int i = itr.offset; i<itr.ptr_->num_elements-1;i++){
            itr.ptr_->elements[i] = itr.ptr_->elements[i+1];
        }
        itr.ptr_->num_elements-=1;
        //if offset is equal to number of elements in that node
        //move on to the next node;
        if(itr.offset == itr.ptr_->num_elements){
            iterator p(itr.ptr_->next_,0);
            return p;
        }
        //if it is not the end of the array move on to the next element
        else{
            iterator p(itr.ptr_,itr.offset);
            return p;
        }
    }
}


template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::insert(iterator itr, const T& v) {
    ++size_ ;
    //if the array in that node is not full
    if((itr.ptr_->num_elements) < NUM_ELEMENTS_PER_NODE){
        for(int i=itr.ptr_->num_elements-1; i>itr.offset-1;i--){
            itr.ptr_->elements[i+1] = itr.ptr_->elements[i];
        }
        itr.ptr_->elements[itr.offset] = v;
        itr.ptr_->num_elements+=1;
    }
    //if the array in that node is full
    else{
        Node<T>* p = new Node<T>(itr.ptr_->elements[NUM_ELEMENTS_PER_NODE-1]);
        p->prev_ = itr.ptr_;
        p->next_ = itr.ptr_->next_;
        itr.ptr_->next_ = p;
        //if itr is the tail node
        if (itr.ptr_ == tail_)
          tail_ = p;
        //if it is not the tail node
        else
          p->next_->prev_ = p;
        for(int i=NUM_ELEMENTS_PER_NODE-1;i>itr.offset;i--){
            itr.ptr_->elements[i] = itr.ptr_->elements[i-1];
        }
        itr.ptr_->elements[itr.offset] = v;
    }
    return iterator(itr);
}


template <class T>
void UnrolledLL<T>::copy_list(const UnrolledLL<T>& old) {
    size_ = old.size_;
    // Handle the special case of an empty list.
    if (size_ == 0) {
      head_ = tail_ = NULL;
      return;
    }
    // Create a new head node.
    head_ = new Node<T>(*(old.head_));
    // tail_ will point to the last node created and therefore will move
    // down the new list as it is built
    tail_ = head_;
    // old_p will point to the next node to be copied in the old list
    Node<T>* old_p = old.head_->next_;
    // copy the remainder of the old list, one node at a time
    while (old_p) {
        tail_->next_ = new Node<T>(*old_p);
        tail_->next_->prev_ = tail_;
        tail_ = tail_->next_;
        old_p = old_p->next_;
    }
}

template <class T>
void UnrolledLL<T>::destroy_list() {
    Node<T>*p = head_;
    Node<T>*tmp;
    while(p!=NULL){
        tmp = p->next_;
        delete p;
        p = tmp;
    }
    size_ = 0;
    head_ = NULL;
    tail_ = NULL;
}

#endif
