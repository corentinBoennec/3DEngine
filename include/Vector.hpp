#pragma once

#include<cmath>
#include <fstream>
#include <iostream>
#include <string>

class Vector
{
public:
	Vector(void);
	Vector(float x, float y, float z);
	~Vector(void);

	float getX();
	float getY();
	float getZ();
	void setX(float x);
	void setY(float y);
	void setZ(float z);

	Vector operator *(float a); // surcharge de l'opérateur * pour la multiplication d'un vecteur par un scalaire
	float operator *(Vector v); //surcharge de l'opérateur * pour le produit scalaire entre 2 vecteurs
	Vector operator /(float a); // surcharge de l'opérateur / pour la division par un scalaire
	Vector operator +(Vector &vector); // surcharge de l'opérateur + pour la somme de 2 vecteurs
	Vector compose(Vector &vector1); // pas de surcharge car pas de signe ressemblant
	float norme(); //norme
	Vector project(Vector &vector1); // projection
	float distance(Vector &vector1); //distance
	Vector operator ^(Vector &vector); //produit vectoriel
	float produitMixte(Vector &vector1, Vector &vector2); //produit mixte

private:
	float x;
	float y;
	float z;

};

