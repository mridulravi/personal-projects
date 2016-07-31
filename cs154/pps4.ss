#lang racket
(define balance 100)
(define (withdraw amount)
  (if (>= balance amount)
      (begin (set! balance (- balance amount))
             balance)
      "Insufficient funds"))

(define new-withdraw
  (let ((balance 100))
    (lambda (amount)
      (if (>= balance amount)
          (begin (set! balance (- balance amount))
                 balance)
          "Insufficient funds"))))

(define (make-withdraw balance)
  (lambda (amount)
    (if (>= balance amount)
        (begin (set! balance (- balance amount))
               balance)
        "Insufficient funds")))

(define (make-account balance)
  (define (withdraw amount)
    (if (>= balance amount)
        (begin (set! balance (- balance amount))
               balance)
        "Insufficient funds"))
  (define (deposit amount)
    (set! balance (+ balance amount))
    balance)
  (define (dispatch m)
    (cond ((eq? m 'withdraw) withdraw)
          ((eq? m 'deposit) deposit)
          (else (error "Unknown request -- MAKE-ACCOUNT"
                       m))))
  dispatch)

(define (make-accumulator balance)
  (lambda (amount)
        (begin (set! balance (+ balance amount))
               balance)))

(define i 0)
(define (make-monitored f)
      (define (reset-count)
        (set! i 0))
      (define (other-input k)
        (begin 
          (set! i (+ i 1))
           (f k)))
      (define (how-many-calls?)
        i)
      (define (mf m)
        (cond ((eq? m 'how-many-calls?) (how-many-calls?))
              ((eq? m 'reset-count) (reset-count))
              (else (other-input m))))
      mf)

(define k 0)
(define (make-new-account balance password)
  (define (withdraw amount)
    (if (>= balance amount)
        (begin (set! balance (- balance amount))
               (set! i 0)
               balance)
        "Insufficient funds"))
  (define (deposit amount)
        (begin 
          (set! balance (+ balance amount))
          (set! i 0)
          balance))
  (define (ditch amount)
          (if (= i 7)
              (begin 
                (set! i 0)
                (call-the-cops))
              (begin 
                (set! i (+ 1 i))
                display "Incorrect Password")))
  (define (dispatch pword m)
    (cond ((and (eq? m 'withdraw) (eq? pword password))  withdraw)
          ((and (eq? m 'deposit) (eq? pword password)) deposit)
          ((eq? m 'req-joint)
           (if (eq? pword password)
               #t
               #f))
          (else ditch)))
  dispatch)

(define (call-the-cops)
  display "Cops-Called")

(define (make-joint account password1 password2)
  (define (withdraw amount)
    ((account password1 'withdraw) amount))
  (define (deposit amount)
    ((account password1 'deposit) amount))
  (define (ditch amount)
          (if (= i 7)
              (begin 
                (set! i 0)
                (call-the-cops))
              (begin 
                (set! i (+ 1 i))
                display "Incorrect Password")))
  (define (dispatch pword m)
    (cond ((and (eq? m 'withdraw) (eq? pword password2))  withdraw)
          ((and (eq? m 'deposit) (eq? pword password2)) deposit)
          (else ditch)))  
  (if (account password1 'req-joint)
      dispatch
      (display "Wrong Root Password")))

;(define random-init 1)
;(define rand
;  (let ((x random-init))
;    (lambda ()
;      (set! x (rand-update x))
;      x)))
;
;(define (rand-update x)
;  (random x))
;
;
;(define (estimate-pi trials)
;  (sqrt (/ 6 (monte-carlo trials cesaro-test))))
;(define (cesaro-test)
;  (= (gcd (rand) (rand)) 1))
;(define (monte-carlo trials experiment)
;  (define (iter trials-remaining trials-passed)
;    (cond ((= trials-remaining 0)
;           (/ trials-passed trials))
;          ((experiment)
;           (iter (- trials-remaining 1) (+ trials-passed 1)))
;          (else
;           (iter (- trials-remaining 1) trials-passed))))
;  (iter trials 0))

(define state 'start-state)

(define (f x)
  (cond [(eq? state 'start-state) (if (= x 0)
                                      (begin
                                        (set! state 'seen-a-0)
                                        0)
                                      (begin
                                        (set! state 'seen-a-1)
                                        1))]
        [(eq? state 'seen-a-0) (if (= x 1)
                                   (begin
                                     (set! state 'start-state)
                                     0)
                                   (begin
                                     (set! state 'start-state)
                                     1))]
        [(eq? state 'seen-a-1) (if (= x 0)
                                   (begin
                                     (set! state 'start-state)
                                     0)
                                   (begin
                                     (set! state 'start-state)
                                     0))]))

(define gatePosition 'bottom)
(define gateOperation 'nop)
(define carAtGate #f)
(define carJustExited #f)

(define (parking-lot-system tick)
  (cond [(and carAtGate (eq? gateOperation 'nop) (eq? gatePosition 'bottom))
         (begin
           (set! gateOperation 'raise)
           (set! gatePosition 'middle)
           "Gate is being raised, currently is in the middle")]
        [(and carAtGate (eq? gateOperation 'raise) (eq? gatePosition 'middle))
         (begin
           (set! gatePosition 'top)
           (set! gateOperation 'nop)
           "Gate is now at top, and stays there")]
        [(and (eq? gatePosition 'top) (eq? gateOperation 'nop) carAtGate)
         (begin
           (set! carJustExited #t)
           (set! carAtGate #f)
           "Car has now passed")]
        [(and (eq? gatePosition 'top) (eq? gateOperation 'nop) (not carAtGate))
         (begin
           (set! gateOperation 'lower)
           (set! gatePosition 'middle)
           (set! carJustExited #f)
           "Gate is being lowerd, currently is in the middle")]
        [(and (eq? gatePosition 'middle) (eq? gateOperation 'lower) (not carAtGate))
         (begin
           (set! gateOperation 'nop)
           (set! gatePosition 'bottom)
           "Gate closed")]))

(define state-to-decimal 
  (cons 0 #f))
(define x 0)

(define (to-decimal l)
  (cond [(null? l) 
         (begin 
           (set! x (* 1.0 (car state-to-decimal)))
           (set! state-to-decimal (cons 0 #f))
           x)]
        [(char=? #\. (car l)) (begin
                             (set! state-to-decimal 
                                   (cons (car state-to-decimal) 1)) 
                             (to-decimal (cdr l)))]
        [(cdr state-to-decimal) (begin
                                  (set! state-to-decimal
                                        (cons (+ (car state-to-decimal) (* (- (char->integer (car l)) 48) 
                                                                           (expt 10 (- 0 (cdr state-to-decimal)))))
                                              (+ 1 (cdr state-to-decimal))))
                                  (to-decimal (cdr l)))]
        [else (begin 
                (set! state-to-decimal
                      (cons (+ (* 10 (car state-to-decimal)) (- (char->integer (car l)) 48)) (cdr state-to-decimal)))
                (to-decimal (cdr l)))]))
        
      




                                  

  


