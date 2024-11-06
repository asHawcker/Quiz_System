#include "QuestionSet.hpp"

int QuestionSet::show(){
    for (int i=0;i<count;i++){
        set[i].show();
    }
    return 0;
}

