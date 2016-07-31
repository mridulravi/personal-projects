#lang racket


(define (myerror a b)
  (newline)
  (display a)
  (newline)
  (display b)
  (newline))

(define adder% 
  (class object% 
    (init-field a1)
    (init-field a2)
    (init-field sum)
    (super-new)

    (define/public (process-new-value)
      (cond [(and (send a1 has-value?) (send a2 has-value?))
             (send sum set-value!
                   (+ (send a1 get-value) (send a2 get-value)) this)]
            ((and (send a1 has-value?) (send sum has-value?))
             (send a2 set-value!
                   (- (send sum get-value) (send a1 get-value)) this))
            ((and (send a2 has-value?) (send sum has-value?))
             (send a1 set-value!
                   (- (send sum get-value) (send a2 get-value)) this))))
    
    (define/public (process-forget-value)
      (send sum forget-value! this)
      (send a1 forget-value! this)
      (send a2 forget-value! this)
      (process-new-value))
     
    (begin
      (send a1 connect this)
      (send a2 connect this) 
      (send sum connect this))))

(define multiplier% 
  (class object% 
    (init-field a1)
    (init-field a2)
    (init-field sum)
    (super-new)
    
    (define/public (process-new-value)
      (cond ((and (send a1 has-value?) (send a2 has-value?))
             (send sum set-value!
                   (* (send a1 get-value) (send a2 get-value)) this))
            ((and (send a1 has-value?) (send sum has-value?))
             (send a2 set-value!
                   (/ (send sum get-value) (send a1 get-value)) this))
            ((and (send a2 has-value?) (send sum has-value?))
             (send a1 set-value!
                   (/ (send sum get-value) (send a2 get-value)) this))))
    
    (define/public (process-forget-value)
      (send sum forget-value! this)
      (send a1 forget-value! this)
      (send a2 forget-value! this)
      (process-new-value))
     
    (begin
      (send a1 connect this)
      (send a2 connect this) 
      (send sum connect this))))

(define constant% 
  (class object% 
    (init-field value)
    (init-field connector)
    (super-new)
    (send connector connect this)
    (send connector set-value! value this)))

(define probe%
  (class object%
    (init-field name)
    (init-field connector)
    (super-new)
    
    (define/public (print-probe value)
      (newline)
      (display "Probe: ")
      (display name)
      (display " = ")
      (display value))
    
    (define/public (process-new-value)
      (print-probe (send connector get-value)))
    
    (define/public (process-forget-value)
      (print-probe "?"))

    (send connector connect this)))

(define connector%
  (class object%
    (init-field [value #f])
    (init-field [informant #f])
    (init-field [constraints '()])
    (super-new)
    (define/public (set-value! newval setter)
      (cond ((not (has-value?))
             (set! value newval)
             (set! informant setter)
             (for-each-except setter
                              `process-new-value
                              constraints))
            ((not (= value newval))
             (myerror "Contradiction" (list value newval)))
            (else 'ignored)))
    
    (define/public (forget-value! retractor)
      (if (eq? retractor informant)
          (begin (set! informant false)
                 (for-each-except retractor
                                  `process-forget-value
                                  constraints))
          'ignored))
    
    (define/public (connect new-constraint)
      (cond [(not (memq new-constraint constraints))
             (set! constraints 
                   (cons new-constraint constraints))])
      (cond [(has-value?)
             (send new-constraint process-new-value)])
           'done) 
    (define/public (has-value?) (if informant true false))
    
    (define/public (get-value) value)
    
    (define/public (for-each-except exception procedure list)
      (define (loop items)
        (cond ((null? items) (begin (newline) 'done))
              ((eq? (car items) exception) (loop (cdr items)))
              (else (begin
                      (cond ((equal? procedure `process-new-value) 
                             (send (car items) process-new-value))
                            ((equal? procedure `process-forget-value) 
                             (send (car items) process-forget-value))))
                    (loop (cdr items)))))
      (loop list))))
      



;(define C (new connector%))
;(define F (new connector%))
;(define u (new connector%))
;(define v (new connector%))
;(define w (new connector%))
;(define x (new connector%))
;(define y (new connector%))
;
;(make-object multiplier% C w u)
;(make-object multiplier% v x u)
;(make-object adder% v y F) 
;(make-object constant% 9 w)
;(make-object constant% 5 x)
;(make-object constant% 32 y)
;
;(define probe1 (make-object probe% "Celsius temp" C))
;(define probe2 (make-object probe% "Fahrenheit temp" F))

;(send C set-value! 5 'user)
;(send F set-value! 5 'user)
;(send C forget-value! 'user)
;
;(send C set-value! 6 'user)



(define a (new connector%))
(define b (new connector%))
(define c (new connector%))
;
(send a set-value! 5 'user)
(send b set-value! 6 'user)
(send c set-value! 19 'user)
;
(make-object adder% a b c) 
;
(define probe4 (make-object probe% "a" a))
(define probe5 (make-object probe% "b" b))
(define probe6 (make-object probe% "c" c))
;(set-value! b 9 'user)


(define account%
  (class object%
    (init-field ah)
    (init-field bal)
    (super-new)
    (define/public (show) bal)))

(define my-acc
  (new account%
       (ah 'AS)
       (bal 10000)))