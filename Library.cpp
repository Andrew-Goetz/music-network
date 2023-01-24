#include "Library.h"
#include <iostream>

#define PRIMARY_NAME "PrimaryUser"

//PrimaryUser name will be reserved
Library::Library(): users{}, RecommendationSystem{}, primaryUserLib{}, SystemLib{}, radius(1)
{
    users.add_user(PRIMARY_NAME);
}

//true chad only uses stack memory, no free needed :smart:
Library::~Library(){}

void Library::add_user(std::string name)
{
    if(name == PRIMARY_NAME || name == "")
    {
        std::cout << "[Warning add_user] invalid name: " << name << " is trying to get added, aborted" << std::endl;
        return;
    }
    users.add_user(name);
}

void Library::make_friends(std::string name1, std::string name2)
{
    if(name1 == "" || name2 == "")
    {
        std::cout << "[Warning make_friends] invalid name: " << name2 << " or " << name1 << " is trying to get added, aborted" << std::endl;
        return;
    }
    users.make_friends(name1, name2);
}

void Library::break_friends(std::string name1, std::string name2)
{
    if(name1 == "" || name2 == "")
    {
        std::cout << "[Warning break_friends] invalid name: " << name2 << " or " << name1 << " is trying to get added, aborted" << std::endl;
        return;
    }
    users.unfriend(name1, name2);
}

void Library::add_song(std::string title)
{
    if(title == "")
    {
        std::cout << "[Warning add_song] invalid name: " << title << " is trying to get added, aborted" << std::endl;
        return;
    }
    std::shared_ptr<Song> song = std::shared_ptr<Song>(new Song(title));
    RecommendationSystem.add_song(song);
    SystemLib.insert(*song);
}
class except{};
int Library::Listen_To_Song(std::string user, std::string title, int times)
{
    if(SystemLib.getSize() <= 0)
    {
        std::cout << "[Warning recommend_songs] You haven't added any songs yet!" << std::endl;
        return 0;
    }
	try
    {
        if(primaryUserLib.find(Song(title)) != std::string()) throw except();
    }
    catch(...)
    {
        std::cout << "[Warning recommend_songs] This song is already recommended or it doesn't exist!" << std::endl;
        return 0;
    }
    if(users.isFriend("PrimaryUser", user, radius))
    {
        Song temp = Song(title);
        try
        {     
            return RecommendationSystem.listen_toSong(SystemLib.find(temp), times);
        }
        catch(...)
        {
            std::cout << "[Warning recommend_songs] This song doesn't exist!" << std::endl;
            return 0;
        }
    }
    else
    {
        std::cout << "[Warning Listen_to_Song] user not within radius of the primary user" << std::endl;
        return 0;
    }
}

int Library::get_PlayCount(std::string title)
{
    Song song = Song(title);
    try
    {
        return SystemLib.find(song).getPlayCount();    
    }
    catch(...)
    {
        std::cout << "[Warning get_PlayCount] This song doesn't exist!" << std::endl;
        return 0;
    }
}

//TODO: look at piazza
std::string Library::recommend_songs(int count)
{
    if(SystemLib.getSize() <= 0)
    {
        std::cout << "[Warning recommend_songs] You haven't added any songs yet!" << std::endl;
        return "";
    }

    std::string names = "";
    for(int i = 0; i < count; i++)
    {
        std::string title = RecommendationSystem.recommend();
        if(title == std::string())
        {
            std::cout << "[Warning recommend_songs] No more songs with listen count greater than 0 found!" << std::endl;
            return names;
        }
        if(primaryUserLib.find(Song(title)) == Song()) // we haven't recommended this yet
        {
            names += title;
            names += "\n";
            primaryUserLib.insert(Song(title));
			names = "";
        }
        else
        {
            std::cout << "[Warning recommend_songs] No more songs with listen count greater than 0 found!" << std::endl;
            return names;
        }
    }
    return names;
}

void Library::remove_from_primaryLib(std::string title)
{
    if(title == "")
    {
        std::cout << "[Warning remove_from_primaryLib] invalid name: " << title << " is trying to get removed, aborted" << std::endl;
        return;
    }
    primaryUserLib.remove(Song(title));
}

std::string Library::get_friends(std::string user)
{
    if(user == "")
    {
        std::cout << "[Warning remove_from_primaryLib] invalid name: " << user << " is trying to get removed, aborted" << std::endl;
        return "";
    }
    return users.getFriends(user);
}

std::vector<Song> Library::get_primaryLib()
{
    return primaryUserLib.getArray();
}

std::vector<Song> Library::get_SystemLib(int count)
{
    std::vector<Song> ret{};
    std::vector<Song> vec = SystemLib.getArray();
    int chance = 0;
    for(Song s : vec) 
    {
        if(chance >= count) break;
        ret.push_back(s);
        chance++;
    }
    return ret;
}

std::vector<Song> Library::get_SystemLib() // same function but gets all songs
{
    return SystemLib.getArray();
}

void Library::setRadius(int EFN_radius) {
	if(EFN_radius <= 0) {
        std::cout << "[Warning setRadius] cannot set radius to 0 or a negative number, aborted" << std::endl;
		return;
	}
	radius = EFN_radius;
}
