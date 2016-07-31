#lang racket/gui
; Make a frame by instantiating the frame% class
;(define frame (new frame% [label "Example"]))
 
(define frame (new frame%
                   [label "Example"]
                   [width 300]
                   [height 300]))
; Make a static text message in the frame
(define msg (new message% [parent frame]
                          [label "No events so far..."]))
 
; Make a button in the frame
(new button% [parent frame]
             [label "Click Me"]
             ; Callback procedure for a button click:
             [callback (lambda (button event)
                         (send msg set-label "Button click"))])
 
; Show the frame by calling its show method
(send frame show #t)

; Derive a new canvas (a drawing window) class to handle events
(define my-canvas%
  (class canvas% ; The base class is canvas%
    ; Define overriding method to handle mouse events
    (define/override (on-event event)
      (send msg set-label "Canvas mouse"))
    ; Define overriding method to handle keyboard events
    (define/override (on-char event)
      (send msg set-label "Canvas keyboard"))
    ; Call the superclass init, passing on all init args
    (super-new)))
 
 ;Make a canvas that handles events in the frame
(new my-canvas% [parent frame])

(new button% [parent frame]
             [label "Pause"]
             [callback (lambda (button event) (sleep 5))])

(define panel (new horizontal-panel% [parent frame]))
(new button% [parent panel]
             [label "Left"]
             [callback (lambda (button event)
                         (send msg set-label "Left click"))])
(new button% [parent panel]
             [label "Right"]
             [callback (lambda (button event)
                         (send msg set-label "Right click"))])

;(new canvas% [parent frame]
;             [paint-callback
;              (lambda (canvas dc)
;                (send dc set-scale 3 3)
;                (send dc set-text-foreground "blue")
;                (send dc draw-text "Don't Panic!" 0 0))])
;(send frame show #t)

; Create a dialog
(define dialog (instantiate dialog% ("Example1")))
 
; Add a text field to the dialog
(new text-field% [parent dialog] [label "Your name"])
 
; Add a horizontal panel to the dialog, with centering for buttons
(define hpane (new horizontal-pane% [parent dialog]
                                     [alignment '(center center)]))
 
; Add Cancel and Ok buttons to the horizontal panel
(new button% [parent hpane] [label "Cancel"])
(new button% [parent hpane] [label "Ok"])
(when (system-position-ok-before-cancel?)
  (send panel change-children reverse))
 
; Show the dialog
(send dialog show #t)