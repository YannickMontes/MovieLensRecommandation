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
	std::map<int, double> similitude;
	std::vector<User> kClosestUsers;
	double moyenneRatings;

public:
	User(int);
	~User();

	int getId(){return this->id;};
	std::map<int, int> getRatedMovies(){return this->ratedMovies;};
	bool hasRated(int movie);
	int getRatingFor(int idFilm);
	void calcAllRatings();
	void addRatingFor(int idFilm, int value);
	void addTestMovie(int idFilm, int value);
	void addSimilitudeTo(User u, double value);
	void setMoyenneRatings(double moy){this->moyenneRatings = moy;}
	double getMoyenneRatings(){return this->moyenneRatings;};
	std::vector<User> getKClosestUsers(){return this->kClosestUsers;};

	std::map<int, int> getRatings() { return ratedMovies; };
	std::map<int, int> getTestRatings() { return testMovies; };
};
