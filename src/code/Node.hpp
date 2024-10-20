struct Node{
    unsigned long long id;
    long long dist;
    bool known;

    Node(unsigned long long id, long long dist, bool known = false): id(id), dist(dist), known(known){};

    Node(): id(-1), dist(-1), known(false){};

    bool operator<(const Node& x){
        return this->dist < x.dist;
    }
    
    bool operator<=(const Node& x){
        return this->dist <= x.dist;
    }
    
    bool operator>(const Node& x){
        return this->dist > x.dist;
    }
    
    bool operator>=(const Node& x){
        return this->dist >= x.dist;
    }
    
    bool operator==(const Node& x){
        return this->dist == x.dist;
    }
};
