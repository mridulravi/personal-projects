#lang racket

(define (fib n)
   (cond[(= n 0) 0]
        [(= n 1) 1]
        [else 
         (+ (fib (- n 1)) (fib (- n 2)))]))

;Memoization:

(define (memoized-fib range)
  (define fib-vec (make-vector range #\_))
  (define (init) (begin 
                   (vector-set! fib-vec 0 0)
                   (vector-set! fib-vec 1 1)))
  (define (fib n)
    (display fib-vec)
    (newline)
    (cond [(number? (vector-ref fib-vec n)) (vector-ref fib-vec  n)]
          [else (begin
                  (vector-set! fib-vec n (+ (fib (- n 1)) (fib (- n 2))))
                  (vector-ref fib-vec n))]))
  (init)
  fib)
    
 
 ;1,2,5,10,20,25,50
 
(define (minchange n r)
  (cond [(= n 0) 0]
        [(= r 1) n]
        [(< n r) (minchange n (next r))]
        [(min (+ 1 (minchange (- n r) r))
              (minchange n (next r)))]))

(define (next r)
  (cond [(= r 50) 25]
        [(= r 25) 20]
        [(= r 20) 10]
        [(= r 10) 5]
        [(= r 5) 2]
        [(= r 2) 1]))

(define (index r)
  (cond [(= r 50) 0]
        [(= r 25) 1]
        [(= r 20) 2]
        [(= r 10) 3]
        [(= r 5) 4]
        [(= r 2) 5]))  

(define (memoized-minchange range)
  (define mc-vec (make-2d-vec range 6 #\_))

  (define  (minchange n r)
    (cond [(= n 0) 0]
          [(= r 1) n]
          [(< n r) (cond [(number? (2d-vector-ref mc-vec  n (index r))) 
                          (2d-vector-ref mc-vec  n (index r))]
                         [else (begin (2d-vector-set! mc-vec  n  (index r) (minchange n (next r)))
                                      (2d-vector-ref mc-vec n (index r)))])]
          [else (cond [(number? (2d-vector-ref mc-vec n (index r))) (2d-vector-ref mc-vec  n (index r))]
                      [else (begin
                              (2d-vector-set! mc-vec n (index r) (min (+ 1 (minchange (- n r) r)) (minchange n (next r))))
                              (2d-vector-ref mc-vec n (index r)))])]))
  minchange)

(define (make-2d-vec r c initial)
  (build-vector r (lambda (x) (make-vector c initial))))

(define (lcs l1 l2)
  (cond ((or (null? l1) (null? l2)) `())
        ((eq? (car l1) (car l2)) 
         (cons (car l1) (lcs (cdr l1) (cdr l2))))
        (else (let ((res1 (lcs (cdr l1) l2))
                    (res2 (lcs l1 (cdr l2))))
                (if (>= (length res1) (length res2)) res1 res2)))))




(define (memo-lcs l1 l2)
  (define table (make-2d-vector 
                 (length l1)  
                 (length l2)))
  (define (memo-lcs-h l1 l2)
    (let ((n1 (- (length l1) 1))
          (n2 (- (length l2) 1)))
      (cond ((or (null? l1) (null? l2)) `())
            ((list? (2d-vector-ref table  n1 n2))         
             (2d-vector-ref table  n1 n2))
            (else 
             (let ((val 
                    (cond ((eq? (car l1) (car l2))     
                           (cons (car l1) 
                                 (memo-lcs-h (cdr l1) (cdr l2))))
                          (else (let ((res1 (memo-lcs-h (cdr l1) l2))
                                      (res2 (memo-lcs-h l1 (cdr l2))))
                                  (if (>= (length res1) (length res2))
                                      res1 res2))))))
               (begin                                      
                 (2d-vector-set! table n1 n2 val)
                 val))))))
  (memo-lcs-h l1 l2))


(define (2d-vector-ref vec r c)
  (vector-ref (vector-ref vec r) c))

(define (2d-vector-set! vec r c val)
  (let ((v (vector-ref vec r)))
    (begin
      (vector-set! v c val)
      (vector-set! vec r v))))

(define l1 `(A B C B D A B))
(define l2 `(B D C A B A))

(define (make-2d-vector r c)
  (make-vector r (make-vector c #\#)))

;(define (2d-vector-ref vec r c)
  ;(vector-ref (vector-ref vec r) c))
