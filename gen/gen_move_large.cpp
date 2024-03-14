#include "testlib.h"
#include <climits>
#include <cassert>
#include <set>
#include <queue>
using namespace std;

#define MAX_P 1000000000
#define MAX_N 1000001

int main(int argc, char* argv[]) {  // gen_move_large seed
    registerGen(argc, argv, 1);
    assert(argc == 2);
    int N = 100000;
    int M = 1000000;
    cout << N << " " << M << '\n';

    set<int> job_id_set;
    set<int> priority_set;
    set<int> non_empty_printer;
    int cur = atoi(argv[1]);
    for(int i = 1; i <= M; i++){
        int op;
        if(i < M * 9 / 10){ // add only
            op = 1;
        }
        else{
            if(i % 2 == 0) op = 2;
            else op = 3;
        }
        if(op == 1){
            int job_id = 1, priority = 1, printer_id = cur;
            while(job_id_set.count(job_id)) job_id = rnd.next(1, MAX_P);
            while(priority_set.count(priority)) priority = rnd.next(1, MAX_P);
            job_id_set.insert(job_id);
            priority_set.insert(priority);
            cout << op << " " << job_id << " " << priority << " " << printer_id << "\n";
        }
        if(op == 2){
            int printer_id = cur;
            cout << op << " " << printer_id << "\n";
        }
        if(op == 3){
            pair<int, int> index;
            index.first = cur;
            index.second = rnd.next(1, N);
            while(index.first == index.second) index.second = rnd.next(1, N);
            cur = index.second;
            cout << op << " " << index.first << " " << index.second << "\n";
        }
    }
    return 0;
}
