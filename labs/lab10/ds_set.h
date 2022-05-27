// Partial implementation of binary-tree based set class similar to std::set.

#ifndef ds_set_h_
#define ds_set_h_
#include <iostream>
#include <utility>

int up_count =0;
int down_count = 0;
// -------------------------------------------------------------------
// DS_ SET CLASS
template <class T>
class ds_set {
public:

  // -------------------------------------------------------------------
  // TREE NODE CLASS
  class TreeNode {
  public:
    TreeNode() : left(NULL), right(NULL), parent(NULL) {}
    TreeNode(const T& init) : value(init), left(NULL), right(NULL), parent(NULL) {}
    T value;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent; // to allow implementation of iterator increment & decrement
  };

  // -------------------------------------------------------------------
  // TREE NODE ITERATOR CLASS
  class iterator {
  public:
    iterator() : ptr_(NULL) {}
    iterator(TreeNode* p,TreeNode* root) : ptr_(p),root_(root) {}
    iterator(const iterator& old) : ptr_(old.ptr_) {}
    ~iterator() {}
    iterator& operator=(const iterator& old) { ptr_ = old.ptr_; return *this; }
    // operator* gives constant access to the value at the pointer
    const T& operator*() const { return ptr_->value; }
    // comparions operators are straightforward
    friend bool operator== (const iterator& lft, const iterator& rgt)
    { return (lft.ptr_ == rgt.ptr_); }
    friend bool operator!= (const iterator& lft, const iterator& rgt)
    { return (lft.ptr_ != rgt.ptr_); }

    // increment & decrement operators
    iterator & operator++() {
      if (ptr_->right != NULL) { // find the leftmost child of the right node
        ptr_ = ptr_->right;
          up_count+=1;
          std::cout<<"down: "<<down_count<<" up: "<<up_count<<std::endl;
          while (ptr_->left != NULL) {
              ptr_ = ptr_->left;
              down_count+=1;
              std::cout<<"down: "<<down_count<<" up: "<<up_count<<std::endl;
          }
      }
      else { // go upwards along right branches...  stop after the first left
          while (ptr_->parent != NULL && ptr_->parent->right == ptr_) {
              ptr_ = ptr_->parent;
              up_count+=1;
              std::cout<<"down: "<<down_count<<" up: "<<up_count<<std::endl;
          }
        ptr_ = ptr_->parent;
        up_count+=1;
          std::cout<<"down: "<<down_count<<" up: "<<up_count<<std::endl;
      }
      return *this;
    }
    iterator operator++(int) {
      iterator temp(*this);
      ++(*this);
      return temp;
    }
    iterator & operator--() {
        if(ptr_==NULL){
            ptr_ = root_;
            while(ptr_->right!=NULL){
                ptr_ = ptr_->right;
                down_count+=1;
                std::cout<<"down: "<<down_count<<" up: "<<up_count<<std::endl;
            }
        }
        if(ptr_->left != NULL){
            ptr_ = ptr_->left;
            down_count+=1;
            std::cout<<"down: "<<down_count<<" up: "<<up_count<<std::endl;
            while(ptr_->right != NULL){
                ptr_ = ptr_->right;
                down_count+=1;
                std::cout<<"down: "<<down_count<<" up: "<<up_count<<std::endl;
            }
        }
        else{
            while(ptr_->parent != NULL && ptr_->parent->left == ptr_){
                ptr_ = ptr_->parent;
                up_count+=1;
                std::cout<<"down: "<<down_count<<" up: "<<up_count<<std::endl;
            }
            up_count+=1;
            std::cout<<"down: "<<down_count<<" up: "<<up_count<<std::endl;
            ptr_ = ptr_->parent;
        }

      
      // you must write this function


      return *this;
    }
    iterator operator--(int) {
      iterator temp(*this);
      --(*this);
      return temp;
    }

  private:
    // representation
    TreeNode* ptr_;
      TreeNode* root_;
  };
  // -------------------------------------------------------------------

  // CONSTRUCTORS, ASSIGNMENT OPERATOR, DESTRUCTOR
  ds_set() : root_(NULL), size_(0) {}
  ds_set(const ds_set<T>& old) : size_(old.size_) {
    root_ = this->copy_tree(old.root_,NULL); }
  ~ds_set() {
    this->destroy_tree(root_);
    root_ = NULL;
  }
  ds_set& operator=(const ds_set<T>& old) {
    if (&old != this) {
      this->destroy_tree(root_);
      root_ = this->copy_tree(old.root_,NULL);
      size_ = old.size_;
    }
    return *this;
  }

  int size() const { return size_; }
  bool operator==(const ds_set<T>& old) const { return (old.root_ == this->root_); }

  // FIND, INSERT & ERASE
  iterator find(const T& key_value) { return find(key_value, root_); }
  std::pair< iterator, bool > insert(T const& key_value) { return insert(key_value, root_, NULL); }
  int erase(T const& key_value) { return erase(key_value, root_); }
  
  // OUTPUT & PRINTING
  friend std::ostream& operator<< (std::ostream& ostr, const ds_set<T>& s) {
    s.print_in_order(ostr, s.root_);
    return ostr;
  }
  void print_as_sideways_tree(std::ostream& ostr) const {
    print_as_sideways_tree(ostr, root_, 0);
  }

  // ITERATORS
  iterator begin() const {
    if (!root_) return iterator(NULL,NULL);
    TreeNode* p = root_;
    while (p->left) p = p->left;
    return iterator(p,root_);
  }
  iterator end() const { return iterator(NULL,root_); }

  bool sanity_check() const {
    if (root_ == NULL) return true;
    if (root_->parent != NULL) {
      return false;
    }
    return sanity_check(root_);
  }

private:
  // REPRESENTATION
  TreeNode* root_;
  int size_;

  // PRIVATE HELPER FUNCTIONS
  TreeNode*  copy_tree(TreeNode* old_root, TreeNode* the_parent) {
    if (old_root == NULL)
      return NULL;
    TreeNode *answer = new TreeNode();
    answer->value = old_root->value;
    answer->left = copy_tree(old_root->left,answer);
    answer->right = copy_tree(old_root->right,answer);
    answer->parent = the_parent;
    return answer;
  }

  void destroy_tree(TreeNode* p) {
    if (!p) return;
    destroy_tree(p->right);
    destroy_tree(p->left);
    delete p;
  }

  iterator find(const T& key_value, TreeNode* p) {
    if (!p) return end();
    if (p->value > key_value)
      return find(key_value, p->left);
    else if (p->value < key_value)
      return find(key_value, p->right);
    else
      return iterator(p,NULL);
  }

  std::pair<iterator,bool> insert(const T& key_value, TreeNode*& p, TreeNode* the_parent) {
    if (!p) {
      p = new TreeNode(key_value);
      p->parent = the_parent;
      this->size_++;
      return std::pair<iterator,bool>(iterator(p,NULL), true);
    }
    else if (key_value < p->value)
      return insert(key_value, p->left, p);
    else if (key_value > p->value)
      return insert(key_value, p->right, p);
    else
      return std::pair<iterator,bool>(iterator(p,NULL), false);
  }
  
  int erase(T const& key_value, TreeNode* &p) {
    if (!p) return 0;
 
    // look left & right
   if (p->value < key_value)
      return erase(key_value, p->right);
    else if (p->value > key_value)
      return erase(key_value, p->left);

    // Found the node.  Let's delete it
    assert (p->value == key_value);
    if (!p->left && !p->right) { // leaf
      delete p;
      p=NULL;
      this->size_--;
    } else if (!p->left) { // no left child
      TreeNode* q = p;
      p=p->right;
      assert (p->parent == q);
      p->parent = q->parent;
      delete q;
      this->size_--;
    } else if (!p->right) { // no right child
      TreeNode* q = p;
      p=p->left;
      assert (p->parent == q);
      p->parent = q->parent;
      delete q;
      this->size_--;
    } else { // Find rightmost node in left subtree
      TreeNode* q = p->left;
      while (q->right) q = q->right;
      p->value = q->value;
      // recursively remove the value from the left subtree
      int check = erase(q->value, p->left);
      assert (check == 1);
    }
    return 1;
  }

  void print_in_order(std::ostream& ostr, const TreeNode* p) const {
    if (p) {
      print_in_order(ostr, p->left);
      ostr << p->value << "\n";
      print_in_order(ostr, p->right);
    }
  }

  void print_as_sideways_tree(std::ostream& ostr, const TreeNode* p, int depth) const {
    if (p) {
      print_as_sideways_tree(ostr, p->right, depth+1);
      for (int i=0; i<depth; ++i) ostr << "    ";
      ostr << p->value << "\n";
      print_as_sideways_tree(ostr, p->left, depth+1);
    }
  }

  bool sanity_check(TreeNode* p) const {
    if (p == NULL) return true;
    if (p->left != NULL && p->left->parent != p) {
      return false;
    }
    if (p->right != NULL && p->right->parent != p) {
      return false;
    }
    return sanity_check(p->left) && sanity_check(p->right);
  }
};

#endif
