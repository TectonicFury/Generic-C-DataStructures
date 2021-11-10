// topological sort is just a reverse post-order ordering of a DAG (maybe even a preorder will do)
// when doing dfs, the last line of the dfs function after looping over the adj of the said vertex, just
// push it onto a stack
