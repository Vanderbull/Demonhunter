#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Highscore
{
public:
	string name;
	int Score;
};

class FillHighScore
{
public:
	FillHighScore();
	void sort( string, unsigned long int );
	void Save();
	void copy( Highscore cop[], int Count ); //kopierar till det som visas i highscore
	Highscore list[ 6 ];
};
