struct Query {
    int l, r, id;
};

class MoAlgorithm {
private:
    int n, block_size;
    vector<int> arr;
    vector<Query> queries;
    vector<long long> answers;

    vector<int> cnt; 
    long long current_ans; 

    static bool compare(const Query& a, const Query& b, int block_size) {
        int block_a = a.l / block_size;
        int block_b = b.l / block_size;
        if (block_a != block_b)
            return block_a < block_b;
        return (block_a & 1) ? (a.r < b.r) : (a.r > b.r);
    }

    void add(int idx) {
        int x = arr[idx];
        if (cnt[x] == 0) {
            current_ans++;
        }
        cnt[x]++;
    }

    void remove(int idx) {
        int x = arr[idx];
        cnt[x]--;
        if (cnt[x] == 0) {
            current_ans--;
        }
    }

public:
    MoAlgorithm(const vector<int>& input_arr, int max_val) {
        arr = input_arr;
        n = arr.size();
        block_size = max(1, (int)sqrt(n));
        
        cnt.assign(max_val + 1, 0);
        current_ans = 0;
    }

    void add_query(int l, int r, int id) {
        queries.push_back({l, r, id});
    }

    vector<long long> solve() {
        int q = queries.size();
        answers.resize(q);

        sort(queries.begin(), queries.end(), [this](const Query& a, const Query& b) {
            return compare(a, b, this->block_size);
        });

        int L = 0, R = -1;

        for (const auto& q : queries) {
            while (L > q.l) {
                L--;
                add(L);
            }
            while (R < q.r) {
                R++;
                add(R);
            }
            while (L < q.l) {
                remove(L);
                L++;
            }
            while (R > q.r) {
                remove(R);
                R--;
            }

            answers[q.id] = current_ans;
        }

        return answers;
    }
};
