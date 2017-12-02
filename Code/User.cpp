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

int User::getRatingFor(int idFilm)
{
	if(this->hasRated(idFilm))
	{
		return this->ratedMovies.at(idFilm);
	}
	return 0;
}

void User::calcAllRatings()
{
	for (auto idFilm : testMovies) {
		int noteSum = 0;
		int nbNotes = 0;
		double finalNote;
		for (int i = 0; i < kClosestUsers.size(); i++) {
			if (kClosestUsers[i].getRatings().find(idFilm.first) != kClosestUsers[i].getRatings().end()) {
				noteSum = noteSum + (kClosestUsers[i].getRatings()[idFilm.first]);
				nbNotes += 1;
			}
		}
		if (nbNotes != 0) {
			finalNote = noteSum / nbNotes;
		}
	}
}
