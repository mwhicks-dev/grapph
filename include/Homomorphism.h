#ifndef GRAPPH_HOMOMORPHISM_H
#define GRAPPH_HOMOMORPHISM_H

#include "Graph.h"

#include <map>

namespace grapph {

    typedef std::map<vertex_t, vertex_t>    vfunc_t;
    typedef std::map<edge_t, edge_t>        efunc_t;
    typedef std::pair<vfunc_t, efunc_t>     homomorphism_t;

    class Homomorphism {

    private:

        Graph & from;
        Graph & to;

        vfunc_t vertex_map;
        efunc_t edge_map;

        void validate();

        bool isInjective();
        bool isSurjective();

    public:

        Homomorphism(Graph&, Graph&, vfunc_t, efunc_t);

        bool isIsomorphism();

    };

    static vfunc_t compose(vfunc_t, vfunc_t);
    static efunc_t compose(efunc_t, efunc_t);
    static Homomorphism compose(Homomorphism, Homomorphism);

}

#endif //GRAPPH_HOMOMORPHISM_H
