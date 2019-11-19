#include <iostream>
#include <stdlib.h>     /* srand, rand */

#include "DDDClasses.h"

int main(){
	srand (time(NULL));

	ArtAndWord *nouns[] = { new ArtAndWord("Der","Apfel","apple"),
							new ArtAndWord("Der","Hund","dog"),
							new ArtAndWord("Der","Himmel","sky"),
							new ArtAndWord("Das","Buch","book"),
							new ArtAndWord("Die","Orange","orange"),
							new ArtAndWord("Die","Katze","cat"),
							new ArtAndWord("Das","Telefon","phone")
						};

	ArtAndWord *ONouns[7];	// hold another array of nouns - used for object of sentence
	copyArray(ONouns,nouns,7);

/*
	Word *prepositions[] = {	new Word("neben","next to")
						
					};
					*/

	Word *prepositions[] = {	new ISVerb("neben","next to")
						
					};

	int maxNounLen = ArtAndWord::getWordMaxlength(nouns,7);

	Word *w1 = (prepositions[0]);

	Word *w = static_cast<Word *>(w1);
	Word *polyPrep[] = { w };

	int maxPrepLen = Word::getWordMaxlength(polyPrep,1);
	
	int ranNNum, ranPNum,ranNONum;
	
	int min = 0, max = 6;

	cout << "--- Nominative Definitive ---- Dative Definit --------" << endl << endl;
	PrepareOutputLines(min,max,ranNNum,ranPNum,ranNONum,nouns,ONouns,polyPrep,maxNounLen,maxPrepLen,true,true);

	cout << "--- Nominative InDefinitive -- Dative Indefinit-------" << endl << endl;
	PrepareOutputLines(min,max,ranNNum,ranPNum,ranNONum,nouns,ONouns,polyPrep,maxNounLen,maxPrepLen,false,true);
	cout << endl;
	
	return 0;
}