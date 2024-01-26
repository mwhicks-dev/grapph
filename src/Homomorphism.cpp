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

        std::set<vertex_t> vertex_domain;
        std::set<vertex_t> vertex_range;
        std::set<edge_t> edge_domain;
        std::set<edge_t> edge_range;

        // Validate vertex mapping
        for ( std::pair<vertex_t, vertex_t> mapping : vertex_map ) {
            vertex_domain.insert(mapping.first);
            vertex_range.insert(mapping.second);
        }
        if ( !setEquals(vertex_domain_expected, vertex_domain) ) {
            throw std::invalid_argument("Vertex homomorphism does not map every from-vertex");
        }
        if ( !setContains(vertex_range_superset_expected, vertex_range) ) {
            throw std::invalid_argument("Vertex homomorphism maps to vertex not in to-vertices");
        }

        // Construct edge mapping
        for ( edge_t edge : from.getEdges() ) {
            edge_t mapped_edge = { vertex_map[edge.first], vertex_map[edge.second] };
            if ( mapped_edge.first > mapped_edge.second ) {
                vertex_t temp = mapped_edge.first;
                mapped_edge.first = mapped_edge.second;
                mapped_edge.second = temp;
            }
            edge_map[edge] = mapped_edge;
        }

        // Validate edge mapping
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

        if ( !setEquals(edge_domain_expected, edge_domain) ) {
            throw std::invalid_argument("Edge homomorphism does not map every from-edge");
        }
        if ( !setContains(edge_range_superset_expected, edge_range) ) {
            throw std::invalid_argument("Edge homomorphism maps to edge not in to-edges");
        }
    }

    Homomorphism::Homomorphism(Graph& from, Graph& to, vfunc_t vertex_map)
            : from(from), to(to), vertex_map(vertex_map), edge_map() {
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
        // Ensure homomorphisms can be composed
        if ( !first.to.equals(second.from) ) {
            throw std::invalid_argument("Cannot compose homomorphisms of different graphs -- check order");
        }
        // Compose vertex homomorphisms
        vfunc_t vertex_map_composition;
        for ( std::pair<vertex_t, vertex_t> mapping : first.getVertexMap() ) {
            vertex_map_composition[mapping.first] = second.getVertexMap()[mapping.second];
        }

        // Create and return composed homomorphism
        Homomorphism composed = Homomorphism(first.getFromGraph(), second.getToGraph(),
                                             vertex_map_composition);
        return composed;
    }

}