#include <iostream>
#include "User.h"
#include "Constantes.h"
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

void readFiles(int, vector<User>*);

int main(int argc, char *argv[])
{
	cout << "Hello wordl" <<endl;

	vector<User> users;
	readFiles(1, &users);

	return 0;
}

void readFiles(int number, vector<User>* users)
{
	ifstream base;
	ostringstream oss;
	oss << INPUT_DEB << number << INPUT_BASE_END;
	base.open(oss.str().c_str());

	if(!base)
	{
		cerr << "Fail to open base file" << endl;
		return;
	}

	int userId, movieId, rating, timestamp, lastUserId = 0;
	User* currentUser = nullptr;
	while(base >> userId >> movieId >> rating >> timestamp)
	{
		if(userId != lastUserId)
		{
			if(currentUser != nullptr)
			{
				users->push_back(*currentUser);
			}
			currentUser = new User(userId);
			lastUserId = userId;
		}
		currentUser->addRatingFor(movieId, rating);
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
}
