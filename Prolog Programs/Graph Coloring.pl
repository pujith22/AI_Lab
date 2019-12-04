graphColoring(A,b,c,d,e):- different(a,b), different(b,c), different(c,d),different(d,e),different(e,a).

different(red,blue).
different(blue,red).
different(green,red).
different(red,green).
different(green,blue).
different(blue,green).