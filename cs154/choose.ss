#lang racket

(define-syntax for
  (syntax-rules (:)
    [(for init : bexp : change : statements )
     (begin
       init
       (define (loop)
         (cond[bexp (begin
                      statements
                      change
                      (loop))]))
       (loop))]))
  

(define (memo-choose n r)
  (define ch (build-vector (+ n 1) (lambda (x) (make-vector (+ r 1) #f))))
  (define (initial i)
    (vector-set! (vector-ref ch i) 0 1))
  (define (helper n r)
    (cond[(vector-ref (vector-ref ch n) r)
          (vector-ref (vector-ref ch n) r)] 
         [(= n r) (begin
                    (vector-set! (vector-ref ch n) r 1)
                    (vector-ref (vector-ref ch n) r ))]
         [else (begin
                 ;(display ch)
                 ;(newline)
                 (vector-set! (vector-ref ch n) r 
                              (+ (helper (- n 1) r)
                                 (helper (- n 1) (- r 1))))
                 ;(vector-set! (vector-ref ch n) (- n r)
                              ;(vector-ref (vector-ref ch n) r))
                 (vector-ref (vector-ref ch n) r))]))
     (for (begin
          (define i 0)) :
    (<= i n) :
    (set! i (+ i 1)) :
    (initial i))
  (helper n r))
  
(define (choose n r)
  (cond[(= n r) 1]
       [(= r 0) 1]
       [else (begin
               ;(display "count\n")
               (+
              (choose (- n 1) (- r 1))
              (choose (- n 1) r)))]))



; wrong implementation, create 2d vector and use it
;(define (memo-choose n r)
;  (define ch (make-vector (+ n 1) #f))
;  (define (init)
;    (vector-set! ch 0 1)
;    (vector-set! ch n 1))
;  (define (choose r)
;    (cond[(vector-ref ch r) (vector-ref ch r)]
;         [else (begin
;                 (vector-set! ch r
;                              (+ (choose (- r 1))
                                