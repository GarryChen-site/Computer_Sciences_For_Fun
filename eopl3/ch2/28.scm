(load "../libs/init.scm")

(define id?
  (lambda (symbol)
    (not (and (symbol? symbol)
        (eqv? symbol 'lambda)))))


(define-datatype lc-expr lc-expr?
  (var-expr
   (var id?))
  (lambda-expr
   (bound-var id?)
   (body  lc-expr?))
  (app-expr
   (rator lc-expr?)
   (rand  lc-expr?)))

(define unparse
  (lambda (exp)
    (cases lc-expr exp
	 (var-expr (var)
		   (symbol->string var))
	 (lambda-expr (bound-var body)
		      (format "(lambda (~a) ~a)" bound-var (unparse body)))
	 (app-expr (rator rand)
		   (format "(~a ~a)" (unparse rator) (unparse rand))))))


(define expA (var-expr 'a))
(define expB (var-expr 'b))
(define app (app-expr expA expB))
(define lexp (lambda-expr 'a app))
(equal?? (unparse app) "(a b)")
(equal?? (unparse lexp) "(lambda (a) (a b))")


(exit)