#define CATCH_CONFIG_FAST_COMPILE

#include "catch_amalgamated.hpp"
#include "../avlTree.h"
#include "util.h"

using namespace std;

template<typename T>
avlTree<T> make_easy_test_tree() {
	// order of insertion requires AVL no balancing
	avlTree<T> tree;
	for (T i: {6, 3, 9, 2, 4, 7, 10, 1, 5, 8})
		tree.insert(i);
	return tree;
}

template<typename T>
avlTree<T> make_complete_tree_3_out_of_3() {
	// order of insertion requires AVL no balancing
	avlTree<T> tree;
	for (T i: {7, 4, 9})
		tree.insert(i);
	return tree;
}

template<typename T>
avlTree<T> make_complete_tree_2_out_of_3() {
	// order of insertion requires AVL no balancing
	avlTree<T> tree;
	for (T i: {7, 4})
		tree.insert(i);
	return tree;
}

TEST_CASE("A. constructor", "[avlTree]") {
	SECTION("Construct empty tree") {
		avlTree<int> tree;

		ostringstream oss;
		oss << tree;
		string test = oss.str();
		REQUIRE(oss.str() == ".");
	}

	SECTION("Construct easy tree") {
		avlTree<int> tree = make_easy_test_tree<int>();

		ostringstream oss;
		oss << tree;
		REQUIRE(oss.str() == "6(3(2(1(.,.),.),4(.,5(.,.))),9(7(.,8(.,.)),10(.,.)))");
	}
}

TEST_CASE("B. insert", "[avlTree]") {

	SECTION("Insert into empty tree") {
		avlTree<int> tree;
		tree.insert(42);

		ostringstream oss;
		tree.show_indented(oss);
		REQUIRE(oss.str() == "42\n");
	}

	SECTION("Insert smaller to the left") {
		avlTree<int> tree;
		tree.insert(3);
		tree.insert(2);

		ostringstream oss;
		tree.show_indented(oss);
		REQUIRE(oss.str() == "3\n"
									"|_ 2\n"
									"|_ .\n");
	}

	SECTION("Insert larger to the right") {
		avlTree<int> tree;
		tree.insert(3);
		tree.insert(4);

		ostringstream oss;
		tree.show_indented(oss);
		REQUIRE(oss.str() == "3\n"
									"|_ .\n"
									"|_ 4\n");
	}

	SECTION("Insert twice has no effect") {
		avlTree<int> tree;
		tree.insert(3);
		tree.insert(4);
		tree.insert(4);

		ostringstream oss;
		tree.show_indented(oss);
		REQUIRE(oss.str() == "3\n"
									"|_ .\n"
									"|_ 4\n");
	}

	SECTION("Easy tree") {
		avlTree<int> tree = make_easy_test_tree<int>();

		ostringstream oss;
		tree.show_indented(oss);
		REQUIRE(oss.str() == "6\n"
									"|_ 3\n"
									"|  |_ 2\n"
									"|  |  |_ 1\n"
									"|  |  |_ .\n"
									"|  |_ 4\n"
									"|     |_ .\n"
									"|     |_ 5\n"
									"|_ 9\n"
									"   |_ 7\n"
									"   |  |_ .\n"
									"   |  |_ 8\n"
									"   |_ 10\n");
	}
}

TEST_CASE("C. constructor by copy", "[avlTree]") {

	SECTION("Copy an empty tree") {
		avlTree<int> tree;
		avlTree<int> tree2(tree);
		tree.insert(1);

		ostringstream oss;
		oss << tree2;
		string str = oss.str();
		string b;
		REQUIRE(oss.str() == ".");
	}

	SECTION("Copy an easy tree") {
		avlTree<int> tree = make_easy_test_tree<int>();
		avlTree<int> tree2(tree);
		tree.insert(11);

		ostringstream oss;
		oss << tree2;
		REQUIRE(oss.str() == "6(3(2(1(.,.),.),4(.,5(.,.))),9(7(.,8(.,.)),10(.,.)))");
	}
}

TEST_CASE("D. copy by affectation", "[avlTree]") {

	SECTION("Affect an empty tree") {
		avlTree<int> tree;
		avlTree<int> tree2 = make_easy_test_tree<int>();
		tree2 = tree;

		ostringstream oss;
		oss << tree2;
		REQUIRE(oss.str() == ".");
	}

	SECTION("Affect an easy tree") {
		avlTree<int> tree = make_easy_test_tree<int>();
		avlTree<int> tree2;
		tree2 = tree;

		ostringstream oss;
		oss << tree2;
		REQUIRE(oss.str() == "6(3(2(1(.,.),.),4(.,5(.,.))),9(7(.,8(.,.)),10(.,.)))");
	}

	SECTION("Auto affectation doesn't change") {
		avlTree<int> tree = make_easy_test_tree<int>();
		tree = tree;

		ostringstream oss;
		oss << tree;
		REQUIRE(oss.str() == "6(3(2(1(.,.),.),4(.,5(.,.))),9(7(.,8(.,.)),10(.,.)))");
	}
}

TEST_CASE("E. destructor", "[avlTree]") {

	SECTION("Destruct an empty tree") {
		resetCount();
		{
			avlTree<C> tree;
		}
		REQUIRE(getCount() == 0);
	}

	SECTION("Destruct an easy test tree") {
		resetCount();
		{
			avlTree<C> tree = make_easy_test_tree<C>();
		}
		REQUIRE(getCount() == 0);
	}
}

TEST_CASE("F. contains", "[avlTree]") {

	SECTION("Contains in empty tree") {
		avlTree<int> tree;
		REQUIRE(!tree.contains(3));
	}

	SECTION("Contains an existing element in easy tree") {
		avlTree<int> tree = make_easy_test_tree<int>();
		REQUIRE(tree.contains(4));
	}

	SECTION("Contains a non existing element in easy tree") {
		avlTree<int> tree = make_easy_test_tree<int>();
		REQUIRE(!tree.contains(15));
	}

	SECTION("Contains an existing element that was just add") {
		avlTree<int> tree = make_easy_test_tree<int>();
		tree.insert(15);
		REQUIRE(tree.contains(15));
	}
}

TEST_CASE("G. min", "[avlTree]") {

	SECTION("Min empty tree") { /// TODO
		avlTree<int> tree;
		REQUIRE_THROWS(tree.min());
	}

	SECTION("Min easy tree") {
		avlTree<int> tree = make_easy_test_tree<int>();
        int const& minimum = tree.min();
        REQUIRE(minimum == 1);
	}

    SECTION("Min 1 element tree") {
        avlTree<int> tree;
        tree.insert(4);
        int const& minimum = tree.min();
        REQUIRE(minimum == 4);
    }
}

TEST_CASE("H. max", "[avlTree]") {
	SECTION("Max empty tree") { /// TODO
		avlTree<int> tree;
        REQUIRE_THROWS(tree.max());
	}

	SECTION("Max easy tree") {
        avlTree<int> tree = make_easy_test_tree<int>();
        int const& maximum = tree.max();
        REQUIRE(maximum == 10);
	}

    SECTION("Max 1 element tree") {
        avlTree<int> tree;
        tree.insert(4);
        int const& minimum = tree.min();
        REQUIRE(minimum == 4);
    }
}

TEST_CASE("I. erase_min", "[avlTree]") {

	SECTION("Erasing min empty tree") {
		avlTree<int> tree;

		tree.erase_min();

		ostringstream oss;
		tree.show_indented(oss);
		REQUIRE(oss.str() == ".\n");
	}

	SECTION("Erasing min easy tree") {
		avlTree<int> tree = make_easy_test_tree<int>();

		tree.erase_min();

		ostringstream oss;
		tree.show_indented(oss);
		REQUIRE(oss.str() == "6\n"
									"|_ 3\n"
									"|  |_ 2\n"
									"|  |_ 4\n"
									"|     |_ .\n"
									"|     |_ 5\n"
									"|_ 9\n"
									"   |_ 7\n"
									"   |  |_ .\n"
									"   |  |_ 8\n"
									"   |_ 10\n");
	}

	SECTION("Erasing min root") {
		avlTree<int> tree;
		tree.insert(4);
		tree.insert(7);

		tree.erase_min();

		ostringstream oss;
		tree.show_indented(oss);
		REQUIRE(oss.str() == "7\n");
	}
}

TEST_CASE("J. erase_max", "[avlTree]") {

	SECTION("Erasing max empty tree") {
		avlTree<int> tree;

		tree.erase_max();

		ostringstream oss;
		tree.show_indented(oss);
		REQUIRE(oss.str() == ".\n");
	}

	SECTION("Erasing max easy tree") {
		avlTree<int> tree = make_easy_test_tree<int>();

		tree.erase_max();

		ostringstream oss;
		tree.show_indented(oss);
		REQUIRE(oss.str() == "6\n"
									"|_ 3\n"
									"|  |_ 2\n"
									"|  |  |_ 1\n"
									"|  |  |_ .\n"
									"|  |_ 4\n"
									"|     |_ .\n"
									"|     |_ 5\n"
									"|_ 9\n"
									"   |_ 7\n"
									"   |  |_ .\n"
									"   |  |_ 8\n"
									"   |_ .\n");
	}

	SECTION("Erasing max root") {
		avlTree<int> tree;
		tree.insert(7);
		tree.insert(4);

		tree.erase_max();

		ostringstream oss;
		tree.show_indented(oss);
		REQUIRE(oss.str() == "4\n");
	}
}

TEST_CASE("Z. erase", "[avlTree]") {

	SECTION("Erasing in empty tree") {
		avlTree<int> tree;

		tree.erase(1);
		tree.erase(10);

		ostringstream oss;
		tree.show_indented(oss);
		REQUIRE(oss.str() == ".\n");
	}

	SECTION("Erasing of an existing element in easy tree") {
		avlTree<int> tree = make_easy_test_tree<int>();

		tree.erase(3);

		ostringstream oss;
		oss << tree;
		REQUIRE(oss.str() == "6(4(2(1(.,.),.),5(.,.)),9(7(.,8(.,.)),10(.,.)))");
	}

	SECTION("Erasing of a non existing element in easy tree") {
		avlTree<int> tree = make_easy_test_tree<int>();

		tree.erase(11);

		ostringstream oss;
		oss << tree;
		REQUIRE(oss.str() == "6(3(2(1(.,.),.),4(.,5(.,.))),9(7(.,8(.,.)),10(.,.)))");
	}

	SECTION("Erasing a whole easy tree") {
		avlTree<int> tree = make_easy_test_tree<int>();
		for (int i = 1; i <= 10; ++i)
			tree.erase(i);

		ostringstream oss;
		tree.show_indented(oss);
		REQUIRE(oss.str() == ".\n");
	}

	SECTION("Erasing of the trunk in easy tree") {
		avlTree<int> tree = make_easy_test_tree<int>();

		tree.erase(6);

		ostringstream oss;
		oss << tree;
		REQUIRE(oss.str() == "7(3(2(1(.,.),.),4(.,5(.,.))),9(8(.,.),10(.,.)))");
	}
}

TEST_CASE("L. height", "[avlTree]") {

	SECTION("Height empty tree") {
		avlTree<int> tree;

		unsigned char height = tree.height();

		REQUIRE(height == 0);
	}

	SECTION("Height easy tree") {
		avlTree<int> tree = make_easy_test_tree<int>();

		unsigned char height = tree.height();

		REQUIRE(height == 4);
	}

	SECTION("Height that does not change after deleting 1 element") {
		avlTree<int> tree = make_complete_tree_3_out_of_3<int>();

		unsigned char beforeDelete = tree.height();
		tree.erase(4);
		unsigned char afterDelete = tree.height();

		bool ok = beforeDelete == 2 and afterDelete == 2;

		REQUIRE(ok);
	}

	SECTION("Height that changes after deleting 1 element") {
		avlTree<int> tree = make_complete_tree_2_out_of_3<int>();

		unsigned char beforeDelete = tree.height();
		tree.erase(4);
		unsigned char afterDelete = tree.height();
		cout << "before : " << (int) beforeDelete << " after : "
			  << (int) afterDelete << endl;

		bool ok = beforeDelete == 2 and afterDelete == 1;

		REQUIRE(ok);
	}

	SECTION("Height that does not change after adding 1 element") {
		avlTree<int> tree = make_complete_tree_2_out_of_3<int>();

		unsigned char beforeAdd = tree.height();
		tree.insert(10);
		unsigned char afterAdd = tree.height();

		bool ok = beforeAdd == 2 and afterAdd == 2;

		REQUIRE(ok);
	}

	SECTION("Height that changes after adding 1 element") {
		avlTree<int> tree = make_complete_tree_3_out_of_3<int>();

		unsigned char beforeAdd = tree.height();
		tree.insert(10);
		unsigned char afterAdd = tree.height();

		bool ok = beforeAdd == 2 and afterAdd == 3;

		REQUIRE(ok);
	}
}

TEST_CASE("M. display_indented", "[avlTree]") {

	SECTION("Empty tree") {
		avlTree<int> tree;

		ostringstream oss;
		tree.show_indented(oss);
		REQUIRE(oss.str() == ".\n");
	}

	SECTION("Easy test tree") {
		avlTree<int> tree = make_easy_test_tree<int>();

		ostringstream oss;
		tree.show_indented(oss);
		REQUIRE(oss.str() == "6\n"
									"|_ 3\n"
									"|  |_ 2\n"
									"|  |  |_ 1\n"
									"|  |  |_ .\n"
									"|  |_ 4\n"
									"|     |_ .\n"
									"|     |_ 5\n"
									"|_ 9\n"
									"   |_ 7\n"
									"   |  |_ .\n"
									"   |  |_ 8\n"
									"   |_ 10\n");
	}

	SECTION("Non balanced tree") {
		avlTree<int> tree;
		for (int i = 10; i <= 15; ++i)
				tree.insert(i);

		ostringstream oss;
		tree.show_indented(oss);
		cout << oss.str();
		REQUIRE(oss.str() == "13\n"
									"|_ 11\n"
									"|  |_ 10\n"
									"|  |_ 12\n"
									"|_ 14\n"
									"   |_ .\n"
									"   |_ 15\n");
	}
}

TEST_CASE("N. operator<<", "[avlTree]") {

	SECTION("Empty tree") {
		avlTree<int> tree;

		ostringstream oss;
		oss << tree;
		REQUIRE(oss.str() == ".");
	}

	SECTION("Easy test tree") {
		avlTree<int> tree = make_easy_test_tree<int>();

		ostringstream oss;
		oss << tree;
		REQUIRE(oss.str() == "6(3(2(1(.,.),.),4(.,5(.,.))),9(7(.,8(.,.)),10(.,.)))");
	}
}

TEST_CASE("O. operator>>", "[avlTree]") {
	SECTION("Empty tree") {
		avlTree<int> tree;

		istringstream iss(".");
		iss >> tree;

		ostringstream oss;
		oss << tree;

		REQUIRE(oss.str() == ".");
	}

	SECTION("Easy test tree") {
		avlTree<int> tree;

		istringstream iss("6(3(2(1(.,.),.),4(.,5(.,.))),9(7(.,8(.,.)),10(.,.)))");
		iss >> tree;

		ostringstream oss;
		oss << tree;

		REQUIRE(oss.str() == "6(3(2(1(.,.),.),4(.,5(.,.))),9(7(.,8(.,.)),10(.,.)))");
	}
}