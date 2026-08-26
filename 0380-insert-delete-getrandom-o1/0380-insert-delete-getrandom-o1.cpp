class RandomizedSet {
    vector<int> vals;
    unordered_map<int, int> map;
public:
    RandomizedSet() {
        map.clear();
    }
    
    bool insert(int val) {
        if (map.find(val) != map.end()) return false;
        vals.push_back(val);
        map[val] = vals.size()-1;
        return true;
    }
    
    bool remove(int val) {
        if (map.find(val) == map.end()) return false;
        int idxToRemove = map[val];
        int last = vals.back();
        vals[idxToRemove] = last;
        map[last] = idxToRemove;
        vals.pop_back();
        map.erase(val);
        return true;
    }
    
    int getRandom() {
        int idx = rand()%vals.size();
        return vals[idx];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */