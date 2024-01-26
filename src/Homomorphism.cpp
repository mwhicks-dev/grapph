#include "Homomorphism.h"
#include "SetFunctions.h"

#include <sstream>

namespace grapph {

    void Homomorphism::validate() {
        // Get vertex and edge sets
        std::set<vertex_t> vertex_domain_expected = from.getVertices();
        std::set<edge_t> edge_domain_expected = from.getEdges();
        std::set<vertex_t> vertex_range_superset_expected = to.getVertices();
        std::set<edge_t> edge_range_superset_expected = to.getEdges();

        // Build homomorphism domains/ranges
        std::set<vertex_t> vertex_domain;
        std::set<vertex_t> vertex_range;
        std::set<edge_t> edge_domain;
        std::set<edge_t> edge_range;
        for ( std::pair<vertex_t, vertex_t> mapping : vertex_map ) {
            vertex_domain.insert(mapping.first);
            vertex_range.insert(mapping.second);
        }
        for ( std::pair<edge_t, edge_t> mapping : edge_map ) {
            // First, ensure both edges ordered
            if ( mapping.first.first > mapping.first.second ) {
                mapping.first = { mapping.first.second, mapping.first.first };
            }
            if ( mapping.second.first > mapping.second.second ) {
                mapping.second = { mapping.second.second, mapping.second.first };
            }
            edge_domain.insert(mapping.first);
            edge_range.insert(mapping.second);
        }

        // Verify that domains and ranges are appropriate
        if ( !setEquals(vertex_domain_expected, vertex_domain) ) {
            throw std::invalid_argument("Vertex homomorphism does not map every from-vertex");
        }
        if ( !setEquals(edge_domain_expected, edge_domain) ) {
            throw std::invalid_argument("Edge homomorphism does not map every from-edge");
        }
        if ( !setContains(vertex_range_superset_expected, vertex_range) ) {
            throw std::invalid_argument("Vertex homomorphism maps to vertex not in to-vertices");
        }
        if ( !setContains(edge_range_superset_expected, edge_range) ) {
            throw std::invalid_argument("Edge homomorphism maps to edge not in to-edges");
        }

        // Verify homomorphism constraint - f_E(uv) = (f_V(u), f_E(v))
        for ( std::pair<edge_t, edge_t> mapping : edge_map ) {
            if ( mapping.second.first != vertex_map[mapping.first.first]
                    || mapping.second.second != vertex_map[mapping.first.second] ) {
                std::stringstream ss;
                ss << "Failed homomorphism constraint - f_E(uv) = (f_V(u), f_E(v)) "
                    << "for u = " << mapping.first.first << " & v = " << mapping.first.second;
                throw std::invalid_argument(ss.str());
            }
        }
    }

    Homomorphism::Homomorphism(Graph& from, Graph& to, vfunc_t vertex_map)
            : from(from), to(to), vertex_map(vertex_map), edge_map() {
        for ( edge_t edge : from.getEdges() ) {
            edge_t mapped_edge = { vertex_map[edge.first], vertex_map[edge.second] };
            if ( mapped_edge.first > mapped_edge.second ) {
                vertex_t temp = mapped_edge.first;
                mapped_edge.first = mapped_edge.second;
                mapped_edge.second = temp;
            }
            edge_map[edge] = mapped_edge;
        }

        validate();
    }

    bool Homomorphism::isInjective() {
        // Assert no two vertices map to same vertex
        std::set<vertex_t> vertex_range;
        for ( std::pair<vertex_t, vertex_t> mapping : vertex_map ) {
            if ( vertex_range.count( mapping.second ) != 0 )  return false;
            vertex_range.insert( mapping.second );
        }

        // Assert no two edges map to same edge
        std::set<edge_t> edge_range;
        for ( std::pair<edge_t, edge_t> mapping : edge_map ) {
            if ( edge_range.count( mapping.second ) != 0 )  return false;
            edge_range.insert( mapping.second );
        }

        return true;
    }

    bool Homomorphism::isSurjective() {
        // Assert every to-vertex in vertex range
        std::set<vertex_t> vertex_range;
        for ( std::pair<vertex_t, vertex_t> mapping : vertex_map ) {
            vertex_range.insert( mapping.second );
        }
        std::set<vertex_t> expected_vertex_range = to.getVertices();
        if ( !setEquals( vertex_range, expected_vertex_range ) )  return false;

        // Assert every to-edge in edge range
        std::set<edge_t> edge_range;
        for ( std::pair<edge_t, edge_t> mapping : edge_map ) {
            edge_range.insert( mapping.second );
        }
        std::set<edge_t> expected_edge_range = to.getEdges();
        if ( !setEquals( edge_range, expected_edge_range ) )  return false;

        return true;
    }

    bool Homomorphism::isBijective() {
        return isInjective() && isSurjective();
    }

    Homomorphism Homomorphism::compose(Homomorphism first, Homomorphism second) {
        // Compose vertex homomorphisms
        vfunc_t vertex_map_composition;
        for ( std::pair<vertex_t, vertex_t> mapping : first.getVertexHomomorphism() ) {
            vertex_map_composition[mapping.first] = second.getVertexHomomorphism()[mapping.second];
        }

        // Compose edge homomorphisms
        efunc_t edge_map_composition;
        for ( std::pair<edge_t, edge_t> mapping : first.getEdgeHomomorphism() ) {
            edge_map_composition[mapping.first] = second.getEdgeHomomorphism()[mapping.second];
        }

        // Create and return composed homomorphism
        Homomorphism composed = Homomorphism(first.getFromGraph(), second.getToGraph(),
                                             vertex_map_composition, edge_map_composition);
        return composed;
    }

}