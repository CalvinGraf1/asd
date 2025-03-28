#ifndef ASD_2021_AVL_IMPL_H
#define ASD_2021_AVL_IMPL_H

template<typename Key>
avlTree<Key>::avlTree() : root(nullptr) {

}

template<typename Key>
avlTree<Key>::~avlTree() {
    while (root != nullptr)
        avl::erase_min(root);
}

template<typename Key>
avlTree<Key>::avlTree(avlTree const &other) {
    if (this != &other and other.root != nullptr)
        avl::copy_tree(root, other.root);
	 else
        root = nullptr;
}

template<typename Key>
avlTree<Key> &avlTree<Key>::operator=(const avlTree &other) {
    if (this != &other) {
        while (root != nullptr)
            avl::erase_min(root);

        if (other.root != nullptr) // Copie l'autre arbre dans l'actuel
            avl::copy_tree(root, other.root);
        else
            root = nullptr;
    }
    return *this;
}

template<typename Key>
void avlTree<Key>::insert(Key const &k) {
    avl::insert_in_subtree(root, k);
}

template<typename Key>
bool avlTree<Key>::contains(const Key &k) const noexcept {
    return avl::contains(root, k);
}

template<typename Key>
Key const& avlTree<Key>::min() const {
    return avl::min(root);
}

template<typename Key>
Key const& avlTree<Key>::max() const {
    return avl::max(root);
}

template<typename Key>
void avlTree<Key>::erase_min() {
    avl::erase_min(root);
}

template<typename Key>
void avlTree<Key>::erase_max() {
    avl::erase_max(root);
}

template<typename Key>
void avlTree<Key>::erase(const Key &k) noexcept {
    avl::erase_in_subtree(root, k);
}

template<typename Key>
unsigned char avlTree<Key>::height() const noexcept {
    return avl::get_height(root);
}

template<typename Key>
std::ostream &avlTree<Key>::show_indented(std::ostream &out) const {
    return avl::show_indented(root, out);
}

template<typename Key>
std::ostream &operator<<(std::ostream &out, avlTree<Key> const &tree) {
    out << tree.root;
    return out;
}

template<typename Key>
std::istream &operator>>(std::istream &is, avlTree<Key> &tree) {
    is >> tree.root;
    return is;
}

#endif //ASD_2021_AVL_IMPL_H
