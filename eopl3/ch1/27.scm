(load "../libs/init.scm")



(define flatten 
	(lambda (lst)
		(cond ((null? lst) '())
			((not (pair? lst)) (list lst))
			(else (append (flatten (car lst))
				(flatten (cdr lst)))))))

(equal?? (flatten '(a b c)) '(a b c))
(equal?? (flatten '(b ())) '(b))
(equal?? (flatten '((a) () (b ()) () (c))) '(a b c))
(equal?? (flatten '((a b) c (((d)) e))) '(a b c d e))
(equal?? (flatten '(a b (() (c)))) '(a b c))


(exit)