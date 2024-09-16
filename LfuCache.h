#pragma once
#include <cassert>
#include <list>
#include <unordered_map>

using Tick = uint32_t;

Tick curTick = 0;

Tick GetCurTick() {
    return ++curTick;
}

class LFUCache {

    struct ListItem
    {
        int key;
        uint32_t m_freq;
        Tick m_lastTick;
    };

    using List = std::list<ListItem>;

    static bool CmpListItems(const ListItem& lhs, const ListItem& rhs) {
        if (lhs.m_freq < rhs.m_freq)
            return true;
        if (lhs.m_freq > rhs.m_freq)
            return false;

        return lhs.m_lastTick < rhs.m_lastTick;
    }

    struct MapValueItem
    {
        int m_value;
        List::iterator m_listIt;
    };

    static void UpdateListItem(List& list, List::iterator it) {
        ++it->m_freq;
        it->m_lastTick = GetCurTick();

        auto nextIt = std::next(it);
        if (nextIt == list.end() || CmpListItems(*it, *nextIt))
            return;

        while (nextIt != list.end() && !CmpListItems(*it, *nextIt))
            ++nextIt;

        list.splice(nextIt, list, it);
    }

public:
    LFUCache(int capacity)
        : m_capacity(capacity)
    {}

    int get(int key) {
        auto it = m_map.find(key);
        if (it == m_map.end())
            return -1;

        MapValueItem& mapValue = it->second;
        auto& listIt = mapValue.m_listIt;

        UpdateListItem(m_list, listIt);

        return mapValue.m_value;
    }

    void put(int key, int value) {
        auto [it, added] = m_map.emplace(key, MapValueItem{ value, {} });
        MapValueItem& mapValue = it->second;
        if (added) {
            if (m_map.size() > m_capacity) {
                m_map.erase(m_list.front().key);
                m_list.front() = { key, 0 };
            }
            else {
                m_list.emplace_front(key, 0);
            }

            mapValue.m_listIt = m_list.begin();
            UpdateListItem(m_list, m_list.begin());
        }
        else {
            mapValue.m_value = value;
            UpdateListItem(m_list, mapValue.m_listIt);
        }
    }

    const int m_capacity;
    std::map<int, MapValueItem> m_map;
    List m_list;
};