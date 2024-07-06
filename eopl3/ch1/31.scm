(load "../libs/init.scm")


;; 1
;; 2
;; (foo 1 2)
;; (bar 1 (foo 1 2))
;; (baz 
;; 	(bar 1 (foo 1 2))
;; 	(biz 4 5))


(define leaf 
	(lambda (content)
		content))

(define interior-node
	(lambda (content lnode rnode)
		(list content lnode rnode)))

;; an atomic value is a leaf
(define leaf?
	(lambda (bintree)
		(not (pair? bintree))))

(define lson cadr)

(define rson caddr)

(define contents-of 
	(lambda (bintree)
		(if (leaf? bintree)
			bintree
			(car bintree))))


(equal?? (lson (interior-node 'num 1 2)) 1)
(equal?? (rson (interior-node 'num 1 2)) 2)

(equal?? (lson (interior-node 'num2 (leaf 1) (leaf 2))) (leaf 1))
(equal?? (rson (interior-node 'num2 (leaf 1) (leaf 2))) (leaf 2))

(equal?? (lson (interior-node 'num3 (interior-node 'num 1 2) (interior-node 'num 3 4))) (interior-node 'num 1 2))
(equal?? (rson (interior-node 'num3 (interior-node 'num 1 2) (interior-node 'num 3 4))) (interior-node 'num 3 4))

(equal?? (lson (interior-node 'num4 (interior-node 'num41 (leaf 1) (leaf 2)) (interior-node 'num42 (leaf 3) (leaf 4)))) (interior-node 'num41 (leaf 1) (leaf 2)))
(equal?? (rson (interior-node 'num4 (interior-node 'num41 (leaf 1) (leaf 2)) (interior-node 'num42 (leaf 3) (leaf 4)))) (interior-node 'num42 (leaf 3) (leaf 4)))


