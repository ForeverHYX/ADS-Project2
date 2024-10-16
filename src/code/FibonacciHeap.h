struct FibonacciHeap;
struct FibonacciHeapNode;

struct FibonacciHeap{
    int keyNum;   //堆中结点个数
    FibonacciHeapNode *min;//最小堆，根结点
    int maxNumOfDegree;   //最大度
};


struct FibonacciHeapNode{
    int key;       //结点
    int degree;    //度
    FibonacciHeapNode *left;  //左兄弟
    FibonacciHeapNode *right; //右兄弟
    FibonacciHeapNode *parent; //父结点
    FibonacciHeapNode *child;  //第一个孩子结点
    bool marked;           //是否被删除第1个孩子

    FibonacciHeapNode(){
        left = right = this;
    }


};

