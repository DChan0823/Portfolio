#include "Monogram.h"

Monogram::Monogram()
{
	cout << "Welcome to the Nonogram Game!" << endl;
	cout << "Fill or unfill the board with your coordinate to match the hidden pattern." << endl;
	cout << "Input numbers 0-3 for row and 0-3 for column to indicate position on board." << endl;
}


Monogram::~Monogram()
{
}

void Monogram::startGame() {
	string dim, dimEntire;

	ifstream fin;

	fin.open("monogram.txt");
	
	if (fin.fail())
		cout << "File Error!" << endl;
	else {
		vector<char> pattern;
		vector<char> userPattern;
		int startX, startY;
		//fin >> dim;
		getline(fin, dim);

		//cout << dim << endl;
		//vector<vector <char>> patternTemp;

		for (int i = 0; i < stoi(dim); i++) {
			string line;
			
			getline(fin, line);

			//cout << line << endl;

			vector<string> tokens = tokenize(line, ' ');

			//cout << tokens.size() << endl;

			for (int j = 0; j < tokens.size(); j++) {
				pattern.push_back(tokens[j].at(0));
			}
		}

		getline(fin, dimEntire);

		//cout << stoi(dimEntire) << endl;

		for (int i = 0; i < stoi(dimEntire); i++) {
			string line;

			getline(fin, line);

			vector<string> tokens = tokenize(line, ' ');

			/*for (int i = 0; i < tokens.size(); i++) {
				cout << tokens[i] << " ";
			}
			//cout << tokens.size() << endl;*/
			for (int j = 0; j < tokens.size(); j++) {
				userPattern.push_back(tokens[j].at(0));
			}
		}

		string line;
		getline(fin, line);
		startX = stoi(line);
		getline(fin, line);
		startY = stoi(line);
		//cout << stoi(dim) << startX << startY << endl;

		Board board(pattern, userPattern, stoi(dim));
		board.printUser();
		cout << endl;
		string userInput;
		int k = 0; //counting variable
		string token; //token variable when separating string
		string arr2[2];
		
		while (1) {
			cout << "What would you like to fill? ie. 1,2 or Quit or Compare" << endl;
			cin >> userInput;
			if (userInput == "Compare" || userInput == "compare") {
				if (board.missCount() != 0) {
					cout << "Incorrect Count: " << board.missCount() << endl;
				}
				else {
					cout << "CONGRATULATIONS! YOU SOLVED THE MONOGRAM!" << endl;
				}
			}
			else if (userInput == "Quit" || userInput == "quit") {
				break;
			}
			else {
				replace(userInput.begin(), userInput.end(), ',', ' ');

				istringstream ss(userInput);

				while (getline(ss, token, ' ')) {

					arr2[k] = token;
					k++;
				}
				k = 0;
				
				board.fillElement(stoi(arr2[0]) + startX - 1, stoi(arr2[1]) + startY - 1);
				board.printUser();
			}
		}
	}
}

vector<string> Monogram::tokenize(string str, char c = ' ')
{
	vector<string> result;
	const char *strTemp;

	strTemp = str.c_str();

	do
	{
		const char *begin = strTemp;

		while (*strTemp != c && *strTemp)
			strTemp++;

		result.push_back(string(begin, strTemp));
	} while (0 != *strTemp++);

	/*for (int i = 0; i < result.size(); i++) {
		cout << result[i] << endl;
	}*/

	return result;
}

	
	/*int pattern[100] = { 0,1,1,0,
		1,0,0,1,
		1,1,1,1,
		1,0,0,1 };

	//whole board; Z represents the pattern needed from the pattern array
	char entire[300] = { ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', '1', ' ', ' ', ' ',
		' ', ' ', ' ', ' ', '3', ' ', '1', ' ', '1', ' ', '3', ' ',
		' ', ' ', ' ', '-', '-', '-', '-', '-', '-', '-', '-', '-',
		' ', ' ', '2', '|', 'Z', '|', 'Z', '|', 'Z', '|', 'Z', '|',
		' ', ' ', ' ', '-', '-', '-', '-', '-', '-', '-', '-', '-',
		'1', ' ', '1', '|', 'Z', '|', 'Z', '|', 'Z', '|', 'Z', '|',
		' ', ' ', ' ', '-', '-', '-', '-', '-', '-', '-', '-', '-',
		' ', ' ', '4', '|', 'Z', '|', 'Z', '|', 'Z', '|', 'Z', '|',
		' ', ' ', ' ', '-', '-', '-', '-', '-', '-', '-', '-', '-',
		'1', ' ', '1', '|', 'Z', '|', 'Z', '|', 'Z', '|', 'Z', '|',
		' ', ' ', ' ', '-', '-', '-', '-', '-', '-', '-', '-', '-' };

	//int response = 0;

	Board userBoard;
	Board board(pattern, 4);
	userBoard.printEntire(entire);
	cout << endl;
	string userInput;
	int k = 0; //counting variable
	string token; //token variable when separating string
	string arr2[2];

	while (1) {
		cout << "What would you like to fill? ie. 1,2 or Quit or Compare" << endl;
		getline(cin, userInput);
		if (userInput == "Compare" || userInput == "compare") {
			if (userBoard.missCount(board) == 1) {
				cout << "Missing: 1 spot" << endl;
			}
			else if (userBoard.missCount(board) == 0) {
				cout << "Missing: 0 spots" << endl;
			}
			else {
				cout << "Missing: " << userBoard.missCount(board) << " spots" << endl;
			}
		}
		else {
			if (userInput == "Quit" || userInput == "quit")
				break;
			//replaces the "-" character to become a " "
			replace(userInput.begin(), userInput.end(), ',', ' ');


			istringstream ss(userInput);


			while (getline(ss, token, ' ')) {

				arr2[k] = token;
				k++;
			}



			k = 0;
			userBoard.fillSpot(stoi(arr2[0]), stoi(arr2[1]));
			userBoard.printEntire(entire);

		}
	}

	if (userBoard.compare(board))
		cout << "Congratulations! It is correct!" << endl;
	else {
		cout << "Missing: " << userBoard.missCount(board) << endl;
	}
	//shows user the board game pattern
	cout << "Entire Board Game Pattern" << endl;
	board.printEntire(entire);
	system("pause");
	return 0;

	*/