; code for Missile Command game , written by Sahil , Abhishek and Mridul as part of CS 154 project 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#lang racket/gui  ; we use racket/gui for all the graphics
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;"for" macro is defined here
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
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;; some global variables

(define v 140.0)  ; v is speed of the missile
(define v-anti 140.0)  ; v-anti is speed of the anti-missile
(define rotor-speed 3) ; rotor-speed is speed with which gun can rotate 

; list of missiles which have been launched but have neither been destroyed by any anti missile nor collided with any building. 
(define active-missiles '()) 

(define active-buildings '()) ; list of buildings which have not destroyed as yet.
(define active-anti-missiles `()) ; list of anti missiles which have been launched by the gun but have not yet collided with a missile. 

(define time 0) ; the simulation time , is initially 0
(define time-increment 0.01) ; time by which simulation time is increased in every loop
(define num-missiles 0)  ; number of missiles which have been fired in current game
(define allowed-missiles 80)  ; maximum number of missiles which can be fired in a game

; a variable which we use to store a new missile object created when user selects a missile launch pad.
; by setting it to #f when missile is actually launched (on second mouse click) , we ensure that user has to first select a launch pad 
; before launching a missile.
(define temp #f) 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;missile class is defined here
(define missile%
  (class object%
    (init-field (pos1 #f)) ; pos1 refers to position of launch pad which is selected for launch of this missile
    (init-field (pos2 #f)) ; pos2 refers to the current position of the missile 
    (init-field (launch-time #f)) ; time when missile is actually launched 
    (init-field (theta #f)) ; angle made by missile with horizontal axis
    (init-field (ux #f)) ; velocity of missile in horizontal direction
    (init-field (uy #f)) ; velocity of missile in vertical direction
    (init-field (detected-by-radar #f)) ; #t if missile is in range of the radar , #f o/w
    (init-field (is-anti-missile-attached #f)) ; #t if some anti missile has been launched to destroy this particular missile , #f o/w 
    (super-new)
    (define/public (update-missile-position current-time) ; updates pos2 i.e the current position of the missile
      (let*([ t (- current-time launch-time)]
            [ sx (* ux t)]
            [ sy (* uy t)]
            [ x0 (car pos1)]
            [ y0 (cdr pos1)])
      (set! pos2 (cons (+ x0 sx) (+ y0 sy)))))))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;building class is defined here
; a building is a rectangular object
(define building%
  (class object%
    (super-new)
    ; x and y coordinates of upper left point of the building.
    (init-field (posx #f)) 
    (init-field (posy #f)) 
    (init-field (height 60)) ; height of the building 
    (init-field (width 40)))) ; width of the building.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;anti-missile class is defined here
(define anti-missile%
  (class object%
    (init-field (pos1 #f)) ; pos1 is position of anti missile gun from which it is launched
    (init-field (pos2 #f)) ; pos2 is its current position
    (init-field (theta #f)) ; angle made by anti missile with horizontal axis
    (init-field (ux #f)) ; velocity of anti missile in horizontal direction
    (init-field (uy #f)) ; velocity of anti missile in vertical direction
    (init-field (missile-attached #f)) ; stores the missile object it is seeking to destroy
    (init-field (launch-time #f)) ; time when it is actually launched
    (super-new)
    (define/public (update-anti-missile-position current-time) ; updates pos2  i.e current position
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
    (init-field (posx #f)) ;x coordinate of the gun 
    (init-field (posy #f)) ;y coordinate of the gun 
    (init-field (current-angle #f)) ; angle made by the gun with positive horizontal axis in counter clockwise direction
    (init-field (missile-attached-antigun #f)) ; 
    (init-field (final-angle #f)) ; angle to which it must rotate and then release anti missile to hit a missile
    (init-field (isFree? #f)) ; #t if it is not in process of rotating and launching anti missile , #f o/w
    (init-field (radius 200)) ; radius of the semi circle which represents the gun
    (init-field (speed rotor-speed)) ; speed of change of direction in which it points
    (define/public (update) ; updates the position ( angle ) of the gun if it is busy . If gun is free, this functionn does nothing.
      (cond [(not isFree?)
      	; if current angle is "near" to the final angle, 
      	; we set the current angle to final angle and launch the anti missile . Also ,then we set gun to free state. 
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
                                         [ux (* v-anti (cos current-angle))]
                                         [uy (- (* v-anti (sin current-angle)))]
                                         [missile-attached missile-attached-antigun]
                                         [launch-time time]))))
                     (set! missile-attached-antigun #f))]                                
                 ; if current angle is not near to final angle , we increment current angle.
                  [(< current-angle final-angle) (set! current-angle (+ current-angle (* time-increment speed)))]
                  [(> current-angle final-angle) (set! current-angle (- current-angle (* time-increment speed)))])]))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;define the anti-missile-gun% object here (it is the actual gun) 
(define gun (new anti-missile-gun%
                 [current-angle (/ pi 2)] ; it is initially pointing in vertical direction
                 [posx 650] [posy 670] ; the position of the gun 
                 [isFree? #t])) ; it is free initially , i.e it is not engaged in launching any anti missile 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; this function is used to set the game to initial state . It is used when we want to restart the game or when the user 
; loses or wins the game. 
(define (set-to-initial-state)
  (begin
     (set! num-missiles 0)
     (set! time 0)
     (set! active-missiles '())
     (set! active-anti-missiles '())
     (set-field! current-angle gun (/ pi 2))
     (set-field! final-angle gun #f)
     (set-field! isFree? gun #t)
     (set! active-buildings '())
     (send lost-message show #f)
     (send meter set-value 0)
     (send bm-dc clear)
     (send mycanvas refresh)
     (send frame show #f)
     (send frame2 show #t)
     (start)))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;Graphic portion starts from here


;;The top level container window- consists of the main canvas
(define frame (new frame% [label "Missile Command"] [width 1300] [height 670]))


;;The central canvas window for drawing and handling events.
;;This is the white coloured screen where anti-missiles and missiles are displayed.
;;Essentially, it handles the event of second click by the user, where it sets the 
;;parameters for the new missile generated, adds it to the active missiles list, 
;;and also updates the meter-gauge parameter 
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
                                                (cond [(= (car a) (car b))
                                                       (/ pi 2)] 
                                                      [else  (atan (/ (- (cdr b) (cdr a))
                                                                (- (car b) (car a))))])))
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
                       (send meter set-value num-missiles)
                       (set! num-missiles (+ num-missiles 1))            
                       (set! temp #f))])]))))
          

;;The container panel for number of missiles' gauge
(define panel1 (new horizontal-panel% [parent frame]
                   [alignment (list 'left 'top)]))


;;The container panel for missile-gun buttons
(define panel2 (new horizontal-panel% [parent frame]
                   [alignment (list 'left 'top)]))


;;Object of my-canvas class
(define mycanvas (new my-canvas% [parent frame]
                      [min-height 670]
                      [paint-callback
                     (lambda (canvas dc) (paint dc))]))


;;The container window for main menu
(define frame2 (new frame% [label "Missile Command"] [width 1300] [height 670]))


;;The dialog box that appears when user loses the game
(define lost-message (new dialog%	 
                     [label "Game-Over"]	 
                     [parent frame]	 
                     [width 200]	 
                     [height 50]	 
                     [x 700]	 
                     [y 400]	 
                     [enabled #t]
                     [style (list 'close-button)]))


;;The message that appears in the lost-message dialog box
(define l-message (new message% [parent lost-message]
                     [label "You lost the game!"]))


;;The button "Play Again" that appears in the lost-message dialog box
(define l-button (new button% [parent lost-message]
                     [label "Play Again"]
                     [horiz-margin 10]
                     [callback (lambda (button event)
                                 (set-to-initial-state))]))

;;The dialog box that appears when user wins the game
(define win-message (new dialog%	 
                     [label "Congratulations!"]	 
                     [parent frame]	 
                     [width 200]	 
                     [height 50]	 
                     [x 700]	 
                     [y 400]	 
                     [enabled #t]
                     [style (list 'close-button)]))


;;The message that appears in the win-message dialog box
(define w-message (new message% [parent win-message]
                     [label "You won the game."]))


;;The button "Play Again" that appears in the win-message dialog box
(define w-button (new button% [parent win-message]
                     [label "Play Again"]
                     [horiz-margin 10]
                     [callback (lambda (button event)
                                 (set-to-initial-state))]))


;;The main-menu window is divided into 3 regions -horizontally
;;by following three panels

;;This panel holds the Start button
(define panel3 (new horizontal-panel% [parent frame2]
                   [alignment (list 'center 'center)]))

;;This panel holds the Level-selection choice button
(define panel4 (new horizontal-panel% [parent frame2]
                   [alignment (list 'center 'center)]))

;;This panel holds the Exit button
(define panel5 (new horizontal-panel% [parent frame2]
                   [alignment (list 'center 'center)]))


;;The Start button that appers in the main-menu window
(define start-button (new button% [parent panel3]
                          [label "start"]
                          [horiz-margin 500]
                          [style (list 'border)]
                          [min-width 100]
                          [min-height 50]
                          [callback (lambda (button event)
                                      (begin
                                        (send frame2 show #f)
                                        (send frame show #t)
                                      (main)))]))


;;The user can choose the difficulty level at whcih he wishes to play, through this button.
;;The call-backs for each level sets the different values for anti-missiles velocity and
;;missiles velocity and maximum number of allowed missiles.
(define choice-button (new choice%
                     [parent panel4]
                     [label "level"]
                     [selection 0]
                     [choices (list "default" "easy" "medium" "hard")]
                     [callback (lambda (c e)
                                 (cond[(= 1 (send c get-selection));For Easy level 
                                       (begin                          ; Velocity of missile 150
                                         (set! v 150)                  ; Velocity of anti-missile 100
                                         (set! v-anti 100))]           ; Allowed missiles default value
                                      [(= 2 (send c get-selection));For Medium level 
                                       (begin
                                         (set! v 150)                  ;Velocity of missile 150
                                         (set! v-anti 120)             ;Velocity of anti-missile 120
                                         (set! allowed-missiles 60)    ;allowed-missiles 60
                                         (send meter set-range allowed-missiles))]
                                      [(= 3 (send c get-selection));For Hard level
                                       (begin                           
                                         (set! v 160)                  ;Velocity of missile 160
                                         (set! v-anti 160)             ;Velocity of anti-missile 160
                                         (set! allowed-missiles 80)    ;Allowed missiles 80
                                         (send meter set-range allowed-missiles))]))]))


;;The Start button that appers in the main-menu window
;;Its call-back hides the current frame, so that the main gaming window appears.
(define exit (new button% [parent panel5]
                  [label "Exit"]
                  [callback (lambda (button event)
                              (send frame2 show #f))]))


;;This is a horizontal  bar for displaying the number of missiles consumed. It has 
;;its maximum range -the no. of allowed missiles, and the gauge’s current value is always 
;;between 0 and this allowed value, inclusive.                             
(define meter (new gauge% 
                   [parent panel1]
                   [label "Missiles Used"]
                   [range 10]	 
   	 	[enabled #t]	 
   	 	[horiz-margin 20]))


;;This displays the no. of missiles left for the user alongside the meter(gauge)
(define missile-left (new message% [parent panel1]
                         [label "Missiles left"]))


;;This is the Restart-button in the top panel in the gaming window.
;;Its callback takes us back to main window.
(define restart (new button% [parent panel1]
                     [label "Restart"]
                     [callback (lambda (button event)
                                 (set-to-initial-state))]))


;;Set the maximum range of the meter(gauge) to the no. of allowed missiles
(send meter set-range allowed-missiles)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;Four buttons for firing the missiles, declared left to right
;;Their callback creates an object of class missile and sets the pos1 of this 
;;missile as the positon of the button.

(define button1 (new button% [parent panel2]
                     [label "Missile1"]
                     [horiz-margin 190]
                     [callback (lambda (button event)
                                 (begin
                                   (set! temp (new missile%))
                                   (set-field! pos1 temp (cons 225 0))))]))

(define button2 (new button% [parent panel2]
                     [label "Missile2"]
                     [horiz-margin 10]
                     [callback (lambda (button event)
                                 (begin
                                   (set! temp (new missile%))
                                   (set-field! pos1 temp (cons 490 0))))]))

(define button3 (new button% [parent panel2]
                     [label "Missile3"]
                     [horiz-margin 190]
                     [callback (lambda (button event)
                                 (begin
                                   (set! temp (new missile%))
                                   (set-field! pos1 temp (cons 760 0))))]))

(define button4 (new button% [parent panel2]
                     [label "Missile4"]
                     [horiz-margin 10]
                     [callback (lambda (button event)
                                 (begin
                                   (set! temp (new missile%))
                                   (set-field! pos1 temp (cons 1025 0))))]))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; brushes and pens

;;A pen is a drawing tool with a color, width, and style. 
;;A pen draws lines and outlines, such as the outline of a rectangle
(define black-pen (make-object pen% "BLACK" 5 'solid))
(define b-pen (make-object pen% "BLACK" 1 'solid))

;;A brush is a drawing tool with a color and a style that is used for filling 
;;in areas, such as the interior of a rectangle or ellipse. 
(define blue-brush (make-object brush% "BLUE" 'solid))
(define green-brush (make-object brush% "GREEN" 'solid))
(define red-brush (make-object brush% "RED" 'solid))


(define (paint dc) (send dc draw-bitmap face-bitmap 0 0))
(define face-bitmap (make-object bitmap% 1500 1500))


; Create a drawing context for the bitmap
(define bm-dc (make-object bitmap-dc% face-bitmap))
(send bm-dc clear)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;The Main Drawing Routine

(define (draw dc)

  ;Set the Brush, Pen. Refresh the canvas.
  (send mycanvas refresh)
  (send dc clear)
  (send dc set-pen black-pen)
  (send dc set-brush red-brush)

  ;Set the no. of missiles left to be displayed alongside the meter.
  (send missile-left set-label (~a (- allowed-missiles num-missiles)))

  ;;Draw each building from the list of active-buildings using a map
  (map (lambda (a) (let([x (get-field posx a)]
                        [y (get-field posy a)]
                        [sizex (get-field width a)]
                        [sizey (get-field height a)])
                     (send dc draw-rectangle x y sizex sizey))) active-buildings)

  ;;Draw each missile from the list of active-missile using a map
  (send dc set-brush blue-brush)
  (map (lambda (a) (let([x (car (get-field pos2 a))]
                        [y (cdr (get-field pos2 a))])
                     (send dc draw-rectangle x y 20 20))) active-missiles)

  ;;Draw each anti-missile from the list of active-anti-missiles using a map
  (send dc set-brush green-brush)
  (map (lambda (a) (let([x (car (get-field pos2 a))]
                        [y (cdr (get-field pos2 a))])
                     (send dc draw-rectangle x y 20 20))) active-anti-missiles)

  ;;Draw the anti-missile gun - half circle using draw-arc method
  (send dc set-pen b-pen)
  (let([x (-(get-field posx gun) 50)]
       [y (-(get-field posy gun) 50)]
       [rad (/(get-field radius gun) 2)])
    (send dc draw-arc x y rad rad 0 pi))

  ;;Draw the anti-missile gun's pointer using draw-line method
  (send dc set-pen black-pen)
  (let* ([x1 (get-field posx gun)]
         [y1 (get-field posy gun)]
         [length (+ (/ (get-field radius gun) 4) 20)]
         [angle (get-field current-angle gun)]
         [x2 (+ x1 (* length (cos angle)))]
         [y2 (- y1 (* length (sin angle)))])
    (send dc draw-line x1 y1 x2 y2))

  ;; Draw the radars
  (send dc set-pen b-pen)
  (define a1 0)
  (define a2 670)
  (for (define phi (/ pi 2)):
    (>= phi 0):
    (set! phi (- phi 0.05)):
    (begin
      (send dc draw-ellipse (- 1300 (* 450 (cos phi)))
            (- 670 (* 450 (sin phi))) 5 5)
      (send dc draw-ellipse (* 450 (cos phi))
            (- 670 (* 450 (sin phi))) 5 5)))
  (for (set! phi pi):
    (>= phi 0):
    (set! phi (- phi 0.05)):
    (begin
      (send dc draw-ellipse (+ 650 (* 450 (cos phi)))
            (- 670 (* 450 (sin phi))) 5 5))))

;;Graphic portion ends here
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;Functions used are defined here

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Arguments
;    Predicate p
;    List l
; this function returns the elements of the list till the point the predicate is not satisfied by the element of the list
;for the first time
;It is used in the delete function 
(define (takewhile p l)
  (foldr (lambda( x t) (if (p x) (cons x t) `()))  `() l))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Arguments
;    Predicate p
;    List l
;Helper function for the dropwhile function
(define (dropwhile-h p l)
  (foldr (lambda (x y) 
           (if  (p x)
                (cons (car y) (cons x (cdr y)))
                (cons (cons x (cdr y)) (cons x (cdr y)))))
         (cons '(1) '());We are returning a list of 1 element in the base case because we are using cdr dropwhile in
         l))            ;(delete x l), so this is to prevent errors

;Arguments
;    Predicate p
;    List l
;used to return the list from the point where the predicate is false (for that element) for the first time
(define (dropwhile p l)
  (car (dropwhile-h p l)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Arguments
;    Element x
;    List l
;Returns the list with the element x removed
;Used in many functions like missile destroyed etc. to remove the elements from the active objects list
(define (delete x l)
  (cond [(null? l) (error "trying to delete elt from null list")]
        [ else 
          (append (takewhile (lambda(y) (not (eq? y x))) l)
                  (cdr (dropwhile (lambda(y) (not (eq? y x))) l)))]))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Argument
;    List missile-list
;Updates the missile-list, if any missile goes out of scope then it is removed from the active-missile list
(define (update-missiles missile-list)
  (define delete-missiles `())
  (begin 
    (map (lambda (x) 
           (begin 
             (send x update-missile-position time)
             (let* ([ mpos (get-field pos2 x)]
                    [ mx (car mpos)]
                    [ my (cdr mpos)])
               (cond [(or ( > mx 1300) (< mx 0) (> my 670)) 
                      (set! delete-missiles (cons x delete-missiles))]))))
              missile-list)
    (map (lambda(x) (set! missile-list (delete x missile-list))) delete-missiles)))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Argument
;    List anti-missile-list
;Updates the anti-missile-list, if any anti-missile goes out of scope it is removed from the active-anti-missile list
(define (update-anti-missiles anti-missile-list)
   (define delete-anti-missiles `())
  (begin 
    (map (lambda (x) 
           (begin 
             (send x update-anti-missile-position time)
             (let* ([ mpos (get-field pos2 x)]
                    [ mx (car mpos)]
                    [ my (cdr mpos)])
               (cond [(or ( > mx 1300) (< mx 0) (< my 0)) 
                      (set! delete-anti-missiles (cons x delete-anti-missiles))]))))
              anti-missile-list)
    (map (lambda(x) (set! anti-missile-list (delete x anti-missile-list))) delete-anti-missiles)))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Arguments
;    List l (l is the active-anti-missiles list)
;checks whether any missile is destroyed by the anti-missile-associated with it or not, if strikes at this moment
;(i.e  when distance between them is less than 5) then the missile is deleted from the active-missiles list and 
;the anti-missiles is deleted from the active-anti-missiles list
(define (missile-destroyed-by-anti-missile l) 
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

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;returns true if all the buildings are destroyed
(define (all-buildings-destroyed) (null? active-buildings))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Arguments
;    Missile-object missile
;    building-object building
;returns true if the missile is near the building otherwise false
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
;Argument
;    List l (l is the active-missiles list)
;checks for each missile whether it has hit a building or not
;if any missile hits a building then the missile is deleted from the active-missile list and the building is destroyed from
; active-building list
(define (building-hit-by-missile l)  
  (define missiles-deleted `())
  (define buildings-deleted `())
  (define (helper x)
     (for (define i active-buildings) : 
                    (not (null? i)) : 
                    (set! i (cdr i)) : 
                    (begin
                      (define j (car i))
                      (cond [(missile-near-building x j) 
                             (set! missiles-deleted (cons x missiles-deleted))
                             (set! buildings-deleted (cons j buildings-deleted))
                             (set! i `(1))]))))
  
  (begin
    (map (lambda (x) (helper x)) l)
    (map (lambda(x) (set!  active-missiles (delete x active-missiles))) missiles-deleted)
    (map (lambda(x) (set! active-buildings (delete x active-buildings))) buildings-deleted)))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Arguments
; point p1 
; point p2
;(point is basically a cons object, the fist element is the x-coordinate and the second element is the y-coordinate
; returns the distance between two points
(define (distance-between-points p1 p2)
  (sqrt (+ (expt (- (car p1) (car p2)) 2)
           (expt (- (cdr p1) (cdr p2)) 2))))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Arguments
; Missile-object m
; Returns true if the missile is in the scope of the radar otherwise false
(define (is-missile-in-radar-scope m)
  (let* ([ pos (get-field pos2 m)]
         [ pt1 (cons 0 670)]
         [ pt2 (cons 1300 670)]
         [ pt3 (cons 650 670)]
         [ dist 450])
    (or (<= (distance-between-points pos pt1) dist)
        (<= (distance-between-points pos pt2) dist)
        (<= (distance-between-points pos pt3) dist))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Arguments
;    Missile-object M
; checks whether missile is going to hit any building or not
; if it will hit any building then returns true otherwise false
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
                 [else (helper (cdr l) x1 x2 x3)]))]))
                 
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
;This is the main logic function
;it checks for each missile whether it is in radar scope or not, whether an anti-missile has been attached to it or not,
;whether the gun is free or not and whether the missile is going to hit the building
;If the missile is going to hit the building and no anti-missile has been attached to it and the anti-missile-gun is free
;and the missile is in radar scope then it will attach an ant-missile to it
;This process will be done for all the missiles in the active-missiles list
(define (main-logic-function)
  (map (lambda(x) (cond [ (and (not (get-field is-anti-missile-attached x))
                               (is-missile-in-radar-scope x)
                               (get-field isFree? gun)
                               (will-missile-hit-building x))
                          (associate-anti-missile x)]))
       active-missiles))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Argument
;    Missile-object m
;associates an anti-missile to the missile
;sets the required parameters of the anti-missile and the missile

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
             (set-field! final-angle gun fin-angle)
             (set-field! missile-attached-antigun gun m)
             (set-field! is-anti-missile-attached m #t)
             (set-field! isFree? gun #f))))))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Arguments
;    xm - this is the x-coordinate of the current position of the missile
;    ym - this is the y-coordinate of the current position of the missile
;    ux - this is the x-coordinate of the current position of the anti-missile-gun 
;    uy - this is the y-coordinate of the current position of the anti-missile-gun
;    current-angle  - this is the curent angle of the anti-missile-gun
;    speed - this is the rotating speed of the anti-gun
;We get 3 equations in 3 variables and we need to solve them in order to get the answer
;We solve this by taking all the values of phi in 0 to pi, where the step size is pi/180, i.e. we take 180 values of phi 
;in the range 0 to pi, solve for these values and get the time for each phi and take the minimum time as our final answer 
;and all parameters are taken for that value of time
(define (solve xm ym ux uy x0 y0 current-angle speed)
  (define mypair (cons #f #f))
  (begin 
    (for (define phi 0) :
      (<= phi pi) :
      (set! phi (+ phi (/ pi 180))) :
      (begin 
        (define t1  ( + time (/ (abs (- current-angle phi)) speed)))
        (cond [ (not (= 0 (- ux (* v-anti (cos phi))))) 
                (let* ([ tx (/ (+ x0 (* ux time) (* -1 xm) (* -1 t1 (cos phi) v-anti))   
                               (- ux (* v-anti (cos phi))))]
                       [ ty (/ (+ y0 (* v-anti (sin phi) t1) (* uy time) (* -1 ym))
                               (+ uy (* v-anti (sin phi))))])
                  (cond [ (> 0.01 (abs (- tx ty)))  
                          (cond [ (and (car mypair) (< tx (cdr mypair)) (> tx time)) 
                                  (set! mypair (cons phi tx))]
                                [ (not (car mypair)) (set! mypair (cons phi tx))])]))])))
    (car mypair)))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Buildings are created using the for loop 
;;For creating buildings on the left of the anti-missile gun

(define (create-building)
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
                                   active-buildings)))))
  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;main loop function
; It will first check whether the no of missiles has exceeded the allowed limit, if yes then a dialog box will open showing
; that you have lost the game
;If not, then it first increments the time, updates the missile and anti-missile positions, updates the anti-gun and then 
;calls the main-logic-function which will associate anti-missile to missiles,
;It then calls missile-destroyed-by-anti-missile function to check if ,missiles are destroyed from the anti-missiles,
;If yes then those missiles and anti-missiles are deleted from the active-lists
;If then checks whether building are destoyed by missile or not
;Finally it checks whether there is an active building remaining or not, if yes then the game continues otherwise the 
;user wins the game

(define (main)
  (if (> num-missiles allowed-missiles)
      (send lost-message show #t)
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
        (begin 
          (draw bm-dc)
          (send win-message show #t))))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;This is the start function, it will show a frame which has options for setting levels etc., when a level is selected 
; then data has been set according to that level and when start button is pressed, then this frame disappears and the 
; main function is called which will start the game
(define (start)
  (send bm-dc clear)
  (create-building)
  (send mycanvas refresh))
(start)

(send frame2 show #t)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
