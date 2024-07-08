(load "../libs/init.scm")

(define empty-env
  (lambda () (list 'empty-env)))

(define extend-env
  (lambda (var val env)
    (list 'extend-env var val env)))

(define apply-env-err
  (lambda (env search-var all)
    (cond
     ((eqv? (car env) 'empty-env)
      (report-no-binding-found search-var all))
     ((eqv? (car env) 'extend-env)
      (let ((saved-var (cadr env))
	    (saved-val (caddr env))
	    (saved-env (cadddr env)))
	(if (eqv? search-var saved-var)
	    saved-val
	    (apply-env-err saved-env search-var all))))
     (else
      (report-invalid-env env)))))

(define apply-env
  (lambda (env search-var)
    (apply-env-err env search-var env)))


(define display-env-rec
  (lambda (env)
    (if (eqv? (car env) 'extend-env)
	(let ((saved-var (cadr env))
	      (saved-env (cadddr env)))
	  (printf " ~a " saved-var)
	  (display-env-rec saved-env)))))


(define display-env
  (lambda (env)
    (printf "env: ")
    (display-env-rec env)
    (newline)))



(define report-no-binding-found
  (lambda (search-var all)
    (display-env all)
    (error 'apply-env "No binding for" search-var)))

(define report-invalid-env
  (lambda (env)
    (error 'apply-env "Bad environment" env)))

(define e
  (extend-env 'd 6
      (extend-env 'y 8
         (extend-env 'x 7
            (extend-env 'y 14
                (empty-env))))))

(equal?? (apply-env e 'd) 6)
(equal?? (apply-env e 'y) 8)
(equal?? (apply-env e 'x) 7)

;; (apply-env e 'z) -> error
;; (apply-env e 'z)

(exit)