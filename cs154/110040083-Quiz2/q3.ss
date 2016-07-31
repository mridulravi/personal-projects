#lang racket

(define (make-monitored f)
  (define i 0)
  (define (how-many-calls?)
    i)
  (define (reset-counter)
    (begin
      (set! i 0)
      'done))
  (define (other-input l)
    (begin
      (set! i (+ i 1))
      (apply f l)))
  (define (mf x . y)
    (cond
      [(eq? x 'how-many-calls?) (how-many-calls?)]
      [(eq? x 'reset-counter) (reset-counter)]
      [else (other-input (cons x y))]))
  mf)
    
