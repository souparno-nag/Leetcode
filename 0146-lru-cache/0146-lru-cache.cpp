struct Node {
    int key, value;
    Node *prev, *next;
    Node(int k, int v) {
        key = k;
        value = v;
        prev = NULL;
        next = NULL; 
    }
};
class LRUCache {
    int capacity;
    Node *head = new Node(-1, -1), *tail = new Node(-1, -1);
    unordered_map<int, Node*> map;

    void insertAfterHead(Node* node) {
        Node* temp = head->next;
        // head and node
        head->next = node;
        node->prev = head;
        // node and temp;
        node->next = temp;
        temp->prev = node;
    }
    void deleteNode(Node* node) {
        Node* prevNode = node->prev;
        Node* nextNode = node->next;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
    }
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
        head->next = tail;
        tail->prev = head;
        map.clear();
    }
    
    int get(int key) {
        if (map.find(key) == map.end()) return -1;
        Node* node = map[key];
        deleteNode(node);
        insertAfterHead(node);
        return node->value;
    }
    
    void put(int key, int value) {
        if (map.find(key) != map.end()) {
            Node* node = map[key];
            node->value = value;
            deleteNode(node);
            insertAfterHead(node);
        } else {
            if (map.size() == capacity) {
                Node* delNode = tail->prev;
                deleteNode(delNode);
                Node* newNode = new Node(key, value);
                insertAfterHead(newNode);
                map.erase(delNode->key);
                map[key] = newNode;
            } else {
                Node* newNode = new Node(key, value);
                insertAfterHead(newNode);
                map[key] = newNode;
            }
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */