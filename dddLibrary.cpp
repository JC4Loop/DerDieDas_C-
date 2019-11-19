#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "DDDClasses.h"

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


void OutputPairLine(ArtAndWord **pNoun,Word **pVerb,ArtAndWord **pONoun,int maxNounLen,int maxVerbLen,bool definitive,bool dative){
	string aOut1,aOut2,engArticle1, engArticle2;
	if (definitive){
		aOut1 = (**pNoun).article;
		if (dative){
			aOut2 = (*pONoun)->getDefDatObj();
		} else {
			aOut2 = (*pONoun)->getArtAccusative();
		}
		
		engArticle1 = "the", engArticle2 = "the";
	} else {
		if (dative){
			aOut1 = (*pNoun)->getInDefArticle();
			aOut2 =  (*pONoun)->getInDefDatObj();
		} else {
			aOut1 = (*pNoun)->indefArticle;
			aOut2 = (*pONoun)->getInDefArtAccus();
		}
		
		engArticle1 = (*pNoun)->engIDA;
		engArticle2 = (*pONoun)->engIDA;
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
						int maxNounLen,int maxVerbLen,bool definitive,bool dative){

	ArtAndWord **pNoun, **pONoun;	// pointer to pointers
	Word **pVerb;
	for (int i = 0; i < 7; i++){
		ranNNum = getRandomNumber(min,max);

		pNoun = nouns;	// pointer set to first element of array
		pVerb = verbs;
		pONoun = ONouns;
		if (max > 0){
			ranNONum = getRandomNumEx(min,max,ranNNum);
		} else {
			ranNNum = 0;
		}
		pNoun += ranNNum;
		pONoun += ranNONum;
		if (dative){
			ranVNum = 0;
		} else {
			ranVNum = getRandomNumber(min,max);
		}
		pVerb += ranVNum;
		OutputPairLine(pNoun,pVerb,pONoun,maxNounLen,maxVerbLen,definitive,dative);
		removeFromArray(nouns,ranNNum);

		if (dative){

		} else {
			removeFromArray(verbs,ranVNum);
		}

		removeFromArray(ONouns,ranNONum);
		max--;
		}
}