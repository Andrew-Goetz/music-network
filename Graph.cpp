#include "Graph.h"
#include <iostream>

//todo: implement this
friend_Graph::~friend_Graph()
{
    //no longer needed if using shared_ptr
    std::shared_ptr<NameLLNode> temp = vertices.pop();
    while(temp != nullptr)
    {
        delete temp->relationship;
        temp = vertices.pop();
    }
}

NameLLNode& NameLLNode::operator= (const NameLLNode &N1)
{
    if(this == &N1) return *this;

    name = N1.name;
    relationship = N1.relationship;
    hasVisited = N1.hasVisited;
    return *this;
}

NameLLNode::NameLLNode(const NameLLNode& copy) {
    name = copy.name;
    relationship = copy.relationship;
    hasVisited = copy.hasVisited;
}

NameLLNode::NameLLNode(NameLLNode&& copy)
{
    std::swap(name, copy.name);
    std::swap(relationship, copy.relationship);
    std::swap(hasVisited, copy.hasVisited);
}

//O(logn) because have to see if the user existed.
void friend_Graph::add_user(std::string name)
{
    std::shared_ptr<NameLLNode> user = vertices.find(NameLLNode(name, nullptr, false));
    if(user != nullptr)
    {
        std::cout << "[add_user] " << name << " is already a user" << std::endl;
        return;
    }
    //TODO: double check if this is fine
    std::shared_ptr<NameLLNode> thisPerson = std::shared_ptr<NameLLNode>(new NameLLNode(name, nullptr, false));
    vertices.insert(thisPerson);
    LLNode<std::weak_ptr<NameLLNode>>* fwendship = new LLNode<std::weak_ptr<NameLLNode>>(std::weak_ptr<NameLLNode>(thisPerson), nullptr);
    fwendship->getData().lock()->relationship = fwendship;
} 

//O(E + logn) where E the number of edges
void friend_Graph::remove_user(std::string name)
{
    //I mean it doesn't matter what the linked list is, we just need the name
    std::shared_ptr<NameLLNode> user = vertices.find(NameLLNode(name, nullptr, false));

    if(user == nullptr)
    {
        std::cout << "[remove_user] " << name << " is not a user" << std::endl;
        return;
    }

    LLNode<std::weak_ptr<NameLLNode>>* friends = user->relationship;
    //for each friend of his, remove user
    LLNode<std::weak_ptr<NameLLNode>>* friendsbackup = friends;
    friends = friends->getNext();
    while(friends != nullptr)
    {
        std::string friendName = friends->getData().lock()->name;
        LLNode<std::weak_ptr<NameLLNode>>* hisFriends = vertices.find(NameLLNode(friendName, nullptr, false))->relationship;
        while(hisFriends->getNext() != nullptr && hisFriends->getNext()->getData().lock()->name != name)
        {
            hisFriends = hisFriends->getNext();
        }
        if(hisFriends->getNext() == nullptr)
        {
            std::cout << "[Warning: remove_user] " << friendName << " is not friend with " << name << std::endl;
        }
        else
        {
            //remove the friend relationship with him
            hisFriends->removeNodeAfter();
        }
        friends = friends->getNext();
    }
    vertices.remove(NameLLNode(name, nullptr, false));
    //delete him
    delete friendsbackup;
}

//O(logn) look if the user exists
void friend_Graph::make_friends(std::string name, std::string name2)
{
    std::shared_ptr<NameLLNode> user = vertices.find(NameLLNode(name, nullptr, false));
    std::shared_ptr<NameLLNode> user2 = vertices.find(NameLLNode(name2, nullptr, false));

    if(user == nullptr || user2 == nullptr)
    {
        std::cout << "[make_friends] " << "either " << name << " or " << name2 << " is not a user" << std::endl;
        return;
    }

    LLNode<std::weak_ptr<NameLLNode>>* friends = user->relationship;
    while(friends != nullptr)
    {
        if(friends->getData().lock()->name == name2)
        {
            std::cout << "[make_friends] " << name << " and " << name2 << " are already friends" << std::endl;
            return;
        }
        friends = friends->getNext();
    }

    user->relationship->addNodeAfter(std::weak_ptr<NameLLNode>(vertices.find(NameLLNode(name2, nullptr, false))));
    user2->relationship->addNodeAfter(std::weak_ptr<NameLLNode>(vertices.find(NameLLNode(name, nullptr, false))));
}

//O(logn) look if the user exists
void friend_Graph::unfriend(std::string name, std::string name2)
{
    std::shared_ptr<NameLLNode> user = vertices.find(NameLLNode(name, nullptr, false));
    std::shared_ptr<NameLLNode> user2 = vertices.find(NameLLNode(name2, nullptr, false));

    if(user == nullptr || user2 == nullptr)
    {
        std::cout << "[unfriend] " << "either " << name << " or " << name2 << " is not a user" << std::endl;
        return;
    }

    //for each friend of his, remove user
    LLNode<std::weak_ptr<NameLLNode>>* hisFriends = user->relationship;
    while(hisFriends->getNext() != nullptr && hisFriends->getNext()->getData().lock()->name != name2)
    {
        hisFriends = hisFriends->getNext();
    }
    if(hisFriends->getNext() == nullptr)
    {
        std::cout << "[Warning: unfriend] " << user->name << " is not friend with " << user2->name << std::endl;
    }
    else
    {
        //remove the friend relationship with him
        hisFriends->removeNodeAfter();
    }

    //for each friend of his, remove user
    hisFriends = user2->relationship;
    while(hisFriends->getNext() != nullptr && hisFriends->getNext()->getData().lock()->name != name)
    {
        hisFriends = hisFriends->getNext();
    }
    if(hisFriends->getNext() == nullptr)
    {
        std::cout << "[Warning: unfriend] " << user2->name << " is not friend with " << user->name << std::endl;
    }
    else
    {
        //remove the friend relationship with him
        hisFriends->removeNodeAfter();
    }


}

//BFS traversal
//complexity:
//O(V+E)
bool friend_Graph::isFriend(std::string user, std::string name, int depthLimit)
{
    //First, mark all the vertices as not visited
    std::vector<std::shared_ptr<NameLLNode>> lis = vertices.getArray();
    for(std::shared_ptr<NameLLNode> n : lis)
    {
        n->hasVisited = false;
    }

    //then, find the name of the base user
    std::shared_ptr<NameLLNode> userNode = vertices.find(NameLLNode(user, nullptr, -1));

    //some sort of vector to keep track of the queue
    std::vector<std::shared_ptr<NameLLNode>> queue{};
    queue.push_back(userNode);
    queue.push_back(nullptr); // to keep track of depth
    int depth = 0;

    while(queue.size() > 0)
    {
        //dequeue a vertex
        std::shared_ptr<NameLLNode> u = queue.at(0);
        queue.erase(queue.begin());

        //we probably reached the end of this level
        if(u == nullptr)
        {
            depth++;
            queue.push_back(nullptr);
            //we just pushed another nullptr back in the vector
            //abort, we have reached the end of the graph
            if(queue.size() > 0 && queue.at(0) == nullptr)
            {
                break;
            }
            //or, we have reached the depth
            if(depth >= depthLimit)
            {
                break;
            }
            continue;
        }

        //iterate through the friends list
        LLNode<std::weak_ptr<NameLLNode>>* rel = u->relationship;
        while(!u->hasVisited && rel != nullptr)
        {
            std::shared_ptr<NameLLNode> temp = rel->getData().lock();
            if(temp->name == name) // we found this frien!
            {
                return true;
            }   
            queue.push_back(temp);
            rel = rel->getNext(); 
        }
        u->hasVisited = true;
    }




    return false;
}

std::string friend_Graph::getFriends(std::string name)
{
    auto user = vertices.find(NameLLNode(name, nullptr, false));
    if(user == nullptr )
    {
        std::cout << "[getFriends] " << name << " is not a user" << std::endl;
        return "";
    }
    std::string ret = "";
    LLNode<std::weak_ptr<NameLLNode>>* fwendship = user->relationship;
    while(fwendship != nullptr)
    {
        ret += fwendship->getData().lock()->name;
        fwendship = fwendship->getNext();
        ret += "\n";
    }
    return ret;
}
