
#include <deque>
#include <queue>
#include <iostream>

using namespace std;
class Node {
public:
	Node(int v): value(v), left(nullptr), right(nullptr) {}

	int value;
	Node *left;
	Node *right;
};

void printTree(Node *root) {
	if (!root) {
		return;
	}
	queue<Node *> q;
	//vector<int> res;
	q.push(root);
	int layer = 0;
	while (!q.empty()) {
		int size = q.size();
		
		vector<int> line;
		while (size > 0) {
			Node *node = q.front();
			q.pop();
			if (node) {
				line.push_back(node->value);
			}
			if (node && node->left) {
				q.push(node->left);
			}
			if (node && node->right) {
				q.push(node->right);
			}
			--size;
		}
		if (layer % 2 != 0) {
			for (auto l : line) {
				cout << "layer: " << layer << " val: " << l << endl;
			}
		} else {
			for (auto it = line.rbegin(); it != line.rend(); ++it) {
				cout << "layer: " << layer << " val: " << *it << endl;
			}
		}
		++layer;
	}
}

int main() {
	//   0
	// 1   2
	//3 4 5 6
	Node *root = new Node(0);
	Node *left = new Node(1);
	Node *right = new Node(2);
	root->left = left;
	root->right = right;
	Node *leftL = new Node(3);
	Node *leftR = new Node(4);
	Node *rightL = new Node(5);
	Node *rightR = new Node(6);
	left->left = leftL;
	left->right = leftR;
	right->left = rightL;
	right->right = rightR;

	printTree(root);
}