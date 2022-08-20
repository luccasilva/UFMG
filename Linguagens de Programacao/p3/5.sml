fun count (initial:int, last:int) =
  if initial = last
    then last::[]
  else initial::count (initial+1, last);

fun count_main (x:int) =
  let fun count (y:int) =
  if y = x
    then x::[]
  else y::count(y+1);
    in count(1)
   end;