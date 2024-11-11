#include "QuestionSet.hpp"

int QuestionSet::show(){
    for (int i=0;i<count;i++){
        cout << i+1 << '\t';;
        set[i].show();
    }
    return 0;
}

