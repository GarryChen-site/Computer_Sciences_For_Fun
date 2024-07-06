(load "../libs/init.scm")


(define product
	(lambda (lst1 lst2)
		(cond ((null? lst1) '())
			(else (append (product-symbol (car lst1) lst2)
			(product (cdr lst1) lst2))))))

(define product-symbol
	(lambda (sym lst)
		(cond ((null? lst) '())
			(else (cons (list sym (car lst))
			(product-symbol sym (cdr lst)))))))


(equal?? (product '(a b c) '(x y)) '((a x) (a y) (b x) (b y) (c x) (c y)))
(equal?? (product '(x y z) '(e f g)) '((x e) (x f) (x g) (y e) (y f) (y g) (z e) (z f) (z g)))


(exit)