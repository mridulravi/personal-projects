#lang racket

; Question 5

(struct gnode (val ltree rtree) #:transparent)
(struct leaf (val) #:transparent)

(define (valueh tree n)
  (cond
    [(leaf? tree) (leaf-val tree)]
    [(odd? n) (max (valueh (gnode-ltree tree) (- n 1)) (valueh (gnode-rtree tree) (- n 1)))]
    [(even? n) (min (valueh (gnode-ltree tree) (- n 1)) (valueh (gnode-rtree tree) (- n 1)))]))

(define (value tree)
  (valueh tree (height tree)))

(define (fast-value tree)
  (valueh tree (height tree)))

(define (height tree)
  (if (leaf? tree)
      1
      (+ 1 (max (height (gnode-ltree tree)) 
                (height (gnode-rtree tree))))))

(define test-tree
  (gnode 0 (gnode 0 (leaf 40) (gnode 0 (leaf 7) (leaf 15)))
           (gnode 0 (leaf 12) (gnode 0 (leaf 8) (gnode 0 (leaf 18) (leaf 10))))))
