#include <bits/stdc++.h>
using namespace std;

#define TIME_LIMIT 1.98
#define LOOP_INTERVAL 100
#define START_TEMP 1000
#define END_TEMP 0.1
#define MT_MAX 0xffffffff

// utilities

std::mt19937 mt;
chrono::system_clock::time_point start;

int gen_range(int l, int r) {
    assert(l < r);
    return l + mt() % (r - l);
}

int gen_range(int r) {
    return gen_range(0, r);
}

double gen_f(double l, double r) {
    assert(l < r);
    return l + (double)mt() / MT_MAX * (r - l);
}

double gen_f(double r) {
    return gen_f(0, r);
}

double elapsed_seconds() {
    return static_cast<double>(chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now() - start).count() / 1e6);
}

template <typename T>
auto find_iter(vector<T> &v, T val) {
    return find(v.begin(), v.end(), val);
}

template <typename T>
bool contains(vector<T> &v, T val) {
    return find_iter(v, val) != v.end();
}

// log

void write_score_log(vector<int> &score_log) {
    ofstream file_os;
    string file_name = "score.log";
    file_os.open(file_name, ios::out);

    for (int e : score_log) file_os << e << " ";
    file_os << endl;
    file_os.close();
}

// optimize

double update_temp(double progress) {
    return pow(START_TEMP, (1 - progress)) * pow(END_TEMP, progress);
}

bool should_adopt_new_state(double current_score, double new_score, double temp) {
    double score_diff = new_score - current_score;
    return exp(score_diff / temp) > gen_f(1);
}

struct State {
    double get_score() {
        return 0;
    }
};

int main() {
    start = chrono::system_clock::now();

    // read_input;

    State state = State();

    // solve;
    {
        vector<int> score_log;
        int loop_count = 0;
        double progress = 0;
        double temp = START_TEMP;

        while (progress < 1) {
            bool is_interval = loop_count % LOOP_INTERVAL == 0;
            if (is_interval) {
                progress = elapsed_seconds() / TIME_LIMIT;
                temp = update_temp(progress);
                score_log.push_back(state.get_score());
            }

            double current_score = state.get_score();

            // perform action;

            double new_score = state.get_score();

            if (should_adopt_new_state(current_score, new_score, temp)) {
                // adopt;
            } else {
                // rollback;
            }

            loop_count++;
        }

        write_score_log(score_log);
    }

    // output;
}