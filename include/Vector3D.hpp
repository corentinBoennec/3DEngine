#pragma once

#include<cmath>
#include <fstream>
#include <iostream>
#include <string>

#include "Matrix/Matrix4x4.hpp"

class Quaternion;

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

	Vector3D operator *(float a) const; // surcharge de l'opérateur * pour la multiplication d'un vecteur par un scalaire
	float operator *(const Vector3D& v) const; //surcharge de l'opérateur * pour le produit scalaire entre 2 vecteurs
	Vector3D operator /(float a) const; // surcharge de l'opérateur / pour la division par un scalaire
	Vector3D operator +(const Vector3D& vector) const; // surcharge de l'opérateur + pour la somme de 2 vecteurs
	Vector3D operator -(const Vector3D& vector) const; // surcharge de l'opérateur - pour la somme de 2 vecteurs
	void operator +=(const Vector3D& vector); // surcharge de l'operateur += pour ajouter un vecteur dans un autre
	Vector3D compose(const Vector3D& vector1) const; // pas de surcharge car pas de signe ressemblant
	float norme() const; //norme
	Vector3D project(const Vector3D& vector1) const; // projection
	float distance(const Vector3D& vector1) const; //distance
	Vector3D operator ^(const Vector3D& vector) const; //produit vectoriel
	float produitMixte(Vector3D& vector1, const Vector3D& vector2) const; //produit mixte
	Vector3D unit() const;

	void localToWorld(Matrix4x4 transformationMatrix);
	void worldToLocal(Matrix4x4 transformationMatrix);
	


private:
	float x;
	float y;
	float z;

};

