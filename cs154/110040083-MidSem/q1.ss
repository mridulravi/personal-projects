#lang racket

;; Question 1
(define (paths n)
  (cond [(= n 1) 1]
        [(= n 0) 0]
        [(= n 2) 2]
        [(= n 3) 5]
        [else (- (count n) 1)]))

(define (count n)
  (if (= n 0) 0
      (+ n (count (- n 1)))))