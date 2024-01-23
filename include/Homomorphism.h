#ifndef GRAPPH_HOMOMORPHISM_H
#define GRAPPH_HOMOMORPHISM_H

#include "Graph.h"

#include <map>

namespace grapph {

    typedef std::map<vertex_t, vertex_t>    vfunc_t;
    typedef std::map<edge_t, edge_t>        efunc_t;

    class Homomorphism {

    private:

        Graph & from;
        Graph & to;

        vfunc_t vertex_map;
        efunc_t edge_map;

        void validate();

    public:

        Homomorphism(Graph&, Graph&, vfunc_t, efunc_t);

        Graph& getFromGraph() { return from; }
        Graph& getToGraph() { return to; }

        vfunc_t getVertexHomomorphism() { return vertex_map; }
        efunc_t getEdgeHomomorphism() { return edge_map; }

        bool isInjective();
        bool isSurjective();
        bool isBijective();

        static Homomorphism compose(Homomorphism, Homomorphism);

    };

}

#endif //GRAPPH_HOMOMORPHISM_H
