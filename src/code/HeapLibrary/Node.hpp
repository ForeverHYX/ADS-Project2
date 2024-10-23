struct Node{
    long  id;
    long  dist;
    bool known;

    Node( long  id, long  dist, bool known = false): id(id), dist(dist), known(known){};

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
