#pragma once
#include <iostream>
#include <map>

class User
{
private:
	int id;
	std::map<int, int> ratedMovies;//Int id film, int rating
	std::std::map<int, > unratedMovies;//Int id film, int guessed rating
	std::vector<User> kClosestUsers;

public:
	User();
	~User();

	int getId(){return this->id;};
	bool hasRated(int movie);
	int getRatingFor(int idFilm);
	std::vector<int> getKClosestUsers(){return this->kClosestUsers;};
};
