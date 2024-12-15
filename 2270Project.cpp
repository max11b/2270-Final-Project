#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Node {
    int playerId;
    int score;
    bool color; 
    int subtreeSize;
    Node *left, *right, *parent;

    Node(int id, int sc) : playerId(id), score(sc), color(true), subtreeSize(1), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node *root;
    Node *TNULL; 

    void updateSubtreeSize(Node *node) {
        if (node != TNULL) {
            node->subtreeSize = 1;
            if (node->left != TNULL) node->subtreeSize += node->left->subtreeSize;
            if (node->right != TNULL) node->subtreeSize += node->right->subtreeSize;
        }
    }

    void leftRotate(Node *x) {
        Node *y = x->right;
        x->right = y->left;
        if (y->left != TNULL) y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;

        updateSubtreeSize(x);
        updateSubtreeSize(y);
    }

    void rightRotate(Node *x) {
        Node *y = x->left;
        x->left = y->right;
        if (y->right != TNULL) y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;

        updateSubtreeSize(x);
        updateSubtreeSize(y);
    }

    void insertFix(Node *k) {
        Node *u;
        while (k->parent->color == true) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left; // Uncle
                if (u->color == true) {
                    u->color = false;
                    k->parent->color = false;
                    k->parent->parent->color = true;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = false;
                    k->parent->parent->color = true;
                    leftRotate(k->parent->parent);
                }
            } else {
                u = k->parent->parent->right; // Uncle
                if (u->color == true) {
                    u->color = false;
                    k->parent->color = false;
                    k->parent->parent->color = true;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = false;
                    k->parent->parent->color = true;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) break;
        }
        root->color = false;
    }

    Node *insert(Node *node, int playerId, int score) {
        if (node == TNULL) {
            return new Node(playerId, score);
        }

        if (score < node->score) {
            Node *leftChild = insert(node->left, playerId, score);
            node->left = leftChild;
            leftChild->parent = node;
        } else {
            Node *rightChild = insert(node->right, playerId, score);
            node->right = rightChild;
            rightChild->parent = node;
        }

        updateSubtreeSize(node);
        return node;
    }

    int getRank(Node *node, int score) {
        if (node == TNULL) return 0;

        if (score < node->score) {
            return getRank(node->left, score);
        } else {
            int leftSize = (node->left != TNULL) ? node->left->subtreeSize : 0;
            return leftSize + 1 + getRank(node->right, score);
        }
    }

    void topK(Node *node, vector<pair<int, int>> &result, int &k) {
        if (node == TNULL || k == 0) return;

        topK(node->right, result, k);
        if (k > 0) {
            result.push_back({node->playerId, node->score});
            k--;
        }
        topK(node->left, result, k);
    }

public:
    RedBlackTree() {
        TNULL = new Node(-1, -1);
        TNULL->color = false;
        TNULL->subtreeSize = 0;
        root = TNULL;
    }

    void insert(int playerId, int score) {
        Node *node = new Node(playerId, score);
        root = insert(root, playerId, score);
        node->parent = nullptr;
        node->left = TNULL;
        node->right = TNULL;
        node->color = true; 
        insertFix(node);
    }

    int getRank(int score) {
        return getRank(root, score);
    }

    vector<pair<int, int>> getTopK(int k) {
        vector<pair<int, int>> result;
        topK(root, result, k);
        return result;
    }
};

int main() {
    RedBlackTree leaderboard;

    leaderboard.insert(1, 100);
    leaderboard.insert(2, 200);
    leaderboard.insert(3, 150);
    leaderboard.insert(4, 120);

    cout << "Rank of player with score 150: " << leaderboard.getRank(150) << endl;

    vector<pair<int, int>> topPlayers = leaderboard.getTopK(2);
    cout << "Top 2 players: \n";
    for (auto &p : topPlayers) {
        cout << "Player ID: " << p.first << ", Score: " << p.second << endl;
    }

    return 0;
}

