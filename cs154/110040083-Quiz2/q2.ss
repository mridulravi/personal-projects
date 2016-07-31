#lang racket

;--------------------------------------------------------------------------
;------------------------------- 2 a --------------------------------------
(define (for)
  (define x 1)
  (define y 1)
  (define (for-helper i a b)
    (if (< i 10)
        (for-helper (+ i 1) (+ i a (* 2 b)) (* 2 b))
        (+ a b)))
  (for-helper 0 x y))

;--------------------------------------------------------------------------
;------------------------------------2 b ----------------------------------
(define-syntax while
  (syntax-rules (:)
    [(while condition : statement)
     (letrec ((loop (lambda ()
                      (cond [condition (begin
                                         statement
                                         (loop))]))))
       (loop))]))

(define ans 0)
(define temp 0)

(define (fib n)
  (if (= n 1)
      1
  (begin
  (cond [(= n 0) 0]
        [(= n 1) 1]
        [else (let* ((fib-before-last 0)
                    (last-fib 1)
                    (i 1))
                    (while (< i n) : (begin
                                       (set! temp last-fib)
                                       (set! last-fib (+ last-fib fib-before-last))                                       
                                       (set! fib-before-last temp)
                                       (set! ans last-fib)
                                       (set! i (+ i 1)))))])
  ans)))

