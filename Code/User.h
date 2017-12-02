#pragma once
#include <iostream>
#include <map>
#include <vector>

class User
{
private:
	int id;
	std::map<int, int> ratedMovies;//Int id film, int rating
	std::map<int, int> unratedMovies;//Int id film, int guessed rating
	std::vector<User> kClosestUsers;

public:
	User(int);
	~User();

	int getId(){return this->id;};
	bool hasRated(int movie);
	int getRatingFor(int idFilm);
	std::vector<User> getKClosestUsers(){return this->kClosestUsers;};
};
