#include <utility>
#include <list>

using namespace std;
struct EmptyHeap: public std::exception {};

template<class T>
class BinomialHeap {
    private:
        /* inner class: binomial tree */
        struct BinomialTree {
            int _size;
            T element;
            std::list<BinomialTree*> children;

            BinomialTree(T _ele): _size(1), element(_ele) {
                children.clear();
            }

            /* return the size of BinomialTree
             * #note that nullptr->size() == 0
             * (nullptr is a null pointer (like NULL in C))
             */
            int size() {
                return ( (this!=nullptr) ? this->_size : 0);
            }
        };
        /* some definition for convinience
        */
        typedef BinomialTree BT;
        typedef BinomialHeap<T> BH;
        typedef std::pair<BT*, BT*> CarrySum;
        typedef std::pair<T, BH> MaxRemainder;

        /* Merge three binomial trees which have the same sizes
         *
         * INPUT:   a: operand a, b: operand b, c: carry in
         *          (each of them are either nullptr or a pointer of BinomialTree with size 2^n)
         *
         * OUTPUT:  a pair consist of two variables.
         *          first: carry out (nullptr or a pointer of BinomialTree with size 2^(n+1))
         *          second: sum (nullptr or a pointer of BinomialTree with size 2^n)
         *
         * (just as a full adder: http://en.wikipedia.org/wiki/Adder_%28electronics%29#Full_adder )
         */
        CarrySum merge_tree(BT *a, BT *b, BT *c) {
            // write your code here.

            CarrySum tmp;
            if(c == nullptr)
            {
                if(a == nullptr && b == nullptr)
                {
                    tmp = make_pair( nullptr, nullptr );
                    return tmp;
                }
                if(a == nullptr)
                {
                    tmp = make_pair(nullptr, b);
                    return tmp;
                }
                else if(b == nullptr)
                {
                    tmp = make_pair(nullptr, a);
                    return tmp;
                }
                if(a->size() != b->size())
                {
                    // b.size() must > a.size()
                    if(a->size() > b->size())
                        tmp = make_pair(a, b);
                    else
                        tmp = make_pair(b, a);
                }
                else
                {
                    if(a -> element >= b-> element)
                    {
                        a->_size += b->_size;
                        a->children.push_back(b);
                        tmp = CarrySum( a, nullptr);
                    }
                    else
                    {
                        b->_size += a->_size;
                        b->children.push_back(a);
                        tmp = CarrySum( b, nullptr);
                    }
                }
                return tmp;
            }
            else
            {
                if(a == nullptr && b == nullptr)
                {
                    tmp = make_pair(nullptr, c);
                    return tmp;
                }
                if(a == nullptr)
                    tmp = merge_tree(b, c, nullptr);
                else if(b == nullptr)
                    tmp = merge_tree(a, c, nullptr);
                else
                {
                    tmp = merge_tree(b, c, nullptr);
                    tmp = merge_tree(a, tmp.first, nullptr);
                }
                return tmp;
            }
        };

        /* Pop the maximum element of a binomial tree and make other elements a binomial heap.
         *
         * INPUT:   a: a pointer of BinomialTree
         *
         * OUTPUT:  a pair consist of two variables.
         *          first: the maximum element
         *          second: a binomial heap consists of other elements
         */
        MaxRemainder pop_max(BT *a) {
            // write your code here.
            T max = a->element; 
            BH tmp_BH; //size == 0
            typename std::list<BT*>::iterator it = a->children.begin();
            for(; it != a->children.end(); ++it)
            {
                int _binary = 1, i = 0;
                while(_binary < (*it)->size() )
                {
                    _binary *= 2;
                    i++;
                }
                tmp_BH.trees[ i ] = *it;
                tmp_BH.size += (*it)->size();
            }
            delete a;
            MaxRemainder result = make_pair( max, tmp_BH);
            return result;
        }

        int size;
        BT* trees[32]; //binomial trees of the binomial heap, where trees[i] is a tree with size 2^i.

    public:
        BinomialHeap(): size(0) {
            for(int i=0; i<32; ++i) trees[i] = nullptr;
        }
        BinomialHeap(T element): size(1) {
            for(int i=0; i<32; ++i) trees[i] = nullptr;
            trees[0] = new BT(element);
        }

        /* merge all elements in the binomial heap b into *this, and clear the binomial heap b.
         *
         * INPUT:   b: a pointer of BinomialHeap
         */
        void merge(BH &b) {
            // write your code here.
            CarrySum carry = make_pair(nullptr, nullptr);      
            int counter = 0;
            size = 0;
            while(counter < 32)
            {
                carry = merge_tree(trees[counter], b.trees[counter], carry.first);
                trees[counter] = carry.second;
                b.trees[counter] = nullptr;
                if(trees[counter] != nullptr)
                    size += trees[counter]->size();
                counter++;
            }
            b.size = 0;
        }
        int getSize()
        {
            return size;
        } 
        void insert(const T &element) {
            BH tmp = BH(element);
            merge(tmp);
        }
        T pop() {
            if(size==0) 
                throw EmptyHeap();
            else {
                //find the tree contains maximum element
                int max_tree = -1;
                for(int i=0; i<32; ++i)
                    if(trees[i]->size() > 0 && (max_tree == -1 || trees[i]->element > trees[max_tree]->element))
                        max_tree = i;
                MaxRemainder m_r = pop_max(trees[max_tree]);
                T &max_element = m_r.first;
                BH &remainder = m_r.second;

                trees[max_tree] = nullptr;
                //size--; //size will be redefined int merge()

                merge(remainder);
                return max_element;
            }
        }
        T getMax() {
            if(size == 0) throw EmptyHeap();
            else {
                int max_tree = -1;
                for(int i=0; i<32; ++i)
                    if(trees[i]->size() > 0 && (max_tree == -1 || trees[i]->element > trees[max_tree]->element))
                        max_tree = i;
                return trees[max_tree]->element;            
            }
        }
};
