#pragma once
#include "Tree\QuadtreeNode.hpp"

class QuadTree
{
private:
	std::vector<QuadTreeNode> nodes;  // tous les noeuds de l'arbre
	std::vector<RigidBody*> Elements;  // tous les �l�ments de l'arbre

public:
	QuadTree(QuadTreeNode firstNode, std::vector<RigidBody*> Elements); 
	QuadTree();
	void cleanQuadTree();
	std::vector<QuadTreeNode> getNodes(); // renvoi les noeuds
	std::vector<QuadTreeNode> getFinalLeaves(); // renvoi toutes les feuilles en bout d'arbre. en d'autre terme ceux qui n'ont pas d'enfant.
	std::vector<RigidBody*> getElements(); // renvoi les �l�ments
	void divideSpaceNTime(int nbDivision); //divise l'espace du noeud de la racine "nbDivision" fois.
	void divideNodeAtDepth(int depth); //divise les noeuds de l'arbre a la pronfondeur "depth".
	void addElement(RigidBody * newElement);	//ajoute un �l�ment a l'arbre.

};