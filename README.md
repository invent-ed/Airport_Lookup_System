Team members
- Edward Gao: IDL files, airports server (k-d tree)
- Oleg Kovalenko: client, places server (trie)

Data Structures and Algorithms
- Trie
- K-D tree
- K-nearest-neighbors search using k-d tree

Strengths
- Code reasonably clean
- Implemented matching of city and state

Weaknesses
- Took way too much time implementing trie and kd-tree, at the expense of the rest of the code
- The k-nearest-neighbor algorithm is not optimized

Instructions to run
- `$ make`
- `$ ./places` in first terminal
- `$ ./airports` in second terminal
- `$ ./client localhost <city> <state>` in third terminal
