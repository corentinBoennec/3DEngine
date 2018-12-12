#pragma once
#include "RigidBody.hpp"
#include "Plan.hpp"
#include <vector>
#include "Functions.hpp"

class QuadTreeNode
{
private:
	QuadTreeNode * leaves; // pointes vers les noeuds fils de ce noeud
	std::vector<RigidBody*> containedElements; // Les �l�ments contenues dans le noeud
	
	Plan plans[4]; // les 4 plans qui encadre l'espace de ce noeud dans cet ordre :  right / left / top / Bottom
																					 
	bool gotChildren; // vrai si le noeud a des feuilles 


public:
	//Constructeur par default
	QuadTreeNode();
	QuadTreeNode(Plan plans[4]);
	QuadTreeNode(Plan plans[4], std::vector<RigidBody*> containedElements);
	QuadTreeNode(QuadTreeNode * quadTree);
	void destroyQuadTreeNode();
	void divide(); // Donne � un noeud quatre feuilles en r�partissant ses �l�ments dans ses fils.
	void addLeaves(QuadTreeNode leaves[4]); // ajoutes 4 noeuds en temps que feuille a un noeud.
	int getNbContainedElements(); //renvoi le nombre d'�l�ment contenue dans le noeud.
	std::vector<RigidBody*> getContainedElements(); // renvoi les �l�ments contenus dans le noeud.
	void addElement(RigidBody * element); // ajoute un �l�ment au noeud.
	bool doGotChildren(); //renvoi le bool�en gotChildren.
	QuadTreeNode * getLeaves(); // renvoi un pointeur vers les fils de ce noeud.
};