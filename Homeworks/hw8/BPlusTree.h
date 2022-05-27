/* ASSUMPTIONS:
1. When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
2. There will never be a duplicate key passed to insert.
*/

#include <vector>
#include <string>
#include <iostream>
#ifndef DS_BPLUSTREE
#define DS_BPLUSTREE

///////////////////////////////////////////////////////////////////////////////
//DO NOT CHANGE THIS CODE
///////////////////////////////////////////////////////////////////////////////

//Do not implement the class here, this is a forward declaration. Implement at
//the bottom of the .h file
template <class T> class BPlusTree; 

template <class T>
class BPlusTreeNode{
public:
	BPlusTreeNode() : parent(NULL){};
	bool is_leaf();
	bool contains(const T& key);

	//For grading only. This is bad practice to have, because
	//it exposes a private member variable.
	BPlusTreeNode* get_parent() { return parent; } 

	//We need this to let BPlusTree access private members
	friend class BPlusTree<T>; 
private:
	bool contains(const T& key,std::size_t low,std::size_t high);
	std::vector<T> keys;
	std::vector<BPlusTreeNode*> children;
	BPlusTreeNode* parent;
};

template <class T>
bool BPlusTreeNode<T>::is_leaf(){
	for(unsigned int i=0; i<children.size(); i++){
		if(children[i]){
			return false;
		}
	}
	return true;
}


template <class T>
bool BPlusTreeNode<T>::contains(const T& key){
	return contains(key,0,keys.size()-1);
}

//Private method takes advantage of the fact keys are sorted
template <class T>
bool BPlusTreeNode<T>::contains(const T& key,std::size_t low,std::size_t high){
	if(low>high){
		return false;
	}
	if(low==high){
		return key == keys[low];
	}
	std::size_t mid = (low+high)/2;
	if(key<=keys[mid]){
		return contains(key,0,mid);
	}
	else{
		return contains(key,mid+1,high);
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//Your BPlusTree implementation goes below this point.
///////////////////////////////////////////////////////////////////////////////////////
template <class T>
class BPlusTree{
public:
    BPlusTree(): root_(NULL), b(0){}
    BPlusTree(int n): root_(NULL), b(n){}
    
    BPlusTree(const BPlusTree<T>& old): b(old.b){
        root_ = this->copy_tree(old.root_,NULL);
    }
    ~BPlusTree(){
        this->destroy(root_);
        root_=NULL;
    }
    void insert(const T& n);
    BPlusTreeNode<T>* find(const T& n);
    void print_sideways(std::ofstream& outfile);
    void print_BFS(std::ofstream& outfile);
    void print_BFS_pretty(std::ofstream& outfile);
private:
    BPlusTreeNode<T>* copy_tree(BPlusTreeNode<T>* old_root, BPlusTreeNode<T>* parent);
    void destroy(BPlusTreeNode<T>* p);
    void split(BPlusTreeNode<T>* p);
    void insert_to_parent(BPlusTreeNode<T>* p,const T& new_key,BPlusTreeNode<T>* ptr1, BPlusTreeNode<T>* ptr2);
    BPlusTreeNode<T>* tree_find(const T& n, BPlusTreeNode<T>* p);
    void print_tree_sideways(std::ofstream& outfile,const BPlusTreeNode<T>* p,int depth);
    
    BPlusTreeNode<T>* root_;
    int b;
};

template <class T>
BPlusTreeNode<T>* BPlusTree<T>::copy_tree(BPlusTreeNode<T>* old_root, BPlusTreeNode<T>* parent){
    if(old_root == NULL){
        return NULL;
    }
    BPlusTreeNode<T>* answer = new BPlusTreeNode<T>();
    
    for(unsigned int i=0; i<old_root->keys.size();i++){
        answer->keys.push_back(old_root->keys[i]);
    }
    for(unsigned int i=0; i<old_root->children.size();i++){
        copy_tree(old_root->children[i],answer);
    }
    return answer;
}


template <class T>
void BPlusTree<T>::destroy(BPlusTreeNode<T>* p){
    
    if(!p){
        return;
    }
    for(unsigned int i=0; i < p->children.size();i++){
        destroy(p->children[i]);
    }
    delete p;
}

template <class T>
BPlusTreeNode<T>* BPlusTree<T>::tree_find(const T& n, BPlusTreeNode<T>* p){
    if(p->is_leaf()){
        return p;
    }
    else{
        if(n < p->keys[0]){
            return tree_find(n,p->children[0]);
        }
        else if(n>p->keys[b-2]){
            return tree_find(n,p->children[b-1]);
        }
        else{
            for(int i=0; i<b-2;i++){
                if(n >= p->keys[i] && n<= p->keys[i+1]){
                    return tree_find(n,p->children[i+1]);
                }
            }
        }
        return NULL;
    }
    
}

template <class T>
BPlusTreeNode<T>* BPlusTree<T>::find(const T& n){
    if(root_ == NULL){
        return root_;
    }
    else{
        return tree_find(n,root_);
    }
}


template <class T>
void BPlusTree<T>::insert_to_parent(BPlusTreeNode<T>* p,const T& new_key,BPlusTreeNode<T>* ptr1, BPlusTreeNode<T>* ptr2 ){
    
    typename std::vector<T>::iterator itr = p->keys.begin();
    int index = 0;
    bool inserted = false;
    //insert new key to parent node
    
    for(;itr!=p->keys.end();itr++){
        std::cout<<"parent keys inside function "<<*itr<<std::endl;
        if(new_key < *itr){
            p->keys.insert(itr,new_key);
            inserted = true;
            break;
        }
        index++;
    }

    //if it the new key was less than one of the previous keys
    if(inserted){
        p->children[index] = ptr1;
        typename std::vector<BPlusTreeNode<T>*>::iterator tmp = p->children.begin();
        p->children.insert(tmp+index+1,ptr2);
    }
    //if the new key was added as the last key in parent keys
    else{
        std::cout<<"insert to parent function new key:"<<new_key<<std::endl;
        p->keys.push_back(new_key);
        std::cout<<"inside funtion "<<p->keys[1]<<std::endl;
        p->children[b-1] = ptr1;
        p->children.push_back(ptr2);
    }
}



template <class T>
void BPlusTree<T>::split(BPlusTreeNode<T>* p){
    BPlusTreeNode<T>* ptr1 = new BPlusTreeNode<T>();
    BPlusTreeNode<T>* ptr2 = new BPlusTreeNode<T>();
    //if splitting the leaf node
    if(p->is_leaf()){
        std::cout<<"if its a leaf node"<<std::endl;
        //assigne values to the two splitted tree nodes
        for(int i=0;i<b;i++){
            if(i < b/2){
                std::cout<<"pushing back "<<p->keys[i]<<" to ptr1"<<std::endl;
                ptr1->keys.push_back(p->keys[i]);
            }
            else{
                std::cout<<"pushing back "<<p->keys[i]<<" to ptr2"<<std::endl;
                ptr2->keys.push_back(p->keys[i]);
            }
            ptr1->children.push_back(NULL);
            ptr2->children.push_back(NULL);
        }
        T new_key = ptr2->keys[0];
        //if parent exist
        if(p->parent!=NULL){
            std::cout<<"parent already exist"<<std::endl;
            std::cout<<"pushing back "<<new_key<<" to parent"<<std::endl;
            std::cout<<"parent currently has "<<p->parent->keys[0]<<std::endl;
            std::cout<<"parent address before "<<p->parent<<std::endl;
            
            //=============
            insert_to_parent(p->parent,new_key,ptr1,ptr2);
            //======================
            std::cout<<"parent address after "<<p->parent<<std::endl;

            std::cout<<"parent size "<<p->parent->keys.size()<<std::endl;
            std::cout<<"parent now has ";
            for(unsigned int i=0; i<p->parent->keys.size();i++){
                std::cout<<p->parent->keys[i]<<" ";
            }
            std::cout<<std::endl;
            ptr1->parent = p->parent;
            ptr2->parent = p->parent;
            delete p;
            //if parent now has more keys than it should
            if(ptr1->parent->keys.size()>= b ){
                split(ptr1->parent);
            }
            else{
                return;
            }
        }
        //if parent doens't exist
        else{
            std::cout<<"create new parent"<<std::endl;
            BPlusTreeNode<T>* new_parent = new BPlusTreeNode<T>();
            new_parent->children.push_back(ptr1);
            new_parent->children.push_back(ptr2);
            new_parent->keys.push_back(new_key);
            std::cout<<"pushing back "<<new_parent->keys[0]<<" to parent"<<std::endl;
            ptr1->parent = new_parent;
            ptr2->parent = new_parent;
            root_ = new_parent;
            delete p;
            return;
        }
        return;
    }
    //if splitting a non leaf node
    else{
        std::cout<<"if it is not a leaf node"<<std::endl;
        //moving children values to two new nodes
        for(int i=0; i<b+1;i++){
            if(i<(b+1)/2){
                ptr1->children.push_back(p->children[i]);
            }
            else{
                ptr2->children.push_back(p->children[i]);
            }
        }
        //moving key values to two new nodes
        T new_key;
        for(int j=0; j<b;j++){
            if(j<b/2){
                ptr1->keys.push_back(p->keys[j]);
            }
            else if(j==(b/2)){
                new_key = p->keys[j];
            }
            else{
                ptr2->keys.push_back(p->keys[j]);
            }
        }
        
        //if parent exist
        if(p->parent != NULL){
            BPlusTreeNode<T>* tmp = p->parent;
            insert_to_parent(tmp,new_key,ptr1,ptr2);
            ptr1->parent = p->parent;
            ptr2->parent = p->parent;
            delete p;
            //if parent now has more keys than it should
            if(ptr1->parent->keys.size()>= b ){
                split(ptr1->parent);
            }
            else{
                return;
            }
        }
        //if parent doesn't exist
        else{
            std::cout<<"create new parent from a parent"<<std::endl;
            BPlusTreeNode<T>* new_parent = new BPlusTreeNode<T>();
            new_parent->children.push_back(ptr1);
            new_parent->children.push_back(ptr2);
            new_parent->keys.push_back(new_key);
            ptr1->parent = new_parent;
            ptr2->parent = new_parent;
            root_ = new_parent;
            delete p;
            return;
        }
    }
    return;
}

template <class T>
void BPlusTree<T>::insert(const T& n){
    std::cout<<"inserting "<<n<<std::endl;
    //if/ it is a empty tree
    if(root_ == NULL){
        std::cout<<"if root is null"<<std::endl;
        root_ = new BPlusTreeNode<T>();
        root_->keys.push_back(n);
    }
    else{
        std::cout<<"if root is not null"<<std::endl;
        BPlusTreeNode<T>* ptr = this->find(n);
        std::cout<<"putting into a node with ";
        for(unsigned int i=0; i<ptr->keys.size();i++){
            std::cout<<ptr->keys[i]<<" ";
        }
        std::cout<<std::endl;
        typename std::vector<T>::iterator itr = ptr->keys.begin();
        bool insert = false;
        for(;itr!=ptr->keys.end();itr++){
            if(n<*itr){
                ptr->keys.insert(itr,n);
                insert = true;
                break;
            }
        }
        if(!insert){
            ptr->keys.push_back(n);
        }
        if(ptr->keys.size()>b-1){
            std::cout<<"have "<<ptr->keys.size()<<" keys "<<"start splitting"<<std::endl;
            split(ptr);
        }
    }
}

template <class T>
void BPlusTree<T>::print_tree_sideways(std::ofstream& ostr,const BPlusTreeNode<T>* p,int depth){
    
    if(!p&&depth==0){
        ostr<<"tree is empty"<<std::endl;
    }
    else{
        unsigned int i=0;
        for(;i<p->children.size()/2;i++){
            print_tree_sideways(ostr,p->children[i],depth+1);
        }
        for(unsigned int k=0; k<depth;k++){
            ostr<<"\t";
        }
        for(unsigned int j=0; j<p->keys.size();j++){
            ostr<<p->keys[j]<<",";
        }
        for(;i<p->children.size();i++){
            print_tree_sideways(ostr,p->children[i],depth+1);
        }
    }
}


template <class T>
void BPlusTree<T>::print_sideways(std::ofstream& outfile){
    print_tree_sideways(outfile,root_,0);
}

template <class T>
void BPlusTree<T>::print_BFS(std::ofstream& outfile){
    
}

template <class T>
void BPlusTree<T>::print_BFS_pretty(std::ofstream& outfile){
    
}
#endif
