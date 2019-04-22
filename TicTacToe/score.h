#ifndef SCOREKEEPER_H
#define SCOREKEEPER_H

using namespace std;

// stores an initials with its current score
class Score {
public:
    Score(string initials, int score) : initials(initials), score(score) {}
    Score(string initials) : initials(initials), score(0) {}
	Score(){}
    string initials;
    int score;
	//static bool score_comparison(const Score& a, const Score& b);
	static void find_score(vector<Score>::iterator& it, const vector<Score>::iterator& end, const string& initials);
	static void save(vector<Score>& scores, string filepath);
	static vector<Score> load(string filepath);
};
#endif
