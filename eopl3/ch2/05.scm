(load "../libs/init.scm")

(define empty-env
  (lambda ()
    '()))

(define extend-env
  (lambda (var val env)
    (cons (cons var val) env)))

(define apply-env
  (lambda (env search-var)
    (cond 
      ((null? env)
        (report-no-binding-found search-var))
      ((eqv? (caar env) search-var)
        (cdar env))
      (else
        (apply-env (cdr env) search-var)))))

(define report-no-binding-found
  (lambda (search-var)
    (error 'apply-env "No binding for: " search-var)))


(define e
  (extend-env 'd 6
    (extend-env 'y 8
       (extend-env 'x 7
	  (extend-env 'y 14
	    (empty-env))))))

(equal?? (apply-env e 'd) 6)
(equal?? (apply-env e 'y) 8)
(equal?? (apply-env e 'x) 7)
(equal?? (apply-env e 'd) 6)

(exit)