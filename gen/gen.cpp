#include "testlib.h"
#include <climits>
#include <cassert>
#include <set>
#include <queue>
using namespace std;

#define MAX_P 1000000000
#define MAX_N 1000001

int printer_count[MAX_N] = {0};

struct ComparePairs {
    bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) const {
        if (a.second == b.second) {
            return a.first > b.first;
        }
        return a.second > b.second;
    }
};

std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, ComparePairs> pq; // (id, count)

pair<int, int>find_min_second(int N){
    int min_index = 0, sec_index = 0, finish = 0;
    while(finish < 2 && !pq.empty()){
        if(pq.top().second != 0 && pq.top().second == printer_count[pq.top().first]){
            if(finish == 0) min_index = pq.top().first;
            else{
                if(min_index != pq.top().first) sec_index = pq.top().first;
                else break;
            }
            finish += 1;
        }
        pq.pop();
    }
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
    set<int> non_empty_printer;
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
            printer_count[printer_id] += 1;
            cout << op << " " << job_id << " " << priority << " " << printer_id << "\n";
            pq.push({printer_id, printer_count[printer_id]});
            non_empty_printer.insert(printer_id);
        }
        if(op == 2){
            int printer_id = rnd.next(1, N);
            if(rnd.next(0, 1) && non_empty_printer.upper_bound(printer_id) != non_empty_printer.end()){
                printer_id = *non_empty_printer.upper_bound(printer_id);
            }
            if(printer_count[printer_id] > 0) printer_count[printer_id] -= 1;
            if(printer_count[printer_id] == 0) non_empty_printer.erase(printer_id);
            cout << op << " " << printer_id << "\n";
            pq.push({printer_id, printer_count[printer_id]});
        }
        if(op == 3){
            pair<int, int> index = find_min_second(N);
            if(!index.second){
                index.first = rnd.next(1, N);
                index.second = rnd.next(1, N);
                while(index.first == index.second) index.second = rnd.next(1, N);
            }
            cout << op << " " << index.second << " " << index.first << "\n";
            printer_count[index.first] += printer_count[index.second];
            printer_count[index.second] = 0;
            non_empty_printer.erase(index.second);
            pq.push({index.first, printer_count[index.first]});
        }
    }
    return 0;
}
