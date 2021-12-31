# PageRank

This project is a simple implementation of Page Rank algorithm, using C.

## Usage
Clone the repo:
```Bash
git clone git@github.com:joshhauser/PageRank.git
```

Compile the program:
```Bash
make
```

Execute the program, with or without args:
- with args:
```Bash
./pagerank <graph path> <max_iterations> <damping factor>
```

- vithout args:
```Bash
./pagerank # default parameters are hard coded 
```
> Note that most of the time, `0.85` is recommanded for damping factor.

## Useful links

- https://towardsdatascience.com/pagerank-algorithm-fully-explained-dc794184b4af
- https://en.wikipedia.org/wiki/PageRank
