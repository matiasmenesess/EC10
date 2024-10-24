//Integrantes:
//1. Olivares Sarmiento, Javier Ignacio Leon
//2. Silva Reyes, Santiago Miguel
//3. Meneses Roncal, Matias Alonso

#include <iostream>
#include <vector>
#include <algorithm>
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

    vector<string> palabras_con_prefijo(const string& prefix, int npalabras) {
        TrieNode* node = root;
        vector<string> resultado;
        for (char ch : prefix) {
            int index = ch - 'a';
            if (node->children[index] == nullptr) {
                return resultado;
            }
            node = node->children[index];
        }
        palabras(node, prefix, resultado, npalabras);
        return resultado;
    }

    void palabras(TrieNode* node, string palabra, vector<string>& result, int npalabras) {
        if (result.size() >= npalabras) return;
        if (node->isEndOfWord) {
            result.push_back(palabra);
        }

        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (node->children[i] != nullptr) {
                char nextChar = 'a' + i;
                palabras(node->children[i], palabra + nextChar, result, npalabras);
            }
        }
    }

};

class Solution {
public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        sort(products.begin(), products.end());

        Trie trie;
        for (const string& product : products) {
            trie.insert(product);
        }

        vector<vector<string>> resultado;
        string prefix = "";
        for (char ch : searchWord) {
            prefix += ch;
            vector<string> palabras = trie.palabras_con_prefijo(prefix, 3);
            resultado.push_back(palabras);
        }

        return resultado;
    }
};

