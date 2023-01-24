#include "Song.h"
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <string>

Song::Song() : title(""), playCount(0) , arrayPosition(-1) {}

Song::Song(std::string t) : title(t), playCount(0), arrayPosition(-1) {}

Song::Song(const Song &s) {
	title = s.title;
	playCount = s.playCount;
	arrayPosition = s.arrayPosition;
}

Song::Song(Song&& copy)
{
	std::swap(title, copy.title);
	std::swap(playCount, copy.playCount);
	std::swap(arrayPosition, copy.arrayPosition);
}

int& Song::getPosition()
{
	return arrayPosition;
}
// void Song::setPosition(int p)
// {
// 	arrayPosition = p;
// }

Song& Song::operator=(const Song &s) {
	title = s.title;
	playCount = s.playCount;
	arrayPosition = s.arrayPosition;
	return *this;
}

Song& Song::operator= (Song &s)
{
	title = s.title;
	playCount = s.playCount;
	arrayPosition = s.arrayPosition;
	return *this;
}

//Should this be changed to compare play count rather than song titles?
bool Song::operator==(const Song &s) {
	if(title == s.title) {
		return true;
	}
	return false;
}

bool Song::operator!=(const Song &s) {
	if(title == s.title) {
		return false;
	}
	return true;
}

std::ostream &operator<<(std::ostream &out, const Song &s) {
	out << "Title: " << s.title;
	out << "      Listens: " << s.playCount;
	return out;
}

void Song::print() {
	std::cout << "Title: " << title;
	std::cout << "      Listens: " << playCount << std::endl;
}

void Song::setTitle(std::string t) {
	title = t;
}

std::string Song::getTitle() {
	return title;
}

void Song::addPlayCount(int p) {
	playCount += p;
}

int Song::getPlayCount() {
	return playCount;
}

void Song::setPlayCount(int count) {
	playCount = count;
}
