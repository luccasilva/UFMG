﻿fun calculePow (x:int) =
  let
  fun pow(x:int, y:int)=
    if y=0
      then 1
    else x*pow(x, y-1)
    in pow(x, 2)
  end;