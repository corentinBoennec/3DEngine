#pragma once

#include<cmath>
#include <fstream>
#include <iostream>
#include <string>

class Vector3D
{
public:
	Vector3D(void);
	Vector3D(float x, float y, float z);
	~Vector3D(void);

	float getX();
	float getY();
	float getZ();
	void setX(float x);
	void setY(float y);
	void setZ(float z);

	Vector3D operator *(float a); // surcharge de l'opérateur * pour la multiplication d'un vecteur par un scalaire
	float operator *(Vector3D v); //surcharge de l'opérateur * pour le produit scalaire entre 2 vecteurs
	Vector3D operator /(float a); // surcharge de l'opérateur / pour la division par un scalaire
	Vector3D operator +(Vector3D vector); // surcharge de l'opérateur + pour la somme de 2 vecteurs
	Vector3D operator -(Vector3D vector); // surcharge de l'opérateur - pour la somme de 2 vecteurs
	void operator +=(Vector3D vector); // surcharge de l'operateur += pour ajouter un vecteur dans un autre
	Vector3D compose(Vector3D vector1); // pas de surcharge car pas de signe ressemblant
	float norme(); //norme
	Vector3D project(Vector3D vector1); // projection
	float distance(Vector3D vector1); //distance
	Vector3D operator ^(Vector3D vector); //produit vectoriel
	float produitMixte(Vector3D vector1, Vector3D vector2); //produit mixte
	Vector3D unit();

private:
	float x;
	float y;
	float z;

};

