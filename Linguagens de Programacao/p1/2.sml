fun pow (0,y) = 0
  | pow (x,0) = 1
  | pow (x,1) = x
  | pow (x,y) = x*pow (x,y-1);
