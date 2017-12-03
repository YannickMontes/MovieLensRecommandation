#include "User.h"
#include <stdexcept>
#include <algorithm>
#include <functional>
#include <set>
#include <iterator>

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
	return (this->ratedMovies.find(movie) != this->ratedMovies.end());
	/*try
	{
		this->ratedMovies.at(movie);
		return true;
	}
	catch(const out_of_range& oor)
	{
		return false;
	}*/
}

void User::addRatingFor(int idFilm, int value)
{
	if(value == 0)
	{
		cout << "On insert " << value << endl;
	}
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

vector<pair<int, double> >* User::getKClosestUserFor(int idFilm, vector<User*>* users, int k)
{
	vector< pair<int, double> >* toRet = new std::vector<pair<int, double> >();
	int nb =0;
	for(auto &sim : this->sortedSimilitude)
	{
		if(users->at(sim.first -1 )->hasRated(idFilm))
		{
			toRet->push_back(sim);
			nb++;
			if(nb >= k)
			{
				return toRet;
			}
		}
	}
	return toRet;
}

void User::sortSimilitude()
{
	vector<pair<int, double> > sorted(this->similitude.size());
	partial_sort_copy(similitude.begin(),
		similitude.end(),
		sorted.begin(),
		sorted.end(),
		[](pair<const int, double> const& l,
			pair<const int, double> const& r)
		{
			return (l.second >= r.second);
			/*
			if(users->at(l.first - 1).hasRated(idFilm))
			{
				cout << "Id l " << l.first << " Id user " << users->at(l.first-1).getId() << endl;
				return (l.second >= r.second ;
			}
			else
			{
				return false;
			}*/
		});
	for(auto &tmp : sorted)
	{
		this->sortedSimilitude.push_back(tmp);
	}
}
