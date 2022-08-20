datatype area = RConst of real 
    | AQuadrado of area 
    | ARetangulo of area * area 
    | ACirculo of area ;

fun eval (RConst c) = c
    | eval (AQuadrado(c)) = eval(c) * eval(c)
    | eval (ARetangulo(c1,c2)) = eval(c1) * eval(c2)
    | eval (ACirculo(c)) = 3.14 * eval(c) * eval(c);