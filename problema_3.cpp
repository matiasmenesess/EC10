//Integrantes:
//1. Olivares Sarmiento, Javier Ignacio Leon
//2. Silva Reyes, Santiago Miguel
//3. Meneses Roncal, Matias Alonso
    

#include <iostream>
#include <vector>
using namespace std;

#define ALPHABET_SIZE 26

// Nodo del Trie
struct TrieNode {
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
        // Inicializar todos los hijos con nullptr
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            children[i] = nullptr;
        }
    }
};

class Trie {
private:
    TrieNode* root;


public:
    Trie() {
        root = new TrieNode();
    }

    // Insertar una palabra en el Trie
    void insert(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            int index = ch - 'a';  // Convertir el carácter a índice (0-25)
            if (node->children[index] == nullptr) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        node->isEndOfWord = true;  // Marcar el fin de la palabra
    }

    // Buscar una palabra exacta en el Trie
    bool search(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (node->children[index] == nullptr) {
                return false;  // La palabra no existe
            }
            node = node->children[index];
        }
        return node->isEndOfWord;  // Verificar si es el fin de la palabra
    }

    // Buscar si un prefijo existe en el Trie
    bool startsWith(const string& prefix) {
        TrieNode* node = root;
        for (char ch : prefix) {
            int index = ch - 'a';
            if (node->children[index] == nullptr) {
                return false;  // El prefijo no existe
            }
            node = node->children[index];
        }
        return true;  // El prefijo existe
    }

};

class MagicDictionary {
    Trie trie;
    vector<string> palabras;
public:
    MagicDictionary() {
    }

    void buildDict(vector<string> dictionary) {
        palabras = dictionary;
        for (auto word : dictionary) {
            trie.insert(word);
        }
    }

    bool search(string searchWord) {
        for (auto palabra : palabras) {
            if (palabra.size() == searchWord.size()) {
                int contadorCharDiferente = 0;
                for (int i = 0; i < palabra.size(); i++) {
                    if (palabra[i] != searchWord[i]) {
                        contadorCharDiferente++;
                        if (contadorCharDiferente > 1) {
                            break;
                        }
                    }
                }
                if (contadorCharDiferente == 1) return true;
            }
        }
        return false;
    }
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary* obj = new MagicDictionary();
 * obj->buildDict(dictionary);
 * bool param_2 = obj->search(searchWord);
 */
