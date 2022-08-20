fun allTrue [] = false
  | allTrue (x::[]) = if x = true then true else false
  | allTrue (x::y) = (if x = true then true else false) andalso allTrue(y);