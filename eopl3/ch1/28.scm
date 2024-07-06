(load "../libs/init.scm")


(define merge
	(lambda (loi1 loi2)
		(cond ((and (null? loi1) (not (null? loi2)))
			loi2)
			((and (not (null? loi1)) (null? loi2))
			loi1)
			(else (let ((f1 (car loi1))
				(f2 (car loi2)))
				(if (< f1 f2)
					(cons f1 (merge (cdr loi1) loi2))
					(cons f2 (merge loi1 (cdr loi2)))))))))


(equal?? (merge '(1 4) '(1 2 8)) '(1 1 2 4 8))
(equal?? (merge '(35 62 81 90 91) '(3 83 85 90))
	 '(3 35 62 81 83 85 90 90 91))

(exit)