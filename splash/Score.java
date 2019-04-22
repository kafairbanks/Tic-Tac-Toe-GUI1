package splash;

import java.util.Vector;
import java.io.PrintWriter;
import java.io.File;
import java.util.Scanner;
import java.io.IOException;

public class Score {
	
	private String initials;
	private int score;
	
	public Score(String i, int s) {
		initials = i;
		score = s;
	}
	
	public Score(String i) {
		initials = i;
		score = 0;
	}

	public String getInitials() {
		return initials;
	}
	
	public int getScore() {
		return score;
	}
	
	public void setScore(int sc) {
		score = sc;
	}
}
