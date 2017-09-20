// Tester file provided by Prof Levitan at Brooklyn College

#include <assert.h>
#include <iostream>
#include <cstdlib>

#include "Ntree.h"

int main() {

	Ntree<std::string> foodtree("Food");
	foodtree.addChildren("Food", { "Plant", "Animal" });
	foodtree.addChildren("Plant", { "Roots", "Leaves", "Fruits" });
	foodtree.addChildren("Animal", { "Fish", "Mammals", "Birds" });
	foodtree.addChildren("Roots", { "Potatoes", "Carrots" });
	foodtree.addChildren("Leaves", { "Lettuce", "Cabbage" });
	foodtree.addChildren("Fruits", { "Apples", "Pears", "Plums", "Oranges" });
	foodtree.addChildren("Fish", { "Salmon", "Tuna" });
	foodtree.addChildren("Mammals", { "Beef", "Lamb" });
	foodtree.addChildren("Birds", { "Chicken", "Duck" });
	foodtree.addChildren("Salmon", { "Wild", "Farm" });
	foodtree.addChildren("Apples", { "GrannySmith", "Gala" });

	foodtree.serialize("foodtree.out");

	Ntree<std::string> foodtree2;
	foodtree2.deserialize("foodtree.out");

	assert(foodtree == foodtree2);

	Ntree<int> inttree(9);
	inttree.addChildren(9, { 6 });
	inttree.addChildren(6, { 5, 4, 2 });
	inttree.addChildren(5, { 10, 7, 1 });
	inttree.addChildren(4, { 3, 8 });
	inttree.addChildren(3, { 11, 12, 13, 14 });

	inttree.serialize("inttree.out");
	Ntree<int> inttree2;
	inttree2.deserialize("inttree.out");
	assert(inttree == inttree2);
	foodtree.printTree(); foodtree2.printTree();
	inttree.printTree(); inttree2.printTree();

	system("PAUSE");
	return 0;
}
