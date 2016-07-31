
#lang racket

(require (lib "trace.ss"))
(struct dir (info fdlist) #:transparent)
(struct file (info contents) #:transparent)

;Q1
(define thistree 
  (dir 
   (cons "as" 1024)
   (list (dir 
          (cons "cs613" 1024)
          (list (file (cons "quiz" 4246) "junk")
                (file (cons "tut" 7226) "junk")
                (dir (cons "2004" 1024)
                     (list (file (cons "quiz" 576) "junk")
                           (file (cons "tut" 345) "junk")))))
         (dir (cons "cs152" 1024)
              (list (file (cons "quiz1" 4532) "junk")
                    (file (cons "quiz2" 1234) "junk")
                    (file (cons "tut" 1223) "junk")))
         (dir (cons "cs154" 1024)
              (list (file (cons "tut1" 459) "junk")
                    (file (cons "tut2" 782) "junk"))))))

(define (findtree dirtree pathname)
  (if (null? (cdr pathname)) dirtree
      (let ((nexttree (search (cadr pathname) (dir-fdlist dirtree))))
	(findtree nexttree (cdr pathname)))))

(define (search name treelist)
  (car (dropwhile (lambda (x) 
                    (not (or 
                          (and (file? x) (equal? name (car (file-info x))))
                          (and (dir? x) (equal? name (car (dir-info x)))))))
                  treelist)))

(define (ls dirtree pathname)
  (let ((subjecttree (findtree dirtree pathname)))
    (listnames subjecttree)))

(define (listnames tree)
  (if (file? tree) (list (car (file-info tree)))
      (append (list (car (dir-info tree)))
              (concat (map listnames (dir-fdlist tree))))))
(define (concat l) (foldr append `() l))

(define (size dirtree pathname)
  (let ((subjecttree (findtree dirtree pathname)))
    (findsize subjecttree)))

(define (findsize tree)
  (if (file? tree) (cdr (file-info tree))
      (+ (cdr (dir-info tree))
         (foldr + 0 (map findsize (dir-fdlist tree))))))

(define (delete dirtree pathname)
  (if (null? (cdr pathname)) `()
      (let ((l (split (cadr pathname) (dir-fdlist dirtree))))
        (dir (dir-info dirtree) (append (car l) 
                                        (delete (cadr l) (cdr pathname))
                                        (caddr l))))))
(define (split name trees)
  (list (takewhile (lambda (x) (not (equal? name (car (dir-info x))))) trees)
        (car (dropwhile (lambda (x) (not (equal? name (car (dir-info x))))) trees))
        (cdr (dropwhile (lambda (x) (not (equal? name (car (dir-info x))))) trees))))



(define (takewhile p l)
  (cond ((null? l) `())
        ((p (car l)) (cons (car l) (takewhile p (cdr l))))
        (else `())))

(define (dropwhile p l)
  (cond ((null? l) `())
        ((p (car l)) (dropwhile p (cdr l)))
        (else l)))

(define pathname `("as" "cs613" "2004"))

;-------------------------------------------------------------
;Q2
(define len 8)

(struct node (ltree rtree) #:transparent)
(struct leaf (val) #:transparent)
 
  
(define (tobintree l) 
  (cond ((all (is 1) l) (leaf 1))
        ((all (is 0) l) (leaf 0))
        (else (let ((x (take (quotient (length l) 2) l))
                    (y (drop (quotient (length l) 2) l)))
                (node (tobintree x) (tobintree y))))))

(define (union t1 t2)
  (cond [(leaf? t1) (if (= (leaf-val t1) 1) (leaf 1) t2)]
        [(leaf? t2) (if (= (leaf-val t2) 1) (leaf 1) t1)] 
        [else (let ([t11 (union (node-ltree t1)(node-ltree t2))]
                    [t12 (union (node-rtree t1)(node-rtree t2))])
                (combine t11 t12))]))

(define (intersection t1 t2)
  (cond [(leaf? t1) (if (= (leaf-val t1) 0) (leaf 0) t2)]
        [(leaf? t2) (if (= (leaf-val t2) 0) (leaf 0) t1)] 
        [else (let ([t11 (intersection (node-ltree t1)(node-ltree t2))]
                    [t12 (intersection (node-rtree t1)(node-rtree t2))])
                (combine t11 t12))]))
(define (find segmentlength index t)
  (cond [(leaf? t) (leaf-val t)]
        [(<= index (quotient segmentlength 2)) 
         (find (quotient segmentlength 2) index (node-ltree t))]
        [else 
         (find (quotient segmentlength  2) (- index (quotient segmentlength 2)) (node-rtree t))]))

(define (value? i t)
  (find len i t))

(define (combine t1 t2)
  (if (and (leaf? t1) (leaf? t2) (= (leaf-val t1) (leaf-val t2)))
      t1 (node t1 t2)))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Q3
(struct node3 (val ltree rtree) #:transparent)
(struct leaf3 (num) #:transparent)
 
(define (convert t)
  (cond ((leaf? t) (number->string (leaf3-num t)))
        ((eq? '+ (node3-val t))
         (string-append 
          (convert (node3-ltree t))
          (string #\+)
          (convert (node3-rtree t))))
        (else  (let ((lt (cond [(leaf3? (node3-ltree t)) (number->string (leaf3-num (node3-ltree t)))]
                               [(eq? '+ (node3-val (node3-ltree t)))
                                (string-append 
                                 (string #\()
                                 (convert (node3-ltree t))
                                 (string #\)))]
                               [else (convert (node3-ltree t))]))
                     (rt (cond [(leaf3? (node3-rtree t)) (number->string (leaf3-num (node3-rtree t)))]
                               [(eq? '+ (node3-val (node3-rtree t)))
                                (string-append 
                                 (string #\()
                                 (convert (node3-rtree t))
                                 (string #\)))]
                                [else (convert (node3-rtree t))])))
                 (string-append lt (string #\*) rt)))))

;Q4

(define-struct node4(color ltree rtree))
(define-struct leaf4(color))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Q5

(struct gnode  (val  lst) #:transparent)
(define (atlevel t n)
  (cond [(= n 1) (list (gnode-val t))]
        [(null? (gnode-lst t)) '()]
        [else (concat (map (lambda (x) (atlevel x (- n 1))) (gnode-lst t)))]))


(define t (gnode 1 (list (gnode 2 (list (gnode 3 '()) (gnode 4 '())))
               (gnode 5 (list (gnode 6 (list (gnode 7 '()))))))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (is n) (lambda (x) (= x n)))

(define (all p l) (foldr (lambda (x y) (and (p x) y)) #t l))

(define (take n l)
  (cond ((null? l) `())
        ((= n 0) `())
        (else (cons (car l) (take (- n 1) (cdr l))))))

(define (drop n l)
  (cond ((null? l) `())
        ((= n 0) l)
        (else (drop (- n 1) (cdr l)))))
(trace intersection)

