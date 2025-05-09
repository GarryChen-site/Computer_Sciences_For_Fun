(load "../libs/init.scm")

;; var-exp : Var -> Lc-exp
;; assume var is a list, or the result will not be a proper list
(define var-exp
  (lambda (var)
    (cons 'var-exp var)))

;; lmabda-exp : Var * Lc-exp -> Lc-exp
;;(define my-lambda (lambda-exp 'x '(+ x 1)))
;;(lambda-exp (x) (+ x 1))
(define lambda-exp
  (lambda (var lc-exp)
    (list 'lambda-exp (list var) lc-exp)))

;; app-exp : Lc-exp * Lc-exp -> Lc-exp
(define app-exp
  (lambda (lc-exp1 lc-exp2)
    (list 'app-exp lc-exp1 lc-exp2)))

;; var-exp? : Lc-exp -> Bool
(define var-exp?
  (lambda (x)
    (and (pair? x) (eq? (car x) 'var-exp))))

;; lambda-exp? : Lc-exp -> Bool
(define lambda-exp?
  (lambda (x)
    (and (pair? x) (eq? (car x) 'lambda-exp))))

;; app-exp? : Lc-exp -> Bool
(define app-exp?
  (lambda (x)
    (and (pair? x) (eq? (car x) 'app-exp))))

;; var-exp->var :: Lc-exp -> Var
(define var-exp->var
  (lambda (x)
    (cdr x)))

;; lambda-exp->bound-var :: Lc-exp -> Var
(define lambda-exp->bound-var
  (lambda (x)
    (caadr x)))

;; lambda-exp->body :: Lc-exp -> Lc-exp
(define lambda-exp->body
  (lambda (x)
    (caddr x)))

;; app-exp->rator :: Lc-exp -> Lc-exp
(define app-exp->rator
  (lambda (x)
    (cadr x)))

;; app-exp->rand :: Lc-exp -> Lc-exp
(define app-exp->rand
  (lambda (x)
    (caddr x)))

;; occurs-free? : Sym * Lcexp -> Bool
(define occurs-free?
  (lambda (search-var exp)
    (cond
     ((var-exp? exp) (eqv? search-var (var-exp->var exp)))
     ((lambda-exp? exp)
      (and
       (not (eqv? search-var (lambda-exp->bound-var exp)))
       (occurs-free? search-var (lambda-exp->body exp))))
     (else
      (or
       (occurs-free? search-var (app-exp->rator exp))
       (occurs-free? search-var (app-exp->rand exp)))))))

(equal??
 (occurs-free? 'a (lambda-exp 'a (app-exp (var-exp 'b) (var-exp 'a))))
 #f)

(equal??
 (occurs-free? 'b (lambda-exp 'a (app-exp (var-exp 'b) (var-exp 'a))))
 #t)

(define expr1 '(lambda-exp (x) (+ x 1)))
(define expr2 '(lambda (x) (+ x 1)))

(equal??
 (lambda-exp? expr1)
 #t)

(equal??
  (lambda-exp? expr2)
  #f)


(define lambda-exp '(lambda-exp (x) (+ x 1)))

(equal??
 (lambda-exp->bound-var lambda-exp)
 'x)

(equal??
  (lambda-exp->body lambda-exp)
  '(+ x 1))

(exit)
