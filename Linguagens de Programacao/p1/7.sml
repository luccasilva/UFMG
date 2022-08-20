fun splitAux x =
 if (Char.compare (x,#",") = EQUAL) then true
 else
 if ( Char.compare (x,#".") = EQUAL) then true
 else
 if  ( Char.compare (x,#"-") = EQUAL) then true
 else
 if ( Char.compare (x,#" ") = EQUAL) then true
 else false;

fun split x = String.tokens splitAux x;