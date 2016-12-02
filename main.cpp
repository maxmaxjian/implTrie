#include <iostream>
#include <stack>
#include <queue>
#include <memory>
#include <algorithm>

struct TrieNode {
    std::string str;
    std::vector<std::shared_ptr<TrieNode>> children;
    TrieNode(const std::string & s)
        : str(s) {}

    void add(const std::shared_ptr<TrieNode> & child) {
        children.push_back(child);
    }

    void print() {
        if (!children.empty()) {
            std::cout << str << " -> ";
            std::for_each(children.begin(), children.end(), [](const std::shared_ptr<TrieNode> & p){
                std::cout << p->str << " ";
            });
            std::cout << std::endl;
        }
    }
};

using pNode = std::shared_ptr<TrieNode>;

class Trie {
  public:
    Trie() {
        root = std::make_shared<TrieNode>("");
    }

    void insert(const std::string & word) {
        size_t len = word.size();
        while (!search(word.substr(0, len)))
            len--;
        pNode curr = find(root, word.substr(0,len)), next;
        while (len < word.size()) {
            next = std::make_shared<TrieNode>(word.substr(0,len+1));
            curr->add(next);
            curr = next;
            len++;
        }
    }

    bool search(const std::string & word) {
        std::stack<pNode> st;
        st.push(root);
        while (!st.empty()) {
            auto curr = st.top();
            st.pop();
            if (curr != nullptr) {
                if (!curr->str.compare(word))
                    return true;
                else if (word.find(curr->str) != std::string::npos)
                    std::for_each(curr->children.begin(), curr->children.end(),
                                  [&](const pNode & pn){
                                      st.push(pn);
                                  });
            }
        }
        return false;
    }

    bool startsWith(const std::string & prefix) {
        std::queue<pNode> qu;
        qu.push(root);
        while (!qu.empty()) {
            auto curr = qu.front();
            qu.pop();
            if (curr != nullptr) {
                if (!curr->str.compare(prefix))
                    return true;
                else if (prefix.find(curr->str) != std::string::npos)
                    std::for_each(curr->children.begin(), curr->children.end(),
                                  [&](const pNode & pn){
                                      qu.push(pn);
                                  });
            }
        }
        return false;
    }

  private:
    std::shared_ptr<TrieNode> root;

  private:
    pNode find(const pNode & node, const std::string & s) {
        if (node != nullptr) {
            if (!node->str.compare(s))
                return node;
            else if (s.find(node->str) != std::string::npos){
                for (auto it = node->children.begin(); it != node->children.end(); ++it)
                    if (find(*it, s) != nullptr)
                        return find(*it, s);
            }
            else
                return nullptr;
        }
        return nullptr;
    }

  public:
    void print() {
        root->print();
        std::for_each(root->children.begin(), root->children.end(), [](const pNode & p){p->print();});
    }
};


int main() {
    Trie trie;
    trie.insert("A");
    trie.print();
    std::cout << std::endl;
    trie.insert("to");
    trie.print();
    std::cout << std::endl;
    trie.insert("tea");
    trie.print();
    std::cout << std::endl;
    trie.insert("ted");
    trie.print();
    std::cout << std::endl;
    trie.insert("ten");
    trie.print();
    std::cout << std::endl;
    trie.insert("in");
    trie.print();
    std::cout << std::endl;
    trie.insert("inn");
    trie.print();
    std::cout << std::endl;
    
    std::cout << std::boolalpha;
    std::string s{"something"};
    std::cout << "Found " << s << "? "<< trie.search(s) << std::endl;
    std::string t{"to"};
    std::cout << "Found " << t << "? "<< trie.search(t) << std::endl;
    std::string prefix{"it"};
    std::cout << "Found " << prefix << "? "<< trie.search(prefix) << std::endl;
}
