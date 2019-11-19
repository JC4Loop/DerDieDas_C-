#ifndef DDDClasses_H_INCLUDED
#define DDDClasses_H_INCLUDED

using namespace std;

class Word {
	public:
		string word;
		string engTranslation;

		Word(string word, string eng){
			this->word = word;
			this->engTranslation = eng;
		}

		static int getWordMaxlength(Word * array[],int nItems){
			int maxLen = (*array[0]).word.size();
			if ((*array[0]).engTranslation.size() > maxLen){
				maxLen = (*array[0]).engTranslation.size();
			}
			int curLen;
			
			if (nItems > 1){
				for (int i = 1; i < nItems; i++){
					curLen = (*array[i]).word.size();
					if (curLen > maxLen){
						maxLen = curLen;
					}
				}
				for (int i = 1; i < nItems; i++){
					curLen = (*array[i]).engTranslation.size();
					if (curLen > maxLen){
						maxLen = curLen;
					}
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

		ArtAndWord(string article,string word,string eng) : Word(word,eng){
			this->article = article;
			this->indefArticle = getInDefArticle();
			this->engIDA = getEngIArt();
		}

		static int getWordMaxlength(ArtAndWord * array[],int nItems){
			Word * poly[] = {	array[0],
								array[1],
								array[2],
								array[3],
								array[4],
								array[5],
								array[6]
							};
			return Word::getWordMaxlength(poly,nItems);
		}

		// article when word is the object of the sentence
		// accusative

		string getInDefArticle(){
			char c = article[2];
			switch (c){
				case 'r':
					return "ein";
				case 'e':
					return "eine";
				case 's':
					return "ein";
				default:
					return "ERROR IN getInDefArticle";
			}

		}

		string getArtAccusative(){
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

		string getInDefArtAccus(){ //getInDefArtObject(){
			char c = article[2];
			switch (c){
				case 'r':
					return "einen";
				case 'e':
					return "eine";
				case 's':
					return "ein";
				default:
					return "ERROR IN getInDefArtObject";
			}
		}

		string getDefDatObj(){
			char c = article[2];
			switch (c){
				case 'e':
					return "der";
				case 'r':
				case 's':
					return "dem";
				default:
					return "ERROR IN getDefDatObj";
			}
		}

		string getInDefDatObj(){
			char c = article[2];
			switch (c){
				case 'e':
					return "einer";
				case 'r':
				case 's':
					return "einem";
				default:
					return "ERROR IN getInDefDatObj";
			}
		}

		string getEngIArt(){
			// returns the english indefinit article; a or an
			// if first letter of word is a vowel - return an
			char c = engTranslation[0];
			switch(c){
				case 'a':
				case 'e':
				case 'i':
				case 'o':
				case 'u'://	not always accurate - utlity / user- no vowel sound
					return "an";
				default:
					return "a";
			}
		}
};


// verb / preposition that requires preceeding "is"
class ISVerb : public Word {
	public:
		ISVerb(string word,string eng) : Word(word,eng){
			this->word = "ist " + this->word;
			this->engTranslation = "is " + this->engTranslation;
		}

	static int getWordMaxlength(ISVerb * array[],int nItems){
			Word * poly[] = {	array[0]
	
							};
			return Word::getWordMaxlength(poly,nItems);
		}
};

void copyArray(ArtAndWord * newArray[], ArtAndWord * cpyFromarray[], int size);
void PrepareOutputLines(int min, int max, int ranNNum,int ranVNum,int ranNONum,
						ArtAndWord *nouns[],ArtAndWord *ONouns[],Word * verbs[],
						int maxNounLen,int maxVerbLen,bool definitive,bool dative);

#endif