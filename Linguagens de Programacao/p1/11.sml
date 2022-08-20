datatype btree = Leaf | Node of ( btree * int * btree );

fun sumAll (Leaf) = 0
  | sumAll (Node(x,y,z)) = sumAll(x) + y + sumAll(z);