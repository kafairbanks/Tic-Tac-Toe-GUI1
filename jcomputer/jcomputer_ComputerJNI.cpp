#include <jni.h>
#include "jcomputer_ComputerJNI.h"
#include "ComputerWrapper.h"
 
JNIEXPORT jintArray JNICALL Java_jcomputer_ComputerJNI_computerMove
  (JNIEnv * env, jobject obj, jint playerMove) {
    
    jintArray result;
    result = env->NewIntArray(6);
    if (result == NULL) {
        return NULL; /* out of memory error thrown */
    }
    int i;
    // fill a temp structure to use to populate the java int array
    
    int compMoves[6];
    
    ComputerWrapper c;
    //game has been won, create new computer object
    if (playerMove == 64){   
        c.resetComputer();
        for (int i =0; i<6;i++){
            compMoves[i]=i;
        }
    }
    else{
        c.computerCall(compMoves, playerMove);
    }
    
    jint fill[6];
    for (i = 0; i < 6; i++) {
        fill[i] = compMoves[i]; // put whatever logic you want to populate the values here.
        //fill[i] = i;
    }
    // move from the temp structure to the java structure
    env->SetIntArrayRegion(result, 0, 6, fill);
    return result;
}