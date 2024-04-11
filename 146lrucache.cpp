
#include <unordered_map>;
using namespace std;

class LRUCache {
public:
    struct Node
    {
        Node* pre;
        Node* next;
        int key;
        int val;
        Node(int x, int y): key(x), val(y){}
    };

    Node* head;
    Node* tail;
    unordered_map<int, Node* > map;

    int cap;

    LRUCache(int capacity) {
        cap = capacity;
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        head->next = tail;
        tail->pre = head;
    }
    
    int get(int key) {
        if (map.find(key) != map.end()) {
            moveToHead(map[key]);
            return map[key]->val;
        } else {
            return -1;
        }
    }
    
    void put(int key, int value) {
        if (map.find(key) == map.end()) {
            Node* node = new Node(key, value);
            addNode(node);
            map[key] = node;
            if (map.size() > cap) {
                Node* tail = popTail();
                map.erase(tail->key);
            }
        } else {
            Node *node = map[key];
            node->val = value;
            moveToHead(node);
        }
    }

private:
    void moveToHead(Node* node) {
        removeNode(node);
        addNode(node);
    }

    Node* popTail() {
        Node *node = tail->pre;
        removeNode(node);
        return node;
    }

    void addNode(Node* node) {
        Node* next = head->next;

        head->next = node;
        node->pre = head;

        node->next = next;
        next->pre = node;
    }

    void removeNode(Node* node) {
        Node* pre = node->pre;
        Node* next = node->next;

        pre->next = next;
        next->pre = pre;
    }
};