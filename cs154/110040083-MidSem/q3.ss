#lang racket

; Question 3

(define (mult-8 x y)
  (cond [(and (>= x 0) (<= x 255)
              (>= y 0) (<= y 255)) (* x y)]
        [else (error "Input number outside range of unsigned 8-bit integer")]))

(define (div-8 x y)
  (cond [(and (>= x 0) (<= x 255)
              (>= y 0) (<= y 255)) (/ x y)]
        [else (error "Input number outside range of unsigned 8-bit integer")]))

; Do not use * or / in your code
(define (evaluate la lb)
   0)