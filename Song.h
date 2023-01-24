#ifndef SONG_CLASS_H
#define SONG_CLASS_H

#include <string>

class Song {
	private:
		std::string title;
		int playCount;
		int arrayPosition;
	public:
		Song();
		Song(std::string t);
		Song(const Song &s);
		Song(Song&& copy);
		Song& operator=(const Song &s);
		bool operator==(const Song &s);
		bool operator!=(const Song &s);
		friend std::ostream &operator<<(std::ostream &out, const Song &s);
		void print();
		void setTitle(std::string t);
		std::string getTitle();
		void addPlayCount(int p);
		int getPlayCount();
		void setPlayCount(int count);
		int& getPosition(); // better lel
		//void setPosition(int);



		friend bool operator> (const Song &N1, const Song &N2) { return N1.title > N2.title;};
		friend bool operator< (const Song &N1, const Song &N2) { return N1.title < N2.title;};
		friend bool operator>= (const Song &N1, const Song &N2) { return N1.title >= N2.title;};
		friend bool operator<= (const Song &N1, const Song &N2) { return N1.title <= N2.title;};
		friend bool operator== (const Song &N1, const Song &N2) { return N1.title == N2.title;};
		friend bool operator!= (const Song &N1, const Song &N2) { return N1.title != N2.title;};
		//Song& operator= (const Song &N1);
		Song& operator= (Song &N1);
};

#endif
