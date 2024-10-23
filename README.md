# ADS SP24 Group3 Project2

The structure of the repository woule be like the following:

```
ADS-Project2
├── docs 
│   ├── report.pdf
│   ├── report.pptx
│   ├── interface.md
│   └── ...
├── src  
│   ├── code
│   │   ├── outputs  // All outputs of different data from graphwithdiffnode folder
│   │   ├── HeapLibrary // Different heap implementations
│   │   └── other code
│   ├── testcase
│   │   ├── graphwithdiffnode //All testcases
│   │   └── other testcases
│   └── ...
└── README.md
```
### How to run?

If you wanna run the code:
- For any ```.py``` file, click right button of your mouse to run in terminal.
- For ```.c``` file, change input file in ```fscanf```, an then run in terminal with
```bash
g++ xxx.c -o -std=c++11 xxx
./xxx
```
### Testcases

All testcases are attached, for American traffic network data, visit [DIMACS](http://www.dis.uniroma1.it/challenge9/download.shtml), our group used BAY, FLA, NY for testing.

In the testcase/graphwithdiffnode are graphs where linear stands for $M=O(N)$, quadratic-root stands for $M=O(N^{1.5})$ and quadratic stands for $M=O(N^2)$, outside that folder are other samples we've generated.

### Attention

For anyone wanna purchase a commit, follow the rules:

- Make your commit comments clear.
- Do not any purchase meaningless commit.
