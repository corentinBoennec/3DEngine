#pragma once
#include "RigidBody.hpp"
#include "Plan.hpp"
#include <vector>
#include "Functions.hpp"

class QuadTreeNode
{
private:
	QuadTreeNode * leaves; // pointes vers les noeuds fils de ce noeud
	std::vector<RigidBody*> containedElements; // Les éléments contenues dans le noeud
	
	Plan plans[4]; // les 4 plans qui encadre l'espace de ce noeud dans cet ordre :  right / left / top / Bottom
																					 
	bool gotChildren; // vrai si le noeud a des feuilles 


public:
	//Constructeur par default
	QuadTreeNode();
	QuadTreeNode(Plan plans[4]);
	QuadTreeNode(Plan plans[4], std::vector<RigidBody*> containedElements);
	QuadTreeNode(QuadTreeNode * quadTree);
	void destroyQuadTreeNode();
	void divide(); // Donne à un noeud quatre feuilles en répartissant ses éléments dans ses fils.
	void addLeaves(QuadTreeNode leaves[4]); // ajoutes 4 noeuds en temps que feuille a un noeud.
	int getNbContainedElements(); //renvoi le nombre d'élément contenue dans le noeud.
	std::vector<RigidBody*> getContainedElements(); // renvoi les éléments contenus dans le noeud.
	void addElement(RigidBody * element); // ajoute un élément au noeud.
	bool doGotChildren(); //renvoi le booléen gotChildren.
	QuadTreeNode * getLeaves(); // renvoi un pointeur vers les fils de ce noeud.
};