#if __has_include("catch/catch_amalgamated.hpp")
#include "catch/catch_amalgamated.hpp"
#elif __has_include("catch_amalgamated.hpp")
#include "catch_amalgamated.hpp"
#elif __has_include(<catch2/catch.hpp>)
#include <catch2/catch.hpp>
#elif __has_include("catch.hpp")
#include "catch.hpp"
#elif __has_include(<catch2/catch_test_macros.hpp>)
#include <catch2/catch_test_macros.hpp>
#else
#include "catch/catch_amalgamated.hpp"
#endif

#if __has_include("AVLTree.h")
#include "AVLTree.h"
#elif __has_include("../src/AVLTree.h")
#include "../src/AVLTree.h"
#elif __has_include("src/AVLTree.h")
#include "src/AVLTree.h"
#endif

using namespace std;

// Helper to capture cout from execute()
static string runCommand(AVLTree& tree, const string& cmd) {
    stringstream buffer;
    streambuf* prev = cout.rdbuf(buffer.rdbuf());
    tree.execute(cmd);
    cout.rdbuf(prev);
    return buffer.str();
}

TEST_CASE("Test 1: Input Validation and Edge Cases", "[avl][validation]") {
    AVLTree tree;

    // Invalid names (contains digits or symbols)
    REQUIRE(runCommand(tree, "insert \"A123\" 12345678") == "unsuccessful\n");
    REQUIRE(runCommand(tree, "insert \"Alice!\" 12345678") == "unsuccessful\n");

    // Invalid IDs (not 8 digits)
    REQUIRE(runCommand(tree, "insert \"Alice\" 1234567") == "unsuccessful\n");
    REQUIRE(runCommand(tree, "insert \"Alice\" 123456789") == "unsuccessful\n");
    REQUIRE(runCommand(tree, "insert \"Alice\" 1234abcd") == "unsuccessful\n");

    // Name without quotes
    REQUIRE(runCommand(tree, "insert Alice 12345678") == "unsuccessful\n");

    // Valid insert
    REQUIRE(runCommand(tree, "insert \"Alice\" 12345678") == "successful\n");

    // Duplicate ID rejection
    REQUIRE(runCommand(tree, "insert \"Bob\" 12345678") == "unsuccessful\n");

    // Search nonexistent ID and Name
    REQUIRE(runCommand(tree, "search 99999999") == "unsuccessful\n");
    REQUIRE(runCommand(tree, "search \"Nobody\"") == "unsuccessful\n");

    // Remove nonexistent ID
    REQUIRE(runCommand(tree, "remove 99999999") == "unsuccessful\n");
}

TEST_CASE("Test 2: AVL Tree Rotations (LL, RR, LR, RL)", "[avl][rotations]") {
    SECTION("Left-Left Rotation (Right Rotation)") {
        AVLTree tree;
        tree.execute("insert \"C\" 30000000");
        tree.execute("insert \"B\" 20000000");
        tree.execute("insert \"A\" 10000000");
        vector<string> expectedPreorder = {"B", "A", "C"};
        vector<string> actualPreorder = tree.getPreorderNames();
        REQUIRE(actualPreorder == expectedPreorder);
    }

    SECTION("Right-Right Rotation (Left Rotation)") {
        AVLTree tree;
        tree.execute("insert \"A\" 10000000");
        tree.execute("insert \"B\" 20000000");
        tree.execute("insert \"C\" 30000000");
        vector<string> expectedPreorder = {"B", "A", "C"};
        vector<string> actualPreorder = tree.getPreorderNames();
        REQUIRE(actualPreorder == expectedPreorder);
    }

    SECTION("Left-Right Rotation") {
        AVLTree tree;
        tree.execute("insert \"C\" 30000000");
        tree.execute("insert \"A\" 10000000");
        tree.execute("insert \"B\" 20000000");
        vector<string> expectedPreorder = {"B", "A", "C"};
        vector<string> actualPreorder = tree.getPreorderNames();
        REQUIRE(actualPreorder == expectedPreorder);
    }

    SECTION("Right-Left Rotation") {
        AVLTree tree;
        tree.execute("insert \"A\" 10000000");
        tree.execute("insert \"C\" 30000000");
        tree.execute("insert \"B\" 20000000");
        vector<string> expectedPreorder = {"B", "A", "C"};
        vector<string> actualPreorder = tree.getPreorderNames();
        REQUIRE(actualPreorder == expectedPreorder);
    }
}

TEST_CASE("Test 3: Deletion with 0, 1, and 2 Children", "[avl][deletion]") {
    AVLTree tree;
    // Build tree:
    //         50
    //       /    \
    //      30     70
    //     /  \   /  \
    //    20  40 60  80
    tree.execute("insert \"Fifty\" 50000000");
    tree.execute("insert \"Thirty\" 30000000");
    tree.execute("insert \"Seventy\" 70000000");
    tree.execute("insert \"Twenty\" 20000000");
    tree.execute("insert \"Forty\" 40000000");
    tree.execute("insert \"Sixty\" 60000000");
    tree.execute("insert \"Eighty\" 80000000");

    // Case 1: Delete a leaf node (0 children)
    REQUIRE(runCommand(tree, "remove 20000000") == "successful\n");
    vector<string> expected1 = {"Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty"};
    REQUIRE(tree.getInorderNames() == expected1);

    // Case 2: Delete node with 1 child (Thirty now only has Forty as right child)
    REQUIRE(runCommand(tree, "remove 30000000") == "successful\n");
    vector<string> expected2 = {"Forty", "Fifty", "Sixty", "Seventy", "Eighty"};
    REQUIRE(tree.getInorderNames() == expected2);

    // Case 3: Delete node with 2 children (Root Fifty has left Forty and right Seventy)
    REQUIRE(runCommand(tree, "remove 50000000") == "successful\n");
    vector<string> expected3 = {"Forty", "Sixty", "Seventy", "Eighty"};
    REQUIRE(tree.getInorderNames() == expected3);
}

TEST_CASE("Test 4: Traversals and Level Count", "[avl][traversals]") {
    AVLTree tree;
    // Empty tree level count
    REQUIRE(runCommand(tree, "printLevelCount") == "0\n");

    tree.execute("insert \"Root\" 40000000");
    tree.execute("insert \"Left\" 20000000");
    tree.execute("insert \"Right\" 60000000");

    // Level count should be 2
    REQUIRE(runCommand(tree, "printLevelCount") == "2\n");

    vector<string> expectedIn = {"Left", "Root", "Right"};
    vector<string> expectedPre = {"Root", "Left", "Right"};
    vector<string> expectedPost = {"Left", "Right", "Root"};

    REQUIRE(tree.getInorderNames() == expectedIn);
    REQUIRE(tree.getPreorderNames() == expectedPre);
    REQUIRE(tree.getPostorderNames() == expectedPost);
}

TEST_CASE("Test 5: removeInorder Bounds and Order", "[avl][removeinorder]") {
    AVLTree tree;
    tree.execute("insert \"A\" 10000000");
    tree.execute("insert \"B\" 20000000");
    tree.execute("insert \"C\" 30000000");
    tree.execute("insert \"D\" 40000000");

    // Out of bounds negative index
    REQUIRE(runCommand(tree, "removeInorder -1") == "unsuccessful\n");
    // Out of bounds index >= size
    REQUIRE(runCommand(tree, "removeInorder 4") == "unsuccessful\n");
    REQUIRE(runCommand(tree, "removeInorder 10") == "unsuccessful\n");

    // Valid removeInorder at index 0 (removes "A")
    REQUIRE(runCommand(tree, "removeInorder 0") == "successful\n");
    vector<string> expectedAfter0 = {"B", "C", "D"};
    REQUIRE(tree.getInorderNames() == expectedAfter0);

    // Valid removeInorder at index 1 (removes "C" from {"B", "C", "D"})
    REQUIRE(runCommand(tree, "removeInorder 1") == "successful\n");
    vector<string> expectedAfter1 = {"B", "D"};
    REQUIRE(tree.getInorderNames() == expectedAfter1);
}
