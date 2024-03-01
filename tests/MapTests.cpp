#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../unordered_map/unordered_map.h"

TEST_CASE("Test Unordered_map default constructor", "[Unordered_map]") {
    Unordered_map<int, int> map;

    SECTION("Test size") {
        REQUIRE(map.size() == 0);
    }

    SECTION("Test capacity") {
        REQUIRE(map.capacity() == 0);
    }

    SECTION("Test max_load") {
        REQUIRE(map.get_max_load() == Approx(0.8));
    }

    SECTION("Test empty") {
        REQUIRE(map.empty());
    }
}

TEST_CASE("iterator matching test for the forward type", "[Unordered_map]"){
    static_assert(std::forward_iterator<MapIterator<int, false>>);
    static_assert(std::forward_iterator<MapIterator<int, true>>);
}

TEST_CASE("Test Unordered_map insert and find", "[Unordered_map]") {
    Unordered_map<int, std::string> map;

    SECTION("Test inserting and finding elements") {
        map.insert({1, "one"});
        map.insert({2, "two"});

        REQUIRE(map.size() == 2);
        REQUIRE(map.capacity() == 2);
        REQUIRE_FALSE(map.empty());

        REQUIRE(map.find(1) != map.end());
        REQUIRE(map.find(2) != map.end());
        REQUIRE(map.find(3) == map.end());

        REQUIRE(map.find(1)->second == "one");
        REQUIRE(map.find(2)->second == "two");
    }
}

TEST_CASE("Test Unordered_map erase", "[Unordered_map]") {
    Unordered_map<int, std::string> map;
    map.insert({1, "one"});
    map.insert({2, "two"});
    map.insert({3, "three"});

    SECTION("Test erase by iterator") {
        auto it = map.find(2);
        map.erase(it);
        std::cout << map.find(2) -> second;
        REQUIRE(map.size() == 2);
        REQUIRE(map.capacity() == 4);
        REQUIRE(map.find(2) == map.end());
    }

    SECTION("Test erase by key") {
        map.erase(1);

        REQUIRE(map.size() == 2);
        REQUIRE(map.capacity() == 4);
        REQUIRE(map.find(1) == map.end());
    }
}

TEST_CASE("Test Unordered_map at", "[Unordered_map]") {
    Unordered_map<int, std::string> map;
    map.insert({1, "one"});
    map.insert({2, "two"});
    map.insert({3, "three"});

    SECTION("Test at with existing key") {
        REQUIRE(map.at(1) == "one");
        REQUIRE(map.at(2) == "two");
        REQUIRE(map.at(3) == "three");
    }

    SECTION("Test at with non-existing key") {
        REQUIRE_THROWS_AS(map.at(4), std::out_of_range);
    }
}

TEST_CASE("Test Unordered_map subscript operator", "[Unordered_map]") {
    Unordered_map<int, std::string> map;
    map.insert({1, "one"});
    map.insert({2, "two"});
    map.insert({3, "three"});

    SECTION("Test subscript operator with existing key") {
        REQUIRE(map[1] == "one");
        REQUIRE(map[2] == "two");
        REQUIRE(map[3] == "three");
    }

    SECTION("Test subscript operator with non-existing key") {
        REQUIRE_NOTHROW(map[4]);
        REQUIRE(map[4].empty());
    }
}

TEST_CASE("Test Unordered_map count", "[Unordered_map]") {
    Unordered_map<int, std::string> map;
    map.insert({1, "one"});
    map.insert({2, "two"});
    map.insert({3, "three"});

    SECTION("Test count with existing key") {
        REQUIRE(map.count(1) == 1);
        REQUIRE(map.count(2) == 1);
        REQUIRE(map.count(3) == 1);
    }

    SECTION("Test count with non-existing key") {
        REQUIRE(map.count(4) == 0);
    }
}

TEST_CASE("Test Unordered_map contains", "[Unordered_map]") {
    Unordered_map<int, std::string> map;
    map.insert({1, "one"});
    map.insert({2, "two"});
    map.insert({3, "three"});

    SECTION("Test contains with existing key") {
        REQUIRE(map.contains(1));
        REQUIRE(map.contains(2));
        REQUIRE(map.contains(3));
    }

    SECTION("Test contains with non-existing key") {
        REQUIRE_FALSE(map.contains(4));
    }
}

TEST_CASE("Test Unordered_map swap", "[Unordered_map]") {
    Unordered_map<int, std::string> map1;
    map1.insert({1, "one"});
    map1.insert({2, "two"});
    map1.insert({3, "three"});

    Unordered_map<int, std::string> map2;
    map2.insert({4, "four"});
    map2.insert({5, "five"});
    map2.insert({6, "six"});

    map1.swap(map2);

    SECTION("Test map1 after swap") {
        REQUIRE(map1.size() == 3);
        REQUIRE(map1.capacity() == 4);
        REQUIRE(map1.contains(4));
        REQUIRE(map1.contains(5));
        REQUIRE(map1.contains(6));
        REQUIRE_FALSE(map1.contains(1));
        REQUIRE_FALSE(map1.contains(2));
        REQUIRE_FALSE(map1.contains(3));
    }

    SECTION("Test map2 after swap") {
        REQUIRE(map2.size() == 3);
        REQUIRE(map2.capacity() == 4);
        REQUIRE(map2.contains(1));
        REQUIRE(map2.contains(2));
        REQUIRE(map2.contains(3));
        REQUIRE_FALSE(map2.contains(4));
        REQUIRE_FALSE(map2.contains(5));
        REQUIRE_FALSE(map2.contains(6));
    }
}

TEST_CASE("Test Unordered_map merge", "[Unordered_map]") {
    Unordered_map<int, std::string> map1;
    map1.insert({1, "one"});
    map1.insert({2, "two"});
    map1.insert({3, "three"});

    Unordered_map<int, std::string> map2;
    map2.insert({4, "four"});
    map2.insert({5, "five"});
    map2.insert({6, "six"});

    map1.merge(map2);

    auto it = map1.begin();
    auto itd = map1.begin();

    Unordered_map<int, std::string>::const_iterator it1(it);
    Unordered_map<int, std::string>::const_iterator it12(std::move(it));
    Unordered_map<int, std::string>::iterator it2 = itd;
    Unordered_map<int, std::string>::iterator it22 = std::move(itd);


    SECTION("Test map1 after merge") {
        REQUIRE(map1.size() == 6);
        REQUIRE(map1.capacity() == 8);
        REQUIRE(map1.contains(1));
        REQUIRE(map1.contains(2));
        REQUIRE(map1.contains(3));
        REQUIRE(map1.contains(4));
        REQUIRE(map1.contains(5));
        REQUIRE(map1.contains(6));
    }

    SECTION("Test map2 after merge") {
        REQUIRE(map2.empty());
    }
}

TEST_CASE("Test Unordered_map clear", "[Unordered_map]") {
    Unordered_map<int, std::string> map;
    map.insert({1, "one"});
    map.insert({2, "two"});
    map.insert({3, "three"});

    map.clear();

    SECTION("Test size after clear") {
        REQUIRE(map.size() == 0);
    }

    SECTION("Test capacity after clear") {
        REQUIRE(map.capacity() == 0);
    }

    SECTION("Test empty after clear") {
        REQUIRE(map.empty());
    }
}

TEST_CASE("Test Unordered_map reserve", "[Unordered_map]") {
    Unordered_map<int, std::string> map;

    map.reserve(10);

    SECTION("Test capacity after reserve") {
    REQUIRE(map.capacity() == 10);
    }

    SECTION("Test empty after reserve") {
    REQUIRE(map.empty());
    }
}

TEST_CASE("Test Unordered_map copy constructor", "[Unordered_map]") {
    Unordered_map<int, std::string> original_map;
    original_map.insert({1, "one"});
    original_map.insert({2, "two"});
    original_map.insert({3, "three"});

    Unordered_map<int, std::string> copied_map(original_map);

    SECTION("Test size after copy constructor") {
        REQUIRE(copied_map.size() == 3);
    }

    SECTION("Test capacity after copy constructor") {
        REQUIRE(copied_map.capacity() == 4);
    }

    SECTION("Test contents after copy constructor") {
        REQUIRE(copied_map.find(1) != copied_map.end());
        REQUIRE(copied_map.find(2) != copied_map.end());
        REQUIRE(copied_map.find(3) != copied_map.end());
        REQUIRE(copied_map.find(4) == copied_map.end());

        REQUIRE(copied_map.find(1)->second == "one");
        REQUIRE(copied_map.find(2)->second == "two");
        REQUIRE(copied_map.find(3)->second == "three");
    }
}

TEST_CASE("Test Unordered_map move constructor", "[Unordered_map]") {
    Unordered_map<int, std::string> original_map;
    original_map.insert({1, "one"});
    original_map.insert({2, "two"});
    original_map.insert({3, "three"});

    Unordered_map<int, std::string> moved_map{std::move(original_map)};

    SECTION("Test size after move constructor") {
        REQUIRE(moved_map.size() == 3);
    }

    SECTION("Test capacity after move constructor") {
        REQUIRE(moved_map.capacity() == 4);
    }

    SECTION("Test contents after move constructor") {
        REQUIRE(moved_map.find(1) != moved_map.end());
        REQUIRE(moved_map.find(2) != moved_map.end());
        REQUIRE(moved_map.find(3) != moved_map.end());
        REQUIRE(moved_map.find(4) == moved_map.end());

        REQUIRE(moved_map.find(1)->second == "one");
        REQUIRE(moved_map.find(2)->second == "two");
        REQUIRE(moved_map.find(3)->second == "three");
    }

    SECTION("Test original map after move constructor") {
        REQUIRE(original_map.size() == 0);
        REQUIRE(original_map.capacity() == 0);
    }
}

TEST_CASE("Test Unordered_map copy assignment operator", "[Unordered_map]") {
    Unordered_map<int, std::string> original_map;
    original_map.insert({1, "one"});
    original_map.insert({2, "two"});
    original_map.insert({3, "three"});

    Unordered_map<int, std::string> copied_map;
    copied_map = original_map;

    SECTION("Test size after copy assignment operator") {
        REQUIRE(copied_map.size() == 3);
    }

    SECTION("Test capacity after copy assignment operator") {
        REQUIRE(copied_map.capacity() == 4);
    }

    SECTION("Test contents after copy assignment operator") {
        REQUIRE(copied_map.find(1) != copied_map.end());
        REQUIRE(copied_map.find(2) != copied_map.end());
        REQUIRE(copied_map.find(3) != copied_map.end());
        REQUIRE(copied_map.find(4) == copied_map.end());

        REQUIRE(copied_map.find(1)->second == "one");
        REQUIRE(copied_map.find(2)->second == "two");
        REQUIRE(copied_map.find(3)->second == "three");
    }
}

TEST_CASE("Test Unordered_map move assignment operator", "[Unordered_map]") {
    Unordered_map<int, std::string> original_map;
    original_map.insert({1, "one"});
    original_map.insert({2, "two"});
    original_map.insert({3, "three"});

    Unordered_map<int, std::string> moved_map;
    moved_map = std::move(original_map);

    SECTION("Test size after move assignment operator") {
        REQUIRE(moved_map.size() == 3);
    }

    SECTION("Test capacity after move assignment operator") {
        REQUIRE(moved_map.capacity() == 4);
    }

    SECTION("Test contents after move assignment operator") {
        REQUIRE(moved_map.find(1) != moved_map.end());
        REQUIRE(moved_map.find(2) != moved_map.end());
        REQUIRE(moved_map.find(3) != moved_map.end());
        REQUIRE(moved_map.find(4) == moved_map.end());

        REQUIRE(moved_map.find(1)->second == "one");
        REQUIRE(moved_map.find(2)->second == "two");
        REQUIRE(moved_map.find(3)->second == "three");
    }

    SECTION("Test original map after move assignment operator") {
        REQUIRE(original_map.size() == 0);
        REQUIRE(original_map.capacity() == 0);
    }
}

TEST_CASE("Test Unordered_map max_size", "[Unordered_map]") {
    Unordered_map<int, std::string> map;

    SECTION("Test max_size") {
        REQUIRE(map.max_size() == std::numeric_limits<typename Unordered_map<int, std::string>::size_type>::max());
    }
}

TEST_CASE("Test Unordered_map find const", "[Unordered_map]") {
    Unordered_map<int, std::string> map;
    map.insert({1, "one"});
    map.insert({2, "two"});
    map.insert({3, "three"});

    SECTION("Test find existing element") {
        auto it = map.find(2);
        REQUIRE(it != map.end());
        REQUIRE(it->first == 2);
        REQUIRE(it->second == "two");
    }

    SECTION("Test find non-existing element") {
        auto it = map.find(4);
        REQUIRE(it == map.end());
    }

    SECTION("Test find erased element") {
        map.erase(2);
        auto it = map.find(2);
        REQUIRE(it == map.end());
    }
}

TEST_CASE("Test Unordered_map at const", "[Unordered_map]") {
    Unordered_map<int, std::string> map;
    map.insert({1, "one"});
    map.insert({2, "two"});
    map.insert({3, "three"});

    SECTION("Test at existing element") {
        REQUIRE(map.at(2) == "two");
    }

    SECTION("Test at non-existing element") {
        REQUIRE_THROWS_AS(map.at(4), std::out_of_range);
    }
}

TEST_CASE("Test Unordered_map erase const_iterator", "[Unordered_map]") {
    Unordered_map<int, std::string> map;
    map.insert({1, "one"});
    map.insert({2, "two"});
    map.insert({3, "three"});

    auto it = map.find(2);

    SECTION("Test erase const_iterator") {
        auto new_it = map.erase(it);
        REQUIRE(map.size() == 2);
    }
}

TEST_CASE("Unordered_map tests", "[Unordered_map]") {
    SECTION("find method") {
        Unordered_map<int, std::string> map;
        map.insert({1, "one"});
        map.insert({2, "two"});
        map.insert({3, "three"});

        SECTION("Finding existing key") {
            auto it = map.find(2);
            REQUIRE(it != map.end());
            REQUIRE(it->first == 2);
            REQUIRE(it->second == "two");
        }

        SECTION("Finding non-existing key") {
            auto it = map.find(4);
            REQUIRE(it == map.end());
        }
    }

    SECTION("insert method") {
        Unordered_map<int, std::string> map;
        auto [it, inserted] = map.insert({1, "one"});

        SECTION("Inserting a new element") {
            REQUIRE(inserted);
            //REQUIRE(it->first == 1);
            REQUIRE(it->second == "one");
        }

        SECTION("Inserting an element with existing key") {
            auto [it2, inserted2] = map.insert({1, "another one"});
            REQUIRE_FALSE(inserted2);
            REQUIRE(it2->first == 1);
            REQUIRE(it2->second == "one");
        }
    }
}
