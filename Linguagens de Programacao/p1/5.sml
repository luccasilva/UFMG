fun cumSum [] = [0]
  | cumSum (x::[]) = [x]
  | cumSum (x::y::z) = x::cumSum(x+y::z);
