(load "../libs/init.scm")

(define-datatype Red-blue-tree Red-blue-tree?
  (red-node (fst Red-blue-tree?)
            (snd Red-blue-tree?))
  (blue-node 
    (tlst (list-of Red-blue-tree?)))
  (leaf-node (num number?)))



;; returns a new tree with the leaves marked with the depth of red nodes encountered along the path
;; to that leaf
(define aux-mark-leaves-with-red-depth
  (lambda (rbt acc)
    (cases Red-blue-tree rbt
      (red-node (fst snd) 
                (red-node
                 (aux-mark-leaves-with-red-depth fst (+ acc 1))
                 (aux-mark-leaves-with-red-depth snd (+ acc 1))))
      (blue-node (tlst)
                 (if (null? tlst) '()
                       (cases Red-blue-tree (car tlst)
                          (red-node (fst snd)
                                    (blue-node (cons
                                                (aux-mark-leaves-with-red-depth (car tlst) (+ acc 1))
                                                (aux-mark-leaves-with-red-depth (blue-node (cdr tlst)) acc))))
                          (else
                            (blue-node (cons 
                                        (aux-mark-leaves-with-red-depth (car tlst) acc)
                                        (aux-mark-leaves-with-red-depth (blue-node (cdr tlst)) acc)))))))
      (leaf-node (num) (leaf-node acc)))))


(define mark-leaves-with-red-depth
  (lambda (rbt)
    (aux-mark-leaves-with-red-depth rbt 0)))
