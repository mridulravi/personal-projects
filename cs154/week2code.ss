#lang racket
; Q1 Write  a function (has_solution  a b c)  which returns #t  if the
; diophantine eqn.  ax + by =  c has solutions for integer values of x
; and y.

(define (mygcd a b) 
  (define (mygcd-helper a b) 
    (if (= b 0) a
        (mygcd b (remainder a b))))
  (mygcd-helper (abs a) (abs b)))

(define (has-solution a b c) 
  (define (divides a b) 
    (= (remainder a b) 0))
  (divides (mygcd a b) c))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Q2 Write  a function (sub  x y) which  subtracts y from x.   You can
; assume  that  x  is  larger  than  y. Define  sub  in  terms  of  an
; appropriate  function (sub-single  x y  z) with  constraints  on the
; values  of   x,  y,  and   z.   The  function  should   check  these
; constraints. You can also use the function convert to left-shift and
; add.

(define (sub-single x y z)   ;does (x - y - z), x,y,z - single digits 
  (if (and (<= 0 x) (<= x 9)
           (<= 0 y) (<= y 9)
           (<= 0 z) (<= z 9))
           (- x y z) (error "Arguments of wrong size")))

(define (sub x y) (subb x y 0))  ; subb - subtract with borrow
                
(define (subb x y b)
  (cond [(and (= x 0) (= y 0)) 0] ;to deal with x < y, replace 0 with -b
        [else (let* ([column-sub (sub-single (remainder x 10) (remainder y 10) b
)]                  
                     [borrow (if (< column-sub 0) 1 0)]
                     [rem    (modulo column-sub 10)]
                     [qx10 (quotient x 10)]
                     [qy10 (quotient y 10)]
                     [rx10 (remainder x 10)]
                     [ry10 (remainder y 10)])
                (convert (subb qx10 qy10 borrow) rem))]))
(define (convert x y) (+ (* 10 x) y)) 
; Q3 Write a function (ak-mult x  y) to multiply two numbers using the
; Al-Khwarizmi method.


(define (ak-mult x y)
  (cond [(= x 1) y]
        [(even? x) (* 2 (ak-mult (quotient x 2) y))]
        [(odd? x) (+ y (* 2 (ak-mult (quotient x 2) y)))]))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; Q4. Define a  function (div x y),  y is not 0, which  will return a
;; pair of numbers (q,r)  such that x = yq + r and  r < y. This should
;; also work by repeated halvings of x.

(define (div x y)
  (if (< x y) (cons 0 x)
      (let ([q1 (car (div (quotient x 2) y))]
            [r1 (cdr (div (quotient x 2) y))])
        (if (even? x) (cons (+ (* 2 q1) (quotient (* 2 r1) y)) (remainder (* 2 r1
) y))
            (cons (+ (* 2 q1) (quotient (+ 1 (* 2 r1)) y)) (remainder (+ 1 (* 2 
r1)) y))))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Q5. Given two numbers a and b, write a function coeffs which will
;; return a pair of numbers x and y such that a*x + b*y = gcd(a,b)

(define (make-3tuple a b c) (cons a (cons b c)))
(define (first 3t) (car 3t))
(define (second 3t) (car (cdr 3t)))
(define (third 3t) (cdr (cdr 3t)))

(define (coeffs a b)
  (if (= b 0) (make-3tuple 1 0 a)
      (let ([3t (coeffs b (remainder a b))])
        (make-3tuple (second 3t) (- (first 3t) (* (second 3t) (floor (quotient a
 b)))) (third 3t)))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; Q6. Given two integers x and n and an integer exponent y, write a
;; function (modexp x y n) which will output: x^y mod n.

(define (modexp x y N) ;; returns x^y mod N
  (if (= y 0) 1
      (let ([val (modexp x (floor (/ y 2)) N)])
        (if (even? y) (modulo (* val val) N)
            (modulo (* x val val) N)))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; Q7. A Carmichael number is a non-prime number p such that for every 
;; coprime a of p in the range 1 <= a <  p, a ^(p-1) = 1 modulo p.  
;; Define a function (carmichael n) which will give the nth Carmichael number.

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; Q8. Write a function (inverse e n) which will return the inverse of
;; e modulo n.

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; Q9. Write a function (is-prime  n) to implement the Fermat's little
;; theorem  based  probabilistic algorithm  to  test  whether  n is  a
;; prime. Assume that  n is not a Carmichael  number. Use the function
;; (random k) to generate a random number in the range 0..k-1.

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; Q10. Suppose that the RSA algorithm  uses the prime numbers p and q
;; to generate the encryption, the encoding exponent is e and the code
;; of a message (a number) is c.  Write a function (decode p q e c) to
;; decode the message.

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; Q11.  Goldbach's conjecture  says that  every positive  even number
;; greater than 2 is  the sum of two prime numbers. Example:  28 = 5 +
;; 23. It  is one of the most  famous facts in number  theory that has
;; not been  proved to  be correct  in the general  case. It  has been
;; numerically confirmed up to very large numbers (much larger than we
;; can go  with our Scheme system).  Write a function  (goldbach m) to
;; find the two prime numbers that sum up to a given number m. Use the
;; magic function cons to pack a pair of numbers.

(define (goldbach n) 
  (define (is_prime n) 
    (define (divides k n) (= 0 (remainder n k)))
    (define (is_prime_helper k) 
      (cond ((> (* k k) n) #t)
            ((divides k n) #f)
            (else (is_prime_helper (+ k 1)))))
    (if (<= n 1) #f
        (is_prime_helper 2)))
  (define (g_helper i n)
    (cond ((and (is_prime i) (is_prime (- n i))) (cons i (- n i)))
          ((= i (quotient n 2)) "Goldbach conjecture disproved!")
          (else (g_helper (- i 1) n)))) 
  (g_helper (- n 1) n))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; Q  12.  Write a  function (minchange  n) which  will return  the of
;; coins  required to  give  change  of n  paise.  You are  sufficient
;; numbers of 1p, 2p, 3p, 5p, 10p, 20p, 25p, For how high a value of n
;; can you  go in  5 minutes  of minimum number  given and  50p coins.
;; computation time?

(define infinity 10000000)
(define (fast-minchange sum)   
  (define (minchange-helper sum currmin absmin lastden)
    (cond ((or (= sum 0) (>= currmin absmin))  currmin)
	  (else (let* ((m25 (if  (and  (>= sum 25) (>= lastden 25))  
                                 (minchange-helper (- sum 25) (+ currmin 1) absmin 25) absmin))   
		       (m20 (if  (and (>= sum 20) (>= lastden 20)) 
                                 (minchange-helper (- sum 20) (+ currmin 1) m25 20) m25))   
		       (m10 (if  (and (>= sum 10) (>= lastden 10)) 
                                 (minchange-helper (- sum 10) (+ currmin 1) m20 10) m20))   
		       (m5 (if   (and (>= sum 5)  (>= lastden 5)) 
                                 (minchange-helper (- sum 5) (+ currmin 1) m10 5) m10))   
		       (m3 (if   (and (>= sum 3)  (>= lastden 3)) 
                                 (minchange-helper (- sum 3) (+ currmin 1) m5 3) m5))   
		       (m2 (if   (and (>= sum 2)  (>= lastden 2)) 
                                 (minchange-helper (- sum 2) (+ currmin 1) m3 2) m3))   
		       (m1 (if   (and (>= sum 1)  (>= lastden 1))
                                 (minchange-helper (- sum 1) (+ currmin 1) m2 1) m2)))
		  m1))))
  (minchange-helper sum 0 infinity 25))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;



;; Q13.  The  Josephus  problem  is  described as  follows:  n  people
;; numbered 1 to  n are made to stand in a  circle.  Starting from the
;; person numbered 1, every third  live person is killed. This is done
;; till only two persons are left. As an example, if n is 15, then the
;; survivors are  the persons who  were originally at positions  5 and
;; 14.  Your job is to write  a function (cansurvive pos n) that takes
;; as its  arguments a position  pos and the  number of people  n, and
;; returns #t  if the person  at position pos  is one of the  last two
;; survivors; otherwise it returns #f.

(define (survives position total)
  (cond ((< total 3) #t)
        ((= position 3) #f)
        (else (let ((newpos (if (< (- position 3) 0) 
                                (+  (- total 3)  position)
                                (- position 3))))
                (survives newpos (- total 1))))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;14. Eulers totient function. Eulers so-called totient function
;phi(m) is defined as the number of positive integers r (1 <= r < m)
;that are coprime to m. Example: m = 10: r = 1,3,7,9; thus phi(m) =
;4. Note the special case: phi(1) = 1.
(define (totient-phi n)
  (define (t_helper x i r)
    (if (> i (sqrt x))
        (if (> x 1)
            (- r (/ r x))
            r)
        (if (= 0 (modulo x i))
            (t_helper (repeated_divide x i) (+ i 1) (- r (/ r i)))
            (t_helper x (+ i 1) r))))
  (define (repeated_divide a b)
    (if (= 0 (modulo a b))
        (repeated_divide (/ a b) b)
        a))
  (t_helper n 2 n))

(define (prime? n)
  (define (is-prime-helper n x)
    (if (> (sqr x) n) #t
        (if (= 0 (remainder n x)) #f
            (is-prime-helper n (+ x 1)))))
  (is-prime-helper n 2))


;15. Assume that we represent a rational number p/q as (cons p q). With
;this representation, define the following functions on rational
;numbers.
;a. (simplify r) - converts a rational number r into its
;simplest form. 12/18 simplifies to 2/3.
;b. (add r1 r2) - adds two rational numbers r1 and r2.
;c. (muliply r1 r2) - multiplies two rational numbers.
;d. (divide r1 r2) - divides r1 by r2.
(define (simplify rat)
  (let* ((num (car rat))
	 (den (cdr rat))
	 (g (gcd num den)))
    (cons (quotient num  g) (quotient den g))))

(define (add rat1 rat2)
  (let* ((num1 (car rat1))
	 (den1 (cdr rat1))
	 (num2 (car rat2))
	 (den2 (cdr rat2)))
    (simplify (cons (+ (* num1 den2) (* num2 den1))
		    (* den1 den2)))))

(define (multiply rat1 rat2)
  (let* ((num1 (car rat1))
	 (den1 (cdr rat1))
	 (num2 (car rat2))
	 (den2 (cdr rat2)))
    (simplify (cons (* num1 num2)
		    (* den1 den2)))))


;----------------------------------------------------------------------
;16. Consider the diagram shown below. Assume all triangles in the
;diagram are equilateral. The outermost triangle is of height 3. It
;contains 9 triangles of height 1, of which 3 are inverted. It also
;contains 3 triangles of height 2 of which none are inverted. Thus a
;triangle of height 3 contains 9+3+1=13 triangles including
;itself. If (triangles h) is a function which gives the total
;2
;number of triangles contained in a triangle of height h, then
;(triangles 3) = 13. Similarly, you can verify for yourself that
;(triangles 4) = 27.
;a. What is (triangles 5)?
;b. Define triangles. Try to define it in such a way that triangles gives
;an answer for large values(e.g. 10000000) in a reasonable amount of
;time, say a minute.

(define (triangles n)
  (define (triangle-helper k tk1 tk2)
    (cond [(> k n) tk1]
          [else (let ((newtk (+ (* 2 tk1) (- tk2) (quotient k 2) k)))
                  (triangle-helper (+ k 1) newtk tk1))])) 
  (cond [(= n 0) 0]
        [(= n 1) 1]
        [else (triangle-helper 2 1 0)]))

