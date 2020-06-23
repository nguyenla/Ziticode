from itertools import permutations

INF = 1000000000

def bellman_ford_edges(n, edges, s):
    res = [INF] * n
    res[s] = 0

    for i in range(n - 1):
        for j in range(len(edges)):
            (u, v, w) = edges[j]
            if res[u] < INF:
                if res[v] > res[u] + w:
                    res[v] = max(-INF, res[u] + w)

    has_neg_cycle = False
    for j in range(len(edges)):
        (u, v, w) = edges[j]
        if res[u] != INF and res[u] + w < res[v]:
            has_neg_cycle = True

    if has_neg_cycle:
        return [-INF] * n
    else:
        return res


def main():
    # Case 1
    n = 5
    graph = [
        [0, 999, 0, 2, 0],
        [0, 0, 2, 0, 0],
        [0, 1, 0, 0, 0],
        [0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0]
    ]
    edges = [[0, 1, 999],
            [1, 2, -2],
            [2, 1, 1],
            [0, 3, 2]]
    s = 0
    print(bellman_ford_edges(n, edges, s))

    # Case 2 - Google's bunnies
    n = 5
    edges = [[0, 2, 2],
            [2, 0, 9],
            [0, 1, 2],
            [1, 0, 9],
            [0, 3, 2],
            [3, 0, 9],
            [0, 4, -1],
            [1, 2, 2],
            [2, 1, 3],
            [1, 3, 2],
            [3, 1, 3],
            [1, 4, -1],
            [4, 1, 3],
            [2, 3, 2],
            [3, 2, 2],
            [2, 4, -1],
            [4, 2, 2],
            [3, 4, -1],
            [4, 3, 2]
            ]
    s = 0
    print(bellman_ford_edges(n, edges, s))


if __name__=="__main__":
    main()
