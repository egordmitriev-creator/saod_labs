#include <iostream>
#include <vector>
using namespace std;

struct vertex{  // структура вершины
    int data;
    int index;
    vertex* left;
    vertex* right;

    vertex(int value, int idx) : data(value), index(idx), left(nullptr), right(nullptr){}
};

vertex* ISDP(vector<int>& sortArr, int l, int r, int index){ // построение ИСДП
    if (l > r){
        return nullptr;
    }
    int m = (l + r) / 2;
    vertex* root = new vertex(sortArr[m], index);
    //if (root -> left == nullptr){
        //root -> right = ISDP(sortArr, 0, l, 2 * index);
    //}else{
        root -> left = ISDP(sortArr, l, m - 1, 2 * index);
        root -> right = ISDP(sortArr, m + 1, r, 2 * index + 1);
    //}

    return root;
};

void pre_order(vertex* root){   // обход сверху вниз
    if (root == nullptr){
        return;
    }
    cout << root -> data << " ";
    pre_order(root -> left);
    pre_order(root -> right);
}

void in_order(vertex* root){    // обход слева направо
    if (root == nullptr){
        return;
    }
    in_order(root -> left);
    cout << root -> data << " ";
    in_order(root -> right);
}

void in_order_idx(vertex* root){    // обход слева направо
    if (root == nullptr){
        return;
    }
    in_order_idx(root -> left);
    cout << root -> index << " ";
    in_order_idx(root -> right);
}


void post_order(vertex* root){  // обход снизу вверх
    if (root == nullptr){
        return;
    }
    post_order(root -> left);
    post_order(root -> right);
    cout << root -> data << " ";
}

int treeSize(vertex* root){ // определение размера дерева
    if (root == nullptr){
        return 0;
    }
    int leftSize = treeSize(root -> left);
    int rightSize = treeSize(root -> right);
    return leftSize + rightSize + 1;
}

int treeHeight(vertex* root){   // определение высоты дерева
    if (root == nullptr){
        return 0;
    }
    int leftHeight = treeHeight(root -> left);
    int rightHeight = treeHeight(root -> right);
    return max(leftHeight, rightHeight) + 1;
}

float SumPathLen(vertex* root, int l){ // функция суммы длин путей
    if (root == nullptr){
        return 0;
    }
    int spl = l + SumPathLen(root -> left, l + 1) + SumPathLen(root -> right, l + 1);
    return spl;
}

int checkSumm(vertex* root){    // определение контрольной суммы
    if (root == nullptr){
        return 0;
    }
    int summ = root -> data + checkSumm(root -> left) + checkSumm(root -> right);
    return summ;
} 

int main(){

    vector<int> sortArr; // генерация массива
    for (int i = 1; i <= 100; i++){
        sortArr.push_back(i);
    }

    vertex* root = ISDP(sortArr, 0, sortArr.size() - 1, 1);

    // cout << "pre-order traversal: ";
    // pre_order(root);
    // cout << endl;

    cout << "in-order traversal: ";
    in_order(root);
    cout << endl;

    cout << "in-order traversal for index: ";
    in_order_idx(root);
    cout << endl;

    // cout << "post-order traversal: ";
    // post_order(root);
    // cout << endl;

    cout << "Size: " << treeSize(root) << endl;

    cout << "Height: " << treeHeight(root) << endl;

    float averageHeigh = SumPathLen(root, 1) / treeSize(root);
    cout << "Average Height: " << averageHeigh << endl;

    cout << "Check summ: " << checkSumm(root) << endl;
}