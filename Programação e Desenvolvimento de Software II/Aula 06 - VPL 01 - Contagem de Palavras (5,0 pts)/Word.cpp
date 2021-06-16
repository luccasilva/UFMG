#include "Word.hpp"

Word::Word () {
	this->word = "";
	this->count = 1;
}

void Word::incrementFreq () {
	count += 1;
}