#pragma once

#include <cmath>

class Vector
{
public:
	Vector(void);
	Vector(float x, float y, float z);
	~Vector(void);
	Vector operator *(float a);
	Vector operator /(float a);
	Vector operator +(Vector &vector);
	Vector compose(Vector &vector1); // pas de surcharge car pas de signe ressemblant
	float scalaire(Vector &vector); //produit scalaire
	float norme(); //norme
	Vector project(Vector &vector1); // projection
	float distance(Vector &vector1);
	Vector operator ^(Vector &vector); //produit vectoriel
	float produitMixte(Vector &vector1, Vector &vector2); 
	
private:
	float x;
	float y;
	float z;

};

