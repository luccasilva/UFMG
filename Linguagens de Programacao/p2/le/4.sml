datatype UnOp = Not;

datatype BinOp = Add 
  | Sub 
  | Mul 
  | Or 
  | Eq 
  | Gt;

datatype Sexpr = IConst of int 
  | Op1 of UnOp * Sexpr 
  | Op2 of BinOp * Sexpr * Sexpr;

fun simplify (Op2(Add,x,IConst 0)) = simplify x
  | simplify (Op2(Add,IConst 0,x)) = simplify x
  | simplify (Op2(Sub,x,IConst 0)) = simplify x
  | simplify (Op2(Mul,x,IConst 1)) = simplify x
  | simplify (Op2(Mul,IConst 1,x)) = simplify x
  | simplify (Op2(Mul,IConst 0,_)) = IConst 0
  | simplify (Op2(Mul,_,IConst 0)) = IConst 0
  | simplify (Op2(Sub,c1,c2)) =
    if (c1 = c2)
      then IConst 0
    else
      Op2(Sub,c1,c2)
  | simplify (Op2(Or,c1,c2)) =
    if (c1 = c2) 
      then simplify (c1)
    else Op2(Or,c1,c2)
  | simplify (Op1(Not,Op1(Not,x))) = simplify x
  | simplify x =
    case x of (Op1(OP,c1)) =>
      let val evalc = simplify c1; in
        if (evalc = c1)
          then x
        else
          simplify (Op1(OP,evalc))
      end
  | (Op2(OP,c1,c2)) => let
    val evalc1 = simplify c1 val evalc2 = simplify c2 in
      if (evalc1 = c1) andalso (evalc2 = c2)
        then x
      else
        simplify (Op2(OP,evalc1,evalc2))
      end
  |_ => x;