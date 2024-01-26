#ifndef GRAPPH_SETFUNCTIONS_H
#define GRAPPH_SETFUNCTIONS_H

#include <set>

namespace grapph {

    template <typename T>
    static std::set<T> setUnion(std::set<T>& first, std::set<T>& second) {
        std::set<T> set_union;

        for ( T t : first ) {
            set_union.insert(t);
        }

        for ( T t : second ) {
            set_union.insert(t);
        }

        return set_union;
    }

    template <typename T>
    static std::set<T> setIntersection(std::set<T>& first, std::set<T>& second) {
        std::set<T> set_intersection;

        for ( T t : first ) {
            if ( second.count(t) != 0 )  set_intersection.insert(t);
        }

        return set_intersection;
    }

    template <typename T>
    static std::set<T> setDifference(std::set<T>& minuend, std::set<T>& subtrahend) {
        std::set<T> set_difference;

        for ( T t : minuend ) {
            if ( subtrahend.count(t) == 0 )  set_difference.insert(t);
        }

        return set_difference;
    }

    template <typename T>
    static bool setContains(std::set<T>& super, std::set<T>& sub) {
        for ( T t : sub ) {
            if ( super.count(t) == 0 )  return false;
        }

        return true;
    }

    template <typename T>
    static bool setEquals(std::set<T>& a, std::set<T>& b) {
        return setContains(a, b) && setContains(b, a);
    }

}

#endif //GRAPPH_SETFUNCTIONS_H
