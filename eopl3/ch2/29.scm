(load "../libs/init.scm")

(define id?
  (lambda (symbol)
    (not (and (symbol? symbol)
              (eqv? symbol 'lambda)))))

(define list-of
  (lambda (pred)
    (lambda (val)
      (or (null? val)
          (and (pair? val)
                (pred (car val))
                ((list-of pred)(cdr val)))))))

(define-datatype lc-expr lc-expr?
  (var-expr
   (var id?))
  (lambda-expr
   (bound-vars (list-of id?))
   (body      lc-expr?))
  (app-expr
   (rator lc-expr?)
   (rands  (list-of lc-expr?))))

(define parse
  (lambda (exp)
    (cond
      ((eqv? exp 'lambda)
        (error 'parse "lambda is not a valid id"))
      ((symbol? exp) 
        (var-expr exp))
      ((and (pair? exp) (eqv? (car exp) 'lambda))
        ;; access the second and third elements of the list
        (lambda-expr (cadr exp) (parse (caddr exp))))
      ((pair? exp) 
        (app-expr (parse (car exp)) (map parse (cdr exp))))
      (else
        (error 'parse "parse error")))))