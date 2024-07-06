(load "../libs/init.scm")
(load "31.scm")

(define double-tree
	(lambda (bintree)
		(if (leaf? bintree)
			(* 2 bintree)
			(interior-node (contents-of bintree)
				(double-tree (lson bintree))
				(double-tree (rson bintree))))))

(equal?? (double-tree (interior-node 'num 
	1 2))
'(num 2 4))

(equal?? (double-tree (interior-node 'num2 
	(leaf 1)
	(leaf 2)))
'(num2 2 4))

(equal?? (double-tree (interior-node 'numall
	(interior-node 'num1 
		(leaf 1)
		(leaf 2))
	(interior-node 'num2 
		(leaf 3)
		(leaf 4))))
'(numall (num1 2 4) (num2 6 8)))


(equal?? (double-tree (interior-node 'red
	(interior-node 'bar
		(leaf 26)
		(leaf 12))
	(interior-node 'red
		(leaf 11)
		(interior-node 'quux
			(leaf 117)
			(leaf 14))))) 
'(red (bar 52 24) (red 22 (quux 234 28))))
;;
;;
(exit)


