#lang racket

(define (make-2d-vector n r)
  (build-vector n (lambda (x) (make-vector r #f))))

(define (memo-lcs l1 l2)
  (define table (make-2d-vector (length  l1)
                                   (length l2)))
  (define (memo-lcs-h l1 l2)
    (let([h1 (- (length l1) 1)]
         [h2 (- (length l2) 1)])
      (cond[(or (null? l1) (null? l2)) '()]
        [(vector-ref (vector-ref table h1) h2)
            (vector-ref (vector-ref table h1) h2)]
           [(= (car l1) (car l2))
            (cons (car l1)
                  (memo-lcs-h (cdr l1) (cdr l2)))]
           [else (let([res1 (memo-lcs-h (cdr l1) l2)]
                      [res2 (memo-lcs-h l1 (cdr l2))])
                   (if (> (length res1) (length res2))
                       res1 res2))])))
  (memo-lcs-h l1 l2))