#pragma once

struct Connection {
    int fromNodeId;
    int toNodeId;

    Connection(int from, int to)
        : fromNodeId(from), toNodeId(to) {}
};
