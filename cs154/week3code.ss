#lang racket
 
; A higher order function for series summation
(define (hof t r f g k)
  (define (hof_h i)
    (if (= i k) (f (t i) (r i))
        (f (t i) (g (r i) (hof_h (+ i 1))))))
  (hof_h 1)) 

(define (tan x k) (hof (lambda (i) (if (= i 1) x (expt x 2)))
                       (lambda (i) (- (* 2 i) 1))
                       /
                       -
                       k)) 

(define (nested-sqrt x k) 
   (hof (lambda (i) 0)    ;; You could repace the 0 by anything else
        (lambda (i) x)    ;; because f throws away the first argument
        (lambda (a b) (sqrt b))
        +
        k))

;(define (sin x k) (hof (lambda (i) (/ x (factorial (- (* 2 i) 1))))
;                       (lambda (i) (* x x))
;                       -
;                       *))

;The emi calculator

(define (balance pr r y mp)
  (if (= y 0) pr
      (let ([newpr (- (+ pr (* pr r (/ 1 100))) (* 12 mp))])
        (balance newpr r (- y 1) mp))))

(define (emi pr r y) (zero (lambda (mp) (balance pr r y mp))))

(define delta 0.0001)

(define (diff f x) (/ (- (f (+ x delta)) (f x)) delta))

(define (until p f x)
  (if (p x) x
      (until p f (f x))))

(define (zero f) 
  (let ([initial 1.0]
        [improve (lambda (xi) (- xi (/ (f xi) (diff f xi))))]
        [goodenough (lambda (xi) (< (abs (f xi)) delta))])
    (until goodenough improve initial)))

; Representing regions

(define (make-point x y)
  (cons x y))

(define (x-of point)
  (car point))

(define (y-of point)
  (cdr point))

(define (print-point point)
  (newline)
  (display "(")
  (display (x-of point))
  (display ",")
  (display (y-of point))
  (display ")"))
   
(define (circle-maker r) 
  (lambda (p) (<= (+ (sqr (x-of p)) (sqr (y-of p))) (sqr r))))

(define circle1 (circle-maker 5))

(define (in region point) (region point))

(define (square-maker s)
  (lambda (p) (and  (<= (abs (x-of p)) (/ s 2)) (<= (abs (y-of p)) (/ s 2)))))

(define square1 (square-maker 10))


(define (intersection r1 r2)
  (lambda (p) (and (in r1 p) (in r2 p))))


;(define (translate region amount)
;  (define (translate-back point)
;    (make-point (- (x-of point) (x-of amount))
;                (- (y-of point) (y-of amount))))
;  (lambda (p) (in  region  (translate-back point))))

