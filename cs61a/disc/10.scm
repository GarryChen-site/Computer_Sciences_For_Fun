
(define (factorial x)
    (if (= x 1)
        1
        (* x (factorial (- x 1)))))

(define fib n)
    (if (< n 2)
        n
        (+ (fib (- n 1)) (fib (- n 2)))))

(define (my-append a b)
    (if (null? a)
        b
        (cons (car a) (my-append (cdr a) b))))

(car (cdr (cdr (cdr s))))


(define (duplicate lst)
    (if (null? lst)
        '()
        (cons (car lst) (cons (car lst) (duplicate (cdr lst))))))

(define (insert element lst index)
    (if (null? lst) (list element))
    (if (= index 0)
        (cons element lst)
        (else (cons (car lst) (insert element (cdr lst) (- index 1))))))