#lang racket

; If you require global state variables define them here



; ------------------------------------------------------
(define state 'start)

(define (f x)
  (cond [(eq? state 'start) (if (= x 0)
                                (begin
                                  (set! state 'seen-a-0)
                                  0)
                                (begin
                                  (set! state 'seen-a-1)
                                  1))]
        [(eq? state 'seen-a-0) (if (= x 1)
                                (begin
                                  (set! state 'start)
                                  0)
                                'ignore)]
        [(eq? state 'seen-a-1) (if (= x 0)
                                (begin
                                  (set! state 'start)
                                  0)
                                'ignore)]))
                                