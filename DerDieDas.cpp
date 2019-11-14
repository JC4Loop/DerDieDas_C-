#include <iostream>
#include <stdlib.h>     /* srand, rand */

#include "DDDClasses.h"

int main(){
	srand (time(NULL));

	ArtAndWord *nouns[] = { new ArtAndWord("Der","Apfel","apple","ein","an"),
							new ArtAndWord("Der","Hund","dog","ein","a"),
							new ArtAndWord("Der","Himmel","sky","ein","a"),
							new ArtAndWord("Das","Buch","book","ein","a"),
							new ArtAndWord("Die","Orange","orange","eine","an"),
							new ArtAndWord("Die","Katze","cat","eine","a"),
							new ArtAndWord("Das","Telefon","phone","ein","a")
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

	int maxNounLen = ArtAndWord::getWordMaxlength(nouns);
	int maxVerbLen = Word::getWordMaxlength(verbs);
	
	int ranNNum, ranVNum,ranNONum;
	
	bool definitive = true;
	int min = 0, max = 6;

	cout << "--------------Nominative Definitive---------------" << endl;
	PrepareOutputLines(min,max,ranNNum,ranVNum,ranNONum,nouns,ONouns,verbs,maxNounLen,maxVerbLen,definitive);

	cout << "--------------Nominative InDefinitive---------------" << endl;
	PrepareOutputLines(min,max,ranNNum,ranVNum,ranNONum,nouns,ONouns,verbs,maxNounLen,maxVerbLen,false);
	
	cout << endl;
	return 0;
}