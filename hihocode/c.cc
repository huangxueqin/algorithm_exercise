#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int get_entry_height(int r, vector<vector<vector<int>>> &rows, vector<int> &hs);

int get_section_height(vector<int> &section, vector<vector<vector<int>>> &rows, vector<int> &hs) {
    for(int i = 0; i < section.size(); i++) {
        if(hs[section[i]] == -1) {
            get_entry_height(section[i], rows, hs);
        }
    }
    auto comp = [&hs](const int i, const int j) {
        return 1 + std::max(hs[i]-1, hs[j]) < 
            1 + std::max(hs[j]-1, hs[i]);
    };
    std::sort(section.begin(), section.end(), comp);
    int t = 0;
    for(int i = 0; i < section.size(); i++) {
        t = std::max(t, hs[section[i]] - (int) (section.size()-i));
    }
    return section.size() + t;
}

int get_menu_height(vector<vector<int>> &menu, vector<vector<vector<int>>> &rows, vector<int> &hs) {
    vector<int> sectionhs(menu.size());
    vector<int> section_seq(menu.size());
    vector<int> section_sizes(menu.size());
    for(int i = 0; i < menu.size(); i++) {
        section_seq[i] = i;
        sectionhs[i] = get_section_height(menu[i], rows, hs);
    }
    auto comp = [&menu, &sectionhs](const int i, const int j) {
        return menu[i].size() + std::max(sectionhs[i] - (int) menu[i].size(), sectionhs[j]) < 
            menu[j].size() + std::max(sectionhs[j] - (int) menu[j].size(), sectionhs[i]);
    };
    std::sort(section_seq.begin(), section_seq.end(), comp);
    for(int i = section_seq.size()-1; i >= 0; i--) {
        if(i == section_seq.size()-1) {
            section_sizes[i] = menu[section_seq[i]].size();
        }
        else {
            section_sizes[i] = menu[section_seq[i]].size() + section_sizes[i+1];
        }
    }

    int t = 0;
    for(int i = 0; i < section_seq.size(); i++) {
        t = std::max(t, (int) (sectionhs[section_seq[i]] - section_sizes[i]));
    }
    return section_sizes[0] + t;
}

int get_entry_height(int r, vector<vector<vector<int>>> &rows, vector<int> &hs) {
    if(hs[r] == -1) {
        if(rows[r].size() == 0) {
            hs[r] = 1;
        }
        else {
            hs[r] = get_menu_height(rows[r], rows, hs);
        }
    }
    return hs[r];
}


int main(void) {
    int N;
    cin >> N;
    int K;
    cin >> K;
    vector<vector<int>> root(K);
    int count = 0;
    while (count < K) {
        int r;
        vector<int> ivec;
        while((cin >> r, r) && count < K) {
            ivec.push_back(r);
            count++;
        }
        root.push_back(ivec);
    }

    vector<vector<vector<int>>> rows;
    rows.push_back(vector<vector<int>>());
    for(int i = 1; i <= N; i++) {
        cin >> K;
        vector<vector<int>> row;
        int count = 0;
        while(count < K) {
            int r;
            vector<int> ivec;
            while((cin >> r, r) && count < K) {
                ivec.push_back(r);
                count++;
            }
            row.push_back(ivec);
        }
        rows.push_back(row);
    }

    vector<int> hs(N, -1);
    cout << get_menu_height(root, rows, hs) << endl;

    return 0;
}
