#include "QuestionSet.hpp"

int QuestionSet::show(){
    for (size_t i = 0; i < set.size(); ++i) {
            cout << "Question " << i + 1 << ": ";
            set[i]->display();
            cout << endl;
        }
    return 0;
}

