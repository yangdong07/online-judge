
## Pick 定理

参考 https://en.wikipedia.org/wiki/Pick%27s_theorem

非常有趣的定理我居然才知道。。。

![pick's theorem](https://upload.wikimedia.org/wikipedia/commons/f/f1/Pick-theorem.png)

Given a **simple polygon** constructed on a grid of equal-distanced points (i.e., points with integer coordinates) such that **all the polygon's vertices are grid points**, Pick's theorem provides a simple formula for calculating the area $A$ of this polygon in terms of **the number $i$ of lattice points in the interior** located in the polygon and **the number $b$ of lattice points on the boundary** placed on the polygon's perimeter

几个概念：

1. grid/lattice，在物理中表示晶体的点阵结构。
2. 格点：横纵坐标均为为整数的点。
3. 格点多边形：多边形的顶点均为格点。

Pick 定理：  $A = i + b / 2 - 1$

可以用归纳法递归证明。主要思想是任意一个格点多边形可以用一个小的格点多边形和一个格点三角形拼在一起构成，他们有一条公共边。假设定理对小的多边形和三角形成立，则对大的格点多边形也成立。

任意格点多边形总是能够分解成若干三角形。 最后只需要证明此定理对任意格点三角形都成立即可。

证明两点：
1. Pick定理对任意格点三角形都成立
2. Pick定理对任意格点多边形的组合都成立。

具体证明参考： https://en.wikipedia.org/wiki/Pick%27s_theorem

还有一种证明方式参考： http://blog.sina.com.cn/s/blog_a1c409e30101efme.html， 是一个老师给出来的。也非常赞。

它的证明思想是一种构造生成法， 在内部的点可以认为完全占有了一个格子：$i$，  在边界上的点可以认为部分占有了一个格子。 

现在来估计顶点上的点占有了多少格子。 因为多边形内角和为  $(n - 2) * 180 \degree$。这么理解，如果一个点有 $360\degree$ 在多边形内，就认为占了一个格子； 如果有 $180\degree$ 在多边形内，就认为占了半个格子。如果内角和为 $(n - 2) * 180 \degree$， 则认为占有了 $(n - 2) / 2$ 个格子。 

在边上还有一些点，这些点占了半个格子。 所以考虑全部的边界上的点，占了 $b / 2 - 1$ 个格子。

所以总面积为 $A = i + b/ 2 - 1$。 正如文章中提到，上面的解释存在一些较为含糊、不够严谨的地方。 但是适用于教学，适合没有学过数学归纳法基础的小孩学习。


