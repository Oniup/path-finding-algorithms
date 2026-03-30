#ifndef _PATH_FINDING_SPARSE_GRAPH_H_
#define _PATH_FINDING_SPARSE_GRAPH_H_

namespace path_finding {

struct Node {
    struct Edge {
        int index;
        float distance;
    };

    std::vector<Edge> index_connections;
};

class SparseGraph {
public:
    SparseGraph();

private:
    std::vector<Node> graph_;
};

} // namespace path_finding

#endif
