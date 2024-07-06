(load "../libs/init.scm")



(define count-occurs
	(lambda (val list)
		(count-occurs-add val list 0)))

(define count-occurs-add
	(lambda (val list cnt)
		(if (null? list)
			cnt
			(if (list? (car list))
				(count-occurs-add val (cdr list) (+ (count-occurs-add val (car list) 0) cnt))
				(if (equal? (car list) val) 
					(count-occurs-add val (cdr list) (+ cnt 1))
					(count-occurs-add val (cdr list) cnt))))))




(equal?? (count-occurs 'x '((f x) y (((x z) x)))) 3)

(equal?? (count-occurs 'x '((f x) y (((x z) () x)))) 3)
(equal?? (count-occurs 'w '((f x) y (((x z) x)))) 0)


(exit)

