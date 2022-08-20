datatype dinheiro = Centavos of int | Reais of real | Pessoa_Dinheiro of string*real ;

fun amount (Centavos(x)) = x
  | amount (Reais(x)) = (floor(x*100.0))
  | amount (Pessoa_Dinheiro (x,y))  = (floor(y*100.0));