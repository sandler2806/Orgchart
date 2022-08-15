#include "doctest.h"
#include "sources/OrgChart.hpp"
#include <string>
using namespace ariel;
using namespace std;


TEST_CASE("valid input") {
//    test with different type as the template
    OrgChart<int> organization;
//    test with binary tree at first.
    organization.add_root(1)
            .add_sub(1, 2)
            .add_sub(1, 3)
            .add_sub(2, 5)
            .add_sub(2, 6)
            .add_sub(3,7)
            .add_sub(3,8);
    string str="";
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it) {
        str += to_string(*it);
        str += ",";
    }
//    check that the level order iterator working right.
    CHECK(str=="1,2,3,5,6,7,8,");
    str="";
    organization.add_root(10);

    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it) {
        str += to_string(*it);
        str += ",";
    }
//    check that switch the root working
    CHECK(str=="10,2,3,5,6,7,8,");
    str="";


    for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it) {
        str += to_string(*it);
        str += ",";
    }
    //    check that the reverse level order iterator working right.
    CHECK(str=="5,6,7,8,2,3,10,");
    str="";
    organization.add_root(15);

    for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it) {
        str += to_string(*it);
        str += ",";
    }
    //    check that switch the root working
    CHECK(str=="5,6,7,8,2,3,15,");
    str="";


    for (auto it = organization.begin_preorder(); it != organization.end_preorder(); ++it) {
        str += to_string(*it);
        str += ",";
    }
    //    check that the pre-order iterator working right.
    CHECK(str=="15,2,5,6,3,7,8,");
    str="";
    organization.add_root(20);

    for (auto it = organization.begin_preorder(); it != organization.end_preorder(); ++it) {
        str += to_string(*it);
        str += ",";
    }
    //    check that switch the root working
    CHECK(str=="20,2,5,6,3,7,8,");
    str="";


}

TEST_CASE("exceptions check") {
    OrgChart<string> organization;
//  check that the iterator does not throw exception if the organization is empty.
    CHECK_NOTHROW(for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
//  in addition, make sure that the loop is empty because the organization is empty.
        throw invalid_argument( "\nthe first element is not exist in the tree." );
    });
//  check that the iterator does not throw exception if the organization is empty.
    CHECK_NOTHROW(for (auto it = organization.begin_preorder(); it != organization.end_preorder(); ++it)
    {
//  in addition, make sure that the loop is empty because the organization is empty.
        throw invalid_argument( "\nthe first element is not exist in the tree." );
    });
//  check that the iterator does not throw exception if the organization is empty.
    CHECK_NOTHROW(for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it)
    {
//  in addition, make sure that the loop is empty because the organization is empty.
        throw invalid_argument( "\nthe first element is not exist in the tree." );
    });


    organization.add_root("1");
    organization.add_sub("1", "2");
//  check that add sub throws exception if both of the nodes does not exist
    CHECK_THROWS(organization.add_sub("3", "4"));
//  check that add sub throws exception if the left node does not exist
    CHECK_THROWS(organization.add_sub("4", "2"));
}

TEST_CASE("edge cases") {
    OrgChart<string> organization_string;
//    testing on organization with only one node.
    organization_string.add_root("1");
    string str="";
    //    check that the level order iterator working right.
    for (auto it = organization_string.begin_level_order(); it != organization_string.end_level_order(); ++it)
    {
        str+=(*it);
        str+=",";
    }
    CHECK(str=="1,");

    organization_string.add_root("3");
    str="";

//    check that the reverse level order iterator working right.
    for (auto it = organization_string.begin_preorder(); it != organization_string.end_preorder(); ++it)
    {
        str+=(*it);
        str+=",";
    }
    CHECK(str=="3,");

    organization_string.add_root("5");
    str="";

//    check that the pre-order iterator working right.
    for (auto it = organization_string.begin_reverse_order(); it != organization_string.reverse_order(); ++it)
    {
        str+=(*it);
        str+=",";
    }
    CHECK(str=="5,");


//  check on trinary tree.
    OrgChart<int> organization;
    organization.add_root(1)
            .add_sub(1, 2)
            .add_sub(1, 3)
            .add_sub(1, 4)
            .add_sub(2, 5)
            .add_sub(3, 6);
    str="";
    //    check that the level order iterator working right.

    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it) {
        str += to_string(*it);
        str += ",";
    }
            CHECK(str=="1,2,3,4,5,6,");
    str="";
    organization.add_root(10);

    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it) {
        str += to_string(*it);
        str += ",";
    }
//    check that switch the root working
    CHECK(str=="10,2,3,4,5,6,");
    str="";

    //    check that the reverse level order iterator working right.
    for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it) {
        str += to_string(*it);
        str += ",";
    }
            CHECK(str=="5,6,2,3,4,10,");
    str="";
    organization.add_root(15);

    for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it) {
        str += to_string(*it);
        str += ",";
    }
//    check that switch the root working
    CHECK(str=="5,6,2,3,4,15,");
    str="";

    //    check that the pre-order iterator working right.
    for (auto it = organization.begin_preorder(); it != organization.end_preorder(); ++it) {
        str += to_string(*it);
        str += ",";
    }
    CHECK(str=="15,2,5,3,6,4,");
    str="";
    organization.add_root(20);

    for (auto it = organization.begin_preorder(); it != organization.end_preorder(); ++it) {
        str += to_string(*it);
        str += ",";
    }
    //    check that switch the root working
    CHECK(str=="20,2,5,3,6,4,");
    str="";

}
