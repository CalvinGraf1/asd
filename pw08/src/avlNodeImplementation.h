#ifndef ASD_LABS_2021_AVLNODEIMPLEMENTATION_H
#define ASD_LABS_2021_AVLNODEIMPLEMENTATION_H

#include "avlNode.h"
#include <memory> // std::destroy_at();
#include <algorithm> // std::max;

using std::logic_error; // std::logic_error

namespace avl {

	template<typename Key>
	bool contains(Node<Key> *r, Key const &k) noexcept {
		if (r == nullptr) return false;
		else if (k == r->key) return true;
		else if (k < r->key) return contains(r->left(), k);
		else return contains(r->right(), k);
	}

	template<typename Key>
	unsigned char get_height(Node<Key> *r) {
		if (r == nullptr) return 0;
		else return r->height;
	}

	template<typename Key>
	void update_height(Node<Key> *r) {
		if (r != nullptr)
			r->height = 1 + std::max(get_height(r->left()), get_height(r->right()));
	}

	template<typename Key>
	void rotate_left(Node<Key> *&r) {
		Node<Key> *t = r->right();
		r->right() = t->left();
		t->left() = r;
		r = t;
		update_height(r->left());
		update_height(r);
	}

	template<typename Key>
	void rotate_right(Node<Key> *&r) {
		Node<Key> *t = r->left();
		r->left() = t->right();
		t->right() = r;
		r = t;
		update_height(r->right());
		update_height(r);
	}

	template<typename Key>
	int balance(Node<Key> *r) {
		if (r == nullptr) return 0;
		else return (get_height(r->left()) - get_height(r->right()));
	}

	template<typename Key>
	void restore_balance(Node<Key> *&r) {
		if (r == nullptr) return;

		if (balance(r) < -1) {
			if (balance(r->right()) > 0) rotate_right(r->right());
			rotate_left(r);
		} else if (balance(r) > 1) {
			if (balance(r->left()) < 0) rotate_left(r->left());
			rotate_right(r);
		} else update_height(r);
	}

	template<typename Key>
	Node<Key> *get_out_min(Node<Key> *&r) {
		if(r->left() != nullptr)
			return get_out_min(r->left());
		else {
			Node<Key> *tmp = r;
			r = r->right();
			return tmp;
		}
	}

    template<typename Key>
    Key const& min(Node<Key>* r) {
        if (r == nullptr) throw logic_error("empty tree");
        if (r->left() != nullptr)
            return min(r->left());
        else
            return r->key;
    }

    template<typename Key>
    Key const& max(Node<Key>* r) {
        if (r == nullptr) throw logic_error("empty tree");
        if (r->right() != nullptr)
            return max(r->right());
        else
            return r->key;
    }

	template<typename Key>
	void insert_in_subtree(Node<Key> *&r, Key const &k) {
		if (r == nullptr) {
			r = new Node<Key>{k, Node<Key>::NO_CHILD, 1};
		} else if (k == r->key) {
			return;
		} else {
			Side s = k < r->key ? LEFT : RIGHT;
			insert_in_subtree(r->children[s], k);
			restore_balance(r);
		}
	}

	template<typename Key>
	void copy_tree(Node<Key> *&r, Node<Key> *rToCopy)
	{
		if(r == nullptr) r = new Node<Key>{rToCopy->key, Node<Key>::NO_CHILD, 1};
		if(r->height != rToCopy->height) {
			if(rToCopy->left() != nullptr) copy_tree(r->left(), rToCopy->left());
			if(rToCopy->right() != nullptr) copy_tree(r->right(), rToCopy->right());
		}
	}

	template<typename Key>
	void erase_in_subtree(Node<Key> *&r, Key const &k) {
		if (r == nullptr) {}
		else if (k < r->key) erase_in_subtree(r->left(), k);
		else if (k > r->key) erase_in_subtree(r->right(), k);
		else {
			Node<Key> *tmp = r;
			if (r->left() == nullptr) r = r->right();
			else if (r->right() == nullptr) r = r->left();
			else {
				Node<Key> *m = get_out_min(r->right());
				m->right() = r->right();
				m->left() = r->left();
				r = m;
			}
			std::destroy_at(tmp);
		}
		restore_balance(r);
	}

	template<typename Key>
	void erase_min(Node<Key> *&r) {
		if (r == nullptr) {}
		else if (r->left() != nullptr) erase_min(r->left());
		else {
			Node<Key> *d = r->right();
			std::destroy_at(r);
			r = d;
			restore_balance(r);
		}
	}

	template<typename Key>
	void erase_max(Node<Key> *&r) {
		if (r == nullptr) {}
		else if (r->right() != nullptr) erase_max(r->right());
		else {
			Node<Key> *d = r->left();
			std::destroy_at(r);
			r = d;
			restore_balance(r);
		}
	}

	template<typename Key>
	std::ostream &show_indented(Node<Key> *r, std::ostream &out, std::string before,
										 bool isright) {
		out << before;
		if (not r) {
			out << ".\n";
		} else {
			if (not before.empty()) {
				before[before.size() - 2] = ' ';
				if (isright) {
					before[before.size() - 3] = ' ';
				}
			}
			out << r->key << std::endl;
			if (r->children != Node<Key>::NO_CHILD) {
				for (Side s: {LEFT, RIGHT}) {
					show_indented(r->children[s], out, before + "|_ ", s);
				}
			}
		}
		return out;
	}

	template<typename Key>
	std::ostream &operator<<(std::ostream &out, Node<Key> *r) {
		if (r == nullptr) {
			out << ".";
		} else {
			out << r->key;
			out << "(" << r->left() << "," << r->right() << ")";
		}
		return out;
	}

	template<typename Key>
	std::istream &operator>>(std::istream &is, Node<Key> *&r) {
		if (is.peek() == '.') {
			is.get();
			return is;
		}

		r = new Node<Key>{read_label<Key>(is)};

		if (is.peek() == '(') {
			is.get();

			if (is.peek() == '.') {
				is.get();
				r->left() = nullptr;
			} else {
				is >> r->left();
			}

			is.get();

			if (is.peek() == '.') {
				is.get();
				r->right() = nullptr;
			} else {
				is >> r->right();
			}

			is.get();
		} else {
			r->left() = nullptr;
			r->right() = nullptr;
		}
		update_height(r);
		return is;
	}

	template<typename Key>
	Key read_label(std::istream &is) {
		Key k;
		is >> k;

		return k;
	}
}

#endif //ASD_LABS_2021_AVLNODEIMPLEMENTATION_H
