#ifndef map_h
#define map_h
#include<map>

namespace mymap {
    template <class Key, class T>
    class map {
    private:
        // узел дерева
        class Node {
        public:
            std::pair<Key, T> data;
            Node* left;
            Node* right;
            Node* parent;
        };
        Node* root; // корень дерева
        size_t size_; // количество элементов
        // внутренние функции
        Node* insert(Key key, T value, Node*& leaf, Node* parent);  // вставка элемента
        Node* find(Key key, Node* leaf);                            // поиск
        Node* clear(Node* leaf);                                    // очистка
        bool removeLeaf(Node*& leaf, Key key);                      // удаление узла
    public:
        // итераторы
        class iterator {
        private:
            Node* node;
            Node* root;
        public:
            iterator();
            iterator(const iterator&);
            iterator& operator=(const iterator&);

            iterator& operator++();
            iterator operator++(int);
            std::pair<Key, T>& operator*() const;
            std::pair<Key, T>* operator->() const;
            iterator& operator--();
            iterator operator--(int);

            bool operator==(iterator other) const;
            bool operator!=(iterator other) const;

            friend class map;
        };
        class reversed_iterator {
        private:
            iterator it;
        public:
            reversed_iterator();
            reversed_iterator(const reversed_iterator&);
            reversed_iterator& operator=(const reversed_iterator&);

            reversed_iterator& operator++();
            reversed_iterator operator++(int);
            std::pair<Key, T>& operator*() const;
            std::pair<Key, T>* operator->() const;
            reversed_iterator& operator--();
            reversed_iterator operator--(int);

            bool operator==(reversed_iterator other) const;
            bool operator!=(reversed_iterator other) const;

            friend class map;
        };

        // открытые функции
        map();
        ~map();
        iterator begin();
        iterator end();
        reversed_iterator rbegin();
        reversed_iterator rend();
        size_t size();
        iterator find(Key key);
        void clear();
        size_t erase(Key key);
        void erase(iterator it);
        T& operator[](const Key& key);
    };

    // private functions

    template <class Key, class T>
    typename map<Key, T>::Node* map<Key, T>::insert(Key key, T value, Node*& leaf, Node* parent) {
        // рекурсивный алгоритм добавления элемента в дерево
        if (!leaf)
        {
            leaf = new Node;
            leaf->left = leaf->right = nullptr;
            leaf->data.second = value;
            leaf->data.first = key;
            leaf->parent = parent;
            size_++;
            return leaf;
        }
        else if (key < leaf->data.first)
        {
            return insert(key, value, leaf->left, leaf);
        }
        else if (key > leaf->data.first)
        {
            return insert(key, value, leaf->right, leaf);
        }
        else
            return leaf;
    }

    template <class Key, class T>
    typename map<Key, T>::Node* map<Key, T>::find(Key key, Node* leaf) {
        // рекурсивный алгоритм поиска
        if (!leaf || leaf->data.first == key)
            return leaf;
        if (key < leaf->data.first)
            return find(key, leaf->left);
        else
            return find(key, leaf->right);
    }

    template <class Key, class T>
    typename map<Key, T>::Node* map<Key, T>::clear(Node* leaf) {
        // рекурсивный алгоритм очистки дерева
        if (leaf)
        {
            leaf->left = clear(leaf->left);
            leaf->right = clear(leaf->right);
            delete leaf;
        }
        return nullptr;
    }

    template <class Key, class T>
    bool map<Key, T>::removeLeaf(Node*& leaf, Key key) {

        // рекурсивный алгоритм удаления элемента с ключом key

        if (!leaf)
            return false;

        if (key < leaf->data.first)
            return removeLeaf(leaf->left, key);
        else if (key > leaf->data.first)
            return removeLeaf(leaf->right, key);
        else if (leaf->left && leaf->right) {
            Node* tmp = leaf->right;
            while (tmp && tmp->left)
                tmp = tmp->left;
            leaf->data = tmp->data;
            removeLeaf(leaf->right, tmp->data.first);
            return true;
        }
        else {
            Node* toDel = leaf;
            if (!leaf->left)
                leaf = leaf->right;
            else
                leaf = leaf->left;
            if (leaf)
                leaf->parent = toDel->parent;
            delete toDel;
            return true;
        }
    }

    // iterator

    template <class Key, class T>
    map<Key, T>::iterator::iterator() {
        node = nullptr;
        root = nullptr;
    }

    template <class Key, class T>
    map<Key, T>::iterator::iterator(const iterator& other) {
        node = other.node;
        root = other.root;
    }

    template <class Key, class T>
    typename map<Key, T>::iterator& map<Key, T>::iterator::operator=(const map<Key, T>::iterator& other) {
        node = other.node;
        root = other.root;
        return *this;
    }

    template <class Key, class T>
    typename map<Key, T>::iterator& map<Key, T>::iterator::operator++() {
        // переход к следующему по порядку элементу
        if (node->right) {
            node = node->right;
            while (node->left) {
                node = node->left;
            }
        }
        else {
            Node* p = node->parent;
            while (p && node == p->right) {
                node = p;
                p = p->parent;
            }
            node = p;
        }
        return *this;
    }

    template <class Key, class T>
    typename map<Key, T>::iterator map<Key, T>::iterator::operator++(int) {
        iterator it = *this;
        ++(*this);
        return it;
    }

    template <class Key, class T>
    std::pair<Key, T>& map<Key, T>::iterator::operator*() const {
        return node->data;
    }

    template <class Key, class T>
    std::pair<Key, T>* map<Key, T>::iterator::operator->() const {
        return &(node->data);
    }

    template <class Key, class T>
    typename map<Key, T>::iterator& map<Key, T>::iterator::operator--() {
        // переход к предыдущему по порядку элементу
        if (!node) {
            node = root;
            while (node && node->right) {
                node = node->right;
            }
        }
        else if (node->left) {
            node = node->left;
            while (node->right)
                node = node->right;
        }
        else {
            Node* p = node->parent;
            while (p && node == p->left) {
                node = p;
                p = p->parent;
            }
            node = p;
        }
        return *this;
    }

    template <class Key, class T>
    typename map<Key, T>::iterator map<Key, T>::iterator::operator--(int) {
        iterator it = *this;
        --(*this);
        return it;
    }

    template <class Key, class T>
    bool map<Key, T>::iterator::operator==(iterator other) const {
        return node == other.node;
    }

    template <class Key, class T>
    bool map<Key, T>::iterator::operator!=(iterator other) const {
        return node != other.node;
    }

    // reversed iterator
    // заменяем операции ++ на -- и наоборот

    template <class Key, class T>
    map<Key, T>::reversed_iterator::reversed_iterator() {

    }

    template <class Key, class T>
    map<Key, T>::reversed_iterator::reversed_iterator(const reversed_iterator& other) {
        it = other.it;
    }

    template <class Key, class T>
    typename map<Key, T>::reversed_iterator& map<Key, T>::reversed_iterator::operator=(const map<Key, T>::reversed_iterator& other) {
        it = other.it;
        return *this;
    }

    template <class Key, class T>
    typename map<Key, T>::reversed_iterator& map<Key, T>::reversed_iterator::operator++() {
        it--;
        return *this;
    }

    template <class Key, class T>
    typename map<Key, T>::reversed_iterator map<Key, T>::reversed_iterator::operator++(int) {
        reversed_iterator it = *this;
        ++(*this);
        return it;
    }

    template <class Key, class T>
    std::pair<Key, T>& map<Key, T>::reversed_iterator::operator*() const {
        return it.node->data;
    }

    template <class Key, class T>
    std::pair<Key, T>* map<Key, T>::reversed_iterator::operator->() const {
        return &(it.node->data);
    }

    template <class Key, class T>
    typename map<Key, T>::reversed_iterator& map<Key, T>::reversed_iterator::operator--() {
        it++;
        return *this;
    }

    template <class Key, class T>
    typename map<Key, T>::reversed_iterator map<Key, T>::reversed_iterator::operator--(int) {
        reversed_iterator it = *this;
        --(*this);
        return it;
    }

    template <class Key, class T>
    bool map<Key, T>::reversed_iterator::operator==(reversed_iterator other) const {
        return it == other.it;
    }

    template <class Key, class T>
    bool map<Key, T>::reversed_iterator::operator!=(reversed_iterator other) const {
        return it != other.it;
    }


    // public functions

    template <class Key, class T>
    map<Key, T>::map() {
        size_ = 0;
        root = nullptr;
    }

    template <class Key, class T>
    map<Key, T>::~map() {
        root = clear(root);
    }

    template <class Key, class T>
    size_t map<Key, T>::size() {
        return size_;
    }

    template <class Key, class T>
    typename map<Key, T>::iterator map<Key, T>::begin() {
        // минимальный элемент - самый левый
        iterator it;
        it.root = it.node = root;
        while (it.node && it.node->left) {
            it.node = it.node->left;
        }
        return it;
    }

    template <class Key, class T>
    typename map<Key, T>::iterator map<Key, T>::end() {
        // элемент за последним - nullptr
        iterator it;
        it.root = root;
        it.node = nullptr;
        return it;
    }

    template <class Key, class T>
    typename map<Key, T>::reversed_iterator map<Key, T>::rbegin() {
        // последний элемент
        iterator it = end();
        reversed_iterator rit;
        rit.it = --it;
        return rit;
    }

    template <class Key, class T>
    typename map<Key, T>::reversed_iterator map<Key, T>::rend() {
        // элемент перед первым
        iterator it = begin();
        reversed_iterator rit;
        rit.it = --it;
        return rit;
    }

    template <class Key, class T>
    T& map<Key, T>::operator[](const Key& key) {
        // добавляем элемент key, если его нет, и возвращаем ссылку на поле данных
        Node* node = insert(key, T(), root, nullptr);
        return node->data.second;
    }

    template <class Key, class T>
    typename map<Key, T>::iterator map<Key, T>::find(Key key) {
        iterator it;
        it.node = find(key, root);
        return it;
    }

    template <class Key, class T>
    void map<Key, T>::clear() {
        root = clear(root);
        size_ = 0;
    }

    template <class Key, class T>
    size_t map<Key, T>::erase(Key key) {
        if (removeLeaf(root, key)) {
            size_--;
            return 1;
        }
        else
            return 0;
    }

    template <class Key, class T>
    void map<Key, T>::erase(iterator it) {
        if (removeLeaf(root, it.node->data.first))
            size_--;
    }
}
#endif /* map_h */