#include "Highscore.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// reads the list and sorts it
FillHighScore::FillHighScore()
{	
	ifstream infile( "Highscore.txt" );

	for( int i = 0; i < 6 && infile && infile.peek() != EOF; i++)
	{
		string temp;		
							
		infile >> temp;
		infile >> list[ i ].name;
		infile >> temp;
		infile >> list[ i ].Score;	
		
	}

	for( int i = 0; i < 6; i++ )
	{
		for( int j = 0; j < 6; j++ )
		{
			if( list[ i ].Score > list[ j ].Score )
			{
				string temp;
				temp = list[ i ].name;
				list[ i ].name = list[ j ].name;
				list[ j ].name = temp;
				swap( list[ i ].Score, list[ j ].Score );
			}
		}
	}
}

void FillHighScore::Save()
{
	ofstream ofile("Highscore.txt");	
										
	for( int i = 0; i < 6; i++ )
	{
		ofile << "Name: " << list[ i ].name << endl;
		ofile << "Score: " << list[ i ].Score << endl;
	} 
}

// copy the whole list
void FillHighScore::copy( Highscore cop[], int Count )
{	
	ifstream infile( "Highscore.txt" );
	for( int i = 0; i < Count; i++ )
	{
		string temp;		
							
		infile >> temp;
		getline(infile, cop[ i ].name);
		infile >> temp;
		infile >> cop[ i ].Score;
	}
}

void FillHighScore::sort( string a, unsigned long int x )
{
	if( x > list[ 5 ].Score )// if score is bigger
	{
		list[ 5 ].Score = x;
		list[ 5 ].name = a;	// the last one in the list gets value
	}

	for( int i = 0; i < 5; i++ )
	{
		if(list[ i ].Score < list[ i+1 ].Score)
		{
			string temp = list[ i+1 ].name;
			list[ i+1 ].name = list[ i ].name;	
			list[ i ].name = temp;

			swap( list[ i+1 ].Score, list[ i ].Score );
		}

	}	
}
