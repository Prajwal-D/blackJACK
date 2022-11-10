#pragma once
#include <String>
class card
{
public:
	card()= default;
	card(const std::string& newFace, const int& newVal);
	int returnVal();
	std::string returnFace();
private:
	int val = 14;
	std::string face = "SPADES";
};

