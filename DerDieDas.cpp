#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;


class Word {
	public:
		string word;
		string engTranslation;

		Word(string word, string eng){
			this->word = word;
			this->engTranslation = eng;
		}

		static int getWordMaxlength(Word * array[]){
			int maxLen = (*array[0]).word.size();
			int curLen;
			for (int i = 1; i < 7; i++){
				curLen = (*array[i]).word.size();
				if (curLen > maxLen){
					maxLen = curLen;
				}
			}
			for (int i = 0; i < 7; i++){
				curLen = (*array[i]).engTranslation.size();
				if (curLen > maxLen){
					maxLen = curLen;
				}
			}
			//cout << "max len = " << maxLen;
			return maxLen;
		}
};

class ArtAndWord : public Word {
	public:
		string article;
		string indefArticle;
		string engIDA; // english indefinite article

		ArtAndWord(string article,string word,string eng,string ida, string engida) : Word(word,eng){
			this->article = article;
			this->indefArticle = ida;
			this->engIDA = engida;
		}

		static int getWordMaxlength(ArtAndWord * array[]){
			Word * poly[] = {	array[0],
								array[1],
								array[2],
								array[3],
								array[4],
								array[5],
								array[6]
							};
			return Word::getWordMaxlength(poly);
		}

		// article when word become the object of the sentence
		// accusative

		string getObjectArticle(){
			char c = article[2];
			switch (c){
				case 'r':
					return "den";
				case 'e':
					return "die";
				case 's':
					return "das";
				default:
					return "ERROR IN getObjectArticle";
			}
		}

		string getDativeObject(){
			char c = article[2];
			switch (c){
				case 'r':
					return "einen";
				case 'e':
					return "eine";
				case 's':
					return "ein";
				default:
					return "ERROR IN getObjectArticle";
			}
		}

		string getEngIArt(){
			// returns the english indefinit article; a or an
			char c = engTranslation[0];
			switch(c){
				case 'a':
				case 'e':
				case 'i':
				case 'o':
				case 'u':
					return "an";
				default:
					return "a";
			}
		}
};


int getRandomNumber(int min,int max){
	max -= min - 1;
	return (rand() % max) + min;
}

int getRandomNumEx(int min,int max,int ex){
	int rNum;
	do {
		rNum = getRandomNumber(min,max);
	} while (rNum == ex);
	return rNum;
}

void copyArray(ArtAndWord * newArray[], ArtAndWord * cpyFromarray[], int size){
	for (int i = 0; i < size; i++){
		newArray[i] = cpyFromarray[i];
	}
}


void removeFromArray(ArtAndWord * array[], int num){
	bool shifting = false;
	ArtAndWord * current;
	for (int i = 0; i < 7; i++){
		if (shifting){
			if (i != 6){
				array[i] = array[i + 1];
			} else {
				array[i] = current;
			}
		} else {
			if (i == num){
				current = array[i];
				if (i < 6){
					array[i] = array[i + 1];
				}
				shifting = true;
			}
		}	
	}
}


void removeFromArray(Word * array[], int num){
	//cout << "num = " << num << endl;
	bool shifting = false;
	Word * current;
	for (int i = 0; i < 7; i++){
		if (shifting){
			if (i != 6){
				array[i] = array[i + 1];
			} else {
				array[i] = current;
			}
		} else {
			if (i == num){
				current = array[i];
				if (i < 6){
					array[i] = array[i + 1];
				}
				shifting = true;
			}
		}	
	}
}

/* Does not work as only a copy of the array is sent, items removed from copy
void removeFromArray(ArtAndWord * array[],int num){
	Word * poly[] = {	array[0],
					array[1],
					array[2],
					array[3],
					array[4],
					array[5],
					array[6]
				};
	
	removeFromArray(poly,num);

	for (int i = 0; i < 7; i++){
		cout << poly[i]->word << " ";
	}
	cout << num << endl;
	
}
*/

string getPadString(string s, int max){
	int difference = max - s.size();
	for (int i = 0; i < difference; i++){
		s += ' ';
	}
	return s;
}


void OutputLines(ArtAndWord **pNoun,Word **pVerb,ArtAndWord **pONoun,int maxNounLen,int maxVerbLen,bool definitive){
	string aOut1,aOut2,engArticle1, engArticle2;
	if (definitive){
		aOut1 = (**pNoun).article;
		aOut2 = (*pONoun)->getObjectArticle();
		engArticle1 = "the", engArticle2 = "the";
	} else {
		aOut1 = (*pNoun)->indefArticle;
		aOut2 = (*pONoun)->getDativeObject();
		engArticle1 = (*pNoun)->getEngIArt();
		engArticle2 = (*pONoun)->getEngIArt();
	}
	
	string wOut1 = (*pNoun)->word;
	string vOut1 = (*pVerb)->word;
	
	string wOut2 = (*pONoun)->word;
	string wEng1 = (*pNoun)->engTranslation;
	string vEOut = (*pVerb)->engTranslation;
	string wEng2 = (*pONoun)->engTranslation;

	cout << aOut1 << ' ' << getPadString(wOut1,maxNounLen) << '\t' << getPadString(vOut1,maxVerbLen);
	cout << '\t' << aOut2 << ' ' << getPadString(wOut2,maxNounLen) << endl;
	cout << engArticle1 << ' ' << getPadString(wEng1,maxNounLen) << '\t' << getPadString(vEOut,maxVerbLen);
	cout << '\t' << engArticle2 << ' ' << wEng2 << endl << endl;
}

void PrepareOutputLines(int min, int max, int ranNNum,int ranVNum,int ranNONum,
						ArtAndWord *nouns[],ArtAndWord *ONouns[],Word * verbs[],
						int maxNounLen,int maxVerbLen,bool definitive){

	ArtAndWord **pNoun, **pONoun;	// pointer to pointers
	Word **pVerb;
	for (int i = 0; i < 7; i++){
		ranNNum = getRandomNumber(min,max);
		//cout << "ranNNum : " << ranNNum << " ";
		pNoun = nouns;
		pVerb = verbs;
		pONoun = ONouns;
		if (max > 0){
			ranNONum = getRandomNumEx(min,max,ranNNum);
		} else {
			ranNNum = 0;
		}
		pNoun += ranNNum;
		pONoun += ranNONum;
		ranVNum = getRandomNumber(min,max);
		pVerb += ranVNum;
		OutputLines(pNoun,pVerb,pONoun,maxNounLen,maxVerbLen,definitive);
		removeFromArray(nouns,ranNNum);
		removeFromArray(verbs,ranVNum);
		removeFromArray(ONouns,ranNONum);
		max--;
		}
}



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

	ArtAndWord *ONouns[7];
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