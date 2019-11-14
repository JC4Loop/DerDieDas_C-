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

		// article when word is the object of the sentence
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

		string getInDefArtObject(){
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
			// if first letter of word is a vowel - return an
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

void copyArray(ArtAndWord * newArray[], ArtAndWord * cpyFromarray[], int size);
void PrepareOutputLines(int min, int max, int ranNNum,int ranVNum,int ranNONum,
						ArtAndWord *nouns[],ArtAndWord *ONouns[],Word * verbs[],
						int maxNounLen,int maxVerbLen,bool definitive);

#endif