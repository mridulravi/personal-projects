#lang racket

(define inverter%
  (class object%
    
    (init-field input)
    (init-field output)
    (init-field (inverter-delay 1)) 
    
    (super-new)
    
    (define (invert-input)
      (let ([new-value (logical-not (send input get-signal))])
        (after-delay inverter-delay
                     (lambda ()
                       (send output set-signal! new-value)))))
    
    (define (logical-not s)
      (cond ((equal? s 0) 1)
            ((equal? s 1) 0)
            (else `undefined)))
    
    (send input add-action! invert-input)
    'ok)) 

(define and-gate%
  (class object%
    (init-field a1)
    (init-field a2)
    (init-field output)
    (init-field (and-gate-delay 3))
    (super-new)
    
    (define (and-action-procedure)
      (let ((new-value (logical-and (send a1 get-signal) (send a2 get-signal))))
        (after-delay and-gate-delay
                     (lambda ()
                       (send output set-signal! new-value)))))
    
    (define (logical-and s1 s2)
      (cond ((and (equal? s1 0) (equal? s2 0))  0)
            ((and (equal? s1 0) (equal? s2 1))  0)
            ((and (equal? s1 1) (equal? s2 0))  0)
            ((and (equal? s1 1) (equal? s2 1))  1)
            (else `undefined)))
    
    (send a1 add-action! and-action-procedure)
    (send a2 add-action! and-action-procedure)
    'ok))

(define or-gate%
  (class object%
    (init-field a1)
    (init-field a2)
    (init-field output)
    (init-field (or-gate-delay 2))
    (super-new)
    
    (define (or-action-procedure)
      (let ((new-value (logical-or (send a1 get-signal) 
                                   (send a2 get-signal))))
        (after-delay or-gate-delay
                     (lambda ()
                       (send output set-signal! new-value)))))
    
    (define (logical-or s1 s2)
      (cond ((and (equal? s1 0) (equal? s2 0))  0)
            ((and (equal? s1 0) (equal? s2 1))  1)
            ((and (equal? s1 1) (equal? s2 0))  1)
            ((and (equal? s1 1) (equal? s2 1))  1)
            (else `undefined)))
    
    (send a1 add-action! or-action-procedure)
    (send a2 add-action! or-action-procedure)))

(define half-adder%
  (class object%
   
    (init-field a)
    (init-field b)
    (init-field s)
    (init-field c)
    
    (define d (make-object  wire% "d"))
    (define e (make-object  wire% "e"))

    (super-new)
    
    (make-object or-gate% a b d)
    (make-object and-gate% a b c)
    (make-object inverter% c e)
    (make-object and-gate% d e s)))
  


(define wire%
  (class object%
    (init wire-name)
    (define  name wire-name)
    (define signal-value `undefined)
    (define action-procedures '())
 
    (super-new)
    
    (define/public (get-name) name)
    
    (define/public (get-signal) signal-value)
        
    (define/public (set-signal! new-value)
      (cond  ((not (equal? signal-value new-value))
              (begin 
                (set! signal-value new-value)
                (call-each action-procedures)))))
    
    (define/public (add-action! proc)
      (set! action-procedures (cons proc action-procedures)))
    
    (define (call-each procedures)
      (if (null? procedures)
          'done
          (begin
            ((car procedures))
            (call-each (cdr procedures)))))))
    

(define event-queue%
  (class object% 
    (define  current-time 0)
    (define last-event-time 0)
    (define queue (make-vector 20 `()))
    
    (super-new)   
    
    (define/public (add-to-queue! time action)
      (begin
        (vector-set! queue time 
                     (append (vector-ref queue time) 
                             (list action)))
        (cond ((> time last-event-time)
               (set! last-event-time time)))))
      
    (define (queue-empty?)
      (> current-time last-event-time))
    
    (define (increment-time!)
      (set! current-time (+ current-time 1)))
    
    (define (next-item-in-queue)
      (vector-ref queue current-time))
    
    (define/public (get-time)
      current-time)
  
    (define/public (propagate!)
      (if (queue-empty?) 'done
          (let ([action-list (next-item-in-queue)])
            (begin
              (execute! action-list)
              (increment-time!)
              (propagate!)))))
 
    (define (execute! action-list)
      (cond ((not (null? action-list)) 
             (begin
               ((car action-list))
               (execute! (cdr action-list))))))))
    
(define probe% 
  (class object%
    (init-field wire)
    (init-field queue)

    (super-new)
    
    (send wire add-action! 
            (lambda ()
              (newline)
              (display "time = ")
              (display (send queue get-time ))
              (newline)
              (display "wire-name = ")
              (display (send wire get-name))
              (newline)
              (display "New-value = ")
              (display (send wire get-signal))
              (newline)
              (newline)))))
  
    
;(define (propagate queue)
;  (if (send the-queue queue-empty?)
;      'done
;      (let ((action-list (send the-queue next-item-in-queue)))
;        (execute! action-list)
;        (send queue increment-time!)
;;       (send queue print)    ; for debugging
;        (propagate queue))))
; 


;(define (execute! action-list)
;  (cond ((not (null? action-list)) 
;         (begin
;                ((car action-list))
;                (execute! (cdr action-list))))))

(define (after-delay delay action)
  (send the-queue add-to-queue! (+ delay (send the-queue get-time)) action))

(define the-queue (make-object event-queue%))

(define a (make-object  wire% "a"))
(define b (make-object  wire% "b"))
(define s (make-object  wire% "s"))
(define c (make-object  wire% "c"))

(make-object probe% a the-queue)
(make-object probe% b the-queue)
(make-object probe% s the-queue)
(make-object probe% c the-queue)

(make-object half-adder% a b s c)

(send the-queue add-to-queue! 3 (lambda () (send b set-signal! 1)))
(send the-queue add-to-queue! 1 (lambda () (send a set-signal! 0)))

(send the-queue propagate!)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;  
;(define a (make-object  wire% "a"))
;(define b (make-object  wire% "b"))
;(define ci (make-object  wire% "ci"))
;(define s (make-object  wire% "s"))
;(define co (make-object  wire% "co"))

;(make-object probe% "a" a the-queue)
;(make-object probe% "b" b the-queue)
;(make-object probe% "ci" ci the-queue)
;(make-object probe% "s" s the-queue)
;(make-object probe% "co" co the-queue)

;(make-object full-adder% a b ci s co)

;(send the-queue add-to-queue! 3 (lambda () (send b set-signal! 1)))
;(send the-queue add-to-queue! 1 (lambda () (send a set-signal! 0)))
;(send the-queue add-to-queue! 2 (lambda () (send ci set-signal! 1)))


;(define full-adder%
;  (class object%
;   
;    (init-field a)
;    (init-field b)
;    (init-field ci)
;    (init-field s)
;    (init-field co)
;    
;    (define d (make-object  wire% "d"))
;    (define e (make-object  wire% "e"))
;    (define f (make-object  wire% "f"))
;    
;    (super-new)
;    
;    (make-object half-adder% b ci d e)
;    (make-object half-adder% a d s f)
;    (make-object or-gate%  f e co)))