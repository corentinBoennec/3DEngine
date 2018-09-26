#include "RegistreForce.hpp"

void RegistreForce::add(EnregistrementForce eF)
{
	this->registre.push_back(eF);
}
void RegistreForce::suppr(int index)
{
	this->registre.erase(registre.begin() + index);
}
int RegistreForce::count()
{
	return (int)this->registre.size();
}