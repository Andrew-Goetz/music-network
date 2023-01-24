#include "Heap_Table.h"
#include <iostream>

//O(1)
void Heap_Table_SongInfo::add_song(std::shared_ptr<Song> name)
{
    //just push to the end of the array lol
    name->getPosition() = array.size();
    array.push_back(name);
}

//O(logn) because of sift_up
int Heap_Table_SongInfo::listen_toSong(Song& position, int times)
{
    array.at(position.getPosition())->addPlayCount(times);
    int playCount = array.at(position.getPosition())->getPlayCount();
    sift_Up(position.getPosition());
    return playCount;
}

//O(logn) because of sift down
std::string Heap_Table_SongInfo::recommend()
{
    //std::cout << "arraysize: " << array.size() << std::endl;
    std::shared_ptr<Song> position = array.at(0);
    if(array.at(position->getPosition())->getPlayCount() == 0) return std::string();
    array.at(position->getPosition())->setPlayCount(0);
    sift_Down(position->getPosition());
    return position->getTitle();
}

// SongInfo& SongInfo::operator= (const SongInfo &N1)
// {
//     name = N1.name;
//     position = N1.position;
//     recommendation = N1.recommendation;
//     return *this;
// }
// SongInfo& SongInfo::operator= (SongInfo &N1)
// {
//     name = N1.name;
//     position = N1.position;
//     recommendation = N1.recommendation;
//     return *this;
// }

//complexity: O(logn)
//sift_down_force
void Heap_Table_SongInfo::sift_Down(int base)
{
    int root = base;
    int rootbackup = root;
    int arrlen = (int)(unsigned int)array.size();
    while(true){
        int left = root * 2 + 1;
        int right = root * 2 + 2;

        //this node has no child, so it can't be smaller
        if(left >= arrlen && right >= arrlen) break;

        //if there is a left, and it is larger than root
        if(left < arrlen && array[left]->getPlayCount() > array[root]->getPlayCount())
        {
            //set the root to left
            root = left;
        }
        //if there is a right, and it is larger than root
        if (right < arrlen && array[right]->getPlayCount() > array[root]->getPlayCount())
        {
            //set the root to right
            root = right;
        }

        //if there is ever a greater root in the children
        if(root != rootbackup)
        {
            //swap(rootbackup, root);
            std::shared_ptr<Song> tmp; 
            tmp = array[rootbackup]; 
            array[rootbackup] = array[root];
            array[rootbackup]->getPosition() = rootbackup;
            array[root] = tmp; 
            array[root]->getPosition() = root;

            //now we know that the root is no longer the largest, process the subtree?
            rootbackup = root;
            continue;
        }
        //There are no children greater than the root, aborting.
        break;
    }
}

//complexity: O(logn)
void Heap_Table_SongInfo::sift_Up(int base)
{
    int root = base;
    int rootbackup = root;
    while(true){
        int parent = (root - 1) / 2;

        //this node has no parent, so it can't be smaller
        if(parent < 0) break;

        //if there is a parent, and it is smaller than root
        if (parent >= 0 && array[parent]->getPlayCount() < array[root]->getPlayCount())
        {
            //set the root to parent
            root = parent;
        }

        //if there is ever a smaller root in the parent
        if(root != rootbackup)
        {
            //swap(rootbackup, root);
            std::shared_ptr<Song> tmp; 
            tmp = array[rootbackup]; 
            array[rootbackup] = array[root];
            array[rootbackup]->getPosition() = rootbackup;
            array[root] = tmp; 
            array[root]->getPosition() = root;

            //now we know that the root is no longer the largest, process the subtree?
            rootbackup = root;
            continue;
        }
        //There are no parent smaller than the root, aborting.
        break;
    }
}

