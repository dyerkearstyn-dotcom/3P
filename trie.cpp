/*
 * trie.cpp
 *
 * Method definitions for the trie class.
 *
 * Author: <your name here>
 */

#include "trie.h"
#include <cctype>

trie::trie(){
    root = new Node();
}

trie::~trie(){
    delete root;
}

void trie::insert(const std::string& s) {
    Node* current = root;
    
    for (char c : s) {
        char lower_c = tolower(c);
        int index = lower_c - 'a';
        if (current->children[index] == nullptr) {
            current->children[index] = new Node();
        }
        current = current->children[index];
    }
    current->is_word = true;
}

bool trie::contains(const std::string& s) {
    Node* current = root;
    
    for (char c : s) {
        char lower_c = tolower(c);
        int index = lower_c - 'a';
        if (current->children[index] == nullptr) {
            return false;
        }
        
        current = current->children[index];
    }
    return current->is_word;
}

bool trie::is_prefix(const std::string& s) {
    Node* current = root;
    
    for (char c : s) {
        char lower_c = tolower(c);
        int index = lower_c - 'a';
        if (current->children[index] == nullptr) {
            return false;
        }
        
        current = current->children[index];
    }
    return true;
}

void trie::extend(const std::string& prefix, std::vector<std::string>& result) {
    Node* current = root;
    for (char c : prefix) {
        char lower_c = tolower(c);
        int index = lower_c - 'a';
        if (current->children[index] == nullptr) {
            return;
        }
        
        current = current->children[index];
    }
    std::string current_word = prefix;
    collect_words(current, current_word, result);
}
void trie::collect_words(Node* node, std::string& current_word, std::vector<std::string>& result) {
    if (node->is_word) {
        result.push_back(current_word);
    }
    for (int i = 0; i < 26; i++) {
        if (node->children[i] != nullptr) {
            char c = 'a' + i;
            current_word.push_back(c);
            collect_words(node->children[i], current_word, result);
            current_word.pop_back();
        }
    }
}