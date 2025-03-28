#ifndef ASD_LABS_2021_AVLNODE_H
#define ASD_LABS_2021_AVLNODE_H

namespace avl {

	enum Side {
		LEFT = 0, RIGHT = 1
	};

	template<typename Key>
	struct Node {
		Key const key;
		std::array<Node *, 2> children;
		unsigned char height;

		inline Node *&left() noexcept { return children[LEFT]; }

		inline Node *const &left() const noexcept { return children[LEFT]; }

		inline Node *&right() noexcept { return children[RIGHT]; }

		inline Node *const &right() const noexcept { return children[RIGHT]; }

		static constexpr std::array<Node *, 2> NO_CHILD{nullptr, nullptr};
	};

	template<typename Key>
	bool contains(Key const &k) noexcept;// TODO Manque le const: contains() const...

	template<typename Key>
	unsigned char get_height(Node<Key> *r);

	template<typename Key>
	void update_height(Node<Key> *r);

	template<typename Key>
	void rotate_left(Node<Key> *&r);

	template<typename Key>
	void rotate_right(Node<Key> *&r);

	template<typename Key>
	int balance(Node<Key> *r);

	template<typename Key>
	void restore_balance(Node<Key> *&r);

	template<typename Key>
	Node<Key> *get_out_min(Node<Key> *&r);

	template<typename Key>
    Key const& min(Node<Key> *r);

    template<typename Key>
    Key const& max(Node<Key> *r);

	template<typename Key>
	void insert_in_subtree(Node<Key> *&r,
								  Key const &k);

	template<typename Key>
	void copy_tree(Node<Key> *&r, Node<Key> *rToCopy);

	template<typename Key>
	void erase_in_subtree(Node<Key> *&r, Key const &k);

	template<typename Key>
	void erase_min(Node<Key> *&r, Key const &k);

	template<typename Key>
	void erase_max(Node<Key> *&r, Key const &k);

	template<typename Key>
	std::ostream &show_indented(Node<Key> *r,
										 std::ostream &out = std::cout,
										 std::string before = "",
										 bool isright = false);

	template<typename Key>
	std::ostream &operator<<(std::ostream &out, Node<Key> *r);

	template<typename Key>
	std::istream &operator>>(std::istream &is, Node<Key> *&r);

	template<typename Key>
	Key read_label(std::istream &is);

	void signaler_erreur(const char* msg);
}

#include "avlNodeImplementation.h"

#endif //ASD_LABS_2021_AVLNODE_H