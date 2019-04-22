#include "gameengine.h"

using namespace std;

//used for sort()
struct score_comparison {
	inline bool operator() (const Score& a, const Score& b) {
    	return a.score > b.score;
	}
};

//finds the position in scores vector given initials
void Score::find_score(vector<Score>::iterator& it, const vector<Score>::iterator& end, const string& initials) {
    for(; it != end ; it++) {
        if (it->initials == initials) break;
    }
}

//saves scores vector to output file and sorts by high score
void Score::save(vector<Score>& scores, string filepath)
{
    sort(scores.begin(), scores.end(), score_comparison());
    
    ofstream outfile (filepath);
    
    for(int i=0; i<scores.size(); i++)
    {
        outfile << scores.at(i).initials << " " << scores.at(i).score << endl;
    }
    outfile.close();
    
}

//loads input file to scores vector
vector<Score> Score::load(string filepath) {
    ifstream infile(filepath);
    vector<Score> newscores;
    int tempscore;
    string tempinitials;
    
    while(infile >> tempinitials >> tempscore) {
    	newscores.emplace_back(tempinitials, tempscore);
    }
    
    return newscores;
}

