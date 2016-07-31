#lang racket

(define state (list 0 0 0))

(define (sum l)
  (cond[(null? l) 0]
       [else (+ (car l)
                (sum (cdr l)))]))

(define (fun)
  (begin
    (define a (read))
    (display (sum state))
    (set! state (append (cdr state) (list a)))
    (fun)))