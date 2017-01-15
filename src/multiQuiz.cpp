//============================================================================
// Name        : multiQuiz.cpp
// Author      : Ethan Elliott
// Version     :
// Copyright   : (c) Ethan Elliott 2015
// Description :
//============================================================================
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <sstream>

using namespace std;

//Function Predef
int RandomNumber(int seed, int max, int min);
void Cls();
bool MakeChoice(string question);
string Round(const double input, const int decDigits);
void PrintHeader(string title);
bool AskQuestion();


class Timer
{
	//Timer class
	//Allows for timing of events, without stopping the program
	//Uses ETime differences to calculate elapsed time to thousandth of a second.
private:
	bool Running;		//Clock is running
	double start;		//Start Time
	double stopTime;	//Stop Time
	double accumulatedTime;
	double ETime(){return (clock() * 0.001);}
public:
	Timer(void){Running = false;start = 0;stopTime = 0;accumulatedTime = 0;}
	void Start(){if (!Running){start = ETime();Running = true;}}
	void Stop(){double temp = Get();if(Running){accumulatedTime = temp;Running = false;}}
	void Reset(){start = ETime();accumulatedTime = 0;}
	double Get(){double result;double currentTime = ETime();if (Running){result = ((currentTime - start) + accumulatedTime);}else{result = accumulatedTime;}return result;}
	bool isRunning(){return Running;}
};

int main(void)
{
	Timer * t;
	t = new Timer();
	t->Reset();

	bool isDone = false;
	while (!isDone)
	{
		Cls();
		int numOfQ = 0;
		int correct = 0;
		float averageTime = 0.0;
		bool isDone = false;

		while (!isDone)
		{
			Cls();
			PrintHeader("Multiplication Tables");
			t->Reset();
			t->Start();
			if (AskQuestion())
			{
				correct++;
			}
			t->Stop();

			numOfQ++;

			if (averageTime == 0)
			{
				averageTime = t->Get();
			}
			else
			{
				averageTime = (averageTime + t->Get()) / 2;
			}

			cout << "It took you: " << t->Get() << " seconds\n";
			cout << "Average: " << averageTime << " seconds\n";
			cout << "Current Score: " << correct << "/" << numOfQ << " (" << Round(((correct / (float)numOfQ)*100),0) << "%)\n";
			isDone = !MakeChoice("Anotha one?");
		}


	}
	return 0;
}

int RandomNumber(int seed, int max, int min)
{
	time_t now = time(0);
	tm * ltm = localtime(&now);
	Sleep(2);
	srand((rand() % 100) * ltm->tm_sec * (seed + (rand() % 1000 + 1) * (ltm->tm_sec + rand())));
	return ((rand() % max) + min);
}

void Cls()
{
	system("cls");
}

bool MakeChoice(string question)
{
	bool isDone = false;
	bool r = false;
	cout << "\n" << question << " [y / n]\n";
	while (!isDone)
	{
		switch (getch())
		{
		case 'y':
			isDone = true;
			r = true;
			break;
		case 'n':
			isDone = true;
			r = false;
			break;
		default:
			isDone = false;
			break;
		}
	}
	return r;
}

string Round(const double input, const int decDigits)
{
    stringstream out;
    out << fixed;
    out.precision(decDigits);
    out << input;
    return out.str();
}

void PrintHeader(string title)
{
	int width = title.length() + 35;
	cout << "\t\t" << title << "\t\t" << endl;
	cout << setfill ('=') << setw (width) << "=" << endl;
}

bool AskQuestion()
{
	int x = RandomNumber(RandomNumber(0,100,0), 12, 0);
	int y = RandomNumber(RandomNumber(0,100,0), 12, 0);
	int product = x * y;
	int userResponse = 0;
	cout << "What is " << x << " x " << y << "?\n_";
	cin >> userResponse;
	cout << endl;
	if (userResponse == product)
	{
		cout << "That's Correct!\n";
		return true;

	}
	else
	{
		cout << "That's incorrect!\n The correct answer is " << product << "\n";
		return false;
	}
}

