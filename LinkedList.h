#ifndef LL_H
#define LL_H


template<typename T>
class LLNode
{
public:
    LLNode() : data(T{}), next(nullptr){};
    LLNode(T cdata, LLNode* cnext) : data(cdata), next(cnext){};
    ~LLNode(){delete next;}
    T getData() {return data;};
    LLNode* getNext() {return next;};
    void setData(T d) {data = d;};
    void setNext(LLNode* n) {next = n;};
    void addNodeAfter(T);
    void removeNodeAfter();
    static int length(LLNode*);
    static LLNode* findNode(LLNode*, T);
    static LLNode* findNodeAt(LLNode*, int);
    static LLNode* clone(LLNode*);
    static LLNode<T>* clonePart(LLNode*, LLNode*, bool includeEnd = false);
private:
    T data;
    LLNode* next;
};

//add a new node after this node
template<typename T>
void LLNode<T>::addNodeAfter(T elem)
{
    next = new LLNode{elem, next};
}
//remove the node after this node
//if next node is nullptr, nothing is done.
template<typename T>
void LLNode<T>::removeNodeAfter()
{
    if(next != nullptr)
    {
        LLNode* temp = next;
        next = next->next;
        temp->next = nullptr;
        delete temp;
    }
}
//return the length of this linked list
template<typename T>
int LLNode<T>::length(LLNode* head)
{
    int count = 0;
    while(head != nullptr)
    {
        count++;
        head = head->next;
    }
    return count;
}
//return the node containing target
//if the return is nullptr, no target is found
template<typename T>
LLNode<T>* LLNode<T>::findNode(LLNode* head, T targ)
{
    while(head != nullptr)
    {
        if(head->getData() == targ) return head;
        head = head->next;
    }
    
    return nullptr;
}
//position 0 is the head
//if return value is 0, no node is found
template<typename T>
LLNode<T>* LLNode<T>::findNodeAt(LLNode* head, int position)
{
    for (int i = 0; (i < position) && (head != nullptr); i++)
        head = head->next;
    return head;
}
//clone the whole list
//if head is null, nullptr is returned
template<typename T>
LLNode<T>* LLNode<T>::clone(LLNode* head)
{
    LLNode<T>* newHead;

    if(head == nullptr) return nullptr;

    //first, copy the head
    newHead = new LLNode<T>{head->data, nullptr};
    //make a backup of it
    LLNode<T>* copyHead = newHead;

    //start appending
    while(head->next != nullptr)
    {
        head = head->next;
        copyHead->next = new LLNode{head->data, copyHead->next};
        copyHead = copyHead->next;
    }

    return newHead;
}
//clone part of the linked list
template<typename T>
LLNode<T>* LLNode<T>::clonePart(LLNode* start, LLNode* end, bool includeEnd)
{
    LLNode<T>* newHead;
    if(start == nullptr) return nullptr;

    //first, copy the head
    newHead = new LLNode<T>{start->data, nullptr};
    //make a backup of it
    LLNode<T>* copyHead = newHead;

    //start appending
    while(start->next != end)
    {
        start = start->next;
        copyHead->next = new LLNode{start->data, copyHead->next};
        copyHead = copyHead->next;
    }

    //decide whether to include end or not.
    if(includeEnd)
    {
        copyHead->next = new LLNode{end->data, copyHead->next};
    }

    return newHead;
}




#endif