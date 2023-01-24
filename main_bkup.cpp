#include "BST.h"
#include <string>
#include "LinkedList.h"
#include <iostream>
#include "Graph.h"
#include "Heap_Table.h"
#include "BST_ref.h"
#include "Song.h"

// LLNode() : data(T{}), next(nullptr){};
// LLNode(T cdata, LLNode* cnext) : data(cdata), next(cnext){};
// ~LLNode(){delete next;}
// T getData() {return data;};
// LLNode* getNext() {return next;};
// void setData(T d) {data = d;};
// void setNext(LLNode* n) {next = n;};
// void addNodeAfter(T);
// void removeNodeAfter();
// static int length(LLNode*);
// static LLNode* findNode(LLNode*, T);
// static LLNode* findNodeAt(LLNode*, int);
// static LLNode* clone(LLNode*);
// static T* clonePart(LLNode*, LLNode*, bool includeEnd = false);

int main_bkup()
{
    BST<std::string> temp = BST<std::string>();
    temp.insert("blyat");
    temp.insert("ass");
    temp.insert("cyka");
    temp.remove("blyat");
    temp.find("cyka");
    LLNode<std::string>* node = new LLNode<std::string>("Mike", nullptr);
    LLNode<std::string>* copyNode = node;
    copyNode->addNodeAfter("Lewis");
    copyNode = copyNode->getNext();
    copyNode->addNodeAfter("Is");
    copyNode = copyNode->getNext();
    copyNode->addNodeAfter("A");
    copyNode = copyNode->getNext();
    copyNode->addNodeAfter("good");
    copyNode = copyNode->getNext();
    copyNode->addNodeAfter("teacher");
    node->findNode(node, "Is")->addNodeAfter("not");
    node->findNodeAt(node, 2)->removeNodeAfter();

    copyNode = node->clonePart(node, copyNode, true);
    for(int i = 0; i < copyNode->length(copyNode); i++)
    {
        std::cout << copyNode->findNodeAt(copyNode, i)->getData() << " ";
    }
    std::cout << std::endl;

    delete copyNode;

    copyNode = node->clone(node);
    for(int i = 0; i < copyNode->length(copyNode); i++)
    {
        std::cout << copyNode->findNodeAt(copyNode, i)->getData() << " ";
    }
    std::cout << std::endl;

    delete copyNode;

    delete node;



    friend_Graph graph{};
    graph.add_user("Mike");
    graph.add_user("George");
    graph.add_user("Allen");
    graph.add_user("Patton");

    graph.make_friends("Mike", "George");
    graph.make_friends("Mike", "George");
    graph.add_user("Mike");
    graph.make_friends("Allen", "George");
    graph.unfriend("Mike", "George");
    graph.remove_user("George");
    graph.make_friends("Allen", "Patton");
    graph.make_friends("Mike", "George");
    graph.unfriend("Mike", "George");
    graph.remove_user("George");

    graph.add_user("George");
    graph.make_friends("Patton", "Mike");
    graph.make_friends("Mike", "George");
    //Allen->Patton->Mike->George
    std::cout << "Allen influence circle 2: " << graph.isFriend("Allen", "George", 2) << std::endl;
    std::cout << "Allen influence circle 3: " << graph.isFriend("Allen", "George", 3) << std::endl;
    std::cout << "Allen influence circle 4: " << graph.isFriend("Allen", "George", 4) << std::endl;
    std::cout << "Allen influence circle 5: " << graph.isFriend("Allen", "George", 5) << std::endl;

    graph.remove_user("George");
    std::cout << "Allen influence circle 2: " << graph.isFriend("Allen", "George", 2) << std::endl;
    std::cout << "Allen influence circle 3: " << graph.isFriend("Allen", "George", 3) << std::endl;
    std::cout << "Allen influence circle 4: " << graph.isFriend("Allen", "George", 4) << std::endl;
    std::cout << "Allen influence circle 5: " << graph.isFriend("Allen", "George", 5) << std::endl;

    friend_Graph CS240{};
    std::cout << std::endl;
    std::cout << std::endl;
    CS240.add_user("Mike");
    CS240.add_user("George");
    CS240.add_user("Allen");
    CS240.add_user("Hunter");
    CS240.add_user("Andrew");
    CS240.add_user("Aryan");
    CS240.make_friends("Mike", "Aryan");
    CS240.make_friends("Mike", "George");
    CS240.make_friends("George", "Allen");
    CS240.make_friends("Allen", "Andrew");
    CS240.make_friends("Hunter", "Aryan");

//should be all 1
    std::cout << "Aryan influence circle 1 to Mike: " << CS240.isFriend("Aryan", "Mike", 1) << std::endl;
    std::cout << "Aryan influence circle 2 to George: " << CS240.isFriend("Aryan", "George", 2) << std::endl;
    std::cout << "Aryan influence circle 3 to Allen: " << CS240.isFriend("Aryan", "Allen", 3) << std::endl;
    std::cout << "Aryan influence circle 4 to Andrew: " << CS240.isFriend("Aryan", "Andrew", 4) << std::endl;

    std::cout << std::endl;

//should be all 0
    std::cout << "Aryan influence circle 1 to George: " << CS240.isFriend("Aryan", "George", 1) << std::endl;
    std::cout << "Aryan influence circle 2 to Allen: " << CS240.isFriend("Aryan", "Allen", 2) << std::endl;
    std::cout << "Aryan influence circle 3 to Andrew: " << CS240.isFriend("Aryan", "Andrew", 3) << std::endl;



    BST_ref<Song> songLib{};
    Heap_Table_SongInfo recommendation{};


    {
        std::shared_ptr<Song> song = std::shared_ptr<Song>(new Song("VIBEZ"));
        songLib.insert(*song);
        recommendation.add_song(song);
        std::shared_ptr<Song> song2 = std::shared_ptr<Song>(new Song("Gangsta's Paradise"));
        songLib.insert(*song2);
        recommendation.add_song(song2);
        std::shared_ptr<Song> song3 = std::shared_ptr<Song>(new Song("One Day"));
        songLib.insert(*song3);
        recommendation.add_song(song3);
        std::shared_ptr<Song> song4 = std::shared_ptr<Song>(new Song("I wish"));
        songLib.insert(*song4);
        recommendation.add_song(song4);
    }
    //VIBEZ = 4
    Song song = Song("VIBEZ");
    recommendation.listen_toSong(songLib.find(song), 1);
    recommendation.listen_toSong(songLib.find(song), 1);
    recommendation.listen_toSong(songLib.find(song), 1);
    recommendation.listen_toSong(songLib.find(song), 1);

    //Gangsta's paradise = 6
    song = Song("Gangsta's Paradise");
    recommendation.listen_toSong(songLib.find(song), 1);
    recommendation.listen_toSong(songLib.find(song), 1);
    recommendation.listen_toSong(songLib.find(song), 1);
    recommendation.listen_toSong(songLib.find(song), 1);
    recommendation.listen_toSong(songLib.find(song), 1);
    recommendation.listen_toSong(songLib.find(song), 1);

    //One day = 1
    song = Song("One Day");
    recommendation.listen_toSong(songLib.find(song), 1);

    //I wish = 5
    song = Song("I wish");
    recommendation.listen_toSong(songLib.find(song), 1);
    recommendation.listen_toSong(songLib.find(song), 1);
    recommendation.listen_toSong(songLib.find(song), 1);
    recommendation.listen_toSong(songLib.find(song), 1);
    recommendation.listen_toSong(songLib.find(song), 1);

    std::cout << recommendation.recommend() << std::endl;
    std::cout << recommendation.recommend() << std::endl;
    std::cout << recommendation.recommend() << std::endl;
    std::cout << recommendation.recommend() << std::endl;

    std::cout << recommendation.recommend() << std::endl;
    std::cout << recommendation.recommend() << std::endl;
    std::cout << recommendation.recommend() << std::endl;
    std::cout << recommendation.recommend() << std::endl;


    return 0;
}
