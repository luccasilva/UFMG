#include "WordCounter.hpp"
#include "Word.hpp"

using namespace std;

WordCounter::WordCounter(int num_words) {
	words = new Word[num_words];
}

WordCounter::~WordCounter() {
    delete words;
}

void WordCounter::addWord(string w){
	
    for (int i = 0; i < this->size; i++) {
        if (this->words[i].word == w) {
            this->words[i].incrementFreq();
            return;
        }
    }
    this->words[this->size].word = w;
    this->size++;
}

void WordCounter::print() const{

	Word auxiliar;
    int index = 0;
    for (int i = 0; i < this->size; i++) {
        index = i;
        for (int j = i + 1; j < this->size; j++) {
            if (this->words[j].word.compare(this->words[index].word) < 0) {
                index = j;
            }
        }
        auxiliar = this->words[i];
        this->words[i] = this->words[index];
        this->words[index] = auxiliar;
        cout << this->words[i].word << ' ' << this->words[i].count << ' ' << endl;
    }

}

