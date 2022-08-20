fun sumLists x y = 
    if x = [] then []
    else (hd x + hd y)::(sumLists(tl x)(tl y));