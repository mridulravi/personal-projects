#lang racket

; Question 4

(define (number-paren-exps n)
  (cond [(= n 2) 0]
        [(= n 3) 2]
        [else (- (* (- n 1) (number-paren-exps (- n 1))) (count (- n 3)))]))

(define (count n)
  (if (= n 0) 0
      (+ n (count (- n 1)))))
