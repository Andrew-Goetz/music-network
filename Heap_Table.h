//a heap table implementation
//based on an vector

#ifndef HT_H
#define HT_H

#include <string>
#include <vector>
#include <memory>
#include "Song.h"


//could've just inherited this class, fuck it
// class SongInfo : Song
// {
// public:
//     Song name;
//     int position;
// 	//int recommendation;

//     ~SongInfo(){}

//     //a constructor that will return a node that will 100%
//     //be different than any other node
//     SongInfo() : name(""), position(-1){};

//     //a constructor that will assign name and relationship
//     SongInfo(Song n, int p) : name(n), position(p){};

//     //make 100000% sure name won't be accidentally
//     //freed.
//     SongInfo(const SongInfo& copy);
//     SongInfo(SongInfo&& copy);

//     //comparison stuff for BST
//     friend bool operator> (const SongInfo &N1, const SongInfo &N2) { return N1.name > N2.name;};
//     friend bool operator< (const SongInfo &N1, const SongInfo &N2) { return N1.name < N2.name;};
//     friend bool operator>= (const SongInfo &N1, const SongInfo &N2) { return N1.name >= N2.name;};
//     friend bool operator<= (const SongInfo &N1, const SongInfo &N2) { return N1.name <= N2.name;};
//     friend bool operator== (const SongInfo &N1, const SongInfo &N2) { return N1.name == N2.name;};
//     friend bool operator!= (const SongInfo &N1, const SongInfo &N2) { return N1.name != N2.name;};
//     SongInfo& operator= (const SongInfo &N1);
//     SongInfo& operator= (SongInfo &N1);
// };

class Heap_Table_SongInfo
{
public:

    Heap_Table_SongInfo() : array(std::vector<std::shared_ptr<Song>>()){};
    
    void add_song(std::shared_ptr<Song> name);
    int listen_toSong(Song& position, int times);
    std::string recommend();

private:
    void sift_Up(int i);
    void sift_Down(int i);


    std::vector<std::shared_ptr<Song>> array;
};

#endif
