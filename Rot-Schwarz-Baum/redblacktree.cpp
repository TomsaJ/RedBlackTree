#include <iostream>
#include "redblacktree.h"

int main(int argc, char** argv) {

	{
		SearchTree<int> tree;

		// Einfuegen:
		tree.insert(8);
		tree.insert(10);
		tree.insert(9);
		tree.insert(11);
		tree.insert(5);
		tree.insert(4);
		tree.insert(2);
		tree.insert(7);

		// Ausdrucken:

		std::cout << "Tree: " << tree << "\n"; // erwartet: 2, 4, 5, <7>, 8, 9, 10, 11,

		// Suchen:
		std::cout << "Suche 4, Gefunden: " << tree.search(4)->key << "\n";
		std::cout << "Suche 16 (nicht in Der Liste), gefunden: " << (void*)tree.search(16) << "\n"; // Falls element nicht in Liste: nullptr

		// Loeschen:
		// std::cout << "removing 8\n";
		// tree.deleteNode(tree.search(8));
		// std::cout << tree << "\n";

	}

	std::cout << "Baum wird geloescht, keine Fehler gefunden\n"; // wenn nicht erscheint, ist das programm abgestuertzt

	return 0;
}
