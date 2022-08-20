fun multiPairs (x,y) = if x = [] then [] else ((hd x)*(hd y))::(multiPairs((tl x),(tl y)));

multiPairs ([2,5,10],[4,10,8]);