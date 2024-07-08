(load "../libs/init.scm")

(define empty-stack
  (lambda () 
    '()))

;; observers
(define empty-stack?
  (lambda (stack)
    (if (equal? stack '())
  #t
  #f)))

(define push
  (lambda (stack item)
    (cons item stack)))

(define pop
  (lambda (stack)
    (if (empty-stack? stack)
      #f
      (cdr stack))))


;; observers
(define top
  (lambda (stack)
    (if (empty-stack? stack)
      #f
      (car stack))))


