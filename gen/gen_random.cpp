#include "testlib.h"
#include <climits>
#include <cassert>
#include <set>
using namespace std;

#define MAX_P 1000000000
#define MAX_N 1000001

int main(int argc, char* argv[]) {  // gen MAX_N MAX_M add print move
    registerGen(argc, argv, 1);
    assert(argc == 6);
    int N = atoi(argv[1]);
    int M = atoi(argv[2]);
    int add = atoi(argv[3]);
    int print = atoi(argv[4]);
    int move = atoi(argv[5]);
    assert(1 <= N && N <= 1000000);
    assert(0 <= M && M <= 1000000);
    assert(add + print + move == 100);
    cout << N << " " << M << '\n';

    set<int> job_id_set;
    set<int> priority_set;
    for(int i = 1; i <= M; i++){
        int op = rnd.next(1, 100);
        if(op < add) op = 1;
        else if(op < (add + print)) op = 2;
        else op = 3;
        if(op == 1){
            int job_id = 1, priority = 1, printer_id = rnd.next(1, N);
            while(job_id_set.count(job_id)) job_id = rnd.next(1, MAX_P);
            while(priority_set.count(priority)) priority = rnd.next(1, MAX_P);
            job_id_set.insert(job_id);
            priority_set.insert(priority);
            cout << op << " " << job_id << " " << priority << " " << printer_id << "\n";
        }
        if(op == 2){
            int printer_id = rnd.next(1, N);
            cout << op << " " << printer_id << "\n";
        }
        if(op == 3){
            int id1 = rnd.next(1, N);
            int id2 = rnd.next(1, N);
            while(id1 == id2) id2 = rnd.next(1, N);
            cout << op << " " << id1 << " " << id2 << "\n";
        }
    }
    return 0;
}
