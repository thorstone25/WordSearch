// Implements wordlist which stores a list of words

class Wordlist
{
	public: 
		const void readWords(const string filename);
		friend ostream& operator<<(ostream &ostr,const Wordlist &w);
	protected:
		vector<string> wds;
}


ostream& operator<<(ostream &ostr,const Wordlist &w)
{
	 for(int i=0;i<wds.size();i++)
	 { ostr << (wds[i] + ", ");}
	 
	 return ostr;
}
