#ifndef LIB_H
#define LIB_H

#include "Graph.h"
#include "Heap_Table.h"
#include "BST.h"
#include "BST_ref.h"


//putting it all together
class Library
{
public:
    Library();
    ~Library();
    void add_user(std::string name);
    void make_friends(std::string name1, std::string name2);
    void break_friends(std::string name1, std::string name2);
    void add_song(std::string title);
    int Listen_To_Song(std::string user, std::string title, int times);
    std::string recommend_songs(int count);
    void remove_from_primaryLib(std::string title);
    std::string get_friends(std::string user);
    std::vector<Song> get_primaryLib();
    std::vector<Song> get_SystemLib(int count);
    std::vector<Song> get_SystemLib();
    int get_PlayCount(std::string title);
	//int getEFN();
	void setRadius(int EFN_radius);
private:
    friend_Graph users;
    Heap_Table_SongInfo RecommendationSystem;
    BST<Song> primaryUserLib;
    BST_ref<Song> SystemLib;
	int radius;
};



#endif
