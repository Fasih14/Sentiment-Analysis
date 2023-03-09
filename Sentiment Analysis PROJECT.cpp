#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string.h>
#include<windows.h>
#include<iomanip>
using namespace std;
struct N_Base {
	char word[50]{};
	float pos_frequency = 0;
	float neg_frequency = 0;
	float pos_probability{};
	float neg_probability{};
};
void   display(N_Base arr[], int count)
{
	for (int index = 0; index < count; index++)                                                      //Displaying Unique Words for Frequencies.
		cout << arr[index].word << "  ";
	cout << endl;
}
void   display1(N_Base arr[], int count)
{
	for (int index = 0; index < count; index++)                                                   // Displaying Unique Words for Probabilities.
		cout << arr[index].word << "   ";
	cout << endl;
}
void display_Frequency(N_Base arr[], int count)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "-ve Freq:: ";
	for (int index = 0; index < count; index++)                                                 //Displaying Frequencies.
		cout << arr[index].neg_frequency << "      ";
	cout << endl;
	SetConsoleTextAttribute(h, 10);
	cout << "+ve Freq:: ";
	for (int index = 0; index < count; index++)
		cout << arr[index].pos_frequency << "      ";
	cout << endl;

}
void display_Probability(N_Base arr[], int count)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "-ve Prob:: ";
	for (int index = 0; index < count; index++)
		cout << fixed << setprecision(3) << arr[index].neg_probability << "   ";
	cout << endl;                                                                                       //Displaying Probability.
	SetConsoleTextAttribute(h, 10);
	cout << "+ve Prob:: ";
	for (int index = 0; index < count; index++)
		cout << fixed << setprecision(3) << arr[index].pos_probability << "   ";
	cout << endl;
}
void comments(char file[][40], char Label[5])
{
	int index = 0;
	ifstream myFile;
	myFile.open("myFile.txt");                                                                              // Reading from files
	//myFile.open("Data.txt");
	//myFile.open("testFile.txt");
	if (myFile.is_open())
	{
		while (!myFile.eof()) {
			myFile.getline(file[index], 40);
			//cout<<file[index]<<endl;
			index++;
		}
	}
	Label[0] = 'N';
	Label[1] = 'N';
	Label[2] = 'N';
	Label[3] = 'P';
	Label[4] = 'P';
}
void probabilty(N_Base arr[], int nf_Sum, int pf_Sum, int Unique_No)
{
	for (int index = 0; index < Unique_No; index++)
	{
		arr[index].pos_probability = (arr[index].pos_frequency + 1) / (pf_Sum + Unique_No);                   // Calculating Probability.
		arr[index].neg_probability = (arr[index].neg_frequency + 1) / (nf_Sum + Unique_No);

	}
}
void frequency(N_Base Unique[], char Label, int index, int& nf_Sum, int& pf_Sum)
{

	if (Label == 'N') {
		Unique[index].neg_frequency++;                                                                        //Calculating Frequencies.
		nf_Sum++;
	}
	else if (Label == 'P') {
		Unique[index].pos_frequency++;
		pf_Sum++;
	}

}
void new_Unique(N_Base Unique[], char toke[], int& counter, char Label, int& nf_Sum, int& pf_Sum)
{
	int index = 0;
	int d;                                                                                                   //Finding Unique Words.
	bool Append = true;
	for (index = 0; index < counter; index++)
	{
		d = strcmp(Unique[index].word, toke);
		if (d == 0)
		{
			frequency(Unique, Label, index, nf_Sum, pf_Sum);         //Frequency.
			Append = false;
		}
	}
	if (Append == true)
	{
		strcpy(Unique[index].word, toke);
		frequency(Unique, Label, index, nf_Sum, pf_Sum);       //Frequency.
		counter++;
	}
}
void N_B(N_Base arr[], char file[], char label, char* token, int& count, int& nf_Sum, int& pf_Sum)
{
	char del[] = " ";
	char* tok = strtok(file, del);
	while (tok) {
		strcpy(token, tok);
		new_Unique(arr, token, count, label, nf_Sum, pf_Sum);          // Created Struct.
		tok = strtok(NULL, del);
	}
}
void check(N_Base arr[], int counter)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 11);
	float pos_Prob = 1;                                                                 //Enter New Sentence to check Sense.
	float neg_Prob = 1;
	char new_Sent[120];
	cout << "Type Sentence::" << endl;
	cin.getline(new_Sent, 120);
	if (new_Sent[0] != '\0')
	{
		char del[] = " ";
		int d;
		char* tok = strtok(new_Sent, del);
		while (tok) {

			for (int index = 0; index < counter; index++)
			{
				d = strcmp(arr[index].word, tok);
				if (d == 0)
				{
					pos_Prob = pos_Prob * arr[index].pos_probability;
					neg_Prob = neg_Prob * arr[index].neg_probability;
					break;
				}
			}
			tok = strtok(NULL, del);
		}
		if (pos_Prob > neg_Prob)
		{
			SetConsoleTextAttribute(h, 10);
			cout << "Sentence is Postive.";
		}
		else
		{
			SetConsoleTextAttribute(h, 12);
			cout << "Sentence is Negative.";
		}
	}
	else
		cout << "Enter the text!";
}
int main()
{
	N_Base Arr[50];
	char File[5][40];
	char label[5];
	comments(File, label);
	char token[50];

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);                                              //All Declarations
	int count = 0;
	int nf_Sum = 0;
	int pf_Sum = 0;
	for (int index = 0; index < 5; index++)
	{
		N_B(Arr, File[index], label[index], token, count, nf_Sum, pf_Sum);          // making Struct Naive Baise 
	}

	probabilty(Arr, nf_Sum, pf_Sum, count);                                         //getting Output on Console from here till onward.
	SetConsoleTextAttribute(h, 14);
	cout << "Uni_Words::";
	display(Arr, count);
	SetConsoleTextAttribute(h, 12);
	display_Frequency(Arr, count);
	SetConsoleTextAttribute(h, 14);
	cout << "Total Unique_Words:" << count << endl;
	cout << "Total Negative_Words:" << nf_Sum << endl;
	cout << "Total Positive_Words:" << pf_Sum << endl;
	cout << "Uni_Words::";

	display1(Arr, count);
	SetConsoleTextAttribute(h, 12);
	display_Probability(Arr, count);
	check(Arr, count);

}