// redblacktree.cpp : Diese Datei enthaelt die Funktion "main". Hier beginnt und endet die Ausfuehrung des Programms.
//
#pragma warning(disable : 4244)
#pragma warning(disable : 4101)

#include <iostream>
#include <ctime>
#include <string>
#include "redblacktree.h"

using namespace std;


char input;
int inputnumber;
int anzahl;
int number;
int maxnumber;
string news = "";
RedBlackTree<int> tree;
void pause();
void clear();
void deleteTestTree();
void deleteTree();


/*
 * This function inserts a given number of random numbers (specified by the parameter "cfrn") into a tree data structure.
 * It also keeps track of the maximum generated number by comparing it to the previously generated random numbers.
 * It uses the rand() function to generate a random number between 1 and the specified number of random numbers.
 */
void insertRandomNumber(int cfrn) //cfrn: countforrandomnumber
{
	for (int i = 0; i < cfrn; i++)
	{
		number = 1 + rand() + 1;
		if (number > maxnumber)
		{
			maxnumber = number;
		}
		tree.insert(number);
	}
}

/*
 * In this function the function insertRandomNumber() is called, which inserts random numbers into the tree. 
 * The time of the insertion is measured and issued.
 * Then a number is searched in the tree. The time is measured here as well.
 * Finally the tree is deleted. The time is also measured. 
 * The if-query is there to increase the distance between the numbers
 */
void test()
{
	clear();
	clock_t start;
	clock_t end;
	double elapsed_time;
	int counter = 10000;

	while (counter <= (1e7))
	{
		cout << "Das einfuegen von " << counter << " Zahlen hat ";
		start = clock();
		insertRandomNumber(counter);
		end = clock();
		elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000;
		cout << elapsed_time << " ms gedauert." << endl;

		cout << "Das Suchen von der Zahl " << (0.75 * counter) << " hat ";
		start = clock();
		tree.search(0.75 * counter);
		end = clock();
		elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000;
		cout << elapsed_time << " ms gedauert." << endl;

		if (counter < 10000)
		{
			counter += 1000;
		}
		else if (counter >= 10000 && counter < 100000)
		{
			counter += 10000;
		}
		else if (counter >= 100000 && counter < 1000000)
		{
			counter += 100000;
		}
		else
		{
			counter += 1000000;
		}
		cout << endl;
	}
	pause();
}
/*
 * This function clears the console window.
 * It uses the system() function to call the command line "cls" (on Windows systems) or "clear" (on Linux or macOS systems)
 * The #ifdef _WIN32 preprocessor directive is used to check if the code is running on a Windows system and if so, it calls the "cls"
 * command,
 * otherwise it calls the "clear" command, ensuring the correct command is called for the system it is running on.
 */
void clear()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

/*
 * This function creates a pause in the program execution.
 * On Windows systems, the function uses the system() function to call the command line command "pause",
 * which causes the console window to wait for User input before continuing with the next instruction.
 * On other systems, the function uses a while loop that prompts the User to press a specific key (in this case, the number 9)
 * and press enter before continuing with the next instruction.
 * The #ifdef _WIN32 preprocessor directive is used to check if the code is running on a Windows system and if so,
 * it calls the "pause" command, otherwise it uses the while loop to wait for user input.
 */
void pause()
{

	//aktuelle L??sung 
#ifdef _WIN32
	system("pause");
#else
	char a;
	while (a != '9')
	{
		cout << "Taste 9 und Enter Dr??cken . . ." << endl;
		cin >> a;
	}
#endif
}
/*
 * This function is about the same as insertRandomNumber() but it asks how large the smallest or the largest number should be. 
 * Afterwards the old tree, as well as the new bum, is issued. 
 * The time needed for the insertion is measured.
 */
void insertRangeRandomNumber(int cfrn)
{
	int min;
	int max;
	clear();
	if (news != "")
	{
		cout << news << endl;
	}
	cout << "Was soll die kleinste Zahl sein" << endl;
	cin >> min;
	cout << "Was soll die groesste Zahl sein" << endl;
	cin >> max;
	if (min > max)
	{
		news = "Kleinere Zahl ist groesser als die groessere Zahl";
		insertRangeRandomNumber(cfrn);
		news = "";
		return;
	}
	if (max > maxnumber)
	{
		maxnumber = max;
	}
	cout << "Alter Baum:" << endl;
	tree.print();
	clock_t start = clock();
	for (int i = 0; i < cfrn;)
	{
		number = 1 + rand() + 1;
		if (number >= min && number <= max)
		{
			tree.insert(number);
			i++;
		}
	}
	clock_t end = clock();
	cout << "Neuer Baum" << endl;
	tree.print();
	double elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000;
	std::cout << "Benoetigte Zeit zum Loeschen des Baums: " << elapsed_time << "ms" << std::endl;
	pause();
}

/*
 * In insertOwnNumber() the number you want will be inserted.
 */
void insertOwnNumber(int nfon) //nfon: numberforownnumber
{
	if (nfon > maxnumber)
	{
		maxnumber = nfon;
	}
	tree.print();
	for (int i = 0; i < nfon; i++)
	{
		cout << "Alter Baum:" << endl;
		tree.print();
		cout << "Zahl eingeben" << endl;
		cin >> number;
		tree.insert(number);
		cout << "Neuer Baum" << endl;
		tree.print();
	}
	pause();
}
/*
 * The number that shall be deleted is deleted from the tree.
 */
void deletenode()
{
	cout << "Aktueller Baum:" << tree << endl;
	cout << "Zuloeschende Zahl:";
	cin >> inputnumber;
	if (tree.search(inputnumber) != nullptr)
	{
		cout << "Alter Tree:" << tree << endl;
		//tree.deleteNode(tree.search(inputnumber));
		cout << "Neuer Tree:" << tree << endl;

	}
	else
	{
		cout << "Zahl ist in dem Tree nicht vorhanden und kann nicht geloescht werden" << endl;
	}

	pause();

}

/*
 * Works exactly like deleteTree() only without runtime measurement.
 */
void deleteTestTree()
{
	for (int i = 0; i <= maxnumber; i++) 
	{
		while (tree.search(i))
		{
			//tree.deleteNode(tree.search(i));
		}
	}
	maxnumber = 0;
}

/*
 * The whole tree is deleted. A for-loop is used to go through all numbers from 0 to maxnumber. 
 * Existing numbers are deleted from the tree.
 * The time is measured.
 */
void deleteTree()
{
	int count = 0;
	clock_t start = clock();
	for (int i = 0; i <= maxnumber; i++)
	{
		while (tree.search(i))
		{
			//tree.deleteNode(tree.search(i));
			count++;
		}
	}
	clock_t end = clock();
	double elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000;
	std::cout << "Benoetigte Zeit um den Baum mit " << count << " Knoten zu loeschen: " << elapsed_time << "ms" << std::endl;
	maxnumber = 0;
}


/*
 * The start function, if the test mode is not started. 
 * Asks for the number of nodes in the tree and whether you want to insert them with random numbers or your own numbers.
 */
void start()
{
	cout << "Mit wie viele Knoten soll der Baum erstellt werden" << endl;
	cin >> anzahl;
	clear();
	cout << "Wie sollen die " << anzahl << " Knoten erstellt werden" << endl;
	cout << "1. Mit zufaelligen Zahlen" << endl;
	cout << "2. Mit eigene Zahlen" << endl;
	cin >> input;
	switch (input)
	{
	case '1':
		insertRangeRandomNumber(anzahl);
		break;
	case '2':
		insertOwnNumber(anzahl);
		break;
	default:
		cout << "Menuepunkt nicht vorhanden" << endl;
		pause();
		break;
	}
}



/*
 * In the main() the menu is created and output as well as the state of the tree.
 */
int main()
{


	srand(time(0));

	cout << "Welcher Modus soll gestartet werden?" << endl;
	cout << "1. Testmodus" << endl << "2. Normalmodus" << endl;
	cin >> input;
	switch (input)
	{
	case '1':
		test();
		break;
	case '2':
		start();
		break;
	default:
		cout << "Menuepunkt nicht vorhanden" << endl;
		pause();
	}

	while (input != '9')
	{
		clear();
		cout
			<< "Red-Black-Tree" << endl
			<< "Tree:" <<endl; 
				tree.print();
				cout << endl;
			cout << "1. Neue Zahl einfuegen" << endl
			//<< "2. Zahl loeschen" << endl
			<< "2. Zahl suchen" << endl
			//<< "4. Baum loeschen" << endl
			<< "9. Beenden" << endl;
		//cout<< "n. Neustart" << endl; //nur zum debuggen
		cin >> input;
		while (cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(256, '\n');
			cin >> input;
		}


		switch (input)
		{
		case '1':
			cout << "Wie viele Zahlen sollen hinzugefuegt werden" << endl;
			cin >> anzahl;
			cout << "1 Zufaellige?" << endl;
			cout << "2 Eigene" << endl;
			cin >> input;
			try {
				switch (input)
				{
				case '1':
					insertRangeRandomNumber(anzahl);
					break;
				case '2':
					insertOwnNumber(anzahl);
					break;
				}
			}
			catch (int& e)
			{

			}
			break;
		/*case '2':
			deletenode();
			break;*/
		case '2':
			cout << "Gesuchte Zahl:" << endl;
			cin >> number;
			if (tree.search(number) != nullptr)
			{
				cout << "Die Zahl " << number << " ist vorhanden" << endl;
			}
			else
			{
				cout << "Die Zahl " << number << " ist NICHT vorhanden" << endl;
			}
			pause();
			break;
		/*case '4':
			deleteTree();
			pause();
			break;*/
		case '9':
			cout << endl;
			cout << "Erstellt von " << endl
				<< "Laureen Roccotelli und Julian Tomsa" << endl;
			break;
			/*case 'n':
				deletetree();
				clear();
				main();
				break;*/
		default:
			cout << "Menuepunkt nicht vorhanden" << endl;
			pause();
		}
	}

	return 0;
}

// Programm ausfuehren: STRG+F5 oder Menueeintrag "Debuggen" > "Starten ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menue "Debuggen starten"

// Tipps fuer den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufuegen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufuegen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufuegen", um dem Projekt vorhandene Codedateien hinzuzuf???gen.
//   6. Um dieses Projekt spaeter erneut zu oeffnen, wechseln Sie zu "Datei" > "oeffnen" > "Projekt", und waehlen Sie die SLN-Datei aus.
