(load "../libs/init.scm")


(define interior-node? list?)


(load "31.scm")



(define number-leaves
  (lambda (bt)
    (car (number-leaves-from bt 0))))

;; Use let* when there is a linear dependency among the values or when the order of evaluation is important.
;; The order of evaluation is important in this case because the value of the left subtree is used to calculate the value of the right subtree.


(define number-leaves-from
  (lambda (bt n)
    (cond
      ((null? bt) (list bt n))
      ((leaf? bt) (list n (+ n 1)))
      ((interior-node? bt)
        (let* ([lt (number-leaves-from (lson bt) n)]
               [rt (number-leaves-from (rson bt) (cadr lt))])
          (list (interior-node (car bt) (car lt) (car rt)) (cadr rt)))))))


(equal?? (number-leaves
          (interior-node 'root
                          (leaf 'A)
                         (interior-node 'B
                                        (leaf 'C)
                                        (leaf 'D))))
        '(root
          0
          (B 1 2)))

(equal?? (number-leaves
         (interior-node 'foo
                        (interior-node 'bar
                                       (leaf 26)
                                       (leaf 12))
                        (interior-node 'baz
                                       (leaf 11)
                                       (interior-node 'quux
                                                      (leaf 117)
                                                      (leaf 14)))))
        '(foo
          (bar 0 1)
          (baz 2 (quux 3 4))))




(exit)