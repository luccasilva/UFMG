fun good_max(a:int list) =

  if null a
    then 0

  else if null (tl a)
    then hd a

  else
    let val resposta = good_max (tl a)
  
  in
  if hd a > resposta
    then hd a
  else resposta
  end;

