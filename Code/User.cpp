#include "User.h"
#include <stdexcept>


using namespace std;

User::User(int id)
{
	this->id = id;
}

User::~User()
{

}

bool User::hasRated(int movie)
{
	try
	{
		this->ratedMovies.at(movie);
		return true;
	}
	catch(const out_of_range& oor)
	{
		return false;
	}
}

void User::addRatingFor(int idFilm, int value)
{
	this->ratedMovies[idFilm] = value;
}

void User::addTestMovie(int idFilm, int value)
{
	this->testMovies[idFilm] = value;
}

void User::addSimilitudeTo(User u, double value)
{
	this->similitude.emplace(u.getId(), value);
}

void User::addHypotheticalRate(int idFilm, double value)
{
	this->hypotheticalRates.emplace(idFilm, value);
}

int User::getRatingFor(int idFilm)
{
	if(this->hasRated(idFilm))
	{
		return this->ratedMovies.at(idFilm);
	}
	return 0;
}

void User::addClosestUser(int idUser)
{
	this->kClosestUsers.push_back(idUser);
}




