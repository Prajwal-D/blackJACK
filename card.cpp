#include "card.h"
card::card(const std::string& newFace, const int& newVal)
{
	face = newFace;
	val = newVal;
}
int card::returnVal()
{
	return val;
}
std::string card::returnFace()
{
	return face;
}