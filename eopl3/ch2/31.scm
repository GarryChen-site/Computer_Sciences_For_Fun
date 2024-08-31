(load "../libs/init.scm")

(define-datatype prefix-exp prefix-exp?
  (const-exp
   (num integer?))
  (diff-exp
   (operand1 prefix-exp?)
   (operand2 prefix-exp?)))

(define make-prefix-exp
  (lambda (lst)
    (if (null? lst)
	'()
    (if (number? (car lst))
	(cons (const-exp (car lst))
	      (cdr lst))
	(if (eqv? (car lst) '-)
	    (if (null? (cdr lst))
		(error 'make-prefix-exp "need operand")
		(let* ((next (make-prefix-exp (cdr lst)))
		       (op1 (car next))
		       (next (make-prefix-exp (cdr next)))
		       (op2 (car next))
		       (rest (cdr next)))
		  (cons (diff-exp op1 op2)
			rest))))))))


(define make-prefix
  (lambda (prog)
    (car (make-prefix-exp prog))))