#include <string>
#include <iostream>
#include "Library.h"
#include <vector>
#include "Parser.h"
#include <fstream>

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

/*
	------ Commands ------
	1) add user [name]
	2) friend [user1] [user2] (if arg2 is empty, friend with primary user)
	3) break [user1] [user2] (if arg2 is empty, break with primary user)
	4) add song [title]
	5) listen (then prompts for [user], [song], and [n])
	6) radius [K]
	7) recommend [k]
	8) remove song [title]
	9) show friends
	10) show added
	11) show unadded
	12) exit
*/

int main() {
    Library lib;
    std::string input;
    std::string op;
    std::string arg1;
    std::string arg2;
	std::ifstream songs("songs.txt");
	std::ifstream users("users.txt");
	std::string temp;
	while(getline(songs, temp) && songs) {
    	lib.add_song(temp);
	}
	while(getline(users, temp) && users) {
    	lib.add_user(temp);
	}
	songs.close();
	users.close();
    std::cout << "Welcome to your music application!" << std::endl;
    while(input != "exit") {
		std::cout << ">> ";
        getline(std::cin, input);
        Parser command(input);
        op = command.getOperation();
        arg1 = command.getArg1();
        arg2 = command.getArg2();
        if(op == "add" && !arg2.empty()) {
            if(arg1 == "user") {
                lib.add_user(arg2);
            } else if(arg1 == "song") {
                lib.add_song(arg2);
            } else {
                std::cout << "Error: invalid command." << std::endl;
            }
        }

        else if(op == "friend" && !arg1.empty()) {
			if(arg2.empty()) {
            	lib.make_friends(arg1, "PrimaryUser");
			} else {
            	lib.make_friends(arg1, arg2);
			}
        }

        else if(op == "break" && !arg1.empty()) {
			if(arg2.empty()) {
            	lib.break_friends(arg1, "PrimaryUser");
			} else {
            	lib.break_friends(arg1, arg2);
			}
        }

        else if(op == "listen" && arg1.empty() && arg2.empty()) {
            std::string user, title, times;
            std::cout << "User: ";
            getline(std::cin, user);
            std::cout << "Song title: ";
            getline(std::cin, title);
            std::cout << "Listen amount: ";
            getline(std::cin, times);

            lib.Listen_To_Song(user, title, stoi(times));
        }

        else if(op == "radius" && !arg1.empty() && arg2.empty()) {
			lib.setRadius(stoi(arg1));
        }

        else if(op == "recommend" && !arg1.empty() && arg2.empty()) {
            lib.recommend_songs(stoi(arg1));
        }

        else if(op == "remove" && arg1 == "song" && !arg2.empty()) {
            lib.remove_from_primaryLib(arg2);
        }

        else if(op == "show" && arg2.empty()) {
            if(arg1 == "friends") {
                std::string user;
                std::cout << "Show friends of primary user or other? (Enter <PrimaryUser> or <other user name>): ";
                getline(std::cin, user);
                if(user == "PrimaryUser") {
                    std::cout << "Friends of " << lib.get_friends("PrimaryUser") << std::endl;
                } else {
                    std::cout << "Friends of " << lib.get_friends(user) << std::endl;
                }
            } else if(arg1 == "added") { // shows all songs in primary library
                std::vector<Song> song = lib.get_primaryLib();
                for(Song s : song) std::cout << "Title: " << s.getTitle() << std::endl;
                std::cout << std::endl;
            } else if(arg1 == "unadded") { // shows all songs that are not in primary library
                std::vector<Song> primarySongs = lib.get_primaryLib();
                std::vector<Song> allSongs = lib.get_SystemLib();
				if(primarySongs.size() == 0) { //This is to fix a problem with printing out songs when vector sizes = 0
					for(Song s : allSongs) {
						std::cout << "Title: " << s.getTitle() << "    Listens: " << s.getPlayCount() << std::endl;
					}
				} else {
					for(Song s : allSongs) {
                        bool temp = false;
						for(Song sp : primarySongs) {
							if(s == sp) {
								temp = true;
							}
						}
                        if(!temp) std::cout << "Title: " << s.getTitle() << "    Listens: " << s.getPlayCount() << std::endl;
					}
				}
            } else if(arg1 == "playCount"){
                std::string soingtitl;
                std::cout << "Please enter song title name: ";
                getline(std::cin, soingtitl);
                std::cout << lib.get_PlayCount(soingtitl) << std::endl;
            } else {
                std::cout << "Error: invalid command." << std::endl;
            }
        }

        else if(op == "exit" && arg1.empty() && arg2.empty()) {
            std::cout << "The program will now exit." << std::endl;
            input = "exit";
        }

        else {
            if(!op.empty()) {
                std::cout << "Error: invalid command." << std::endl;
            }
        }
        std::cout << "\n";
    }
/*
    lib.add_user("Mike");
    lib.add_user("George");
    lib.add_user("Allen");
    lib.add_user("Hunter");
    lib.add_user("Andrew");
    lib.make_friends("Mike", "PrimaryUser");
    lib.make_friends("Mike", "George");
    lib.make_friends("George", "Allen");
    lib.make_friends("Allen", "Andrew");
    lib.make_friends("Allen", "PrimaryUser");
    lib.break_friends("Allen", "PrimaryUser");
    lib.make_friends("Hunter", "PrimaryUser");

    lib.add_song("VIBEZ");
    lib.add_song("Gangsta's Paradise");
    lib.add_song("One Day");
    lib.add_song("I Wish");

	//should listen
	std::cout << "started listening, shouldn't give any problem\n" << std::endl;
    lib.Listen_To_Song("Mike", "VIBEZ", 1, 4);
    lib.Listen_To_Song("George", "Gangsta's Paradise", 2, 6);
    lib.Listen_To_Song("Allen", "One Day", 3, 1);
    lib.Listen_To_Song("Andrew", "I Wish", 4, 5);

	//should not listen

	std::cout << "started listening, SHOULD give problems\n" << std::endl;
    lib.Listen_To_Song("George", "Gangsta's Paradise", 1, 6);
    lib.Listen_To_Song("Allen", "One Day", 2, 1);
    lib.Listen_To_Song("Andrew", "I Wish", 3, 5);

	std::cout << std::endl;

	//VIBEZ = 4
	//Gangsta's paradise = 6
	//One day = 1
	//I wish = 5

    std::cout << "should recommend: Gangsta's Paradise, I Wish, and VIBEZ" << std::endl;
    std::cout << lib.recommend_songs(3) << std::endl;

	std::cout << std::endl;
    std::cout <<"print out what songs are in the primary lib, which should be the same as above" << std::endl;
    std::vector<std::string> song = lib.get_primaryLib();
    for(std::string s : song) std::cout << s << std::endl;
    std::cout << std::endl;

    std::cout << "print out every song, see comment above" << std::endl;
    song = lib.get_SystemLib(4);
    for(std::string s : song) std::cout << s << std::endl;
    std::cout << std::endl;

    std::cout << "should recommend one song, then print a warning saying no more song is recommended" << std::endl;
    std::cout << lib.recommend_songs(2) << std::endl;
*/
    return 0;
}
