#lang racket

(define-syntax lc
  (syntax-rules (: <- @)
    [(lc exp : var <- lexp) (map (lambda (var) exp) lexp)]
    [(lc exp : @ guard) (if guard (list exp) `())]
    [(lc exp : @ guard qualifier ...) 
     (concat (lc (lc exp : qualifier ...) : guard))]
    [(lc exp : var <- lexp qualifier ...) 
     (concat (lc (lc exp :  qualifier ... ) : var <- lexp))]))

;(lc (+ x y z) : x  <- `(1 2 3 4 5)  y <- `(6 7 8 9 10)  z <- `(33 44 55))
;(lc (* x y) : x <- `(1 2 3)   y <- `(4 5 6) @ (even (+ x y)))

(define (qsort l)
  (if (null? l) `()
      (let ((lows (lc x : x <- (cdr l)  @ (<= x (car l))))
            (highs (lc x : x <- (cdr l)  @ (> x (car l)))))
        (append (qsort lows) (list (car l)) (qsort highs)))))

(define-syntax list-of-three
  (syntax-rules (@ <-)
    [(list-of-three b @ c ... <- d) `(b d c ...)])) 

(define (is-single-digit q)
  (and (<= q 9) (>= q 0)))

(define (convert t v)
  (+(* t 10) v))

(define (square x)
  (* x x))

(define (mult r s)
  (if (is-single-digit s)
      (multunic r s)
      (+ (mult r (remainder s 10)) (* (mult r (quotient s 10)) 10))))

(define (multunic x y)
  (if (and (is-single-digit x) (is-single-digit y))
      (* x y)
      (convert (+ (multunic (quotient x 10)
                            y)
                          (quotient (* (remainder x 10) y) 10))
               (remainder (* (remainder x 10) y) 10))))

(define (akmult x y)
  (cond [(= x 0) 0]
       [(= x 1) y]
       [(even? x) (* 2 (akmult (quotient x 2) y))]
       [(odd? x) (+ (* 2 (akmult (quotient x 2) y)) y)]))



(define (factorial n)
  (if (= n 0) 1
      (* n (factorial (- n 1)))))





(define (fact-iter n acc)
  (if (= n 0) acc
      (fact-iter (- n 1) (* n acc))))

(define (fib n)
  (cond [(= n 0) 1]
        [(= n 1) 1]
        [else (+ (fib (- n 1)) (fib (- n 2)))]))

(define (fibnew n)
  (cond [(= n 0) 1]
        [(= n 1) 1]
        [else (fib-iter 1 1 2 n)]))

(define (fib-iter n1 n2 i n)
  (if (= i n) (+ n1 n2)
      (fib-iter n2 (+ n1 n2) (+ i 1) n)))

(define (akmultnew x y)
  (akmultiter x y 0))
(define (akmultiter x y c)
  (cond [(even? x) (akmultiter (/ x 2) (* 2 y) c)]
        [else (if (> x 1)
                  (akmultiter (quotient x 2) (* 2 y) (+ c y))
                  (+ y c))]))

(define (exp x y)
  (cond [(= y 1) x]
        [(odd? y) (* (exp x (quotient y 2)) (exp x (quotient y 2)) x)]
        [else (* (exp x (quotient y 2)) (exp x (quotient y 2)))]))

(define (expmod x y n)
  (cond [(= y 1) (remainder x n)]
        [(odd? y) (expmod (* (expmod x (quotient y 2) n) (expmod x (quotient y 2) n) (expmod x 1 n)) 1 n)]
        [else (expmod (* (expmod x (quotient y 2) n) (expmod x (quotient y 2) n)) 1 n)]))

(define (gcd a b)
  (if (= b 0) a
      (gcd b (remainder a b))))

(define (has_solution a b c)
  (= (remainder c (gcd a b)) 0))

(define (hof op1 op2 n m k)
  (define (hof-h i)
    (if (> i k) 
        (op2 (m i) (n i))
        (op1 (n i) (op2 (m i) (hof-h (+ i 1))))))
  (hof-h 1))

(define (tan x k)
  (define (n i) (if( = i 1) x (* x x)))
  (define (m i) (-(* 2 i) 1))
  (hof / - n m k))
;
;(define (sub x y)
;  (sub-single x y ))

;(define (sub-single x y )
;  (if (and (is-single-digit x) (is-single-digit y))
;      (- (convert z x) y)
;      (convert (sub-single (quotient x 10) (quotient y 10) z) (sub-single (remainder x 10) (remainder y 10) z))))


(define (div x y)
  (cond [(< x y) (cons 0 x)]
        [(even? x) (let* ((result (div (quotient x 2) y))
                        (qdash (car result))
                        (rdash (cdr result)))
                     (if (< (* 2 rdash) y)
                         (cons (* 2 qdash) (* 2 rdash))
                         (cons (+ (* 2 qdash) 1) (- (* 2 rdash) y))))]
        [(odd? x) (let* ((result (div (quotient x 2) y))
                        (qdash (car result))
                        (rdash (cdr result)))
                     (if (< (+ (* 2 rdash) 1) y)
                         (cons (* 2 qdash) (+ (* 2 rdash) 1))
                         (cons (+ (* 2 qdash) 1) (+ (- (* 2 rdash) y) 1))))]))

(define (coeff a b)
  (cond [(= b 0) (cons 1 0)]
        [else (let* ((ans (coeff b (remainder a b)))
                    (xd (car ans))
                    (yd (cdr ans)))
                (cons yd (- xd (* (quotient a b) yd))))])) 

(define (inverse e n)
  (if ( = (gcd e n) 1)
   (let ((ans (car (coeff e n))))
     (if (> ans 0)
         ans
         (+ ans n)))
   (error "e & n should be coprime for inverse to exist")))

(define (triangle n)
  (tri-iter 5 1 3 n))

(define (tri-iter n1 n2 i n)
  (if (= i n)
      (+ ( + (- (* 2 n1) n2) n) (quotient n 2))
      (tri-iter (+ ( + (- (* 2 n1) n2) i) (quotient i 2)) n1 (+ i 1) n)))

(define (simplify r)
  (let*((p (car r))
       (q (cdr r))
       (t (gcd p q)))
    (cons (/ p t) (/ q t))))
       
(define (add r1 r2)
  (let*((p (car r1))
       (q (cdr r1))
       (r (car r2))
       (s (cdr r2)))
    (simplify (cons (+ (* p s) (* r q)) (* q s)))))

(define (minchange n)
  (change 0 n 50))

(define (change acc n c)
  (cond [(= c 50) (change (+ acc (quotient n c)) (remainder n c) 25)]
        [(= c 25) (change (+ acc (quotient n c)) (remainder n c) 20)]
        [(= c 20) (change (+ acc (quotient n c)) (remainder n c) 10)]
        [(= c 10) (change (+ acc (quotient n c)) (remainder n c) 5)]
        [(= c 5) (change (+ acc (quotient n c)) (remainder n c) 3)]
        [(= c 3) (change (+ acc (quotient n c)) (remainder n c) 2)]
        [(= c 2) (change (+ acc (quotient n c)) (remainder n c) 1)]
        [(= c 1) (+ acc n)]))

(define (decode p q e c)
  (let* ((n (* p q))
         (d (inverse e (* (- p 1) (- q 1)) ))
         (first (exp c e))
         (second (remainder first n))
         (third (exp second d))
         (forth (remainder third n)))
    forth))

(define (is-prime p)
  (let ((a (random p)))
     ( = (remainder (- (exp a (- p 1)) 1) p) 0)))

(define (prime? p)
  (define (non-divisible-by n d)
    (cond
     ((= d 1) #t)
     (else (if(= (remainder n d) 0)
          #f
          (non-divisible-by n (- d 1))))))
  (if (= p 1)
      #t
      (non-divisible-by p (- p 1))))
         
(define (filtered-accumulate inc-func acc total limit inc-func-iter)
  (if (<= (inc-func-iter acc) limit)
      (filtered-accumulate inc-func (inc-func-iter acc) (+ total (inc-func acc limit)) limit inc-func-iter)
      total))
   

(define (f0 x y) 
  (filtered-accumulate inc0 x 1 y inc0-iter))

(define (f1 x y)
  (if (and (even? x) (<= x y))
      (filtered-accumulate inc1 (+ x 1) (expt (+ x 1) 2)  y inc1-iter)
      (filtered-accumulate inc1 x (expt x 2) y inc1-iter)))

(define (f2 x y)
  (cond 
      [(= (remainder x 3) 2) (filtered-accumulate inc2 (+ x 1) (factorial (+ x 1))  y inc2-iter)]
      [(= (remainder x 3) 1) (filtered-accumulate inc2 (+ x 2) (factorial (+ x 2)) y inc2-iter)]
      [else (filtered-accumulate inc2  x (factorial x) y inc2-iter)]))

(define (f3 x y)
  (filtered-accumulate inc3 x 
                       (if (prime? x)
                           (expt x 2)
                           0)                      
                       y inc3-iter))

(define (f4 y)
  (filtered-accumulate inc4 1 1 y inc4-iter))

(define (inc0 i y)
  (+ i 13))

(define (inc0-iter i)
  (+ i 13))

(define (inc1 i y)
      (expt (+ i 2) 2))

(define (inc1-iter i)
      (+ i 2))

(define (inc2 i y)
  (factorial (+ i 3)))

(define (inc2-iter i)
  (+ i 3))

(define (inc3 i y)
     (if (prime? (+ i 1)) 
         (expt (+ i 1) 2)
         0))

(define (inc3-iter i)
      (+ i 1))

(define (inc4 i y)
     (if (= (gcd (+ i 1) y) 1) 
         (+ i 1)
         0))

(define (inc4-iter i)
      (+ i 1))

(define (sum l)
  (if (null? l) 0
      (+ (car l) (sum (cdr l)))))

(define (product l)
  (if (null? l) 1
      (* (car l) (product (cdr l)))))

(define (len l)
  (if (null? l) 0
      (+ 1 (len (cdr l)))))

;(define (append l1 l2)
;  (if (null? l1) l2
;      (cons (car l1) (append (cdr l1) l2))))

(define (reverse l)
  (if (null? l) l
      (append (reverse (cdr l)) (list (car l)))))

(define (map f l)
  (if (null? l) l
      (cons (f (car l)) (map f (cdr l))))) 

(define (filter p l)
  (cond
     [(null? l) l]
     [(p (car l)) (cons (car l) (filter p (cdr l)))]
     [else (filter p (cdr l) )]))

(define (foldr f id l)
  (if (null? l) id
      (f (car l) (foldr f id (cdr l)))))

(define (sumr l)
  (foldr + 0 l))

(define (productr l)
  (foldr * 1 l))

(define (appendr l1 l2)
  (foldr cons l2 l1))

(define (reverser l)
  (foldr (lambda (x l1) (append l1 (list x))) 
         '() l))

(define (mapr f l)
  (foldr (lambda (x l1) (cons (f x) l1)) '() l))

(define (filterr p l)
  (foldr (lambda (x l1) 
          (if (p x)
              (cons x l1)
              l1))
         '() l))

(define (act x l)
  (if (null? l) '()
      (cons (cons x (car l)) (act x (cdr l)))))

(define (put x l)
  (cons '() (act x l)))

(define (powerput x l)
  (append l (poweract x l)))

(define (poweract x l)
  (if (null? l) '()
      (cons (append (list x) (car l)) (poweract x (cdr l)))))

(define (powerset l)
  (foldr powerput (list (list )) l))

(define (inits l)
  (foldr put (list (list )) l))

(define (tails l)
  (map reverse (foldr put (list (list )) (reverse l))))

(define (sublist-h l)
  (if (null? l) '(())
  (append (cdr (inits l)) (sublist-h (cdr l)))))

(define (sublist l)
  (cons '() (reverse (cdr (reverse (sublist-h (list 1 2 3 4)))))))

(define (concat l) (foldr append `() l))

(define (zip l1 l2)
  (cond [(null? l1) `()]
        [(null? l2) `()]
        [else (cons (cons (car l1) (car l2)) (zip (cdr l1) (cdr l2)))]))

(define (one-to-n n)
  (if (= n 0) `()
  (append (one-to-n (- n 1)) (list n))))

(define (evaluate-h valuex poly)
  (if (null? poly) 0
  (+ (* (car poly) (expt valuex (- (len poly) 1))) (evaluate-h valuex (cdr poly)))))

(define (evaluate valuex poly)
  (evaluate-h valuex (reverse poly)))

(define (addpoly poly1 poly2)
  (cond [(null? poly1) `()]
        [(null? poly2) `()]
        [else (cons (+ (car poly1) (car poly2)) (addpoly (cdr poly1) (cdr poly2)))]))

(define (split n)
  (split-h n n))

(define (split-h x n)
  (if (= x 0)
      (list(list n 0))
      (cons (list (- n x) x) (split-h (- x 1) n))))

(define (adjust l n)
  (if (= n 0)
      l
      (adjust (append l '(0)) (- n 1))))

(define (get l n)
  (if (= n 0)
      (car l)
      (get (cdr l) (- n 1))))
      
(define (power n poly1 poly2)
  (if (and (< n (len poly1)) (< n (len poly2)))
      (if ( < (len poly1) (len poly2))
            (let ((l1 (adjust poly1 (+ (- (len poly2) (len poly1)) 1)))
                  (l2 poly2)
                  (l (split n)))
              (powerh l1 l2 l))
            (let ((l1 poly1)
                  (l2 (adjust poly2 (+ (- (len poly1) (len poly2)) 1)))
                  (l (split n)))
              (powerh l1 l2 l)))         
      (let ((l1 (adjust poly1 (+ (- n (len poly1)) 1)))
            (l2 (adjust poly2 (+ (- n (len poly2)) 1)))
            (l (split n)))
        (powerh l1 l2 l))))

(define (powerh l1 l2 l)
  (if (null? l) 0
  (+ (* (get l1 (car (car l))) (get l2 (car (cdr (car l)))))
     (powerh l1 l2 (cdr l)))))

(define (multiply poly1 poly2)
  (let ((n (* (- (len poly1) 1) (- (len poly2) 1))))
    (multiply-h n poly1 poly2)))

(define (multiply-h n poly1 poly2)
  (if (= n -1)
      '()
      (cons (power n poly1 poly2) (multiply-h (- n 1) poly1 poly2))))

(define (gc n)
  (if (= n 1)
      (list (list 1) (list 0))
      (append (poweract 0 (gc (- n 1))) (poweract 0 (gc (- n 1))))))

(define (flatten l)
  (if (list? l) 
      (if (null? l) '()
      (append (flatten (car l)) (flatten (cdr l))))
      (list l)))

(define (cprod l)
  (if (null? l)
      (list (list ))
      (cprod-h (car l) (cprod (cdr l))))) 

(define (cprod-h l1 l2)
  (if (null? l1)
      '()
      (append (poweract (car l1) l2) (cprod-h (cdr l1) l2)))) 

(define (shuffle-h x l)
  (if (null? l)
      '()
      (cons (append (list x) l)
            (cons (list (car l)) (shuffle-h x (cdr l))))))

(define (transpose1 l)
  (if (null? l)
      '()
      (cons (transpose-h l) (transpose1 (transpose-t l)))))


(define (transpose-h l) 
  (if (null? l)
      '()
      (if (null? (car l))
          '()
          (cons (caar l) (transpose-h (cdr l))))))

(define (transpose-t l) 
  (if (null? l)
      '()
      (if (null? (car l))
          '()
          (cons (cdar l) (transpose-t (cdr l))))))

(define (transpose l)
  (reverse (cdr (reverse (transpose1 l)))))

(define (listmult l1 l2)
  (if (null? l1)
      0
      (+ (* (car l1) (car l2)) (listmult (cdr l1) (cdr l2)))))

(define (listmult1 l1 l2)
  (if (null? l2)
      '()
      (cons (listmult l1 (car l2)) (listmult1 l1 (cdr l2)))))

(define (listmult2 l1 l2)
  (if (null? l1)
      '()
      (cons (listmult1 (car l1) l2) (listmult2 (cdr l1) l2))))

(define (matmult m1 m2)
  (listmult2 m1 (transpose m2)))
  
(define (rleh l t)
  (if (null? (cdr l))
      (list (list (car l) t))  
  (if (= (car l) (cadr l))
      (rleh (cdr l) (+ t 1))
      (cons (list (car l) t) (rleh (cdr l) 1)))))

(define (rle l)
  (rleh l 1))

(define (fewest-movesh l t)
  (if (null? l)
      t
  (if (= (car l) 1)
      (let ((l1 (fewest-movesh (cdr l) (+ t 1))) 
            (l2 
             (if (null? (cdr l))
                 t
                 (fewest-movesh (cddr l) (+ t 1)))))
        (if (< l1 l2)
            l1
            l2))
      (let ((l1 (fewest-movesh (cdr l) (+ t 1))) 
            (l2
             (if (null? (cdr l))
                 t
                 (if (null? (cddr l))
                     t
                     (if (null? (cdr (cddr l)))
                         t
                         (fewest-movesh (cddr (cddr l)) (+ t 1)))))))
        (if (< l1 l2)
            l1
            l2)))))

(define (fewest-moves l)
  (fewest-movesh l 0))

;(define (summandsh n)
;  (if (= n 1)
;      (list (list 1))
;      (summands-help  (cons (list n) (summandsh (- n 1))))))
;
;(define (summands-help l)
;  (if (null? l)
;      '()
;      (append (summands-help2 (car l)) (summands-help (cdr l)))))
;
;(define (summands-help2 l)
;  (let ((l1 (append '(1) l))
;        (l2 (append l '(1))))
;    (list l1 l2)))
;
;(define (summands n)
;  (cons (list n) (summandsh n)))

(define (pascal1 n)
  (cond [(= n 1) '(1)]
        [(= n 2) '(1 1)]
        [else (append '(1) (append (pascal-h (pascal1 (- n 1))) '(1)))]))

(define (pascal-h l)
  (if (null? (cdr l))
      '()
      (cons (+ (car l) (cadr l)) (pascal-h (cdr l)))))

(define (pascal2 n)
  (if (= n 0)
      '()
      (cons (pascal1 n) (pascal2 (- n 1)))))

(define (pascal n)
  (reverse (pascal2 n)))

(define (ssmh l last-inserted)
  (if (null? l)
      '()
  (if (<= (car l) last-inserted)
      (ssmh (cdr l) last-inserted)
      (cons (car l) (ssmh (cdr l) (car l))))))

(define (ssm xs)
  (cons (car xs) (ssmh xs (car xs))))

(define (mssh l thissum maxsum)
  (if (null? l)
      maxsum
      (cond [(> (+ thissum (car l)) maxsum) (mssh (cdr l) (+ thissum (car l)) (+ thissum (car l)))]
            [(> 0 (+ thissum (car l))) (mssh (cdr l) 0 maxsum)]
            [else (mssh (cdr l) (+ thissum (car l)) maxsum)])))

(define (mss l)
  (mssh l 0 0))
 
(struct node (ltree rtree) #:transparent)
(struct leaf (val) #:transparent) 

(define (take n l)
  (if (= n 0)
      '()
      (cons (car l) (take (- n 1) (cdr l)))))

(define (drop n l)
  (if (= n 0)
      l
      (drop (- n 1) (cdr l))))

(define (all-1 l)
  (if (null? l)
      #t
  (if (= (car l) 1)
      (all-1 (cdr l))
      #f)))

(define (all-0 l)
  (if (null? l)
      #t
  (if (= (car l) 0)
      (all-0 (cdr l))
      #f)))
 
(define (tobintree l)
  (cond [(all-1 l) (leaf 1)]
        [(all-0 l) (leaf 0)]
        [else (node 
                (tobintree (take (quotient (len l) 2) l))
                (tobintree (drop (quotient (len l) 2) l)))]))

(define (bitwise-and t1 t2)
  (cond [(leaf? t1) (if (= (leaf-val t1) 0)
                        t1
                        t2)]
        [(leaf? t2) (if (= (leaf-val t2) 0)
                        t2
                        t1)]
        [else (comb-tree 
               (node 
                (bitwise-and (node-ltree t1) (node-ltree t2))
                (bitwise-and (node-rtree t1) (node-rtree t2))))]))

(define (comb-tree t1)
  (cond [(and (leaf? (node-ltree t1)) (leaf? (node-rtree t1))) 
         (cond [(and (= (leaf-val (node-ltree t1)) 1) (= (leaf-val (node-rtree t1)) 1))
                (leaf 1)]
               [(and (= (leaf-val (node-ltree t1)) 0) (= (leaf-val (node-rtree t1)) 0))
                (leaf 0)]
               [else t1])]
        [else t1]))

(define (value? i bt)
  (define (value-h i n bt)
    (cond [(leaf? bt) (leaf-val bt)]
          [(<= i (quotient n 2)) (value-h i (quotient n 2) (node-ltree bt))]
          [(> i (quotient n 2)) (value-h (- i (quotient n 2)) (quotient n 2) (node-rtree bt))])) 
(value-h i 8 bt))

(struct cnode(op ltree rtree) #:transparent)
(struct cleaf (num) #:transparent)


(define (cconvert tree)
  (cond [(cleaf? tree) (cleaf-num tree)]
        [(eq? "+" (cnode-op tree))
         (string-append
          (string #\()
             (cconvert (cnode-ltree tree))             
             (string #\+)              
             (cconvert (cnode-rtree tree))
             (string #\))
             )]
        [(eq? "*" (cnode-op tree))
         (string-append 
             (cconvert (cnode-ltree tree))
             (string #\*)                    
             (cconvert (cnode-rtree tree))                    
             )])) 
                      
       
(define ctree (cnode "*" (cnode "+" (cleaf "4") (cleaf "5"))
                (cnode "*" (cleaf "7") (cleaf "8"))))

;         (string-append 
;          (string #\()
;          (string #\+)
;          (string #\)))

(struct rnode (color ltree rtree) #:transparent)
(struct rleaf (color) #:transparent)

(define (insert radixtree l)
  (cond
      [(and (rnode? radixtree) (null? l))
          (rnode 'white 
                 (rnode-ltree radixtree)
                 (rnode-rtree radixtree))]
      [(and (rleaf? radixtree) (null? l))
          (rleaf 'white )]
      [(and (rleaf? radixtree) (= (car l) 0)) 
          (rnode (rleaf-color radixtree)
                 (rleaf 'black)
                 (insert-h2 (cdr l)))]
      [(and (rleaf? radixtree) (= (car l) 1)) 
          (rnode (rleaf-color radixtree) 
                 (insert-h2 (cdr l))
                 (rleaf 'black))]
      [(= (car l) 0)
          (rnode (rnode-color radixtree) 
                 (insert (rnode-ltree radixtree) (cdr l))
                 (rnode-rtree radixtree))]
      [(= (car l) 1)
          (rnode (rnode-color radixtree)
                 (rnode-ltree radixtree)
                 (insert (rnode-rtree radixtree) (cdr l)))]))

(define (insert-h2 l)
  (if (null? l)
      (rleaf 'white)
      (if (= (car l) 0)
          (rnode 'black
                 (insert-h2 (cdr l))
                 (rleaf 'black))
          (rnode 'black
                 (rleaf 'black)
                 (insert-h2 (cdr l))))))

(define radtree (rnode 'white (rnode 'black (rleaf 'white) (rleaf 'black))
  (rnode 'white (rleaf 'black) (rleaf 'white))))

(struct gnode(val lst) #:transparent)

(define (atlevel t n)
  (if (= n 1)
      (list (gnode-val t))
      (concat (map (lambda (x) (atlevel x (- n 1))) (gnode-lst t)))
      ))

(define t (gnode 1 (list (gnode 2 (list (gnode 3 '()) (gnode 4 '())))
               (gnode 5 (list (gnode 6 (list (gnode 7 '()))))))))

(struct bnode (ltree rtree) #:transparent)
(struct bleaf () #:transparent)

(define (all-symmetric-trees n)
  (lc (bnode x (mirror-image x)) : x <- (get-all-trees (quotient n 2))))

(define (mirror-image t)
  (if (bleaf? t)
      t
      (bnode 
            (mirror-image (bnode-rtree t))
            (mirror-image (bnode-ltree t)))))


(define (get-all-trees n)
  (if (= n 1)
      bleaf
      (lc (bnode (get-all-trees i) 
             (get-all-trees (- n i 1))) : i <- (one-ton (- n 1)))))

(define (one-ton n)
  (if (= 0 n)
      '(0)
      (cons n (one-ton (- n 1)))))
