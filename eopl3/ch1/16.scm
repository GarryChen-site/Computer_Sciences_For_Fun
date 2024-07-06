(load "../libs/init.scm")

(define invert
  (lambda (list)
    (if (null? list)
	'()
	  (cons
		 (sub-invert (car list))
	   (invert (cdr list))))))

(define sub-invert
	(lambda (list)
		(cons
		 (cadr list)
		 (car list))))

(equal?? (invert '((a 1) (a 2) (b 1) (b 2)))
         '((1 . a) (2 . a) (1 . b) (2 . b)))

(invert '((a 1)))
(equal?? (invert '((a 1))) '((1 . a)))
