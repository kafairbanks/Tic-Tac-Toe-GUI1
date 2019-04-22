# CSCE315-Project4
CSCE 315 - Project 4

To complie and run on compute (make sure a display server [such as xserver] is running)

/pub/faculty_share/daugher/java/jdk1.8.0_161/bin/javac board/*.java rules/\*.java splash/\*.java jcomputer/\*.java gameover/\*.java ./\*.java; 

/pub/faculty_share/daugher/java/jdk1.8.0_161/bin/javah -d ./jcomputer/include jcomputer.ComputerJNI; 

g++ -std=c++11 -shared -fPIC -I./jcomputer/include/ -I$JAVA_INC -I/pub/faculty_share/daugher/java/jdk1.8.0_161/include/linux/ -I/pub/faculty_share/daugher/java/jdk1.8.0_161/include/ -I/usr/lib/jvm/java-1.8.0-openjdk-1.8.0.161-0.b14.el7_4.x86_64/include/linux/ jcomputer/\*.cpp -o jcomputer/libcomputer.so; 

/pub/faculty_share/daugher/java/jdk1.8.0_161/bin/java -Djava.library.path=./jcomputer Main;
