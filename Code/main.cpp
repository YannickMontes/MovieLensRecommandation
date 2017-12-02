#include <iostream>
#include "User.h"
#include "Constantes.h"
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

void readFiles(int, vector<User>*);
void fillSimilitudeBetweenUsers(vector<User>* users);

int main(int argc, char *argv[])
{
	cout << "TP4 - Movie Lens" <<endl;
	cout << "Arnaud Ricaud 17 je sais pas" << endl;
	cout << "Yannick Montes 17 138 937" << endl;

	vector<User> users;
	readFiles(1, &users);

	fillSimilitudeBetweenUsers(&users);

	return 0;
}

void readFiles(int number, vector<User>* users)
{
	cout << "Lecture des fichiers..." << endl;
	ifstream base;
	ostringstream oss;
	oss << INPUT_DEB << number << INPUT_BASE_END;
	base.open(oss.str().c_str());

	if(!base)
	{
		cerr << "Fail to open base file" << endl;
		return;
	}

	int userId, movieId, rating, timestamp, lastUserId = 0, nbMoviesRated = 0;
	double moyenne = 0;
	User* currentUser = nullptr;
	while(base >> userId >> movieId >> rating >> timestamp)
	{
		if(userId != lastUserId)
		{
			if(currentUser != nullptr)
			{
				currentUser->setMoyenneRatings(moyenne / nbMoviesRated);
				users->push_back(*currentUser);
			}
			currentUser = new User(userId);
			lastUserId = userId;
			moyenne = 0;
			nbMoviesRated = 0;
		}
		currentUser->addRatingFor(movieId, rating);
		moyenne += rating;
		nbMoviesRated++;
	}
	users->push_back(*currentUser);

	base.close();

	ifstream test;
	oss.flush();
	oss << INPUT_DEB << number << INPUT_TEST_END;

	if(!test)
	{
		cerr << "Fail to open test file" << endl;
		return;
	}

	while(test >> userId >> movieId >> rating >> timestamp)
	{
		users->at(userId - 1).addTestMovie(movieId, rating);
	}

	test.close();

	cout << "Lecture terminée." << endl;
}

void fillSimilitudeBetweenUsers(vector<User>* users)
{
	cout << "Calcul de la similitude entre chaque user..." << endl;
	vector<int> moviesRatedBoth;
	for(User userU : *users)
	{
		for(User userV : *users)
		{
			if(userU.getId() != userV.getId())
			{
				moviesRatedBoth.clear();
				map<int, int> ratedMoviesU = userU.getRatedMovies();
				for(auto &pair : ratedMoviesU)
				{
					if(userV.hasRated(pair.first))
					{
						moviesRatedBoth.push_back(pair.first);
					}
				}

				double numeratorSum = 0;
				double denomSumU = 0;
				double denomSumV = 0;
				for(auto &movieId : moviesRatedBoth)
				{
					numeratorSum += ((userU.getRatingFor(movieId) - userU.getMoyenneRatings()) * (userV.getRatingFor(movieId) - userV.getMoyenneRatings()));
					denomSumU += pow((userU.getRatingFor(movieId) - userU.getMoyenneRatings()), 2);
					denomSumV += pow((userV.getRatingFor(movieId) - userV.getMoyenneRatings()), 2);
				}

				double pearsonCoeff = (numeratorSum / sqrt((denomSumU * denomSumV)));

				if(pearsonCoeff != pearsonCoeff)
				{
					pearsonCoeff = 0;
				}

				userU.addSimilitudeTo(userV, pearsonCoeff);
				userV.addSimilitudeTo(userU, pearsonCoeff);
			}
		}
	}

	cout << "Calcul de la similitude terminé." << endl;
}
