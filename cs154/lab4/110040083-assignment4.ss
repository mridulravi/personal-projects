#lang racket
(require racket/mpair)
(require compatibility/mlist)
;(require racket/vector)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Problem : 2

(define timer%
  (class object%
    (init-field (list-of-actions '()))
    (init-field (list-of-credit-card-actions '()))
    (super-new)
    (define/public (add-to-list action)
      (set! list-of-actions (cons action list-of-actions)))
    (define/public (add-to-credit-card-list action)
      (set! list-of-credit-card-actions 
            (cons action list-of-credit-card-actions)))
    (define/public (process-accounts-tick)
      (call-each list-of-actions))
    (define/public (process-credit-card-tick)
      (call-each list-of-credit-card-actions))
    (define (call-each procedures)
      (cond ((not (null? procedures))
             (begin
               ((car procedures))
               (call-each (cdr procedures))))))))      

(define this-timer (new timer%))

(define account% 
  (class object%
    (init-field passwd)
    (init-field balance)
    (init-field interest-rate)
    (super-new)
    (define/public (show password)
      (if (eq? password passwd)
          balance
          "Incorrect Passwd"))
    (define/public (withdraw amount password)
      (if (eq? password passwd)
          (if (<= amount balance)
              (set! balance (- balance amount))
              "Insufficient funds")
          "Incorrect Passwd"))
    (define/public (deposit amount)
      (set! balance (+ balance amount)))
    (define (pay-interest)
      (set! balance (+ balance (* balance interest-rate))))
    (send this-timer add-to-list pay-interest)))

(define credit-card%
  (class object%
    (init-field acct)
    (init-field passwd)
    (define temp 0)
    (super-new)
    (define/public (make-purchase amount)
      (set! temp amount))
    (define/public (clear-outstanding-amount)
      (begin
        (send acct withdraw temp passwd)
        (set! temp 0)
        ))
    (define (pay-fine)
      (if (= temp 0)
          (set! temp 0)
          (set! temp (+ temp (* temp 0.2)))))
    (send this-timer add-to-credit-card-list pay-fine)))

(define joint-account%
  (class object%
    (init-field account)
    (init-field passwd)
    (init-field new-passwd)
    (super-new)
    (define/public (show password)
      (if (eq? password new-passwd)
          (send account show passwd)
          "Incorrect Passwd"))
    (define/public (withdraw amount password)
      (if (eq? password new-passwd)
          (send account withdraw amount passwd)
          "Incorrect Passwd"))
    (define/public (deposit amount)
      (send account deposit amount))))
  


(define my-account (new account% (passwd "amitabha") 
                                 (balance 1000) 
                                 (interest-rate 0.05)))
(define my-card (new credit-card% (acct my-account) 
                                  (passwd "amitabha")))
(define another-account (new account% (passwd "abcd")
                                      (balance 5000) 
                                      (interest-rate 0.1)))
(define another-card (new credit-card% (acct another-account) 
                                       (passwd "abcd")))
(define jnt-account (new joint-account% (account my-account) 
                                        (passwd "amitabha") 
                                        (new-passwd "xyz")))
(define jnt-card (new credit-card% (acct jnt-account) 
                                  (passwd "xyz")))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Problem : 1

(define (foldr f id l)
  (if (null? l) id
      (f (car l) (foldr f id (cdr l)))))

(define (concat l) (foldr append `() l))

(define-syntax lc
  (syntax-rules (: <- @)
    [(lc exp : var <- lexp) (map (lambda (var) exp) lexp)]
    [(lc exp : @ guard) (if guard (list exp) `())]
    [(lc exp : @ guard qualifier ...) 
     (concat (lc (lc exp : qualifier ...) : guard))]
    [(lc exp : var <- lexp qualifier ...) 
     (concat (lc (lc exp :  qualifier ... ) : var <- lexp))]))

(define storable%
  (class object%
    (super-new)
    (define/public (read) (error "Should be overridden"))
    (define/public (write) (error "Should be overridden"))
    (define/public (print) (error "Should be overridden"))))


(define register-bank%
  (class storable%
    (init-field reg-names-list)
    (define m-list-reg (list->mlist (lc (mcons x 0) : x <- reg-names-list)))
    (super-new)
    (define/override (read reg)
      (read-h reg m-list-reg))
    (define (read-h r l)
      (if (eq? (mcar (mcar l)) r)
          (mcdr (mcar l))
          (read-h r (mcdr l))))
    (define/override (write reg-val)
      (write-h reg-val m-list-reg))
    (define (write-h r-v l)
      (if (eq? (mcar (mcar l)) (mcar r-v))
          (set-mcdr! (mcar l) (mcdr r-v))
          (write-h r-v (mcdr l))))
    (define/override (print)
      (display "Registers:")
      (newline)
      (newline)
      (display m-list-reg)
      (newline)
      (newline))))
      

    
(define memory%
  (class storable%
    (init-field size)
    (define mem (make-vector size 0))
    (super-new)
    (define/override (print)
      (display "Memory:")
      (newline)
      (newline)
      (display mem)
      (newline)
      (newline))
    (define/override (write pos val)
      (vector-set! mem pos val))
    (define/override (read pos)
      (vector-ref mem pos))))
    
(define processor%
  (class object%
    (init-field mem-size)
    (init-field reg-names)
    (init-field inst-set)
    (define registerb (make-object register-bank% reg-names))
    (define memory (make-object memory% mem-size))
    (super-new)
    (define/public (execute prog)
      (cond
        [(null? prog) "Done"]
        [(eq? (caar prog) 'load) 
         (begin
           (send registerb write (mcons (cadar prog) (caddar prog)))
           (send memory print)
           (send registerb print)
           (execute (cdr prog)))]
        [(eq? (caar prog) 'store)
         (begin
           (send memory write (cadar prog) (send registerb read (caddar prog)))
           (send memory print)
           (send registerb print)
           (execute (cdr prog)))]
        [else
         (begin
           (send registerb write (mcons (cadar prog)
                                        (if (= 2 (length (cdar prog)))
                                            (car (lc ((cadr x)
                                                  (send registerb read (cadar prog))
                                                  (send registerb read (caddar prog))) 
                                                 : x <- inst-set @ (eq? (car x) (caar prog))))
                                            (car (lc ((cadr x)
                                                  (send registerb read (cadar prog)))
                                                  ;(send registerb read (caddar prog)))  
                                                 : x <- inst-set @ (eq? (car x) (caar prog)))))))
           (send memory print)
           (send registerb print)
           (execute (cdr prog)))]))))


(define as2013
(new processor%
     [mem-size 32]
     [reg-names (list 'r1 'r2 'r3 'r4)]
     [inst-set (list (list 'add (lambda (val1 val2)
                                  (+ val1 val2)))
                     (list 'mul (lambda (val1 val2)
                                  (* val1 val2)))
                     (list 'incr (lambda (val)
                                   (+ val 1))))]))



(define sample-prog (list
                     (list 'load 'r2   15)   ;Put in register r2 the number 15
                     (list 'load 'r1    5)
                     (list 'store  1  'r1)
                     (list 'add  'r1  'r2)   ;Add r1 and r2, the result goes to r1
                     (list 'load 'r3    2)   ;Put in register r3 the number 2
                     (list 'incr 'r3)        ;Increment contents of r4 by 1
                     (list 'mul  'r3  'r2)   ;Multiply r3 and r2, the result goes to r3
                     (list 'add  'r1  'r3)   ;Add r1 and r3, the result goes to r1
                     (list 'store  1  'r1)))

;(send as2013 execute sample-prog)  
