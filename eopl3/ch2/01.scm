(load "../libs/init.scm")

(define base 16)
(define bzero '())
(define bzero? null?)

;; 32 = (0 2) , 33 = (1 2), 34 = (2 2)
(define succ
  (lambda (n)
    (if (bzero? n)
  '(1)
  (let ((t (+ (car n) 1)))
    (if (= t base)
        (cons 0 (succ (cdr n)))
        (cons t (cdr n)))))))

(define pred
  (lambda (n)
    (cond
      ((bzero? n) #f)
      ((>= (car n) base) #f)
      ((equal? n '(1)) '())
      ((zero? (car n))
       (if (null? (cdr n))
    #f
    (cons (- base 1) (pred (cdr n)))))
      (else (cons (- (car n) 1) (cdr n))))))

(equal?? (succ '(0 2)) '(1 2))
(equal?? (succ '(15 2)) '(0 3))

(equal?? (pred '(0 2)) '(15 1))
(equal?? (pred '(1 2)) '(0 2))
(equal?? (pred '(0 3)) '(15 2))
(equal?? (pred '(16 2)) #f)

(exit)