// #include <unordered_map>
//
// // should arrange this according to LRU
// class ValueList {
//       public:
//         int value;
//         ValueList *prev;
//         ValueList *next;
//
//         ValueList(int value) { this->value = value; }
//
//         ValueList *head = new ValueList(-1);
//         ValueList *tail = new ValueList(-1);
//
//         void addNode(ValueList *newnode) {
//                 ValueList *temp = head->next;
//
//                 newnode->prev = head;
//                 newnode->next = temp;
//
//                 temp->prev = newnode;
//                 head->next = newnode;
//         }
//
//         void deleteNode(ValueList *oldnode) {
//                 ValueList *prevv = oldnode->prev;
//                 ValueList *nextt = oldnode->next;
//
//                 prevv->next = nextt;
//                 nextt->prev = prevv;
//         }
// };
//
// class FrequencyList {
//         int frequency;
//         int key;
//         ValueList *values;
//
//         FrequencyList *prev;
//         FrequencyList *next;
// };
//
// class LFUCache {
//         int capacity;
//         std::unordered_map<int, FrequencyList *> cache;
//
//       public:
//         LFUCache(int capacity) {}
//
//         int get(int key) {}
//
//         void put(int key, int value) {}
// };

#include <iterator>
#include <list>
#include <unordered_map>

class LFUCache {
        int capacity, minFreq;

        struct Element {
                int value, fr;
                std::list<int>::iterator it;
        };

        std::unordered_map<int, Element> cache;
        std::unordered_map<int, std::list<int>> freq;

      public:
        LFUCache(int capacity) { this->capacity = capacity; }

        int get(int key) {
                if (cache.find(key) == cache.end())
                        return -1;
                freq[cache[key].fr].erase(cache[key].it);
                cache[key].fr++;
                freq[cache[key].fr].push_back(key);
                cache[key].it = std::prev(freq[cache[key].fr].end());
                minFreq += freq[minFreq].empty();
                return cache[key].value;
        }

        void put(int key, int value) {
                if (get(key) != -1) {
                        cache[key].value = value;
                        return;
                }

                if (cache.size() == capacity) {
                        cache.erase(freq[minFreq].front());
                        freq[minFreq].pop_front();
                }

                freq[1].push_back(key);
                cache[key] = {value, 1, std::prev(freq[1].end())};
                minFreq = 1;
        }
};
