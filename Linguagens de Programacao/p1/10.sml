datatype Planeta = Mercurio | Venus | Terra | Marte | Jupiter | Saturno | Urano | Netuno ;

fun planetAge (x,y) =
  if y = Mercurio then (x div 12) * 88
  else
  if y = Venus then (x div 12) * 225
  else
  if y = Terra then (x div 12) * 365
  else
  if y = Marte then (x div 12) * 687
  else
  if y = Jupiter then (x div 12) * 4332
  else
  if y = Saturno then (x div 12) * 10760
  else
  if y = Urano then (x div 12) * 30681
  else
  if y = Netuno then (x div 12) * 60190
  else 0;