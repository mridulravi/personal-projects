#lang racket

(require compatibility/mlist)
 (require "assignment4-2013.scm")
 
;test cases for Q1 

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
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;Direct withdrawals
(send my-account withdraw 200 "amitabha")
(send my-account deposit 100)
;(send jnt-account deposit 100)
(send my-account show "amitabha")
(send jnt-account withdraw 200 "amitabha")
;(send jnt-account deposit 100)
(send jnt-account show "xyz")
(send this-timer process-accounts-tick)
(send my-account show "amitabha")
(send another-account show "abcd")

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;Credit card transactions
(send my-card make-purchase 100)
(send this-timer process-credit-card-tick)
(send my-card clear-outstanding-amount)
(send my-account show "amitabha")
;
(send jnt-card make-purchase 100)
(send this-timer process-credit-card-tick)
(send jnt-card clear-outstanding-amount)
;(send jnt-account deposit 100)
(send jnt-account show "xyz")
;
(send my-card make-purchase 50)
(send my-account show "amitabha")
(send my-account withdraw 200 "amitabha")
(send another-card make-purchase 1000)
(send another-card clear-outstanding-amount) 
(send this-timer process-credit-card-tick)
(send my-account show "amitabha")
(send my-card clear-outstanding-amount)
(send another-account show "abcd")
(send my-account show "amitabha")

;test-case for Q2

;Define as2013 here 
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

(send as2013 execute sample-prog) 
;(define l (mcons 'r1 3))
;(define mem (make-vector 2 0))
;(print mem)
;l
;(mcdr l)