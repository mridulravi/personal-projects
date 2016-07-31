#lang racket/gui
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;macros are defined here
(define-syntax for
  (syntax-rules (:)
    [(for init : bexp : change : statements)
     (begin
       init
       (define (loop)
         (cond[bexp (begin
                      statements
                      change
                      (loop))]))
     (loop))]))

(define v 50.0)
(define active-missiles '())
(define temp #f)
(define time 0)
(define active-buildings '())
(define active-anti-missiles `())
(define time-increment 0.01)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;missile class is defined here
(define missile%
  (class object%
    (init-field (pos1 #f))
    (init-field (pos2 #f))
    (init-field (launch-time #f))
    (init-field (theta #f))
    (init-field (ux #f))
    (init-field (uy #f))
    (init-field (detected-by-radar #f))
    (init-field (is-anti-missile-attached #f))
    (super-new)
    (define/public (update-missile-position current-time) ; updates pos2 
      (let*([ t (- current-time launch-time)]
            [ sx (* ux t)]
            [ sy (* uy t)]
            [ x0 (car pos1)]
            [ y0 (cdr pos1)])
      (set! pos2 (cons (+ x0 sx) (+ y0 sy)))))))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;building class is defined here
(define building%
  (class object%
    (super-new)
    (init-field (posx #f))
    (init-field (posy #f))
    (init-field (height 60))
    (init-field (width 40))))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;anti-missile class is defined here
(define anti-missile%
  (class object%
    (init-field (pos1 #f))
    (init-field (pos2 #f))
    (init-field (theta #f))
    (init-field (ux #f))
    (init-field (uy #f))
    (init-field (missile-attached #f))
    (init-field (launch-time #f))
    (super-new)
    (define/public (update-anti-missile-position current-time) ; updates pos2 
      (let*([ t (- current-time launch-time)]
            [ sx (* ux t)]
            [ sy (* uy t)]
            [ x0 (car pos1)]
            [ y0 (cdr pos1)])
      (set! pos2 (cons (+ x0 sx) (+ y0 sy)))))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;Anti-missile-gun class is defined here
(define anti-missile-gun%
  (class object%
    (super-new)
    (init-field (posx #f))
    (init-field (posy #f))
    (init-field (current-angle #f))
    (init-field (missile-attached-antigun #f))
    (init-field (final-angle #f))
    (init-field (isFree? #f))
    (init-field (radius 200))
    (init-field (speed 1))
    (define/public (update)
      (cond [(not isFree?)
             (cond[(< (abs (- current-angle final-angle)) (* time-increment speed))
                   (begin
                     (set! isFree? #t)
                     (set! current-angle final-angle)
                     (set! final-angle #f)
                     (set! active-anti-missiles 
                           (append active-anti-missiles
                                   (list
                                    (new anti-missile% 
                                         [pos1 (cons posx posy)]
                                         [pos2 (cons posx posy)]
                                         [theta current-angle]
                                         [ux (* v (cos current-angle))]
                                         [uy (- (* v (sin current-angle)))]
                                         [missile-attached missile-attached-antigun]
                                         [launch-time time]))))
                     (set! missile-attached-antigun #f))]                                
                 
                  [(< current-angle final-angle) (set! current-angle (+ current-angle (* time-increment speed)))]
                  [(> current-angle final-angle) (set! current-angle (- current-angle (* time-increment speed)))])]))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;define anti-missile gun here
(define gun (new anti-missile-gun%
                 [current-angle (/ pi 2)]
                 [posx 650]
                 [posy 670]
                 [isFree? #t]))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;Graphic portion starts from here
(define frame (new frame% [label "Test"] [width 1300] [height 670]))

(define my-canvas%
  (class canvas%
    (super-new)
    (define/override (on-event e)
      (cond [(equal? (send e get-event-type) 'left-down)
          (cond[(not (eq? temp #f))
                     (begin
                       (set-field! pos2 temp (cons (send e get-x) (send e get-y)))
                       (set-field! launch-time temp time)
                       (set-field! theta temp (let*([a (get-field pos1 temp)]
                                                    [b (get-field pos2 temp)])
                                                (atan (/ (- (cdr b) (cdr a))
                                                         (- (car b) (car a))))))
                       (let*([p1 (get-field pos1 temp)]
                             [p2 (get-field pos2 temp)]
                             [x1 (car p1)]
                             [y1 (cdr p1)]
                             [x2 (car p2)]
                             [y2 (cdr p2)])
                         (cond[(= x1 x2)
                               (begin
                                 (set-field! ux temp 0)
                                 (set-field! uy temp v))]
                              [(> x1 x2)
                               (begin
                                 (set-field! ux temp (- (* v (cos (get-field theta temp)))))
                                 (set-field! uy temp (- (* v (sin (get-field theta temp))))))]
                              [else (begin
                                      (set-field! ux temp (* v (cos (get-field theta temp))))
                                      (set-field! uy temp (* v (sin (get-field theta temp)))))]))
                       (set! active-missiles (append active-missiles (list temp)))
                       (set! temp #f))])]))))
          

(define panel (new horizontal-panel% [parent frame]
                   [alignment (list 'left 'top)]))

(define mycanvas (new my-canvas% [parent frame]
                      [min-height 670]
                      [paint-callback
                     (lambda (canvas dc) (paint dc))]))

(define button1 (new button% [parent panel]
                     [label "Missile1"]
                     [horiz-margin 190]
                     [callback (lambda (button event)
                                 (begin
                                   (set! temp (new missile%))
                                   (set-field! pos1 temp (cons 225 0))))]))

(define button2 (new button% [parent panel]
                     [label "Missile2"]
                     [horiz-margin 10]
                     [callback (lambda (button event)
                                 (begin
                                   (set! temp (new missile%))
                                   (set-field! pos1 temp (cons 490 0))))]))

(define button3 (new button% [parent panel]
                     [label "Missile3"]
                     [horiz-margin 190]
                     [callback (lambda (button event)
                                 (begin
                                   (set! temp (new missile%))
                                   (set-field! pos1 temp (cons 760 0))))]))

(define button4 (new button% [parent panel]
                     [label "Missile4"]
                     [horiz-margin 10]
                     [callback (lambda (button event)
                                 (begin
                                   (set! temp (new missile%))
                                   (set-field! pos1 temp (cons 1025 0))))]))

(send frame show #t)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; brushes and pens
(define black-pen (make-object pen% "BLACK" 1 'solid))
(define no-brush (make-object brush% "BLACK" 'transparent))
(define blue-brush (make-object brush% "BLUE" 'solid))
(define yellow-brush (make-object brush% "YELLOW" 'solid))
(define red-pen (make-object pen% "RED" 2 'solid))

(define (paint dc) (send dc draw-bitmap face-bitmap 0 0))
(define face-bitmap (make-object bitmap% 1500 1500))
; Create a drawing context for the bitmap
(define bm-dc (make-object bitmap-dc% face-bitmap))

(send bm-dc clear)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (draw dc)
  (send mycanvas refresh)
  (send dc clear)
  (send dc set-pen black-pen)
  (send dc set-brush blue-brush)
  (map (lambda (a) (let([x (get-field posx a)]
                        [y (get-field posy a)]
                        [sizex (get-field width a)]
                        [sizey (get-field height a)])
                     (send dc draw-rectangle x y sizex sizey))) active-buildings)
  (map (lambda (a) (let([x (car (get-field pos2 a))]
                        [y (cdr (get-field pos2 a))])
                     (send dc draw-rectangle x y 20 20))) active-missiles)
  (map (lambda (a) (let([x (car (get-field pos2 a))]
                        [y (cdr (get-field pos2 a))])
                     (send dc draw-rectangle x y 20 20))) active-anti-missiles)
  (let([x (-(get-field posx gun) 50)]
       [y (-(get-field posy gun) 50)]
       [rad (/(get-field radius gun) 2)])
    (send dc draw-arc x y rad rad 0 pi))
  (let* ([x1 (get-field posx gun)]
         [y1 (get-field posy gun)]
         [length (+ (/ (get-field radius gun) 4) 20)]
         [angle (get-field current-angle gun)]
         [x2 (+ x1 (* length (cos angle)))]
         [y2 (- y1 (* length (sin angle)))])
    (send dc draw-line x1 y1 x2 y2)))

;;Graphic portion ends here
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;Functions used are defined here

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (takewhile p l)
  (cond [ (null? l) `()]
        [ (p (car l)) (cons (car l) (takewhile p (cdr l)))]
        [ else `()]))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (dropwhile p l)
  (cond [ (null? l) `()]
        [ (p (car l)) (dropwhile p (cdr l))]
        [ else l]))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (delete x l)
  (cond [(null? l) (error "trying to delete elt from null list")]
        [ else 
          (append (takewhile (lambda(y) (not (eq? y x))) l)
                  (cdr (dropwhile (lambda(y) (not (eq? y x))) l)))]))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;update missile positions
(define (update-missiles missile-list)
  (cond[(not (null? missile-list))
        (begin
          (send (car missile-list) update-missile-position time)
          (update-missiles (cdr missile-list)))]))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;update anti-missiles positions
(define (update-anti-missiles anti-missile-list)
  (cond[(not (null? anti-missile-list))
        (begin
          (send (car anti-missile-list) update-anti-missile-position time)
          (update-anti-missiles (cdr anti-missile-list)))]))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (missile-destroyed-by-anti-missile l) ; l is the active-anti-missiles list.
  (define missiles-deleted `())
  (define anti-missiles-deleted `())
  (define (helper l1)
    (cond [ (and (not( null? l1))
                 (get-field missile-attached (car l1)))
            (let* ([ A (car l1)]
                   [ M (get-field missile-attached A)]
                   [ A-pos (get-field pos2 A)]
                   [ M-pos (get-field pos2 M)]
                   [ Ax (car A-pos)]
                   [ Ay (cdr A-pos)]
                   [ Mx (car M-pos)]
                   [ My (cdr M-pos)]
                   [ dist (sqrt (+ (expt (- Mx Ax) 2) (expt (- My Ay) 2)))])
              (begin 
                (cond [ (<= dist 5) 
                        (begin 
                          (set! missiles-deleted (cons M missiles-deleted))
                          (set! anti-missiles-deleted (cons A anti-missiles-deleted)))])
                (helper (cdr l1))))]
          [(and (not( null? l1))
                 (not (get-field missile-attached (car l1)))) (helper (cdr l1))]))
  (begin
    (helper l)
    (map (lambda(x) (set!  active-anti-missiles (delete x active-anti-missiles))) anti-missiles-deleted)
    (map (lambda(x) (set! active-missiles (delete x active-missiles))) missiles-deleted)))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;   
(define (all-buildings-destroyed) (null? active-buildings))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (missile-near-building missile building)
  (let*([b-lux (get-field posx building)]
        [b-luy (get-field posy building)]
        [b-llx b-lux]
        [b-lly (+ (get-field height building)
                  (get-field posy building))]
        [b-rux (+ (get-field width building)
                  (get-field posx building))]
        [b-ruy b-luy]
        [b-rlx b-rux]
        [b-rly b-lly]
        [m-pos (get-field pos2 missile)]
        [m-posx (car m-pos)]
        [m-posy (cdr m-pos)])
    (cond[(and (<= m-posx b-rux) (>= m-posx b-lux)
               (<= m-posy b-rly) (>= m-posy b-ruy))
          #t]
         [else #f])))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (building-hit-by-missile l) ; l is the active-missiles list
  (define missiles-deleted `())
  (define buildings-deleted `())
  (define (helper l1)
    (cond [ (not (null? l1))
                (begin 
                (let* ([ M (car l1)])
                  (for (define i active-buildings) : 
                    (not (null? i)) : 
                    (set! i (cdr i)) : 
                    (begin
                      (define j (car i))
                      (cond [(missile-near-building M j) 
                             (set! missiles-deleted (cons M missiles-deleted))
                             (set! buildings-deleted (cons j buildings-deleted))
                             (set! i `(1))]))))
                (helper (cdr l1)))]))
  (begin
    (helper l)
    (map (lambda(x) (set!  active-missiles (delete x active-missiles))) missiles-deleted)
    (map (lambda(x) (set! active-buildings (delete x active-buildings))) buildings-deleted)))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (distance-between-points p1 p2)
  (sqrt (+ (expt (- (car p1) (car p2)) 2)
           (expt (- (cdr p1) (cdr p2)) 2))))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (is-missile-in-radar-scope m)
  ;(begin (print "is missile in radar scope entered")
  (let* ([ pos (get-field pos2 m)]
         [ pt1 (cons 0 670)]
         [ pt2 (cons 1300 670)]
         [ pt3 (cons 650 670)]
         [ dist 400])
    (or (<= (distance-between-points pos pt1) dist)
        (<= (distance-between-points pos pt2) dist)
        (<= (distance-between-points pos pt3) dist))))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (main-logic-function)
  (define (helper l)
    (cond [(not (null? l)) 
           ;(print "helper of main logic entered")
           (let* ([ M (car l)])
             (cond [ (and (not (get-field is-anti-missile-attached M))
                          (is-missile-in-radar-scope M)
                          (get-field isFree? gun))
                     (associate-anti-missile M)]))           
           (helper (cdr l))]))
  (helper active-missiles))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (associate-anti-missile m)
  (let* ([ mpos (get-field pos2 m)]
         [ xm (car mpos)]
         [ ym (cdr mpos)]
         [ ux (get-field ux m)]
         [ uy (get-field uy m)]
         [ x0 (get-field posx gun)]
         [ y0 (get-field posy gun)]
         [ current-angle (get-field current-angle gun)]
         [ speed (get-field speed gun)]
         [ fin-angle (solve xm ym ux uy x0 y0 current-angle speed)])
    (cond (fin-angle 
           (begin 
             ;(print "final angle set")
             (set-field! final-angle gun fin-angle)
             (set-field! missile-attached-antigun gun m)
             (set-field! is-anti-missile-attached m #t)
             (set-field! isFree? gun #f))))))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (solve xm ym ux uy x0 y0 current-angle speed)
  (define mypair (cons #f #f))
  (begin 
    ;(print "ent solve")
    (for (define phi 0) :
      (<= phi pi) :
      (set! phi (+ phi (/ pi 180))) :
      (begin 
        (define t1  ( + time (/ (abs (- current-angle phi)) speed)))
        (cond [ (not (= 0 (- ux (* v (cos phi))))) 
                (let* ([ tx (/ (+ x0 (* ux time) (* -1 xm) (* -1 t1 (cos phi) v))   
                               (- ux (* v (cos phi))))]
                       [ ty (/ (+ y0 (* v (sin phi) t1) (* uy time) (* -1 ym))
                               (+ uy (* v (sin phi))))])
                  (cond [ (> 0.9 (abs (- tx ty)))  
                          (cond [ (and (car mypair) (< tx (cdr mypair))) 
                                  (set! mypair (cons phi tx))]
                                [ (not (car mypair)) (set! mypair (cons phi tx))])]))])))
    (car mypair)))
  
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                            
                        
              
    
  
  
  
  
    
         

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;For creating buildings on the left of the anti-missile gun
(for (define i 0) :
  (< i 5) :
  (set! i (+ i 1)) :
  (begin
    (set! active-buildings (cons (new building%
                                      [posx (+ 70 (* i 100))]
                                      [posy 610])
                                 active-buildings))))

;;For creating buildings on the right of the anti-missile gun
(for (define j 0) :
  (< j 5) :
  (set! j (+ j 1)) :
  (begin
    (set! active-buildings (cons (new building%
                                      [posx (+ 790 (* j 100))]
                                      [posy 610])
                                 active-buildings))))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;main loop
(define (main)
  (begin
    (set! time (+ time time-increment))
    (update-missiles active-missiles)
    (update-anti-missiles active-anti-missiles)
    (send gun update)
    (main-logic-function)
    (missile-destroyed-by-anti-missile active-anti-missiles)
    (building-hit-by-missile active-missiles)
    (if (not (all-buildings-destroyed))
        (begin
          (draw bm-dc)
          (sleep/yield 0.01)
          (main))
        "you win")))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(main)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (will-missile-hit-building M)
  (define (helper l x1 x2 x3)
    (cond[(null? l) #f]
         [else
          (let*([a (car l)]
                [b-x1 (get-field posx a)]
                [b-x2 (+ b-x1 (get-field width a))])
            (cond[(and (>= x1 b-x1) (<= x1 b-x2)) #t]
                 [(and (>= x2 b-x1) (<= x2 b-x2)) #t]
                 [(and (>= x3 b-x1) (<= x3 b-x2)) #t]
                 [else (helper (cdr l))]))]))
                 
  (let*([mpos (get-field pos2 M)]
        [m-x (car mpos)]
        [m-y (cdr mpos)]
        [m-vx (get-field ux M)]
        [m-vy (get-field uy M)]
        [b-uy (get-field posy (car active-buildings))]
        [b-ly (+ b-uy (get-field height (car active-buildings)))]
        [b-my (/ (+ b-uy b-ly) 2.0)]
        [t-uy (/ (- b-uy m-y) m-vy)]
        [t-ly (/ (- b-ly m-y) m-vy)]
        [t-my (/ (- b-my m-y) m-vy)]
        [mx-at-t-uy (+ m-x (* m-vx  t-uy))]
        [mx-at-t-my (+ m-x (* m-vx  t-my))]
        [mx-at-t-ly (+ m-x (* m-vx  t-ly))])
    (helper active-buildings mx-at-t-uy mx-at-t-my mx-at-t-ly)))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
