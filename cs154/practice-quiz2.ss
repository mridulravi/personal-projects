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
                  (vector-set! fib-vec n (+ (fib (- n 1)) (fib(- n 2))))
                  (vector-ref fib-vec n))]))
  (init)
  fib)

(define (make-2d-vector r c)
  (make-vector r (make-vector c #f)))

(define (2d-vector-ref vec r c)
  (vector-ref (vector-ref vec r) c))

(define (2d-vector-set! vec r c val)
  (let ((v (vector-ref vec r)))
    (begin 
      (vector-set! v c val)
      (vector-set! vec r v))))

(define (memo-lcs l1 l2)
  (define mem-vec (make-2d-vector 
                   (length l1) 
                   (length l2)))
  (define (memo-lcs-h l1 l2)
    (let ((n1 (- (length l1) 1))
          (n2 (- (length l2) 1)))
      (cond [(or (null? l1) (null? l2)) '()]
            [(2d-vector-ref mem-vec n1 n2) (2d-vector-ref mem-vec n1 n2)]
            [else
             (let ((val
                    (cond [(eq? (car l1) (car l2)) 
                           (cons (car l1) 
                                 (memo-lcs-h (cdr l1) (cdr l2)))]
                          [else (let ((rs1 (memo-lcs-h (cdr l1) l2))
                                      (rs2 (memo-lcs-h l1 (cdr l2))))
                                  (if (>= (length rs1) (length rs2))
                                      rs1
                                      rs2))])))
               (begin
                 (2d-vector-set! mem-vec n1 n2 val)
                 val))])))
  (memo-lcs-h l1 l2))
  
(define l1 '(1 4 5 2 2))
(define l2 '(4 3 6 5 2))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


(define balance 100)

(define (withdraw amount)
  (if (<= amount balance)
      (begin
        (set! balance (- balance amount))
        balance)
      "Insufficient Funds"))

(define new-withdraw
  (let ((balance 100))
    (lambda (amount)
      (if (<= amount balance)
          (begin
            (set! balance (- balance amount))
            balance)
          "Insufficient Funds"))))

(define (make-withdraw balance)
  (lambda (amount)
      (if (<= amount balance)
          (begin
            (set! balance (- balance amount))
            balance)
          "Insufficient Funds")))

(define (make-account balance)
  (define (withdraw amount)
    (if (<= amount balance)
        (begin
          (set! balance (- balance amount))
          balance)
        "Insufficent Funds"))
  (define (deposit amount)
    (begin
      (set! balance (+ balance amount))
      balance))
  (define (dispatch m)
    (cond [(eq? m 'withdraw) withdraw]
          [(eq? m 'deposit) deposit]
          [else "No-such Message"]))
  dispatch)

(define (make-accumulator initial)
  (lambda (amount)
    (begin
      (set! initial (+ initial amount))
      initial)))

(define (make-monitored f)
  (define i 0)
  (define (other-input x)
    (begin
      (set! i (+ 1 i))
      (f x)))
  (define (how-many-calls?)
    i)
  (define (reset-count)
    (set! i 0))
  (define (mf m)
    (cond [(eq? m 'how-many-calls?) (how-many-calls?)]
          [(eq? m 'reset-count) (reset-count)]
          [else (other-input m)]))
  mf)
  
(define (make-paccount balance passwd)
  (define i 0)
  (define (withdraw amount)
    (if (<= amount balance)
        (begin
          (set! balance (- balance amount))
          (set! i 0)
          balance)
        "Insufficent Funds"))
  (define (deposit amount)
    (begin
      (set! balance (+ balance amount))
      (set! i 0)
      balance))
  (define (incorrectpw amount)
    (if (= i 7)
        (begin
          (set! i 0)
          (call-the-cops))
        (begin
          (set! i (+ 1 i))
          (display "Incorrect Password"))))
  (define (call-the-cops)
    (display "Cops Called"))
  (define (dispatch pw m)
    (if (eq? pw passwd)
        (cond [(eq? m 'withdraw) withdraw]
              [(eq? m 'deposit) deposit]
              [(eq? m 'joint-req)  #f]
              [else "No-such Message"])
        incorrectpw))
  dispatch)

(define (make-joint account o-pw passwd)
  (define (withdraw amount)
    ((account o-pw 'withdraw) amount))    
  (define (deposit amount)
    ((account o-pw 'deposit) amount))
  (define (incorrectpw amount)
    (display "Incorrect Password"))
  (define (joint-req)
    #t)
  (define (dispatch pw m)
    (if (eq? pw passwd)
        (cond [(eq? m 'withdraw) withdraw]
              [(eq? m 'deposit) deposit]
              [(eq? m 'joint-req) joint-req]
              [else "No-such Message"])
        incorrectpw))
  (if (account o-pw 'joint-req)
      (display "Original Root Password")
       dispatch))



(define state 'start)

(define (f x)
  (cond 
    [(eq? state 'start) (if (= 0 x)
                            (begin 
                              (set! state 'read-0)
                              0)
                            (begin
                              (set! state 'read-1)
                              1))]
    [(eq? state 'read-0) (if (= 1 x)
                            (begin 
                              (set! state 'start)
                              0)
                            'ignored)]
    [(eq? state 'read-1) (if (= 0 x)
                            (begin 
                              (set! state 'start)
                              0)
                            'ignored)]))
      
(define pstate (cons 0 #f))

(define (to-decimal l)
  (cond [(null? l)
         (let ((ans (exact->inexact (car pstate))))
           (begin
             (set! pstate (cons 0 #f))
             ans))]
        [(and (not (cdr pstate)) (not (eq? #\. (car l)))) 
         (begin
           (set! pstate (cons (+ (* 10 (car pstate)) (- (char->integer (car l)) 48))
                              #f))
           (to-decimal (cdr l)))]
        [(and (not (cdr pstate)) (eq? #\. (car l)))
         (begin
           (set! pstate (cons (car pstate) 1)) 
           (to-decimal (cdr l)))]
        [(cdr pstate)
         (begin
           (set! pstate (cons (+ (car pstate) (* (- (char->integer (car l)) 48)
                                                 (expt 10 (- 0 (cdr pstate)))))
                              (+ (cdr pstate) 1)))
           (to-decimal (cdr l)))]))
         
;(define v (read))
;(display v) (newline)
(define kstate '(#f #f #f))
(define (keyboard)
  (let ((v (read)))
    (cond [(equal? kstate '(#f #f #f)) (begin 
                                         (set! kstate (list v #f #f))
                                         (keyboard))]
          [(equal? (cdr kstate) '(#f #f)) (begin
                                           (set! kstate (list (car kstate) v #f))
                                           (keyboard))]
          [(equal? (cddr kstate) '(#f)) (begin
                                           (set! kstate (list (car kstate) (cadr kstate) v))
                                           (display (+ (car kstate) (cadr kstate) (caddr kstate))) 
                                           (keyboard))]
          [else (let ((l1 (car kstate))
                      (l2 (cadr kstate))
                      (l3 (caddr kstate)))
                  (begin 
                    (set! kstate (list l2 l3 v))
                    (display (+ (car kstate) (cadr kstate) (caddr kstate)))
                    (keyboard)))])))
                                        
                                        
(define (fa i q)
  (define (p) i)
  (if (> i 3) (fa (- i 2) p)
      (begin
        (+ (p)(q)))))
(define (g) '())
(define (m) (fa 4 g))
(m)
                                        
(define (choose n r)
  (if (or (= r 0) (= r n))
      1
      (+ (choose (- n 1) (- r 1))
         (choose (- n 1) r))))

(define (make-2d-vec r c)
  (make-vector r (make-vector c #f)))

(define (2d-vec-ref vec r c)
  (vector-ref (vector-ref vec r) c))

(define (2d-vec-set! vec r c val)
  (let ((v (vector-ref vec r)))
    (begin
      (vector-set! v c val)
      (vector-set! vec r v))))

(define (memo-choose n r)
  (define mem-vec
    (make-2d-vec (+ n 1) (+ r 1)))
  (define (memo-choose-h n1 r1)
    (cond 
      [(2d-vec-ref mem-vec n1 r1) (2d-vec-ref mem-vec n1 r1)]
      [(or (= 0 r1) (= r1 n1)) (begin
                                (2d-vec-set! mem-vec n1 r1 1)
                                1)]
      [else (let ((val (+ (memo-choose-h (- n1 1) (- r1 1))
                          (memo-choose-h (- n1 1) r1))))
              (begin
                (2d-vec-set! mem-vec n1 r1 val)
                val))]))
  (memo-choose-h n r))
           
(define account%
  (class object%
    (init-field account-holder)
    (init-field balance)
    (super-new)
    (define/public (show) balance)
    (define/public (withdraw amount)
      (if (<= amount balance)
          (begin
            (set! balance (- balance amount))
            balance)
          "Insufficient Balance"))
    (define/public (deposit amount)
      (begin
        (set! balance (+ balance amount))
        balance))))
                                      
(define my-account
  (new account%
       [account-holder 'AS]
       [balance 100]))
  
                         
(define protected-account%
  (class account%
    (init passwd)
    (init acholder)
    (init bal)
    (define password passwd)
    (super-new [account-holder acholder] [balance bal])
    (define/override (withdraw pw amount)
      (if (eq? pw password)
          (super withdraw amount)
          "Wrong Password"))))
                                        
                                        
                                        
                                        
                                        
                                        