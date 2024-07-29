#include <iostream>
#include <cstdlib>
using namespace std;

struct vertex{  // структура вершины
    int data;
    vertex* left;
    vertex* right;

    vertex(int value) : data(value), left(nullptr), right(nullptr){}
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

int SumPathLen(vertex* root, int l){ // функция суммы длин путей
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
    vertex* root = new vertex(1);
    root -> left = new vertex(2);
    root -> left -> left = new vertex(3);
    root -> left -> right = new vertex(4);
    root -> left -> left -> right = new vertex(5);
    root -> left -> left -> right -> left = new vertex(6);

    // vertex* root = new vertex(1);
    // root -> left = new vertex(2);
    // root -> right = new vertex(3);
    // root -> left -> left = new vertex(4);
    // root -> right -> right = new vertex(5);
    // root -> right -> right -> left = new vertex(6);

    cout << "pre-order traversal: ";
    pre_order(root);
    cout << endl;

    cout << "in-order traversal: ";
    in_order(root);
    cout << endl;

    cout << "post-order traversal: ";
    post_order(root);
    cout << endl;

    cout << "Size: " << treeSize(root) << endl;

    cout << "Height: " << treeHeight(root) << endl;

    int averageHeigh = SumPathLen(root, 1) / treeSize(root);
    cout << "Average Height: " << averageHeigh << endl;

    cout << "Check summ: " << checkSumm(root) << endl;
}