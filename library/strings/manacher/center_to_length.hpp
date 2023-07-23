/** @file */
#pragma once
#include "manacher.hpp"

inline int get_len(const vector<int>& man, int cl, int cr) {
    assert(0 <= cl && cr < (ssize(man)+1)/2);
    assert(cl == cr || cl+1 == cr);
    //return man[
}
