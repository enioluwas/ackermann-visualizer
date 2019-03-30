# ackermann-visualizer

A basic tool for visually tracing the recursive call stack for the [Ackermann–Péter function](https://en.wikipedia.org/wiki/Ackermann_function).

## Build

### gcc

 ``` bash
 g++ -std=c++11 -o ackermann_visualizer ackermann_visualizer.cpp
```

### clang

```bash
clang++ -Wall -std=c++11 ackermann_visualizer.cpp -o ackermann_visualizer
```

## Usage

```bash
 ackermann_visualizer m n [filename]
 ```

- m: positive integer m in A(m, n)
- n: positive integer n in A(m, n)
- filename: optionally output to a file instead of console

### Example

```bash
 ackermann_visualizer 2 2
 ```

 Output:

```
A(1, 2)
A(0, A(1, 1))
A(0, A(0, A(1, 0)))
A(0, A(0, A(0, 1)))
A(0, A(0, 2))
A(0, 3)
Value: 4
Number of calls: 6
Run time: 0.000000 seconds
```

#### Note

This program may crash with high enough input values due to a recursion stack overflow. The Ackermann call stack grows very quickly.

#### Why?

Examining the definition of the function, Let RA(m, n) define the number of calls to A(m, n).

<img src="https://latex.codecogs.com/gif.latex?RA(m,n)=&space;\begin{cases}&space;1&space;&&space;\text{for&space;}&space;m=0\\&space;1&space;&plus;&space;RA(m-1,&space;1)&space;&&space;\text{for&space;}&space;m>0&space;\text{&space;and&space;}&space;n=0\\&space;1&space;&plus;&space;RA(m,&space;n-1)&space;&plus;&space;RA(m-1,&space;A(m,&space;n-1))&space;&&space;\text{for&space;}&space;m>0&space;\text{&space;and&space;}n>0&space;\\&space;\end{cases}" title="RA(m,n)= \begin{cases} 1 & \text{for } m=0\\ 1 + RA(m-1, 1) & \text{for } m>0 \text{ and } n=0\\ 1 + RA(m, n-1) + RA(m-1, A(m, n-1)) & \text{for } m>0 \text{ and }n>0 \\ \end{cases}" alt="RA(m, n)"/>

It can be concluded through some proof that:

<img src="https://latex.codecogs.com/gif.latex?RA(m,n)=(n&plus;1)&space;&plus;&space;RA(m-1,1)&space;&plus;&space;\sum_{k=0}^{n-1}&space;RA(m-1,A(m,k))" title="RA(m,n)=(n+1) + RA(m-1,1) + \sum_{k=0}^{n-1} RA(m-1,A(m,k))" />

So for example:

<img src="https://latex.codecogs.com/gif.latex?RA(3,n)&space;=&space;128\frac{4^n-1}{3}&space;-&space;40\left(2^n-1\right)&space;&plus;&space;3n&space;&plus;&space;15" title="RA(3,n) = 128\frac{4^n-1}{3} - 40\left(2^n-1\right) + 3n + 15" />

So, the number of calls for A(3, 6):

<img src="https://latex.codecogs.com/gif.latex?RA(3,6)&space;=&space;172233" title="RA(3,6) = 172233" />

And even crazier:

<img src="https://latex.codecogs.com/gif.latex?RA(4,1)=2862984010" title="RA(4,1)=2862984010" />

[Source](https://math.stackexchange.com/questions/2511594/ackermann-function-how-to-calculate-the-number-of-times-it-calls-itself?answertab=votes#tab-top)

It is then evident how quickly one can hit the limit of the stack size even for small integer input. Also, I doubt most of the output would be useful visually for computations with that level of recursion. This program is however quite nice for input that produces smaller output.

## License

[MIT](https://github.com/enioluwa23/ackermann-visualizer/blob/master/LICENSE)
