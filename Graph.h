//Ironically, this should be called BST with list nodes LOL
#ifndef GRAFF_H
#define GRAFF_H

#include "BST_shared_ptr.h"
#include "LinkedList.h"
#include <string>

class NameLLNode
{
public:
    std::string name;
    LLNode<std::weak_ptr<NameLLNode>>* relationship;
    bool hasVisited;

    ~NameLLNode(){}

    //a constructor that will return a node that will 100%
    //be different than any other node
    NameLLNode() : name(""), relationship(nullptr), hasVisited(false){};

    //a constructor that will assign name and relationship
    NameLLNode(std::string n, LLNode<std::weak_ptr<NameLLNode>>* r, bool h) : name(n), relationship(r), hasVisited(h){};

    //make 100000% sure name won't be accidentally
    //freed.
    NameLLNode(const NameLLNode& copy);
    NameLLNode(NameLLNode&& copy);

    //comparison stuff for BST
    friend bool operator> (const NameLLNode &N1, const NameLLNode &N2) { return N1.name > N2.name;};
    friend bool operator< (const NameLLNode &N1, const NameLLNode &N2) { return N1.name < N2.name;};
    friend bool operator>= (const NameLLNode &N1, const NameLLNode &N2) { return N1.name >= N2.name;};
    friend bool operator<= (const NameLLNode &N1, const NameLLNode &N2) { return N1.name <= N2.name;};
    friend bool operator== (const NameLLNode &N1, const NameLLNode &N2) { return N1.name == N2.name;};
    friend bool operator!= (const NameLLNode &N1, const NameLLNode &N2) { return N1.name != N2.name;};
    NameLLNode& operator= (const NameLLNode &N1);
};

//general structure:
//every BST node will contain a NameLLNode, which contains a name, and a pointer to linked list
//the first element in the linked list will always point back to current user, it is 
//the nodes after it that will be different.
class friend_Graph
{
public:
    friend_Graph() : vertices(BST_shared_ptr<NameLLNode>{}){};
    ~friend_Graph();

    void add_user(std::string name);
    void remove_user(std::string name);
    void make_friends(std::string name, std::string name2);
    void unfriend(std::string name, std::string name2);
    bool isFriend(std::string user, std::string name, int depth);
    std::string getFriends(std::string user);

private:
    //a vertices storing everything
    BST_shared_ptr<NameLLNode> vertices;
};

#endif