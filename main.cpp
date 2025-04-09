#include "std_lib_facilities.h"

const int easyModeSwap = 2;
const int easyModeGuess = 3;
const int hardModeSwap = 4;
const int hardModeGuess = 5;

void wordInitializer(void);
void assorter(string toAdd);
void wordAdder(void);
int selector(void);
void listManager(void);
string jumbler(string quest, int swapNumber);
void initialMenu(void);
void guesser(void);
void doGame(string correct, int guessNumber, int swapNumber);


vector<string> wordList = {"add", "bang", "base", "chain", "charter", "coast", "coincide", "command", "commerce", "corner", "craftsman", "deficiency", "deliver", "depend", "desk", "dimension", "dirty", "disaster", "drift", "duck", "economic", "feign", "gown", "gregarious", "highway", "holiday", "huge", "midnight", "mutual", "professional", "progress", "recommend", "relevance", "road", "scatter", "score", "scrap", "shift", "sigh", "spell", "spit", "table", "umbrella", "unlike", "van", "veil", "venture", "visit", "vote", "wriggle"};

vector<string> shortWord; // 2-5 letters
vector<string> longWord; // from 5 letters

int main(void) {
	wordInitializer();
	initialMenu();
	return 0;
}

void wordInitializer(void) {
	sort(wordList);
	for (string word : wordList) 
		assorter(word);
	return;
}

void assorter(string toAdd) {
	if (toAdd.size() <= 5) {
		shortWord.push_back(toAdd);
	}
	if (toAdd.size() >= 5) {
		longWord.push_back(toAdd);
	}
	return;
}

int selector(void) {
	int choice = 0;
	while (choice != 1 && choice != 2 && choice != 3) {
		cout << "Choose an option (1-3) : ";
		cin >> choice;
		// cin에 다른 자료형 입력시 버퍼 비우기
		while (!cin) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	return choice;
}

void initialMenu(void) {
	int choice;
	while (true) {
		choice = 0;
		cout << "\n<<< WORD JUMBLE >>>" << endl;
		cout << "1. Manage List" << endl;
		cout << "2. Solve Puzzle" << endl;
		cout << "3. Exit" << endl << endl;
		choice = selector();
		if (choice == 3) {
			cout << "\nGood bye!!!" << endl;
			exit(0);
		}
		switch (choice) {
		case 1:
			listManager();
			break;
		case 2:
			guesser();
			break;
		default:
			break;
		}
	}
	return;
}

void listManager(void) {
	int choice;
	while (true) {
		choice = 0;
		cout << "\n[ MANAGE LIST ]" << endl;
		cout << "1. Print Words" << endl;
		cout << "2. Add Word" << endl;
		cout << "3. Return" << endl << endl;
		choice = selector();
		if (choice == 3)
			return;
		switch (choice) {
		case 1:
			cout << "\nA total of " << wordList.size() << " words are avaliable:" << endl;
			for (string s : wordList)
				cout << s << endl;
			break;
		case 2:
			wordAdder();
			break;
		default:
			break;
		}
	}
	return;
}

void wordAdder(void) {
	string toAdd;
	cout << "\nInput a new word: ";
	cin >> toAdd;
	if (find(wordList.begin(), wordList.end(), toAdd) != wordList.end()) {
		cout << "The word \'" << toAdd << "\' already exists in the list." << endl;
		return;
	}
	else {
		wordList.push_back(toAdd);
		sort(wordList);
		assorter(toAdd);
		cout << "The word \'" << toAdd << "\' has been succesfully inserted in the list." << endl;
		return;
	}
	return;
}

void guesser(void) {
	int choice;
	while (true) {
		choice = 0;
		cout << "\n[ SOLVE PUZZLE ]" << endl;
		cout << "1. Easy Mode" << endl;
		cout << "2. Hard Mode" << endl;
		cout << "3. Return" << endl << endl;
		choice = selector();
		if (choice == 3)
			return;
		switch (choice) {
		case 1:
			doGame(shortWord[randint(shortWord.size() - 1)], easyModeGuess, easyModeSwap);
			break;
		case 2:
			doGame(longWord[randint(longWord.size() - 1)], hardModeGuess, hardModeSwap);
			break;
		default:
			break;
		}
	}
	return;
}

void doGame(string correct, int guessNumber, int swapNumber) {
	string jumbled = jumbler(correct, swapNumber);
	string answer;
	bool right;
	cout << "\nI give you a jumbled word \'" << jumbled << "\' ." << endl;
	for (int i = 0; i < guessNumber; i++) {
		cout << '[' << i+1 << '/' << guessNumber << ']' << " Guess the original word: ";
		cin >> answer;
		right = (answer.size() != correct.size()) ? false : true;
		cout << ">> [";
		for (int j = 0; j < correct.size(); j++) {
			if (answer.size() <= j) {
				cout << '-';
				right = false;
				continue;
			}
			else if (answer[j] == correct[j])
				cout << answer[j];
			else {
				cout << '-';
				right = false;
			}
		}
		cout << "]\n" << endl;
		if (right) {
			cout << "Congratulation! You got the answer right!" << endl;
			return;
		}
	}
	cout << "Oops! you failed to solve the puzzle..." << endl;
	cout << "The correct answer is \'" << correct << "\'." << endl;
	return;
}

string jumbler(string quest, int swapNumber) {
	string jumbled = quest;
	for (int i = 0; i < swapNumber; i++) {
		int a = randint(quest.size() - 1);
		int b = a + randint(1, quest.size() - 1);
		b %= quest.size();
		swap(jumbled[a], jumbled[b]);
	}
	return jumbled;
}