fun max [] = 0
  | max (x::[]) = x
  | max (x::y) =
      let 
        val z = max y
      in
        if x > z then x else z
      end;