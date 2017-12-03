#include <iostream>
#include "User.h"
#include "Constantes.h"
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <functional>
#include <set>
#include <vector>
#include <cmath>

using namespace std;

void readFiles(int, vector<User>*);
void fillSimilitudeBetweenUsers(int, vector<User>* users, bool);
void writeResult(int number, vector<User>* users);
void calcNewRates(vector<User>* users);
void computeMeanSquaredError(int, vector<User>*);

int main(int argc, char *argv[])
{
	cout << "TP4 - Movie Lens" <<endl;
	cout << "Arnaud Ricaud 17 132 853" << endl;
	cout << "Yannick Montes 17 138 937" << endl;

	int docToLoad = 1;

	vector<User> users;
	readFiles(docToLoad, &users);
	calcNewRates(&users);
	writeResult(docToLoad, &users);
	computeMeanSquaredError(docToLoad, &users);
	system("pause");
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
	oss.clear();
	oss.str(string());
	oss << INPUT_DEB << number << INPUT_TEST_END;

	test.open(oss.str().c_str());

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

	ifstream similitude;
	oss.clear();
	oss.str(string());
	oss << OUT_SIMILITUDE_DEB << number << OUT_SIMILITUDE_END;

	similitude.open(oss.str().c_str());

	if(!similitude)
	{
		cout << "Le fichier similitude n'existe pas. Nous allons calculer cette dernière" << endl;
		fillSimilitudeBetweenUsers(number, users, true);
	}
	else
	{

		int id1, id2;
		double simi;
		while(similitude >> id1 >> id2 >> simi)
		{
			users->at(id1 -1).addSimilitudeTo(id2, simi);
			users->at(id2 -1).addSimilitudeTo(id1, simi);
		}

		cout << "Lecture terminee." << endl;
		cout << "Calcul des plus proches voisins..." << endl;
		/*
		for(int i = 0; i< users->size(); i++){
			for (int j = 0; j < K_CLOSEST_USR; j++) {
				double simValue = 0;
				int idCloseUser;
				bool alreadyIn = false;
				for (auto key : (*users)[i].getSimilitude()) {
					if (abs(key.second) > simValue) {
						for (int k = 0; k < (*users)[i].getKClosestUsers().size(); k++) {
							if ((*users)[i].getKClosestUsers()[k] == key.first) {
								alreadyIn = true;
							}
						}
						if (!alreadyIn) {
							idCloseUser = key.first;
							simValue = key.second;
						}
					}
				}
				(*users)[i].addClosestUser(idCloseUser);
			}
		}
		*/
		for(User u : *users)
		{
			//cout << "Avant" << u.getSimilitude().size() << endl;
			u.sortSimilitude();

			//cout <<  "Après " << u.getSimilitude().size() << endl;
		}
	}

	cout << "Calculs des plus proches voisins termines." << endl;
}

void fillSimilitudeBetweenUsers(int number, vector<User>* users, bool writeFile)
{
	cout << "Calcul de la similitude entre chaque user..." << endl;

	ofstream similitudeFile;
	if(writeFile)
	{
		ostringstream oss;
		oss << OUT_SIMILITUDE_DEB << number << OUT_SIMILITUDE_END;

		similitudeFile.open(oss.str().c_str());

		if(!similitudeFile)
		{
			cerr << "Fail to open output file" << endl;
		}
	}

	vector<int> moviesRatedBoth;
	for(User userU : *users)
	{
		for(User userV : *users)
		{
			if(userV.getId() > userU.getId())
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

				if(writeFile)
					similitudeFile << userU.getId() << " " << userV.getId() << " " << pearsonCoeff << "\r\n";
			}
		}
	}

	if(writeFile)
		similitudeFile.close();

	cout << "Calcul de la similitude terminé." << endl;
}

void writeResult(int number, vector<User>* users) {
	cout << "Debut de l'ecriture des resultats" << endl;
	string file = "../Data/resultU.txt";
	ofstream output;
	output.open(file);
	if(!output)
	{
		cout << "Fail to write results" << endl;
		return;
	};
	for (int i = 0; i < users->size(); i++)
	{
		for (auto film : ((*users)[i]).getHypotheticalRates()) {
			output << ((*users)[i]).getId() << " " << film.first << " " << film.second << "\r\n";
		}
		i++;
	}

	output.close();
	cout << "Ecriture terminee" << endl;
}



void calcNewRates(vector<User>* users)
{
	cout << "Calcul des notes hypothetiques..." << endl;
	int nbNoteNull = 0;
	//Pour chaque user:
	vector<int> closestNeigh;
	for (User current : *users) {
		for (auto idFilm : current.getTestRatings()) {
			double noteSum = 0;
			double nbNotes = 0;
			double finalNote;
			closestNeigh.clear();
			int nbClosest = 0;
			for (auto &element : current.getSimilitude())
			{
				User* tmp = &users->at(element.first - 1);
				if(tmp->hasRated(idFilm.first))
				{
					closestNeigh.push_back(tmp->getId());
					nbClosest++;
					if(nbClosest >= K_CLOSEST_USR)
					{
						break;
					}
				}
			}

			for (int neigh : closestNeigh)
			{
				noteSum = noteSum + users->at(neigh-1).getRatingFor(idFilm.first);
				nbNotes++;
			}
			if (nbNotes != 0)
			{
				finalNote = noteSum / nbNotes;
				current.addHypotheticalRate(idFilm.first, finalNote);
			} else {
				nbNoteNull += 1;
			}
		}
		if(current.getId() % 100 == 0)
		{
			cout << "Utilisateur "<< current.getId() << endl;
		}
	}
	cout << "Calcul termine... Notes nulles: "<< nbNoteNull << endl;
}


void computeMeanSquaredError(int number, vector<User>* users)
{
	double meanSquaredError = 0;
	for(User u : *users)
	{
		map<int, int> trueRatings = u.getTestRatings();
		map<int, int> guessRatings = u.getHypotheticalRates();
		for(auto &rating : guessRatings)
		{
			meanSquaredError += pow((guessRatings[rating.first] - trueRatings[rating.first]), 2);
		}
	}

	meanSquaredError = sqrt((1 / (0.2*NB_RATINGS)) * meanSquaredError);

	cout << "L'erreur moyenne est de " << meanSquaredError << endl;
}
