(define (missile-destroyed-by-anti-missile l) ; l is the active-anti-missiles list.
  (define missiles-deleted `())
  (define anti-missiles-deleted `())
(map (lambda(x)
       (cond [ (get-field missile-attached x) 
                (let* ([ M (get-field missile-attached x)]
                       [ A-pos (get-field pos2 x)]
                       [ M-pos (get-field pos2 M)]
                       [ Ax (car A-pos)]
                       [ Ay (cdr A-pos)]
                       [ Mx (car M-pos)]
                       [ My (cdr M-pos)]
                       [ dist (sqrt (+ (expt (- Mx Ax) 2) (expt (- My Ay) 2)))])
                  (cond [ (<= dist 5) 
                        (begin 
                          (set! missiles-deleted (cons M missiles-deleted))
                          (set! anti-missiles-deleted (cons x anti-missiles-deleted)))]))])) l)
       (map (lambda(x) (set!  active-anti-missiles (delete x active-anti-missiles))) anti-missiles-deleted)
       (map (lambda(x) (set! active-missiles (delete x active-missiles))) missiles-deleted))
