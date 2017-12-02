#pragma once
#include <iostream>
#include <map>
#include <vector>

class User
{
private:
	int id;
	std::map<int, int> ratedMovies;//Int id film, int rating
	std::map<int, int> testMovies;//Int id film, int guessed rating
	std::map<User, int> similitude;
	std::vector<User> kClosestUsers;

public:
	User(int);
	~User();

	int getId(){return this->id;};
	bool hasRated(int movie);
	int getRatingFor(int idFilm);
	void addRatingFor(int idFilm, int value);
	void addTestMovie(int idFilm, int value);
	std::vector<User> getKClosestUsers(){return this->kClosestUsers;};
};
