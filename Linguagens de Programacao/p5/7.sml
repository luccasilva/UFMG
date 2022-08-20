exception NegativeNum

signature MATH =
sig
   val fact : int -> int
   val halfPi : real
   val pow : int * int -> int
   val double : int -> int
end;

structure MyMathLib :> MATH =
struct
   fun fact 0 = 1
      | fact n = if n > 0 then n * fact (n-1) else raise NegativeNum

   val halfPi = Math.pi/2.0

   fun pow (n,0) = 1
      | pow (n,x) = if n > 0 then n * pow (n , x-1) else raise NegativeNum

   fun double n = if n > 0 then n*2 else raise NegativeNum
end;

fun useMyMathLib (n , opr) =
   let fun f n "fact" = print(Int.toString(MyMathLib.fact(n)))
      | f n "pow" = print(Int.toString(MyMathLib.pow(n, n)))
      | f n "double" = print(Int.toString(MyMathLib.double(n)))
      | f n _ = raise Match
   in
      f n opr
   end
   handle NegativeNum => print("Números negativos!");