fun expr() =
  let
    val a = 1
  in
    (let val a=2 in a+1 end) + (let val b = a+2 in b+1 end)
  end;