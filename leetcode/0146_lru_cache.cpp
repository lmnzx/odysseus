#include <iostream>
#include <unordered_map>

class Node {
      public:
        int key;
        int val;
        Node *prev;
        Node *next;

        Node(int key, int val) {
                this->key = key;
                this->val = val;
        }
};

class LRUCache {

        Node *head = new Node(-1, -1);
        Node *tail = new Node(-1, -1);
        std::unordered_map<int, Node *> cache;
        int capacity;

        void addNode(Node *newnode) {
                Node *temp = head->next;

                newnode->next = temp;
                newnode->prev = head;

                head->next = newnode;
                temp->prev = newnode;
        }

        void deleteNode(Node *delnode) {
                Node *prevv = delnode->prev;
                Node *nextt = delnode->next;

                prevv->next = nextt;
                nextt->prev = prevv;
        }

      public:
        LRUCache(int capacity) {
                this->capacity = capacity > 1 ? capacity : 0;
                head->next = tail;
                tail->prev = head;
        }

        int get(int key) {
                if (cache.find(key) != cache.end()) {
                        Node *res = cache[key];

                        cache.erase(key);
                        deleteNode(res);
                        addNode(res);
                        cache[key] = head->next;

                        return res->val;
                }
                return -1;
        }

        void put(int key, int value) {
                if (cache.find(key) != cache.end()) {
                        Node *curr = cache[key];
                        cache.erase(key);
                        deleteNode(curr);
                }

                if (cache.size() == capacity) {
                        cache.erase(tail->prev->key);
                        deleteNode(tail->prev);
                }

                addNode(new Node(key, value));
                cache[key] = head->next;
        }

        int getMostRecent() {
                int recentKey = head->next->key;
                if (recentKey == -1) {
                        return -1;
                }
                return cache[recentKey]->val;
        }
};

int main(int argc, char *argv[]) {
        LRUCache *cache = new LRUCache(3);
        std::cout << cache->getMostRecent() << "\n";
        cache->put(2, 4444);
        int val = cache->get(2);
        std::cout << val << "\n";
        cache->put(4, 11111);
        val = cache->get(4);
        std::cout << val << "\n";
        val = cache->get(34);
        std::cout << val << "\n";
        cache->put(4, 111);
        cache->put(1, 223);
        cache->put(3, 45);
        std::cout << cache->get(2) << "\n";
        std::cout << cache->get(1) << "\n";
        std::cout << cache->get(3) << "\n";
        std::cout << cache->getMostRecent() << "\n";
        std::cout << cache->getMostRecent() << "\n";
        return 0;
}
