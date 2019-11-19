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

	// transitive verbs
	Word *verbs[] = {	new Word("berührt ","touches"),
						new Word("findet","finds"),
						new Word("liest","reads"),
						new Word("hört ","hears"),
						new Word("schiebt","pushes"),
						new Word("sieht","sees"),
						new Word("wirft","throws"),
					};

	Word *prepositions[] = {	new Word("neben","near")
						
					};

	int maxNounLen = ArtAndWord::getWordMaxlength(nouns,7);
	int maxVerbLen = Word::getWordMaxlength(verbs,7);
	
	int ranNNum, ranVNum,ranNONum;
	
	bool definitive = true;
	int min = 0, max = 6;

	cout << "--- Nominative Definitive ---- Accusative Definit --------" << endl << endl;
	PrepareOutputLines(min,max,ranNNum,ranVNum,ranNONum,nouns,ONouns,verbs,maxNounLen,maxVerbLen,definitive,false);

	cout << "--- Nominative InDefinitive -- Accusative Indefinit-------" << endl << endl;
	PrepareOutputLines(min,max,ranNNum,ranVNum,ranNONum,nouns,ONouns,verbs,maxNounLen,maxVerbLen,false,false);
	cout << endl;
	return 0;
}