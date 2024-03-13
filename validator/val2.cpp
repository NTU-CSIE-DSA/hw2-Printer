#include "testlib.h"
#include <assert.h>
#include <unordered_set>
using namespace std;

int main() {
    registerValidation();
    int N = inf.readInt(1, 5000);
    inf.readSpace();
    int M = inf.readInt(1, 5000);
    inf.readEoln();
    set<int> job, p;
    for(int i = 1; i <= M; i++){
        int op = inf.readInt(1, 3);
        inf.readSpace();
        if(op == 1){
            int job_id = inf.readInt(1, 1e9);
            inf.readSpace();
            int priority = inf.readInt(1, 1e9);
            inf.readSpace();
            int printer_id = inf.readInt(1, N);
            ensure(!job.count(job_id));
            ensure(!p.count(priority));
            job.insert(job_id);
            p.insert(priority);
        }
        if(op == 2){
            int printer_id = inf.readInt(1, N);
        }
        if(op == 3){
            int id1 = inf.readInt(1, N);
            inf.readSpace();
            int id2 = inf.readInt(1, N);
            ensure(id1 != id2);
        }
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}
