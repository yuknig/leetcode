#pragma once
#include <unordered_map>
#include <list>

class LRUCache {
public:
    LRUCache(int capacity)
        : m_capacity(capacity)
    {}

    int get(int key) {
        auto it = m_map.find(key);
        if (it == m_map.end())
            return -1;

        m_list.splice(m_list.end(), m_list, it->second.second);
        //m_list.erase(it->second.second);
        //m_list.push_back(key);
        it->second.second = std::prev(m_list.end());
        return it->second.first;
    }

    void put(int key, int value) {
        auto [it, added] = m_map.emplace(key, MapValue(value, {}));
        if (added) {
            m_list.push_back(key);
            it->second.second = std::prev(m_list.end());

            if (m_map.size() > static_cast<size_t>(m_capacity)) {
                const int oldestKey = m_list.front();
                m_list.pop_front();
                m_map.erase(oldestKey);
            }
        }
        else {
            m_list.splice(m_list.end(), m_list, it->second.second);
            //m_list.erase(it->second.second);
            //m_list.push_back(key);
            it->second = { value, std::prev(m_list.end()) };
        }
    }

    const int m_capacity;
    using MapValue = std::pair<int, std::list<int>::iterator>;
    std::unordered_map<int, MapValue> m_map;
    std::list<int> m_list;
};
