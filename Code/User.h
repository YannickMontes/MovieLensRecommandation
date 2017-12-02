#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <cmath>

class User
{
private:
	int id;
	std::map<int, int> ratedMovies;//Int id film, int rating
	std::map<int, int> testMovies;//Int id film, int guessed rating
	std::map<int, int> hypotheticalRates; //Int id film, int note
	std::map<int, double> similitude;
	std::vector<int> kClosestUsers;
	double moyenneRatings;

public:
	User(int);
	~User();

	int getId(){return this->id;};
	std::map<int, int> getRatedMovies(){return this->ratedMovies;};
	bool hasRated(int movie);
	int getRatingFor(int idFilm);
	void addClosestUser(int idUser);
	void addRatingFor(int idFilm, int value);
	void addTestMovie(int idFilm, int value);
	void addSimilitudeTo(User u, double value);
	void addHypotheticalRate(int idFilm, double value);
	void setMoyenneRatings(double moy){this->moyenneRatings = moy;}
	double getMoyenneRatings(){return this->moyenneRatings;};
	std::vector<int> getKClosestUsers(){return this->kClosestUsers;};

	std::map<int, int> getRatings() { return ratedMovies; };
	std::map<int, int> getTestRatings() { return testMovies; };
	std::map<int, int> getHypotheticalRates() { return hypotheticalRates; };
	std::map<int, double> getSimilitude() { return similitude; };
};
