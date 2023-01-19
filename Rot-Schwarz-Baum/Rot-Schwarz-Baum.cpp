// Rot-Schwarz-Baum.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include "redblacktree.hpp"

int main(int argc, char** argv) {
	{
		// TreeNode<int> tree(5);
		RedBlackTree<int> tree;

		// Einfuegen:
		tree.insert(5);
		tree.insert(4);
		tree.insert(3);
		tree.insert(2);
		tree.insert(7);
		tree.insert(8);
		tree.insert(9);
		tree.insert(10);

		// Ausdrucken:
		std::cout << "Tree: " << tree << "\n"; // erwartet: 2, 3, 4, <5>, 7, 8, 9, 10,

		// Suchen:
		std::cout << "Searching 3, found: " << tree.search(3)->key << "\n";
		std::cout << "Searching 21 (not in list), found: " << (void*)tree.search(21) << "\n"; // Falls element nicht in Liste: nullptr

		// Loeschen:
		std::cout << "removing 8\n";
		tree.deleteNode(tree.search(8));
		std::cout << tree << "\n";

		std::cout << "removing 10\n";
		tree.deleteNode(tree.search(10));
		std::cout << tree << "\n";

		// Sonderfall: Wurzel loeschen:
		std::cout << "removing 5 (root node)\n";
		tree.deleteNode(tree.search(5));
		std::cout << tree << "\n";

		// Predecessor testen:
		std::cout << "removing element before 4 (3)\n";
		tree.deleteNode(tree.search(4)->predecessor());
		std::cout << tree << "\n";

		// Successor testen:
		std::cout << "removing element after 4 (7)\n";
		tree.deleteNode(tree.search(4)->successor());
		std::cout << tree << "\n";

		// <<--  Hier wird aufgrund des Scope-Endes automatisch der destruktor von tree aufgerufen
	}

	std::cout << "deleted tree, no errors occurred\n"; // Falls dieser text NICHT erscheint, dann ist das Programm im Destruktor von tree abgestuerzt

	return 0;
}

// Programm ausführen: STRG+F5 oder Menüeintrag "Debuggen" > "Starten ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.
