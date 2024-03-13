#include "testlib.h"
#include <climits>
#include <cassert>
#include <set>
using namespace std;

#define MAX_P 1000000000
#define MAX_N 1000001

int printer_count[MAX_N] = {0};

pair<int, int>find_min_second(int N){
    int min = INT_MAX, min_index = 0, sec = INT_MAX, sec_index = 0;
    for(int i = 1; i <= N; i++){
        if(printer_count[i] == 0) continue;
        if(printer_count[i] < min){
            min = printer_count[i];
            min_index = i;
        }
        else if(printer_count[i] < sec){
            sec = printer_count[i];
            sec_index = i;
        }
    }
    if(min_index == 0 || sec_index == 0) return make_pair(0, 0);
    return make_pair(min_index, sec_index);
}

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
        int op, sum;
        if(i < M * add / 100){ // more add
            op = rnd.next(1, 1000);
            if(op == 1) op = 2; // print
            else op = 1;
        }
        else if(i < M * (add + move) / 100){ // more move
            op = rnd.next(1, 1000);
            if(op == 1) op = 2; // print
            else op = 3;
        }
        else{
            op = 2; // print
        }
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
            pair<int, int> index = find_min_second(N);
            if(!index.first){
                index.first = rnd.next(1, N);
                index.second = rnd.next(1, N);
                while(index.first == index.second) index.second = rnd.next(1, N);
            }
            cout << op << " " << index.first << " " << index.second << "\n";
        }
    }
    return 0;
}
