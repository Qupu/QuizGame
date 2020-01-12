
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <sstream>

//number of questons asked in the 'play'
#define HOW_MANY_QUESTONS 5 //carefull to not have this higher than the number of questons in the file or the program will crash...

using namespace std;

//class used to keep track of the queston and their answers and which one is correct
class Queston 
{
public:

	//constructor so its easier to read the data from the file
	Queston(string s1, string s2, string s3, string s4, string s5, string s6) 
	{
		queston = s1;
		answers.push_back(s2);
		answers.push_back(s3);
		answers.push_back(s4);
		answers.push_back(s5);
		correct = s6;
	}

	//used to scramble the anwers so they are in a different order every time you play
	void scrambleq()
	{
		random_shuffle(answers.begin(), answers.end());
	}

	//getters for the private values
	string getCorrect() { return(correct); }
	string getQueston() { return(queston); }
	vector<string> getAnswers() { return (answers); }

private:
	string queston; //holds the queston
	vector<string> answers; //vector holding the answers
	string correct; //holds the correct answer
};
	
//used to list all the questons, takes the vector holding all the "loaded" questons as a parameter
void viewq(vector<Queston> questons) 
{
	for (unsigned int i = 0; i < questons.size(); ++i)
	{
		cout << i+1 << ". " << questons[i].getQueston() << endl;
	}
}

//used to add a queston to the 'questons.txt' and to the vector holding the questons inside the programm
Queston addq()
{

	string input;
	string str =""; //the string that is added to the file at the end of function
	vector<string> tokens; //used to hold the strings
	
	cin.ignore(); //needed so that getline works if there is \n in stream before this

	//the queston to be added
	cout << "Give the queston:" << endl;
	cout << ">> ";
	getline(cin, input);
	str += input;
	str += ";";
	tokens.push_back(input);
	cout << endl;

	//the first possible answer
	cout << "Give the answer A:" << endl;
	cout << ">> ";
	getline(cin, input);
	str += input;
	str += ";";
	tokens.push_back(input);
	cout << endl;

	//the second possible answer
	cout << "Give the answer B:" << endl;
	cout << ">> ";
	getline(cin, input);
	str += input;
	str += ";";
	tokens.push_back(input);
	cout << endl;

	//the third possible answer
	cout << "Give the answer C:" << endl;
	cout << ">> ";
	getline(cin, input);
	str += input;
	str += ";";
	tokens.push_back(input);
	cout << endl;

	//the fourth possible answer
	cout << "Give the answer D:" << endl;
	cout << ">> ";
	getline(cin, input);
	str += input;
	str += ";";
	tokens.push_back(input);
	cout << endl;

	//shows the queston and all the choices
	cout << tokens[0] << endl;
	cout << "A) " << tokens[1] << endl;
	cout << "B) " << tokens[2] << endl;
	cout << "C) " << tokens[3] << endl;
	cout << "D) " << tokens[4] << endl;
	cout << endl;
	cout << "Give the correct answer: (A,B,C,D)" << endl;

	string temp;

	//depending on your answer (a,b,c or d) adds that as the correct answer
	while (1) //will ask until you enter a,b,c or d
	{
		cout << ">> ";
		getline(cin, input);

		if (input == "A" || input == "B" || input == "C" || input == "D" || input == "a" || input == "b" || input == "c" || input == "d") //accepts capital and noncapitals as answers
		{
			if (input == "A" || input == "a") temp = tokens[1];
			else if (input == "B" || input == "b") temp = tokens[2];
			else if (input == "C" || input == "c") temp = tokens[3];
			else if (input == "D" || input == "d") temp = tokens[4];

			break;
		}
		else cout << "You imputed invalid answer, try again." << endl;
	}

	str += temp;
	tokens.push_back(temp);
	str += "\n";

	std::ofstream out;
	out.open("questons.txt", ios::app);
	out << str;
	out.close();
	return Queston(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], tokens[5]); //returns as a constructed Queston
}

//reads the 'questons.txt' file and returns a vector to be used in the programm (format is queston;answerA;answerB;answerC;answerD;correctanswer)
vector<Queston> readq()
{

	vector<Queston> questons;
	string str; //used to hold the line that was read
	string delimiter = ";";

	fstream qs("questons.txt");

	while (getline(qs, str)) { //reads the file line by line

		if (str == "") continue; //skips the lines that are empty

		stringstream ss(str);
		vector<string> tokens; //holds the tokenized line
		string temp_str;
		while (getline(ss, temp_str, ';')) {
			tokens.push_back(temp_str);
		}

		questons.push_back(Queston(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], tokens[5]));
	}

	qs.close();
	return questons; //returns the vector that holds all the questons
}

//functon that "plays" the game, takes the vector holding the questons as a parameter
void play(vector<Queston> questons)
{
	int score = 0; //used to keep score how many you got correct
	string input;

	random_shuffle(questons.begin(), questons.end()); //shuffles the questons vector so the order is random every time you play

	cout << endl;
	cout << "In this game there is " << HOW_MANY_QUESTONS << " rounds." << endl;
	cout << "Do your best to answer as many correcly as possible." << endl << endl;

	for (int i = 0;i < HOW_MANY_QUESTONS; ++i) //how many round are played depending on 'HOW_MANY_QUESTONS'
	{
		questons[i].scrambleq(); //scrambles the answers so they are in a random order
		cout << questons[i].getQueston() << endl; //queston
		cout << "A) " << questons[i].getAnswers()[0] << endl; //answer A
		cout << "B) " << questons[i].getAnswers()[1] << endl; //answer B
		cout << "C) " << questons[i].getAnswers()[2] << endl; //answer C
		cout << "D) " << questons[i].getAnswers()[3] << endl; //answer D

		//asks you give the anwer to the queston
		while (1)
		{
			cout << endl << "Give the correct answer: (A,B,C,D)" << endl;
			cout << ">> ";
			cin >> input;

			//depending if you got it right you get a point to score
			if (input == "A" || input == "B" || input == "C" || input == "D" || input == "a" || input == "b" || input == "c" || input == "d")
			{
				if (input == "A" || input == "a") 
				{
					if (questons[i].getAnswers()[0] == questons[i].getCorrect())
					{
						cout << "CORRECT!" << endl << endl;
						++score;
					}
					else
					{
						cout << "INCORRECT!" << endl << endl;
					}
					break;
				}
				else if (input == "B" || input == "b") 
				{
					if (questons[i].getAnswers()[1] == questons[i].getCorrect())
					{
						cout << "CORRECT!" << endl << endl;
						++score;
					}
					else
					{
						cout << "INCORRECT!" << endl << endl;
					}
					break;
				}
				else if (input == "C" || input == "c") {
					if (questons[i].getAnswers()[2] == questons[i].getCorrect())
					{

						cout << "CORRECT!" << endl << endl;
						++score;
					}
					else
					{
						cout << "INCORRECT!" << endl << endl;
					}
					break;
				}
				else if (input == "D" || input == "d") {
					if (questons[i].getAnswers()[3] == questons[i].getCorrect())
					{

						cout << "CORRECT!" << endl << endl;
						++score;
					}
					else
					{
						cout << "INCORRECT!" << endl << endl;
					}
					break;
				}
			}
			else cout << "You imputed invalid answer, try again." << endl;
		}
	}

	cout << "You got " << score << "/" << HOW_MANY_QUESTONS << " correct." << endl;

	//you get a response depending on if you got more than half correct
	if ((float)score / HOW_MANY_QUESTONS > 0.5)
	{
		cout << "Good job. :)" << endl << endl;
	}
	else cout << "Better luck next time. :(" << endl << endl;

}

//used to iniatilize the game by deleting all the questons and then making you add the minimum needed to play the game
vector<Queston> initquestons() 
{
	vector<Queston> newquestons; //holds the new questons after the reset

	ofstream ofs;
	ofs.open("questons.txt", ofstream::out | ofstream::trunc); //basically deletes all the data in a file
	ofs.close();

	cout << endl << "Now we need you to add the minimum number of questons needed to play. (" << HOW_MANY_QUESTONS << " questons)" << endl << endl;

	for (int i = 0; i < HOW_MANY_QUESTONS; ++i) //adds the amount of questons needed to play 
	{
		cout << "Queston no." << i + 1 << endl;
		newquestons.push_back(addq());
		cout << endl;
	}

	return newquestons; //returns the new set of questons to the programm
}

//main used to play the game and view or add questons, should be pretty self explanatory what everything does here
int main()
{

	vector<Queston> questons = readq(); //loads the questons from the file
	
	string input = "";
	string temp;

	cout << endl << endl;
	cout << "Welcome to the quiz game ;)" << endl;
	cout << "Type:" << endl;
	cout << "'play' - to get " << HOW_MANY_QUESTONS << " random questons to answer." << endl;
	cout << "'add' - to add new queston to the pool." << endl;
	cout << "'view' - to view all the questons." << endl;
	cout << "'quit' - to stop playing." << endl;
	cout << "'initialize' - to DELETE all questons and reset them." << endl;

	while(1)
	{
		cout << endl << ">> ";
		cin >> input;

		if (input == "play") 
		{
			play(questons);
		}
		else if (input == "add")
		{
			questons.push_back(addq());
		}
		else if (input == "view")
		{
			viewq(questons);
		}
		else if (input == "initialize")
		{
			while (1)
			{
				cout << "Are you absolutely sure? ('YES' or 'NO')" << endl;
				cout << "This is inreversable and all your hardmade questons will be DELETED." << endl << ">> ";
				cin >> temp;

				if (temp == "YES")
				{
					questons = initquestons();
					break;
				}
				else if (temp == "NO") 
				{
					cout << "Ok good." << endl;
					break;
				}
			}

		}
		else if (input == "quit") 
		{ 
			cout << "Thanks for playing!" << endl;
			break; 
		}
		else
		{
			cout << "Invalid input, try again." << endl;
			continue;
		}
		
		cout << endl;
		cout << "Type:" << endl;
		cout << "'play' - to get " << HOW_MANY_QUESTONS << " random questons to answer." << endl;
		cout << "'add' - to add new queston to the pool." << endl;
		cout << "'view' - to view all the questons." << endl;
		cout << "'quit' - to stop playing." << endl;
		cout << "'initialize' - to DELETE all questons." << endl;
	}
}