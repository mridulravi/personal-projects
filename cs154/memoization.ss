#lang racket

(define (memoized-fib range)
  (define fib-vec 
           (make-vector range #f))
  (define (init)
    (begin 
      (vector-set! fib-vec 0 0)
      (vector-set! fib-vec 1 1)))
  (define (fib n)
    (cond [(vector-ref fib-vec n) (vector-ref fib-vec n)]
          [else (begin 
                  (vector-set! fib-vec n 
                               (+ (fib (- n 1))
                                  (fib (- n 2))))
                  (vector-ref fib-vec n))]))
  (init)
  fib)

(define (memoized-fact range)
  (define fact-vec 
           (make-vector range #f))
  (define (init)
    (begin 
      (vector-set! fact-vec 0 1)
      (vector-set! fact-vec 1 1)))
  (define (fact n)
    (cond [(vector-ref fact-vec n) (vector-ref fact-vec n)]
          [else (begin 
                  (vector-set! fact-vec n 
                               (* (fact (- n 1))
                                  n))
                  (vector-ref fact-vec n))]))
  (init)
  fact)


(define fast-fact (memoized-fact 50))
(fast-fact 7)

(define fast-fib (memoized-fib 50))
(fast-fib 10)

(define (lcs l1 l2)
  (cond [(or (null? l1) (null? l2)) '()]
        [(eq? (car l1) (car l2)) (cons (car l1) (lcs (cdr l1) (cdr l2)))]
        [else (let ((rs1 (lcs (cdr l1) l2))
                    (rs2 (lcs l1 (cdr l2))))
                (if (<= (length rs1) (length rs2))
                    rs2
                    rs1))]))
                
(define (make-2d-vector r c)
  (make-vector r (lambda (x) (make-vector c #f))))

(define (2d-vector-ref vec r c)
  (vector-ref (vector-ref vec r) c))

(define (2d-vector-set! vec bec r c val)
  (vector-set! (vector-ref vec r) c val))

(define (memo-lcs l1 l2)
  (define table (make-2d-vector (length l1) (length l2)))  
  (define (memo-lcs-h l1 l2)
    (let ([n1 (- (length l1) 1)]
          [n2 (- (length l2) 1)])
      (cond [(or (null? l1) (null? l2)) '()]
            [(2d-vector-ref table n1 n2) (2d-vector-ref table n1 n2)]
            [else (let ((val (cond [(eq? (car l1) (car l2)) (cons (car l1) (memo-lcs-h (cdr l1) l2 ))]
                                   [else (let ((rs1 (memo-lcs-h (cdr l1) l2))
                                               (rs2 (memo-lcs-h l1 (cdr l2))))
                                           (if (<= (length rs1) (length rs2))
                                               rs2
                                               rs1))])))
                    val)])))
  (memo-lcs-h l1 l2))
                    
