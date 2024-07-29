#include <iostream>
#include <string>
#include <ctime>
#include <unordered_set>

using namespace std;

struct tree
{
    int data;
    tree *left;
    tree *right;
    tree(int val) : data(val), left(NULL), right(NULL) {}
};

struct treeavl
{
    int data;
    int Bal;
    treeavl *left;
    treeavl *right;
    treeavl(int val, int bal) : data(val), Bal(bal), left(NULL), right(NULL) {}
};

int check_sum(tree *root)
{
    if (root == NULL)
    {
        return 0;
    }
    return root->data + check_sum(root->left) + check_sum(root->right);
}

int check_sum(treeavl *root)
{
    if (root == NULL)
    {
        return 0;
    }
    return root->data + check_sum(root->left) + check_sum(root->right);
}

int size(tree *root)
{
    if (root == nullptr)
    {
        return 0;
    }
    int leftSize = size(root->left);
    int rightSize = size(root->right);
    return leftSize + rightSize + 1;
}

int size(treeavl *root)
{
    if (root == nullptr)
    {
        return 0;
    }
    int leftSize = size(root->left);
    int rightSize = size(root->right);
    return leftSize + rightSize + 1;
}

int height(tree *root)
{
    if (root == nullptr)
    {
        return 0;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return max(leftHeight, rightHeight) + 1;
}

int height(treeavl *root)
{
    if (root == nullptr)
    {
        return 0;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return max(leftHeight, rightHeight) + 1;
}

float sumlen(tree *root, int l)
{
    if (root == nullptr)
    {
        return 0;
    }
    return l + sumlen(root->left, l + 1) + sumlen(root->right, l + 1);
}

float sumlen(treeavl *root, int l)
{
    if (root == nullptr)
    {
        return 0;
    }
    return l + sumlen(root->left, l + 1) + sumlen(root->right, l + 1);
}

void left_right(treeavl *root)
{
    if (root == NULL)
    {
        return;
    }
    left_right(root->left);
    cout << root->data << " ";
    left_right(root->right);
}

void SDP(tree *sdp, int Data)
{
    tree **p = &sdp;
    while (*p != NULL)
    {
        if (Data < (*p)->data)
        {
            p = &((*p)->left);
        }
        else if (Data > (*p)->data)
        {
            p = &((*p)->right);
        }
        else
        {
            break;
        }
    }
    if (*p == NULL)
    {
        (*p) = new tree(Data);
    }
}

void ll(treeavl **avl)
{
    treeavl *q = (*avl)->left;
    (*avl)->Bal = 0;
    q->Bal = 0;
    (*avl)->left = q->right;
    q->right = *avl;
    *avl = q;
}

void rr(treeavl **avl)
{
    treeavl *q = (*avl)->right;
    (*avl)->Bal = 0;
    q->Bal = 0;
    (*avl)->right = q->left;
    q->left = *avl;
    *avl = q;
}

void lr(treeavl **p)
{
    treeavl *q = (*p)->left;
    treeavl *r = q->right;
    if (r->Bal < 0)
    {
        (*p)->Bal = 1;
    }
    else
    {
        (*p)->Bal = 0;
    }
    if (r->Bal > 0)
    {
        q->Bal = -1;
    }
    else
    {
        q->Bal = 0;
    }
    r->Bal = 0;
    q->right = r->left;
    (*p)->left = r->right;
    r->left = q;
    r->right = *p;
    (*p) = r;
}

void rl(treeavl **p)
{
    treeavl *q = (*p)->right;
    treeavl *r = q->left;
    if (r->Bal < 0)
    {
        (*p)->Bal = 1;
    }
    else
    {
        (*p)->Bal = 0;
    }
    if (r->Bal > 0)
    {
        q->Bal = -1;
    }
    else
    {
        q->Bal = 0;
    }
    r->Bal = 0;
    q->left = r->right;
    (*p)->right = r->left;
    r->right = q;
    r->left = (*p);
    (*p) = r;
}

void AVL(treeavl *&avl, int Data, bool &Rost)
{
    if (avl == NULL)
    {
        avl = new treeavl(Data, 0);
        Rost = true;
    }
    else if (avl->data > Data)
    {
        AVL(avl->left, Data, Rost);
        if (Rost)
        {
            if (avl->Bal > 0)
            {
                avl->Bal = 0;
                Rost = false;
            }
            else if (avl->Bal == 0)
            {
                avl->Bal = -1;
                Rost = true;
            }
            else
            {
                if (avl->left->Bal < 0)
                {
                    ll(&avl);
                    Rost = false;
                }
                else
                {
                    lr(&avl);
                    Rost = false;
                }
            }
        }
    }
    else if (avl->data < Data)
    {
        AVL(avl->right, Data, Rost);
        if (Rost)
        {
            if (avl->Bal < 0)
            {
                avl->Bal = 0;
                Rost = false;
            }
            else if (avl->Bal == 0)
            {
                avl->Bal = 1;
                Rost = true;
            }
            else
            {
                if (avl->right->Bal > 0)
                {
                    rr(&avl);
                    Rost = false;
                }
                else
                {
                    rl(&avl);
                    Rost = false;
                }
            }
        }
    }
}

void shuffle(int m[], int size)
{
    srand(time(0));
    for (int i = 0; i < size; ++i)
        std::swap(m[i], m[std::rand() % size]);
}

void InsertSort(int *A, int N)
{
    int i, j, temp;
    for (i = 1; i < N; i++)
    {
        temp = A[i];
        j = i - 1;
        while (j > 0 && A[j] > temp)
        {
            A[j + 1] = A[j];
            j = j - 1;
        }
        A[j + 1] = temp;
    }
}

int main()
{
    srand(time(NULL));
    tree *sdp = NULL;
    treeavl *avl = NULL;
    int n = 100;
    int A[n];
    unordered_set<int> s;
    do
    {
        s.insert(rand() % 100 + 1);
    } while (s.size() < 100);
    unordered_set<int>::iterator p;
    int i = 0;
    for (p = s.begin(); p != s.end(); ++p)
    {
        A[i++] = *p;
    }
    // InsertSort(A, n);
    int l = 0, r = n - 1;
    bool Rost = false;
    sdp = new tree(A[0]);
    avl = new treeavl(A[0], 0);
    for (int i = 1; i < 100; i++)
    {
        AVL(avl, A[i], Rost);
        SDP(sdp, A[i]);
    }
    cout << "left_to_right AVL: ";
    left_right(avl);
    printf("\n\n_______________________________________________\n");
    printf("|n = 100 | Size |  Sum  | Height | Av.height  |\n");
    printf("|--------|------|-------|--------|------------|\n");
    printf("|  SDP   | %3d  |  %4d |  %3d   |    %.2f    |\n", size(sdp), check_sum(sdp), height(sdp), sumlen(sdp, 1) / size(sdp));
    printf("|--------|------|-------|--------|------------|\n");
    printf("|  AVL   | %3d  |  %4d |  %3d   |    %.2f    |\n", size(avl), check_sum(avl), height(avl), sumlen(avl, 1) / size(avl));
    printf("|________|______|_______|________|____________|");
    return 0;
}