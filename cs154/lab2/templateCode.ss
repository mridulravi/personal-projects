#lang racket

(define n 4)
(define m 8)
(define k 4)
(define l 3)

; Returns a pair of carry and sum (carry.sum)
; carry = (a & b) | (b & c) | (a & c)
; sum = a ^ b ^ c
(define (bit-adder a b c)
  (cons (bitwise-ior (bitwise-and a b)
                     (bitwise-and b c)
                     (bitwise-and a c))
        (bitwise-xor a b c)))

; Returns a pair of borrow and subtraction (borrow-out.sub)
; Does m - n - borrow-in
; borrow-out = (m' & borrow-in) | (n & (m ^ borrow-in)')
; sub = m ^ n ^ borrow-in
(define (bit-subtractor m n borrow-in)
  (cons (bitwise-ior (bitwise-and (bitwise-not m) borrow-in)
                     (bitwise-and n (bitwise-not (bitwise-xor m borrow-in))))
        (bitwise-xor m n borrow-in)))

