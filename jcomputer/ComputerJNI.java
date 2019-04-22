package jcomputer;

public class ComputerJNI {
	static {
      System.loadLibrary("computer"); // computer.dll (Windows), computer.so (Unixes) or libcomputer.dylib (MacOS)
	}
	
   // Declare a native method sumAndAverage() that receives an int and
   //  return a int[2] array with [0] as sum and [1] as average
   public native int[] computerMove(int num);
 
   public static int[] javaComputer(int a) {
      int[] results = new jcomputer.ComputerJNI().computerMove(a);
      return results;
   }
   
   //testing as own application for debugging
   public static void main(String[] args){
       int[] attempt = javaComputer(5);
       for (int i = 0; i <6; i++){
           System.out.println(attempt[i]);
       }
       attempt = javaComputer(0);
       for (int i = 0; i <6; i++){
           System.out.println(attempt[i]);
       }
   }
}
