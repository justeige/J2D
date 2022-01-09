#ifndef JUL_MAP_EXT_H
#define JUL_MAP_EXT_H

/*
MIT License

Copyright(c) 2019 Julian Steigerwald

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright noticeand this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <map>
#include <unordered_map>
#include <vector>

namespace jul 
{
    // ---------------------------------------------------------------------------------
    // Does a map contain a certain key? This function will NOT create that value in the map.
    // example:
    // std::map<int, std::string> m{ {1, "one"}, {2, "two"}, {3, "three"} };
    // bool has_one = contains(m, 1);
    //
    // => has_one = true
    // ---------------------------------------------------------------------------------
    template <class Key, class Value>
    bool contains(const std::map<Key, Value>& m, const Key& key)
    {
        auto it = m.find(key);
        return it != std::end(m);
    }

    template <class Key, class Value>
    bool contains(const std::unordered_map<Key, Value>& um, const Key& key)
    {
        auto it = um.find(key);
        return it != std::end(um);
    }



    // ---------------------------------------------------------------------------------
    // Copy all keys from a map into a vector.
    // example:
    // std::map<int, std::string> m{ {1, "one"}, {2, "two"}, {3, "three"} };
    // auto keys = copy_keys(m);
    //
    // => keys = {1,2,3}
    // ---------------------------------------------------------------------------------
    template<typename Key, typename Value>
    std::vector<Key> copy_keys(std::map<Key, Value> const& m)
    {
        std::vector<Key> keys;
        for (auto kv : m) {
            keys.push_back(kv.first);
        }
        return keys;
    }



    // ---------------------------------------------------------------------------------
    // Copy all values from a map into a vector.
    // example:
    // std::map<int, std::string> m{ {1, "one"}, {2, "two"}, {3, "three"} };
    // auto values = copy_values(m);
    //
    // => values = {"one", "two", "three"}
    // ---------------------------------------------------------------------------------
    template<typename Key, typename Value>
    std::vector<Value> copy_values(std::map<Key, Value> const& m)
    {
        std::vector<Value> values;
        for (auto kv : m) {
            values.push_back(kv.second);
        }
        return values;
    }



    // ---------------------------------------------------------------------------------
    // Split a map by copying its keys and values into vectors.
    // example:
    // std::map<int, std::string> m{ {1, "one"}, {2, "two"}, {3, "three"} };
    // auto [keys, values] = split_map(m);
    //
    // => keys = {1,2,3}, values = {"one", "two", "three"}
    // ---------------------------------------------------------------------------------
    template<typename Key, typename Value>
    std::pair<std::vector<Key>, std::vector<Value>> split_map(std::map<Key, Value> const& m)
    {
        std::vector<Key>   keys;
        std::vector<Value> values;
        for (auto [key, value] : m) {
            keys.push_back(key);
            values.push_back(value);
        }
        return {keys, values};
    }
}

#endif // JUL_MAP_EXT_H