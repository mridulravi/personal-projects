#lang racket
(define (foldr f id l)
  (if (null? l)
      id
      (f (car l) (foldr f id (cdr l)))))
       
(define (sum l)
  (foldr + 0 l))

(define (product l)
  (foldr * 1 l))

(define (append l1 l2)
  (if (null? l1)
      l2
      (cons (car l1) (append (cdr l1) l2))))

(define (reverse l)
  (if (null? l)
      '()
      (append (reverse (cdr l)) (list (car l)))))

(define (sqr x)
  (* x x))

(define (map f l)
  (if (null? l)
      '()
      (cons (f (car l)) (map f (cdr l)))))

(define (len l)
  (if (null? l)
      0
      (+ 1 (len (cdr l)))))

(define (filter p l)
  (cond [(null? l) '()]
        [(p (car l))
         (cons (car l) (filter p (cdr l)))]
        [else 
         (filter p (cdr l))]))

(define (flatten l)
  (cond [(null? l) '()]
        [(list? (car l)) (append (flatten (car l)) (flatten (cdr l)))]
        [else (append (list (car l)) (flatten (cdr l)))]))

(define (insert-begin k l)
  (append (list k) l))

(define (gcd n)
  (cond [(= n 1) (list (list 0) (list 1))]
        [else (gcd-h (gcd (- n 1)))]))

(define (gcd-h l)
  (append (gcd-h1 l) (gcd-h2 (reverse l))))

(define (gcd-h1 l)
  (if (null? l)
      '()
      (cons (insert-begin 0 (car l)) (gcd-h1 (cdr l)))))

(define (gcd-h2 l)
  (if (null? l)
      '()
      (cons (insert-begin 1 (car l)) (gcd-h2 (cdr l)))))

(define (rle l)
  (cond [(null? l) '()]
        [(let ((p (car l)))
           (cons 
            (cons p (len (takewhile (lambda (x) (= p x)) l)))
            (rle (dropwhile (lambda (x) (= p x)) l)))
            )]))

(define (takewhile p l)
  (cond [(null? l) '()]
        [(p (car l)) (cons (car l)
                           (takewhile p (cdr l)))]
        [else '()]))
(define (dropwhile p l)
  (cond [(null? l) '()]
        [(p (car l)) 
                           (dropwhile p (cdr l))]
        [else l]))      
    