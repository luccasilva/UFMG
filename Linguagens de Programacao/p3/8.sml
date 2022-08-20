fun split(nil) = (nil, nil)
    |split([x]) = ([x], nil)
    |split(x::y::rest) =

  let
    val (left,right) = split(rest)
  in (x::left, y::right)
  end;

