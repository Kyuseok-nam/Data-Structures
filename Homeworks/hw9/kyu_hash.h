#ifndef kyu_hashset_h_
#define kyu_hashset_h_
// The set class as a hash table instead of a binary search tree.  The
// primary external difference between ds_set and ds_hashset is that
// the iterators do not step through the hashset in any meaningful
// order.  It is just the order imposed by the hash function.
#include <iostream>
#include <list>
#include <string>
#include <vector>

// The ds_hashset is templated over both the type of key and the type
// of the hash function, a function object.
template <class KeyType, class HashFunc >
class ds_hashset {
private:
    // HASH SET REPRESENTATION
    std::vector<std::string> m_table;  // actual table with keys
    std::vector<std::list<int> > values;  // table with values
    HashFunc m_hash;                            // hash function
    unsigned int m_size;                        // number of keys
    float occupancy;
    
    
    typedef typename std::list<int>::iterator hash_list_itr;
public:

  
    // =================================================================
    // HASH SET IMPLEMENTATION
    
    // Constructor for the table set just accepts the size of the table.
    // The default constructor for the hash function object is
    // implicitly used.
    ds_hashset(unsigned int init_size,float occ) : m_table(init_size),
    values(init_size), m_size(0),occupancy(occ) {}
  
    // Copy constructor just uses the member function copy constructors.
    ds_hashset(const ds_hashset<KeyType, HashFunc>& old)
        : m_table(old.m_table), values(old.values), m_size(old.m_size), occupancy(old.occupancy){}

    ~ds_hashset() {}

    
    unsigned int size() const { return m_size; }
    void set_size(int n){m_table.resize(n); values.resize(n);}
    void set_occ(float o){occupancy = o;}
    
    // Insert the key if it is not already there.
    void insert(KeyType const& key,int position) {

        if (m_size >= occupancy * m_table.size())
            this->resize_table(2*m_table.size()+1);

        //  Compute the hash value and then the table index
        unsigned int hash_value = m_hash(key);
        unsigned int index = hash_value % m_table.size();
        
        //when that given index is availbe
        if(m_table[index]==""){
            m_table[index] = key;
            values[index].push_back(position);
        }
        else if(m_table[index]==key){
            values[index].push_back(position);
        }
        //if that valid index is not available
        else{
            int tmp_index = 1+index;
            //loop thorugh to search if a key already exists
            //or find a blank space to insert new key
            while(tmp_index!=index){
                //if temporary index reaches end go back to the beginnings
                if(tmp_index==m_table.size()){
                    tmp_index = 0;
                }
                //if it is a blank space insert the key
                if(m_table[tmp_index]==""){
                    m_table[tmp_index] = key;
                    values[tmp_index].push_back(position);
                    break;
                }
                //if I found a key push back value
                else if(m_table[tmp_index]==key){
                    values[tmp_index].push_back(position);
                    break;
                }
                tmp_index++;
            }
        }
        m_size++;
    }
    
    
    // Find the key, using hash function, indexing and list find
    std::pair<std::list<int>,bool> find(const KeyType& key) {
        unsigned int hash_value = m_hash(key);
        unsigned int index = hash_value % m_table.size();
        std::list<int> p;
        //if key is in that index
        if(m_table[index]==key){
            p = values[index];
            return std::make_pair(p,true);
        }
        //if key is not in that index
        else{
            int tmp_index = 1+index;
            //loops through to search for key
            while(tmp_index!=index){
                //if it hits the end of table go back to beginning
                if(tmp_index==m_table.size()){
                    tmp_index = 0;
                }
                //if found key return iterator
                if(m_table[tmp_index] ==key){
                    p = values[tmp_index];
                    return std::make_pair(p,true);
                }
                //if found blank key doesn't exist
                else if(m_table[tmp_index] ==""){
                    return std::make_pair(p,false);
                }
                tmp_index++;
            }
            return std::make_pair(p,false);
        }
    }

    
private:
    // resize the table with the same values but a
    void resize_table(unsigned int new_size) {
        // Implemented in class

        std::vector<std::string> old_table = m_table;
        std::vector<std::list<int> > old_values = values;
        m_table.clear();
        values.clear();
        m_table.resize( new_size );
        values.resize(new_size);
        
        for ( unsigned int i=0; i<old_table.size(); ++i ){
            unsigned int index = m_hash(old_table[i]) % new_size;
            m_table[index] = old_table[i];
            for (hash_list_itr p = old_values[i].begin(); p!=old_values[i].end(); ++p ){
                values[index].push_back(*p);
            }
        }
    }

};
#endif
