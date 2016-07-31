#lang racket

(require racket/mpair)



;Q2

(define processor%
  (class object%
    (super-new)
    (init mem-size)
    (init reg-names)
    (define memory (new memory% [size mem-size]))
    (define reg-bank (new register-bank% [names (list->mlist reg-names)]))
    (init-field inst-set)
    (define/public (execute prog)
      (executeh prog 0))
    (define/public (executeh prog i)
      (if (= i (vector-length prog)) "Done"
          (begin
            (let* ([instr (vector-ref prog i)]
                   [no-of-operands (- (length instr) 1)]
                   [mnemonic (car instr)])
              (cond [(eq? mnemonic `load)
                     (cond [(number? (caddr instr)) 
                            (send reg-bank write (cadr instr) (caddr instr))]
                           [else (send reg-bank write (cadr instr) 
                                       (send reg-bank read (caddr instr)))])]
                    [(eq? mnemonic `jmp)
                     (executeh prog (cadr instr))]
                    [(eq? mnemonic `if)
                     (if (car instr)
                         (executeh prog (cadr instr))
                         (executeh prog (caddr instr)))]
                    [(eq? mnemonic `end)
                     (executeh prog (vector-length prog))]
                    [(assoc mnemonic inst-set)
                     (let* ([fun (cadr (assoc mnemonic inst-set))])
                       (cond [(= no-of-operands 1) 
                              (let* ([rname (cadr instr)]
                                     [val (fun (send reg-bank read rname))])
                                (send reg-bank write rname val))]
                             [(= no-of-operands 2) 
                              (let* ([rname1 (cadr instr)]
                                     [rname2 (caddr instr)]
                                     [val (fun (send reg-bank read rname1)
                                               (send reg-bank read rname2))])
                                (send reg-bank write rname1 val))]))]
                    [else (error "Unexpected instruction")]))
            (newline) 
            (display "Memory:")  
            (newline) 
            (send  memory print)
            (newline) 
            (display "Registers:")  
            (newline) 
            (send  reg-bank print)
            (executeh prog (+ i 1)))))))

(define (mzip l1 l2)
  (cond [(or (null? l1) (null? l2)) `{}]
        [(mcons (mcons (mcar l1) (mcar l2))
                (mzip (mcdr l1) (mcdr l2)))]))

(define (all-zeroes n)
  (if (= n 1) (mlist 0)
      (mappend (all-zeroes (- n 1)) (mlist 0))))

(define storable%
  (class object%
    (super-new)
    (define/public (read) (error "Should be overridden"))
    (define/public (write) (error "Should be overridden"))
    (define/public (print) (error "Should be overridden"))))

(define register-bank%
  (class storable%  
    (super-new)
    (init names)
    (init-field (registers (mzip names 
                                (all-zeroes (length (mlist->list names))))))
    (define/override (read rname) 
      ; Here the register bank gets a valid register name
      (mcdr (massoc rname registers)))
    (define/override (write rname value) 
      (set-mcdr! (massoc rname registers)  value))
    (define/override (print)
      (newline)
      (display registers)
      (newline))))

(define memory%
  (class storable%
    (super-new)
    (init-field size)
    (define memory (make-vector size 0))
    (define/override (read addr)
      (vector-ref memory addr))
    (define/override (write addr val)
      (vector-set! memory addr val))
    (define/override (print) 
      (newline) 
      (display memory) 
      (newline))))

(define as2013 
  (new processor% 
       [mem-size 32] 
       [reg-names (list `r1 `r2 `r3 `r4)]
       [inst-set (list  (list 'add  (lambda (val1 val2) 
                                      (+ val1 val2)))
                        (list 'mul  (lambda (val1 val2) 
                                      (* val1 val2)))
                        (list 'incr (lambda (val) 
                                      (+ 1 val))))]))


(define sample-prog (list->vector (list
    (list 'load 'r1  0)   ;Put in register r2 the number 15
    (list 'load 'r2  5)
    (list 'load 'r3  1)
    (list 'load 'r4  'r1)
    (list 'add  'r1  'r2)   ;Add r1 and r2, the result goes to r1
    (list 'load 'r3    2)   ;Put in register r3 the number 2
    (list 'incr 'r3)        ;Increment contents of r4 by 1
    (list 'mul  'r3  'r2)   ;Multiply r3 and r2, the result goes to r3
    (list 'add  'r1  'r3)   ;Add r1 and r3, the result goes to r1
    ))) ;Store r1 in memory location 1

(send as2013 execute sample-prog)
