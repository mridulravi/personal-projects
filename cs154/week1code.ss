#lang racket
; Week 1 Code Summary

;concept of recursion
;(factorial n)
;(add x y)
;(add-single x y z)
;(addc x y c)
;(convert x y)
;(mult x y)
;syntax of let, let*

;-----------------------------------------------------------------------------
(require (lib "trace.ss"))  ;In case you want to trace a function 
;; The Josephus problem  

(define (survives position total)
(cond ((< total 3) #t)
 ((= position 3) #f)
    (else (let ((newpos (if (< (- position 3) 0)
                            (+  (- total 3)  position)
                            (- position 3))))
            (survives newpos (- total 1))))))

;-----------------------------------------------------------------------------




;; Useful functions  

(define (even? y) (= 0 (modulo y 2)))
(define (odd? y) (not (even? y)))

;;Problems that I have done in the class

(define (add-single x y z)
  (if (and (<= 0 x) (<= x 9)
           (<= 0 y) (<= y 9)
           (<= 0 z) (<= z 9))
           (+ x y z) (error "Arguments of wrong size")))


(define (addc x y c)
  (cond [(and (= x 0) (= y 0)) c]
        [else (let ([column-add (add-single (remainder x 10) (remainder y 10) c)]
                        [qx10 (quotient x 10)]
                        [qy10 (quotient y 10)]
                        [rx10 (remainder x 10)]
                        [ry10 (remainder y 10)])
                  (convert (addc qx10 qy10 (quotient column-add 10))
                                (remainder column-add 10)))]))
(define (add x y) (addc x y 0))
(define (convert x y) (+ (* 0 x) y))


(define (mult x y)
  (if (= y 0) 0
      (convert1 (mult x (quotient y 10)) (multn1 x (remainder y 10)))))

(define (convert1 x y) (add (* x 10) y))

(define (multn1 x y) (multn1c x y 0))

(define (multn1c x y c) 
  (if (= x 0) c
      (let ([qx10 (quotient x 10)]
             [rx10 (remainder x 10)])
        (convert (multn1c qx10 y (quotient (mult-and-add-single rx10 y c) 10))
                 (remainder  (mult-and-add-single rx10 y c) 10)))))

(define (mult-and-add-single x y c)
  (if (and (<= 0 x) (<= x 9)
              (<= 0 y) (<= y 9)
              (<= 0 c) (<= y c)) 
              (+ (* x y) c) (error "Arguments of wrong size")))

; tail-recursive programs

(define (fib-iter n)
  (define (fib-iter-h i res1 res2)
    (cond [(= i n) (+ res1 res2)]
          [else (fib-iter-h (+ i 1) res2 (+ res1 res2))]))
  (cond [(= n 0) 0]
        [(= n 1) 1]
        [else (fib-iter-h 2 0 1)]))

(define (fast-expt b n)
  (define (fast-expt-helper b n a)
    (if (= n 0) a
	(if (even? n) 
	    (fast-expt-helper (* b b) (/ n 2) a)
	    (fast-expt-helper  b  (- n 1) (* a b)))))
  (fast-expt-helper b n 1))

