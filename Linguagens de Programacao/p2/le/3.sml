datatype perimetro  = RConst of real 
  | PQuadrado of perimetro
  | PRetangulo of perimetro * perimetro
  | PCirculo of perimetro
  | PTriangulo of perimetro * perimetro * perimetro;

fun eval (RConst c) = c
  | eval (PQuadrado (c)) = 4.0 * eval(c)
  | eval (PRetangulo (c1,c2)) = 2.0 * (eval(c1) + eval(c2))
  | eval (PCirculo (c)) = 2.0 * 3.14 * eval(c)
  | eval (PTriangulo (c1,c2,c3)) = (eval c1) + (eval c2) + (eval c3);