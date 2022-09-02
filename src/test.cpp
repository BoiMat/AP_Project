#define BOOST_TEST_MODULE Exam_RedBlackTree
#define BOOST_TEST_LOG_LEVEL = all
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
#include <boost/test/tools/output_test_stream.hpp>
#include "rbtree.hpp"

RBTree<int, std::less<int>> tree;

BOOST_AUTO_TEST_CASE(test_insert)
{
    BOOST_TEST_MESSAGE("Unit testing the 'Insert' function...\n\n");
    tree.Insert(8);
	tree.Insert(18);
	tree.Insert(5);
	tree.Insert(15);
	tree.Insert(17);
	tree.Insert(25);
	tree.Insert(40);
	tree.Insert(80);

    BOOST_CHECK(*tree.Get_root() == 17);
    BOOST_CHECK(*tree.Get_root()->left == 8);
    BOOST_CHECK(*tree.Get_root()->right == 25);
    BOOST_CHECK(*tree.Get_root()->left->left == 5);
    BOOST_CHECK(*tree.Get_root()->left->right == 15);
}

BOOST_AUTO_TEST_CASE(test_delete)
{
    BOOST_TEST_MESSAGE("Unit testing to 'Delete' function...\n\n");
    BOOST_CHECK(tree.Contains(17));
    tree.Delete(17);
    BOOST_CHECK(!tree.Contains(17));
}

    
BOOST_AUTO_TEST_CASE(test_contains)
{
    BOOST_TEST_MESSAGE("Unit testing the 'Contains' function...\n\n");
    BOOST_CHECK(tree.Contains(8));
    BOOST_CHECK(tree.Contains(18));
    BOOST_CHECK(tree.Contains(5));
    BOOST_CHECK(tree.Contains(15));
    BOOST_CHECK(tree.Contains(26) == false);
    BOOST_CHECK(tree.Contains(41) == false);
    BOOST_CHECK(tree.Contains(81) == false);

}

BOOST_AUTO_TEST_CASE(test_print)
{
    BOOST_TEST_MESSAGE("Unit testing different printing orders...\n\n");
    tree.print();

    BOOST_TEST_MESSAGE("\nInOrder printing:\n");
    tree.InOrderPrint();

    BOOST_TEST_MESSAGE("\nPreOrder printing:\n");
    tree.PreOrderPrint();

    BOOST_TEST_MESSAGE("\nPostOrder printing:\n");
    tree.PostOrderPrint();
}

BOOST_AUTO_TEST_CASE(test_iterator)
{
    BOOST_TEST_MESSAGE("Unit testing the 'const_iterator' function...\n\n");
    RBTree<int, std::less<int>>::const_iterator it = tree.begin();
    BOOST_CHECK(*it == 5);
    ++it;
    BOOST_CHECK(*it == 8);
    ++it;
    BOOST_CHECK(*it == 15);
    ++it;
    BOOST_CHECK(*it == 18);
    ++it;
    BOOST_CHECK(*it == 25);
    ++it;
    BOOST_CHECK(*it == 40);
    ++it;
    BOOST_CHECK(*it == 80);
    ++it;
    BOOST_CHECK(it == tree.end());

    RBTree<int, std::less<int>>::const_iterator it2 = tree.begin();
    std::string str = "";
    while (it2 != tree.end()) {
        str += std::to_string(*it2);
        str += " ";
        ++it2;
    }
    BOOST_CHECK(str == "5 8 15 18 25 40 80 ");
}