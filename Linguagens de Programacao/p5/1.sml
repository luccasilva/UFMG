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
      | fact n = n*fact(n-1)

   val halfPi = Math.pi/2.0

   fun pow (n,0) = 1
      | pow (n,x) = n * pow(n,x-1)

   fun double n = n*2
end;