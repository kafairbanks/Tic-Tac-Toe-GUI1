package splash;

import java.util.Vector;
import java.io.PrintWriter;
import java.io.File;
import java.util.Scanner;
import java.io.IOException;
import java.io.*;

public class ScoreManager {
    //finds the position in scores vector given initials
    public Score findScore(Vector<Score> v, String initials) {
        Score player = null;
        
        for(int i=0; i<v.size() ; i++) {
            if (v.get(i).getInitials().equals(initials)) {
                player = v.get(i);
                break;
            }
        }
        
        return player;
    }
    
    // simple selection sort function
    public Vector<Score> sort(Vector<Score> scores)
    {
        Vector<Score> sorted = new Vector<Score>();
        
        // Find the minimum element in unsorted array
        while (!scores.isEmpty()) {
            int min_idx = 0;
            int n = scores.size();
            for (int j = 1; j < n; j++) {
                if (scores.get(j).getScore() > scores.get(min_idx).getScore()) {
                    min_idx = j;
                }
            }
            
            // Swap the found minimum element with the first
            // element
            int tempSc = scores.get(min_idx).getScore();
            String tempIn = scores.get(min_idx).getInitials();
            Score tempScore = new Score(tempIn, tempSc);
            sorted.add(tempScore);
            scores.remove(min_idx);
        }
        
        return sorted;
    }
    
    //saves scores vector to output file and sorts by high score
    public void save(Vector<Score> scores, String filepath) throws IOException {
        scores = sort(scores);
        
        PrintWriter output = new PrintWriter(filepath);
        
        for(int i=0; i<scores.size(); i++)
        {
            output.println(scores.get(i).getInitials() + " " + scores.get(i).getScore());
        }
        output.close();
        
    }
    
    //loads input file to scores vector
    public Vector<Score> load(String filepath) throws IOException {
        
        File f = new File(filepath);
        Scanner infile = new Scanner(f);
        
        Vector<Score> newscores = new Vector<Score>();
        int tempscore;
        String tempinitials;
        String str = "";
        
        while(infile.hasNextLine()) {
            str = infile.nextLine();
            String[] tokens = str.split(" ");
            tempinitials = tokens[0];
            tempscore = Integer.valueOf(tokens[1]);
            newscores.add(new Score(tempinitials, tempscore));
        }
        
        return newscores;
    }
}